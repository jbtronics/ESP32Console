#include "./ArgParseCommand.h"
#include "Arduino.h"

const static char *TAG = "ArgParseCommand";

namespace ESP32Console
{
    std::unordered_map<std::string, ArgParseCommand> ArgParseCommand::registry_ = std::unordered_map<std::string, ArgParseCommand>();

    int ArgParseCommand::delegateResolver(int argc, char **argv)
    {
        // Retrieve ArgParserCommand from registry
        auto it = registry_.find(argv[0]);
        if (it == registry_.end())
        {
            log_e("Could not resolve the delegated function call!");
            return 1;
        }

        ArgParseCommand command = it->second;

        int code = 0;

        try
        {
            return command.delegateFn_(argc, argv, command.parser);
        }
        catch (const std::runtime_error &err)
        {
            std::cerr << err.what() << std::endl;
            std::cerr << command.parser;
            return 1;
        }
    }
}
