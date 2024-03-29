#!/usr/bin/python3
#===============================================================================
## @file demo-grpc-server.py
## @brief Python flavor of 'Demo' gRPC server
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Modules relative to install dir
from demo.grpc.service import DemoService
from demo.native import NativeDemo
from picarro.messaging.grpc.server import create_async_server

### Standard Python modules
import logging
import asyncio

async def main():
    logger = logging.getLogger()
    logger.setLevel(logging.INFO)

    service = DemoService(NativeDemo())
    server = create_async_server(service)

    try:
        logging.info("Starting Python gRPC Demo Server")
        await server.start()
        await server.wait_for_termination()
    except KeyboardInterrupt:
        pass
    finally:
        logging.info("Shutting down Python gRPC Demo Server")
        await server.stop(5)

if __name__ == '__main__':
    asyncio.run(main())
