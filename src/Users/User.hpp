#pragma once

#include <string>
#include <tuple>

namespace vkpg {

using UserTypePG = std::tuple<std::string,  // nickname
                              std::string,  // fullname
                              std::string,  // about
                              std::string   // email
                              >;

}