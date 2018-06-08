#pragma once

#include "ServiceLayerRoute.h"
#include "ServiceLayerException.h"
#include <arpa/inet.h>
#include <google/protobuf/text_format.h>
#include <csignal>

using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::CompletionQueue;
using grpc::Status;
using service_layer::SLInitMsg;
using service_layer::SLVersion;
using service_layer::SLGlobal;


namespace iosxr {

using AddrFamily = std::map<std::string, const int>;
using RouteBatch = std::vector<std::map<std::string, std::string>>;
using VrfBatch = std::map<std::string, RouteBatch>;

extern RouteBatch routeBatch;

class TelemetryAction {
public:
    explicit TelemetryAction(std::shared_ptr<grpc::Channel> Channel);
    ~TelemetryAction();

    std::unique_ptr<IosxrslRoute> iosxrsl_route_;

    // Set VRF context for V4 routes
    void setIosxrslRouteVrfV4(std::string vrfName);
    // Set VRF context for V6 routes
    void setIosxrslRouteVrfV6(std::string vrfName);

    // Set VRF context for V4 and V6 routes
    void setIosxrslRouteVrf(std::string vrfName);



    void IosxrslRoutePlay(std::string vrf,
                          RouteBatch route_batch,
                          service_layer::SLObjectOp routeOp); 

};

}
