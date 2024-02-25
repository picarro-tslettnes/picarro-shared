#!/bin/echo Do not invoke directly.
#===============================================================================
## @file signals.py
## @brief Local signal store for DEMO application
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Modules relative to install dir
from picarro.io.protobuf.signalstore import SignalStore
from .types import Picarro

#===============================================================================
# Signal store to propagate `greeting` and `time` signals for application.

demo_signals = SignalStore(use_cache=True, signal_type = Picarro.Demo.Signal)
