#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

#include "echo_impl.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::Status;

void RunServer() {
	std::string server_address("0.0.0.0:50051");
	EchoImpl service;

	ServerBuilder builder;
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);
	std::unique_ptr<Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << server_address << std::endl;
	server->Wait();
}

int main(int argc, char** argv)
{
	RunServer();
	return 0;
}