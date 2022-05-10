#include <echo.pb.h>

#include <iostream>
#include <fstream>
#include <grpcpp/server_context.h>

#include "echo_impl.h"

extern "C" __declspec(dllexport) int main(int argc, const char* argv[]);

using namespace std;

int main(int argc, const char* argv[]) {
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	if (argc < 2) {
		printf("Usage: %s <protobuf file>\n", argv[0]);
		return 0;
	}

	ifstream inFile;
	inFile.open(argv[1], ios::binary | ios::in);

	EchoImpl service;
	grpc::ServerContext context;

	echo::Message output;
	echo::Message input;
	input.ParseFromIstream(&inFile);
	service.EchoMessage(&context, &input, &output);

	inFile.close();

	return 0;
}