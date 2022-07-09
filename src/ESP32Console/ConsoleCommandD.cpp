#include "./ConsoleCommandD.h"
#include "Arduino.h"

const static char *TAG = "ConsoleCommandD";

namespace ESP32Console
{
    std::unordered_map<std::string, delegateFunc> ConsoleCommandD::registry_ = std::unordered_map<std::string, delegateFunc>();

    int ConsoleCommandD::delegateResolver(int argc, char **argv)
    {
        // Retrieve ConsoleCommandD from registry
        auto it = registry_.find(argv[0]);
        if (it == registry_.end())
        {
            log_e("Could not resolve the delegated function call!");
            return 1;
        }

        delegateFunc command = it->second;

        int code = 0;

        try
        {
            return command(argc, argv);
        }
        catch (const std::exception &err)
        {
            printf("%s", err.what());
            return 1;
        }
    }
}