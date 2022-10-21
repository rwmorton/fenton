#pragma once

#include <string_view>
#include <source_location>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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

const std::string readFile(const std::string& filePath)
{
    std::string fileData;
    std::ifstream file;
    
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        file.open(filePath);
        std::stringstream fileStream;
        fileStream << file.rdbuf();
        file.close();
        fileData = fileStream.str();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return fileData;
}

} // namespace core

} // namespace fenton
