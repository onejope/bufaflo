#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include <echo.grpc.pb.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using echo::Echo;
using echo::Message;

class EchoImpl final : public Echo::Service {
  public:

	Status EchoMessage(ServerContext* context, const Message* recvMessage, Message* rtnMessage) override {
		std::cout << "Received message: " << recvMessage->message() << std::endl;

		// Buffer Overflow on purpose here. Fuzzer should be able to find this.
		char buffer[128];
		memcpy(buffer, recvMessage->message().c_str(), recvMessage->length());

		rtnMessage->set_message(recvMessage->message());
		rtnMessage->set_length(recvMessage->length());
		return Status::OK;
	}
};

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