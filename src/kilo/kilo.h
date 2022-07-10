#pragma once

#include "ESP32Console/Helpers/PWDHelpers.h"
#include <exception>
#include "linenoise/linenoise.h"

namespace ESP32Console::Kilo
{
    int kilo(int argc, char **argv);

    struct KiloException : public std::exception
    {
    private:
        int code_;

    public:
        KiloException(int code) : code_(code){};

        const char *what() const throw()
        {
            return "Kilo exited";
        }
    };
}