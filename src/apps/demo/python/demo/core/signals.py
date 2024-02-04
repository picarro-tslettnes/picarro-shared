#!/bin/echo Do not invoke directly.
#===============================================================================
## @file demo.py
## @brief Demo - native Python implementation
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Modules relative to install dir
from ipc.base.signalstore import SignalStore
from .types import Picarro

#===============================================================================
# Signal store to propagate `greeting` and `time` signals for application.

demo_signals = SignalStore(use_cache=True, signal_type = Picarro.Demo.Signal)
