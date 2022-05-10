#include <grpc/grpc.h>
#include <grpcpp/server_context.h>

#include <echo.grpc.pb.h>

#include "echo_impl.h"

using grpc::ServerContext;
using grpc::Status;

using echo::Echo;
using echo::Message;

Status EchoImpl::EchoMessage(ServerContext* context, const Message* recvMessage, Message* rtnMessage) {
	std::cout << "Received message: " << recvMessage->message() << std::endl;

	// Buffer Overflow on purpose here. Fuzzer should be able to find this.
	char buffer[128];
	memcpy(buffer, recvMessage->message().c_str(), recvMessage->length());

	rtnMessage->set_message(recvMessage->message());
	rtnMessage->set_length(recvMessage->length());
	return Status::OK;
}