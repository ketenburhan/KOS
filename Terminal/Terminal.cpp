#include <iostream>
#include "Terminal.h"

namespace Terminal {
    void Log(const char* msg) {
        std::cout << msg << std::endl;
    }
}