#include "IosxrTelemetryAction.h"
#include <string>


namespace iosxr {


namespace {

    AddrFamily addrFamily = { 
                               { "IPv4" , AF_INET},
                               { "IPv6" , AF_INET6}
                             };
  
    RouteBatch routeBatch = {
                              {
                                  {"address_family", "IPv4"},
                                  {"prefix", "30.1.1.0"},
                                  {"prefixlen", "24"},
                                  {"admin_distance", "120"},
                                  {"nexthop_address", "11.1.1.20"},
                                  {"nexthop_interface", "GigabitEthernet0/0/0/0"},
                              },

                              {   
                                  {"address_family", "IPv4"},
                                  {"prefix", "40.1.1.0"},
                                  {"prefixlen", "24"}, 
                                  {"admin_distance", "120"},
                                  {"nexthop_address", "11.1.1.20"},
                                  {"nexthop_interface", "GigabitEthernet0/0/0/0"},
                              },


                              {   
                                  {"address_family", "IPv4"},
                                  {"prefix", "50.1.1.0"},
                                  {"prefixlen", "24"}, 
                                  {"admin_distance", "120"},
                                  {"nexthop_address", "11.1.1.20"},
                                  {"nexthop_interface", "GigabitEthernet0/0/0/0"},
                              },


                              {   
                                  {"address_family", "IPv4"},
                                  {"prefix", "60.1.1.0"},
                                  {"prefixlen", "24"}, 
                                  {"admin_distance", "120"},
                                  {"nexthop_address", "11.1.1.20"},
                                  {"nexthop_interface", "GigabitEthernet0/0/0/0"},
                              },

                            };
  
}


TelemetryAction::TelemetryAction(std::shared_ptr<grpc::Channel> Channel)
  : iosxrsl_route_(std::make_unique<IosxrslRoute>(Channel))
{}


// Set VRF context for V4 routes
void
TelemetryAction::setIosxrslRouteVrfV4(std::string vrfName)
{
    iosxrsl_route_->setVrfV4(vrfName);
}

// Set VRF context for V6 routes
void
TelemetryAction::setIosxrslRouteVrfV6(std::string vrfName)
{
    iosxrsl_route_->setVrfV6(vrfName);
}

// Set VRF context for V4 and V6 routes
void
TelemetryAction::setIosxrslRouteVrf(std::string vrfName)
{
    setIosxrslRouteVrfV4(vrfName);
    setIosxrslRouteVrfV6(vrfName);
}



void 
TelemetryAction::IosxrslRoutePlay(std::string vrf,
                                 RouteBatch route_batch,
                                 service_layer::SLObjectOp routeOp)
{

    try
    {
        setIosxrslRouteVrf(vrf);
        for (auto & route : route_batch) {
            switch(addrFamily[route["address_family"]]) {
      
            case AF_INET:
                {
                    if (routeOp == service_layer::SL_OBJOP_UPDATE ||
                        routeOp == service_layer::SL_OBJOP_ADD) {
                        iosxrsl_route_->insertAddBatchV4(route["prefix"],
                                                         std::stoi(route["prefixlen"]),
                                                         std::stoi(route["admin_distance"]),
                                                         route["nexthop_address"],
                                                         route["nexthop_interface"]);
                    } else if (routeOp == service_layer::SL_OBJOP_DELETE) {
                        iosxrsl_route_->insertDeleteBatchV4(route["prefix"],
                                                            std::stoi(route["prefixlen"])); 
                    }
                    break;                
                }                       
            case AF_INET6:
                {  
                    if (routeOp == service_layer::SL_OBJOP_UPDATE ||
                        routeOp == service_layer::SL_OBJOP_ADD) {
 
                        iosxrsl_route_->insertAddBatchV6(route["prefix"],
                                                         std::stoi(route["prefixlen"]),
                                                         std::stoi(route["admin_distance"]),
                                                         route["nexthop_address"],
                                                         route["nexthop_interface"]);


                    } else if (routeOp == service_layer::SL_OBJOP_DELETE) {
                        iosxrsl_route_->insertDeleteBatchV6(route["prefix"],
                                                            std::stoi(route["prefixlen"])); 
                    }
                    break;  
                }

            }

        }

        iosxrsl_route_->routev4Op(routeOp);
        iosxrsl_route_->routev6Op(routeOp);
    } catch(IosxrslException const& ex) {
        LOG(ERROR) << "Failed push route batch into vrfs";
        LOG(ERROR) << ex.what();
    } catch(std::exception const& ex) {
         LOG(ERROR) << "Failed to decode Telemetry data as GPB";
         LOG(ERROR) << ex.what();
    } 

}


}
