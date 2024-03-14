#!/usr/bin/python3
#===============================================================================
## @file demo-grpc-server.py
## @brief Python flavor of 'Demo' gRPC server
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Modules relative to install dir
from demo.grpc.service import DemoService
from demo.native import NativeDemo
from picarro.messaging.grpc.server import create_server

### Standard Python modules
import logging

if __name__ == '__main__':
    logger = logging.getLogger()
    logger.setLevel(logging.INFO)

    demoservice = DemoService(NativeDemo())
    demoserver = create_server(demoservice)
    logging.info("Starting Python gRPC Demo Server")
    try:
        demoserver.start()
        demoserver.wait_for_termination()
    except KeyboardInterrupt:
        pass
    finally:
        logging.info("Shutting down Python gRPC Demo Server")
        demoserver.stop(5)
