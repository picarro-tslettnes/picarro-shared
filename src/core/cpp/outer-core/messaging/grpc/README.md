C++ gRPC service utilities
==========================

This contains custom additions to [gRPC](https://grpc.io/).

All of these modules are implemented in the `picarro::grpc::` namespace.

Directories
-----------
 * `common` - service settings (incl. port lookup), status ...
 * `client` - client-side wrappers, including `Picarro.Service.Signal()` reader
 * `server` - server-side handlers, including `Picarro.Service.Signal()` streamer
