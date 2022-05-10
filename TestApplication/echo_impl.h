#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_context.h>

#include <echo.grpc.pb.h>

class EchoImpl final : public echo::Echo::Service {
  public:

	  grpc::Status EchoMessage(
		  grpc::ServerContext* context, 
		  const echo::Message* recvMessage, 
		  echo::Message* rtnMessage) override;
};