## XR-Telemetry + SL-API based path failover

1) XR-Telemetry Stream is set up to receive IPv6 Neighbor entries and process Active Path state.

2) Service-Layer API uses the router vertical and is invoked by the Telemetry client if the active path toggles.


## Build the app

You'll need the iosxr sl-api library and the telemetry grpc libraries built before issuing a `make` in this directory.

### Build the IOS-XR SL-API library
Clone the Service-layer-objmodel repository:

```
https://github.com/Cisco-Service-Layer/service-layer-objmodel/

```

Build the service layer library and install it:

```
cd service-layer-objmodel/grpc/cpp/
sudo ./build_libiosxrsl.sh

```


### Build the IOS-XR Telemetry grpc library
Clone the bigmuddy-telemetry git repository:

```
git clone https://github.com/akshshar/bigmuddy-network-telemetry-proto

```
Build the telemetry base library along with the decoding libraries for specific Models like the one for IPv6 ND used by this app and install the bindings generated.

```
cd bigmuddy-network-telemetry-proto/
./build_ipv6_nd_lib.sh
sudo make install
```


### Build the miscellaneous dependencies required by the app

```
git clone https://github.com/akshshar/xrtelemetry-slapi
cd xrtelemetry-slapi/
./build_misc_dependencies.sh
```

### Build the xrtelemetry-slapi app

Build the xrtelemetry-slapi app by issuing a `make` in the root directory


```
make

```


## Execute the app

Finally, execute the generated binary:

```
GLOG_v=3 ./iosxrtelemetrysubmain

```
