#include "./NetworkCommands.h"
#include <Arduino.h>

#include <esp_ping.h>
#include <ping/ping.h>
#include <ping/ping_sock.h>
#include "lwip/inet.h"
#include "lwip/netdb.h"
#include "lwip/sockets.h"

#include "WiFi.h"

static int ping(int argc, char **argv)
{
    return EXIT_SUCCESS;
}

static const char *wlstatus2string(wl_status_t status)
{
    switch (status)
    {
    case WL_NO_SHIELD:
        return "Not initialized";
    case WL_CONNECT_FAILED:
        return "Connection failed";
    case WL_CONNECTED:
        return "Connected";
    case WL_CONNECTION_LOST:
        return "Connection lost";
    case WL_DISCONNECTED:
        return "Disconnected";
    case WL_IDLE_STATUS:
        return "Idle status";
    case WL_NO_SSID_AVAIL:
        return "No SSID available";
    case WL_SCAN_COMPLETED:
        return "Scan completed";
    default:
        return "Unknown";
    }
}

const char* wlmode2string(wifi_mode_t mode)
{
    switch(mode) {
        case WIFI_MODE_NULL:
            return "Not initialized";
        case WIFI_MODE_AP:
            return "Accesspoint";
        case WIFI_MODE_STA:
            return "Station";
        case WIFI_MODE_APSTA:
            return "Station + Accesspoint";
        default:
            return "Unknown";
    }
}

static void ipconfig_wlan()
{
    printf("==== WLAN ====\n");
    auto status = WiFi.status();
    printf("Mode: %s\n", wlmode2string(WiFi.getMode()));
    printf("Status: %s\n", wlstatus2string(status));

    if (status == WL_NO_SHIELD) {
        return;
    }
    
    printf("\n");
    printf("SSID: %s\n", WiFi.SSID().c_str());
    printf("BSSID: %s\n", WiFi.BSSIDstr().c_str());
    printf("Channel: %d\n", WiFi.channel());

    printf("\n");
    printf("IP: %s\n", WiFi.localIP().toString().c_str());
    printf("Subnet Mask: %s (/%d)\n", WiFi.subnetMask().toString().c_str(), WiFi.subnetCIDR());
    printf("Gateway: %s\n", WiFi.gatewayIP().toString().c_str());
    printf("IPv6: %s\n", WiFi.localIPv6().toString().c_str());
    
    printf("\n");
    printf("Hostname: %s\n", WiFi.getHostname());
    printf("DNS1: %s\n", WiFi.dnsIP(0).toString().c_str());
    printf("DNS2: %s\n", WiFi.dnsIP(0).toString().c_str());
}

static int ipconfig(int argc, char **argv)
{
    ipconfig_wlan();
    return EXIT_SUCCESS;
}

namespace ESP32Console::Commands
{
    const ConsoleCommand getPingCommand()
    {
        return ConsoleCommand("ping", &ping, "Ping host");
    }

    const ConsoleCommand getIpconfigCommand()
    {
        return ConsoleCommand("ipconfig", &ipconfig, "Show IP and connection informations");
    }
}