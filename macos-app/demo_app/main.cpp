#include "vehicles.hpp"
#include "machines.hpp"
#include <iostream>

// main() uses vehicles and machines, machines internally uses robots
int main()
{
    std::cout << "Entering main()" << std::endl;
    print_from_vehicles("hello");
    print_from_machines("world");
    std::cout << "Exiting main()" << std::endl;

    return 0;
}
