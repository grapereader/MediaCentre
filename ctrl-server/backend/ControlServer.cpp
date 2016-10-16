#include <iostream>

#include "Application.h"

#define VERSION "0.0.1"

int main(int argc, char **argv)
{
    std::cout << "Running ViaWare Control Server v" << VERSION << std::endl;

    vmc::start();

    return 0;
}
