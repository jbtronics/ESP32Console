#pragma once

#include "ESP32Console/ConsoleCommand.h"

namespace ESP32Console::Commands
{
    const ConsoleCommand getClearCommand();

    const ConsoleCommand getEchoCommand();

    const ConsoleCommand getSetMultilineCommand();
}