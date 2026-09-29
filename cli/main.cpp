#include "sentinel/version.h"
#include <iostream>

int main() {
    std::cout << "Sentinel " << sentinel::version() << '\n';
}