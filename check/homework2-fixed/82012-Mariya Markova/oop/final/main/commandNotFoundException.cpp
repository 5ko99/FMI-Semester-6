#include "commandNotFoundException.h"

CommandNotFoundException::CommandNotFoundException()
    :std::runtime_error("no such command")
{}
