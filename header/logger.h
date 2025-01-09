#include <iostream>
#include <source_location>
// will be replced with smarter one
#define LOG std::cout << std::source_location::current().file_name() << ":" << std::source_location::current().line() << ":" << std::source_location::current().function_name() << " " << ":\n\t\t"