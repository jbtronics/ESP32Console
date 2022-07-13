#pragma once

#include "ESP32Console/ConsoleCommand.h"

namespace ESP32Console::Commands
{
    const ConsoleCommand getSysInfoCommand();

    const ConsoleCommand getRestartCommand();

    const ConsoleCommand getMemInfoCommand();

    const ConsoleCommand getDateCommand();
};