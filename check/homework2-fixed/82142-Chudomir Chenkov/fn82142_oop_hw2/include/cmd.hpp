#ifndef _CMD_HPP_
#define _CMD_HPP_

#include <string>
#include <vector>

namespace CMD {
    struct Command {
        std::string type;
        std::vector<std::string> args;
    };

    Command parse_str(const std::string &str);
}

#endif // _CMD_HPP_
