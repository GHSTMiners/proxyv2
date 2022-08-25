#include <stdio.h>
#include "Bootstrapper/Bootstrapper.hpp"

int main(int argc, char const *argv[])
{
    Bootstrapper bootstrapper;
    bootstrapper.bootstrap(argc, argv);

    return 0;
}
