# bufaflo

Still in development.

bufaflo is a protoc plugin that will generate a test driver from a protobuf proto file that can be used with AFL to fuzz the 
underlying server code.

Currently, the bufaflo plugin generates a test driver that can be used with WinAFL: https://github.com/googleprojectzero/winafl

To use the plugin, an example protoc command can be seen in the cmake file for the Test Application: https://github.com/onejope/bufaflo/blob/main/TestApplication/CMakeLists.txt

The Test Application uses gRPC, which it builds from source.  Therefore, it requires the tools needed to build gRPC.
https://github.com/grpc/grpc/blob/master/BUILDING.md#windows

Example of a winafl command using a bufaflo generated test driver:
``afl-fuzz.exe -i afl_in -o afl_out -D DynamoRIO\bin64 -t 20000 -w build64\bin\Release\winafl.dll -- -coverage_module echo_bufaflo.exe -target_module echo_bufaflo.exe -target_method main -nargs 2 -- echo_bufaflo.exe Echo.EchoMessage @@``
