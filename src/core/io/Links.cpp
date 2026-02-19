#include <iostream>
#include <string>
#include <cstdlib>
#include "core/io/Links.hpp"

Links::Links() {}

void Links::open(std::string url) {
    std::string command = "xdg-open " + url;
    std::system(command.c_str());
}