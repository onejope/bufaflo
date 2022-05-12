# bufaflo

Still in development.

bufaflo is a protoc plugin that will generate a test driver from a protobuf proto file that can be used with AFL to fuzz the 
underlying server code.

Currently, the bufaflo plugin generates a test driver that can be used with WinAFL: https://github.com/googleprojectzero/winafl

To use the plugin, an example protoc command can be seen in the cmake file for the Test Application: https://github.com/onejope/bufaflo/blob/main/TestApplication/CMakeLists.txt

The Test Application uses gRPC, which it builds from source.  Therefore, it requires the tools needed to build gRPC.
https://github.com/grpc/grpc/blob/master/BUILDING.md#windows

