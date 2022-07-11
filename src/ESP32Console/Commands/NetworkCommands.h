#pragma once

#include "ESP32Console/ConsoleCommand.h"

namespace ESP32Console::Commands
{
    const ConsoleCommand getPingCommand();


    const ConsoleCommand getIpconfigCommand();
}