#include <iostream>
#include <stdexcept>
#include "System.h"

int main() {
    try {
        System courseSystem;
        courseSystem.run();
    } catch (const std::exception& e) {
        std::cerr << "FATAL ERROR: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}