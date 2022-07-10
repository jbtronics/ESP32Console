#pragma once

#include "ESP32Console/ConsoleCommand.h"

namespace ESP32Console::Commands
{
    const ConsoleCommand getCatCommand();

    const ConsoleCommand getPWDCommand();

    const ConsoleCommand getCDCommand();

    const ConsoleCommand getLsCommand();

    const ConsoleCommand getMvCommand();

    const ConsoleCommand getCPCommand();

    const ConsoleCommand getRMCommand();

    const ConsoleCommand getRMDirCommand();

    const ConsoleCommand getEditCommand();
}