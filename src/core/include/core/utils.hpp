#pragma once

#include <string_view>
#include <source_location>
#include <iostream>

namespace fenton
{

namespace core
{

// void log(const std::string_view& message,const std::source_location& location = std::source_location::current())
// {
//     std::cout << "info: "
//                 << location.file_name() << ":"
//                 << location.line() << " "
//                 << location.function_name() << " "
//                 << message << "\n";
// }

} // namespace core

} // namespace fenton
