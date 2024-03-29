#!/usr/bin/echo Do not invoke directly.
#===============================================================================
## @file signalstore.py
## @brief Mix-in base to handle ProtoBuf signal messages
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Modules relative to install folder
from picarro.io.protobuf import Picarro, ProtoBuf
from picarro.core.scalar_types import enums
from picarro.core.invocation   import safe_invoke

### Standard Pyton modules
from typing import Optional, Callable, Mapping
import threading
import asyncio

#===============================================================================
# Enumerated values

MappingChange = enums(Picarro.Signal.MappingChange, globals())


#===============================================================================
# Annotation types

SignalSlot  = Callable[[ProtoBuf.Message], None]


#===============================================================================
# SignalStore class

class SignalStore (ProtoBuf):
    ## `signal_type` should be set in the final subclass, and is used to decode
    ##  ProtoBuf messages streamed back from the server's `watch()` method.
    signal_type = None

    def __init__(self,
                 use_cache          : bool = False,
                 completion_timeout : float = 3.0,
                 signal_type        : ProtoBuf.MessageType = None):

        if signal_type:
            self.signal_type = signal_type

        self.init_signals(use_cache, completion_timeout)

    def init_signals(self,
                     use_cache: bool,
                     completion_timeout : float):

        assert self.signal_type,\
            ("%s instance must define `signal_type`, either by "
             "declaring a static member or passing it as argument "
             "to SignalSubscriber.__init__()"%(type(self).__name__,))

        assert isinstance(self.signal_type, type) and \
            issubclass(self.signal_type, ProtoBuf.Message), \
            'Signal type must be derived from google.protobuf.Message, ' \
            'not %s'%(self.signal_type,)

        self.slots                = {}
        self._completion_event    = threading.Event()
        self._completion_mutex    = threading.Lock()
        self._completion_timeout  = completion_timeout
        self._completion_deadline = None
        self._deadline_expired    = False

        if use_cache:
            self._cache = {}
        else:
            self._cache = None


    def descriptor(self):
        return self.signal_type.DESCRIPTOR

    def field_name(self, fieldnumber: int) -> str:
        '''
        Obtain the signal name associated with the specified field number.

        @return
            Number associated with the field name of the Signal message.

        @exception KeyError
            The specified field number does not exist
        '''
        try:
            return self.descriptor().fields_by_number[fieldnumber].name
        except KeyError:
            return None

    def field_number(self, fieldname: str) -> int:
        '''
        Return the field number associated with the specified signal name.

        @return
            Number associated with the field name of the Signal message.

        @exception KeyError
            The speicfied field does not exist.
        '''

        return self.descriptor().fields_by_name[signalname].number

    def signal_fields(self) -> dict:
        '''Return a dictionary of signal names to corresponding field numbers
        within the protobuf Signal message'''

        items = [(f.name, f.number)
                 for f in self.descriptor().oneofs[0].fields]

        return dict(items)

    def signal_names(self) -> list:
        '''
        Return a list of signal/slot names in the protobuf Signal message
        for this service.
        '''
        return [f.name for f in self.descriptor().oneofs[0].fields]

    def signal_name(self, msg):
        selector = msg.DESCRIPTOR.oneofs[0].name
        return msg.WhichOneof(selector) or ""



    def get_cached(self,
                   signalname: str,
                   timeout: float=3) -> Mapping[str, ProtoBuf.Message]:
        '''Get a specific signal map from the local cache.

        @param[in] signalname
            Signal name, corresponding to a field of the Signal message
            streamed from the server's `watch()` method.

        @param[in] timeout
            If the specified signal does not yet exist in the local cache, allow
            up to the specified timeout for it to be received from the server.
            Mainly applicable immediately after `start_watching()`, before the
            server cache has been received.

        @exception KeyError
            The specified `signalname` is not known

        @return
            The cached value, or None if the specified signal has yet not been
            received.
        '''

        if self._cache is None:
            raise RuntimeError("Signal cache is not enabled in %s instance"%
                               (type(self).__name__,))

        elif signalname in self.signal_fields():
            self.wait_complete()
            return self._cache.get(signalname, {})

        else:
            return self._cache[signalname]

    def connect_all(self,
                    slot: SignalSlot):
        '''
        Connect a handler to _all_ signals in this store.
        '''

        self.slots.setdefault(None, []).append(slot)
        for name in self.signal_names():
            self.emit_cached_to(name, slot)


    def disconnect_all(self,
                       slot: SignalSlot):
        '''
        Disconnect handlers that are connected to _all_ signals.
        '''

        self.disconnect_signal(None, slot)

    def connect_signal(self,
                       name: str,
                       slot: SignalSlot):

        '''Connect a callback handler (slot) to receive emitted Signal messages.

        @param[in] name
            Signal name, corresponding to a field of the Signal message.

        @param[in] slot
            A callable handler (e.g. a function) that accepts the Signal
            instance as its first and only required argument.

        This variant is mainly suitable for mapping signals, since the entire
        Signal message including the mapping `change` and `key` fields are
        passed on to the receiver.  For simple signals where these fields are
        unused, consider instead `connect_signal_data()` which passes on just
        the extracted payload from the named signal.

        '''

        assert callable(slot), \
            "Slot must be a callable object, like a function"

        assert name in self.signal_names(), \
            "Message type %s does not have a %r field"%(self.signal_type.__name__, name)

        self.slots.setdefault(name, []).append(slot)
        self.emit_cached_to(name, slot)


    def disconnect_signal(self,
                          name: str,
                          slot: Optional[SignalSlot] = None):
        '''Disconnect a simple handler from the specified signal.

        @param[in] name
           Signal name

        @param[in] slot
           Signal handler. If not provided, remove all handlers from the
           specified signal slot.

        Returns True if the handler was found and removed; False otherwise.
        '''

        if slot:
            try:
                slots = self.slots[name]
                slots.remove(slot)
            except KeyError:
                return False
            except ValueError:
                if not slots:
                    self.slots.pop(name, None)
                return True
        else:
            return bool(self.slots.pop(name, None))


    def connect_signal_data(self,
                            name: str,
                            slot: SignalSlot):

        '''.

        Connect a callback handler (slot) to a receive just the extracted
        payload from emitted signals.  This is mainly suitable for simple
        (event) signals rather than mapping signals (where the receiver also
        needs the mapping `change` and `key` fields from the original `Signal`
        container).

        @param[in] name
            Signal name, corresponding to a field of the Signal message.

        @param[in] slot
            A callable handler (e.g. a function) that accepts the
            extracted signal data as its first and only required argument.

        '''

        self.connect_signal(name,
                            lambda signal: slot(getattr(signal, name)))



    def disconnect_signal_data(self,
                               name: str,
                               slot: Optional[SignalSlot] = None):
        '''Disconnect a callback handler (slot) from a specific simple signal.

        @param[in] name
            Signal name, corresponding to a field of the Signal message.

        @param[in] slot
            A callable handler (e.g. a function) that accepts the
            extracted signal data as its first and only required argument.
        '''

        if slot:
            _slot = (lambda signal: slot(getattr(signal, name)))
        else:
            _slot = None

        self.disconnect_signal(name, _slot)


    def wait_complete(self) -> bool:
        '''
        Wait for all currently mapping signals to be received from the server.
        May be invoked after first connectint to ensure the local cache is
        complete before proceeding.

        Note that it is not usually necessary to invoke this method in order to
        obtain values from the local cache, because the `get_cached()` method
        implicitly waits for the specified signal map to be completed before
        proceeding.
        '''
        if self._completion_deadline and not self._deadline_expired:
            remaining = self._completion_deadline - time.time()
            if remaining > 0:
                self._deadline_expired = not self._completion_event.wait(remaining)

        return self._completion_event.is_set()


    def emit_cached_to(self, name, slot):
        if self._cache:
            mapped = False
            for key, signal in self.get_cached(name).items():
                self._emit_to(name, slot, signal)
                mapped = bool(key)

            ## Once the cache is exhausted, emit an empty signal
            ## to indicate that intialization is complete.
            if mapped:
                self._emit_to(name, slot, self.signal_type())


    def emit(self, msg):
        try:
            change = MappingChange[msg.change]
        except IndexError:
            change = msg.change

        name = self.signal_name(msg)

        if name:
            if isinstance(self._cache, dict):
                self._update_cache(name, change, msg.key, msg)

            ## Invoke each slot that was connected to this signal by name
            for callback in self.slots.get(name, []):
                self._emit_to(name, callback, msg)

            ## Invoke each slot that was connected to `all` signals
            for callback in self.slots.get(None, []):
                self._emit_to(name, callback, msg)


        if change == Picarro.Signal.MAP_NONE:
            self._completion_event.set()

    def emit_event(self,
                   signal_name : str,
                   value       : ProtoBuf.Message):

        signal = self.signal_type(**{signal_name:value})
        self.emit(signal)

    def emit_mapping(self,
                     signal_name : str,
                     change      : MappingChange,
                     key         : str,
                     value       : ProtoBuf.Message):

        if key and not change:
            if value.ByteSize() == 0:
                change = Picarro.Signal.MAP_REMOVAL
            else:
                try:
                    self.get_cached(signal_name, {})[key]
                except KeyError:
                    change = Picarro.Signal.MAP_ADDITION
                else:
                    change = Picarro.Signal.MAP_UPDATE

        signal = self.signal_type(change=change, key=key, **{signal_name:value})
        self.emit(signal)


    def _update_cache(self, signalname, change, key, data):
        datamap = self._cache.setdefault(signalname, {})
        if change in (Picarro.Signal.MAP_ADDITION, Picarro.Signal.MAP_UPDATE):
            datamap[key] = data
        elif change == Picarro.Signal.MAP_REMOVAL:
            datamap.pop(key, None)

    def _emit_to(self, name, slot, signal):
        result = safe_invoke(slot,
                             (signal,),
                             {},
                             "Signal %s slot %s(%s, %r, ...)"%(
                                 name,
                                 slot.__name__,
                                 MappingChange.get(signal.change, signal.change),
                                 signal.key))
        if asyncio.iscoroutine(result):
            asyncio.create_task(result)

