#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>

#include <echo.grpc.pb.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using echo::Echo;
using echo::Message;

class EchoClient {
  public:
      EchoClient(std::shared_ptr<Channel> channel)
          : stub_(Echo::NewStub(channel)) {
      }

      void EchoMessage() {
          Message sendMessage;
          Message recvMessage;
          ClientContext context;

          std::string message = "Hello Hello All";

          sendMessage.set_message(message);
          // Incorrect conversion of size_t to signed int
          sendMessage.set_length(message.size());

          Status status = stub_->EchoMessage(&context, sendMessage, &recvMessage);
          if (!status.ok()) {
              std::cout << "GetFeature rpc failed." << std::endl;
              return;
          }

          std::cout << "Message from server: " << recvMessage.message() << std::endl;
      }
  private:
      std::unique_ptr<Echo::Stub> stub_;
};

int main(int argc, char** argv) {

    EchoClient client(
        grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials())
    );

    std::cout << "----------------------- EchoMessage -----------------------" << std::endl;
    client.EchoMessage();
    
    return 0;
}