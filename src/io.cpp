#include "io.hpp"
#include <fstream>
#include <sstream>

std::string io::load_file(const std::string &dir) {
    std::ifstream ifs(dir);
    std::stringstream buf;
    buf << ifs.rdbuf();

    return buf.str();
}
