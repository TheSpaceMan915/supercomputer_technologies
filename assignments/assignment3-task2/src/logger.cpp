#include "assignment3_task2/logger.h"
#include <iostream>

namespace assignment3_task2
{
    void log_info(const std::string& msg)
    {
        std::cout << "[INFO] " << msg << std::endl;
    }

    void log_error(const std::string& msg)
    {
        std::cerr << "[ERROR] " << msg << std::endl;
    }
}
