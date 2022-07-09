#include "./OptionsConsoleCommand.h"
#include "Arduino.h"

const static char *TAG = "ArgParseCommand";

namespace ESP32Console
{
    std::unordered_map<std::string, OptionsConsoleCommand> OptionsConsoleCommand::registry_ = std::unordered_map<std::string, OptionsConsoleCommand>();

    int OptionsConsoleCommand::delegateResolver(int argc, char **argv)
    {
        // Retrieve ArgParserCommand from registry
        auto it = registry_.find(argv[0]);
        if (it == registry_.end())
        {
            log_e("Could not resolve the delegated function call!");
            return 1;
        }

        OptionsConsoleCommand command = it->second;

        int code = 0;

        try
        {
            return command.delegateFn_(argc, argv, command.options);
        }
        catch (const std::runtime_error &err)
        {
            std::cerr << err.what() << std::endl;
            std::cerr << command.options.help();
            return 1;
        }
    }
}
