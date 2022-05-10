# bufaflo

Still in development.

bufaflo is a protoc plugin that will generate a test driver from a protobuf proto file that can be used with AFL to fuzz the 
underlying server code.

The Test Application uses gRPC, which it builds from source.  Therefore, it requires the tools needed to build gRPC.
https://github.com/grpc/grpc/blob/master/BUILDING.md#windows

