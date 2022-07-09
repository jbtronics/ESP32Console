#include "./NetworkCommands.h"
#include <Arduino.h>

#include <esp_ping.h>
#include <ping/ping.h>
#include <ping/ping_sock.h>
#include "lwip/inet.h"
#include "lwip/netdb.h"
#include "lwip/sockets.h"

int ping(int argc, char** argv)
{
    return EXIT_SUCCESS;
}

namespace ESP32Console::Commands
{
    const ConsoleCommand getPingCommand()
    {
        return ConsoleCommand("ping", &ping, "Ping host");
    }
}