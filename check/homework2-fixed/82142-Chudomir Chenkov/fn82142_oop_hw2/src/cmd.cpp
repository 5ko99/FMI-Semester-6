#include "cmd.hpp"
#include "utils.hpp"

#include <algorithm>

CMD::Command CMD::parse_str(const std::string &str) {
    std::vector<std::string> split_str = split(str, ' ');
    std::string command_type = to_lowercase(split_str.at(0));
    split_str.erase(split_str.begin());

    return CMD::Command{command_type, split_str};
}
