#pragma once

#if !defined(ESP32)
#error This library depends on ESP-IDF and only works on ESP32!
#endif

#include "ESP32Console/Console.h"
#include "ESP32Console/ConsoleCommand.h"
#include "ESP32Console/ConsoleCommandD.h"
#include "ESP32Console/OptionsConsoleCommand.h"