#include "assignment3_task1/logger.h"
#include <iostream>
namespace assignment3_task1 {
void log_info(const std::string& m){ std::cout << "[INFO] " << m << std::endl; }
void log_error(const std::string& m){ std::cerr << "[ERROR] " << m << std::endl; }
}
