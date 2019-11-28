/*
 * main.cpp
 * Copyright (C) 2019 flo <flo@knightknight>
 *
 * Distributed under terms of the MIT license.
 */

#include "../generated/dummy.grpc.pb.h"
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/client_context.h>

#include <thread>

int main()
{
  auto channel = grpc::CreateChannel("localhost:50051",
      grpc::InsecureChannelCredentials());
  auto stub = Mq::NewStub(channel);
  for(;;)
  {
    {
      grpc::ClientContext context;
      StartQ startq;
      StartR startr;
      grpc::Status status = stub->Start(&context, startq, &startr);
      if (!status.ok())
      {
        std::cerr << "Start error:" << status.error_message() << std::endl;
      }
      std::cout << "Start succeeded" << std::endl;
    }
    {
      grpc::ClientContext context;
      StopQ stopq;
      StopR stopr;
      grpc::Status status = stub->Stop(&context, stopq, &stopr);
      if (!status.ok())
      {
        std::cerr << "Stop error:" << status.error_message() << std::endl;
      }
      std::cout << "Stop succeeded" << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}
