#!/usr/bin/python3 -i
#===============================================================================
## @file shell.py
## @brief Interactive service control, shared components loaded
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Make the contents of Python client modules available in namespaces roughly
### corresponding to the package names of the corresponding `.proto` files

from picarro.io.protobuf     import Picarro, ProtoBuf
from picarro.messaging.grpc.client  import ArgParser as _ArgParser

import logging

### Add a few arguments to the base argparser
class ArgParser (_ArgParser):
    def __init__ (self, host=None, identity="DemoShell", *args, **kwargs):
        super().__init__(host, *args, **kwargs);

        self.add_argument('--debug',
                          default=False,
                          action='store_const',
                          const=True,
                          help='Print debug messages')


def legend ():
    '''
    Interactive Python shell with Picarro types preloaded:

        ProtoBuf - Google-provided ProtoBuf types, e.g. `ProtoBuf.Empty`
        Picarro       - Picarro types, e.g. `Picarro.Variant.Value'

    To import modules, use their paths relative to `share/python`, e.g.:

        >>> import demo.grpc.client
        >>> demo_client = demo.grpc.client.Client('localhost')

    '''
    print(legend.__doc__)

if __name__ == "__main__":
    args   = ArgParser().parse_args()

    logger = logging.getLogger()
    logger.setLevel((logging.INFO, logging.DEBUG)[args.debug])

    legend()
