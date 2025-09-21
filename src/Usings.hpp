#ifndef USINGS_HPP
#define USINGS_HPP

// #define INCLUDE_COMMON
#include <regex>
#include <cctype>
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <filesystem>
#include <thread>
#include <limits>
#include <functional>
#include <exception>
#include <algorithm>
#include <numeric>

#define USING_STD_ASSESSMENT \
    using std::string; \
    using std::to_string; \
    using std::shared_ptr; \
    using std::ostream; \
    using std::fixed; \
    using std::setprecision; \
    using std::cout; \
    using std::endl; \
    using std::abs;

#define USING_STD_COURSE \
    using std::string; \
    using std::vector; \
    using std::shared_ptr; \
    using std::ostream; \
    using std::invalid_argument; \
    using std::runtime_error;

#define USING_STD_GRADECALCULATOR \
    using std::vector; \
    using std::string; \
    using std::min; \
    using std::nth_element; \
    using std::greater; \

#define USING_STD_FILEHANDLER \
    using std::string; \
    using std::stoi; \
    using std::vector; \
    using std::shared_ptr; \
    using std::make_shared; \
    using std::transform; \
    using std::pair; \
    using std::sort; \
    using std::fixed; \
    using std::setprecision; \
    using std::stringstream; \
    using std::find_if; \
    using std::cout; \
    using std::endl; \
    using std::exception; \
    using std::time; \
    using std::localtime; \
    using std::put_time; \
    using std::ostringstream; \
    using std::ofstream; \
    using std::ifstream; \
    using std::to_string; \
    using std::ios; \
    using std::getline; \
    using std::chrono::system_clock; \
    using std::this_thread::sleep_for; \
    using std::chrono::milliseconds; \
    using std::chrono::time_point_cast; \

#define USING_STD_STUDENT \
    using std::ostream; \
    using std::string; \
    using std::vector; \
    using std::shared_ptr; \
    using std::invalid_argument;

#define USING_STD_SYSTEM \
    using std::shared_ptr; \
    using std::function; \
    using std::stringstream; \
    using std::string; \
    using std::cout; \
    using std::cin; \
    using std::cerr; \
    using std::endl; \
    using std::exception; \
    using std::vector; \
    using std::shared_ptr; \
    using std::getline; \
    using std::chrono::system_clock; \
    using std::put_time; \
    using std::localtime; \
    using std::streamsize; \
    using std::numeric_limits; \
    using std::transform;

#define USING_STD_COMMON \
    using std::string; \
    using std::vector; \
    using std::regex; \
    using std::regex_match; \
    using std::remove; \
    using std::replace; \
    using std::all_of; \
    using std::isalnum; \
    using std::isdigit; \
    using std::stoi; \
    using std::stod; \
    using std::transform; \
    using std::tolower; \
    using std::unique; \
    using std::isspace; \
    using std::cout; \
    using std::endl; \
    using std::ostringstream; \
    using std::chrono::system_clock; \
    using std::put_time; \
    using std::localtime;

#endif //USINGS_HPP
