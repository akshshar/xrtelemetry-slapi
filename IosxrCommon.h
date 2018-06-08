#pragma once
#include <map>
#include <string>
#include <vector>

namespace iosxr {

using AddrFamily = std::map<std::string, const int>;
using RouteBatch = std::vector<std::map<std::string, std::string>>;
using RouteBatchMap = std::map<std::string, RouteBatch>;

}
