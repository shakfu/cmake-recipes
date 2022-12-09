#include <string>
#include <iostream>
#include "robots.hpp"

void print_from_machines(const std::string& message)
{
    std::cout << "Entering print_from_machines()" << std::endl;
    print_from_robots(message);
    std::cout << "Exiting print_from_machines()" << std::endl;
}
