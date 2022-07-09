#include "./SystemCommands.h"
#include <Arduino.h>

static String mac2String(uint64_t mac)
{
    byte *ar = (byte*) &mac;
    String s;
    for (byte i = 0; i < 6; ++i)
    {
        char buf[3];
        sprintf(buf, "%02X", ar[i]); // J-M-L: slight modification, added the 0 in the format for padding
        s += buf;
        if (i < 5)
            s += ':';
    }
    return s;
}

static const char* getFlashModeStr()
{
    switch(ESP.getFlashChipMode()) {
        case FM_DIO:
            return "DIO";
        case FM_DOUT:
            return "DOUT";
        case FM_FAST_READ:
            return "FAST READ";
        case FM_QIO:
            return "QIO";
        case FM_QOUT:
            return "QOUT";
        case FM_SLOW_READ:
            return "SLOW READ";
        case FM_UNKNOWN:
        default:
            return "UNKNOWN";
    }
}

static int sysInfo(int argc, char **argv)
{
    esp_chip_info_t info;
    esp_chip_info(&info);

    printf("IDF Version: %s\n", ESP.getSdkVersion());

    printf("Chip info:\n");
    printf("\tModel: %s\n", ESP.getChipModel());
    printf("\tRevison number: %d\n", ESP.getChipRevision());
    printf("\tCores: %d\n", ESP.getChipCores());
    printf("\tClock: %d MHz\n", ESP.getCpuFreqMHz());
    printf("\tFeatures:%s%s%s%s%s\r\n",
           info.features & CHIP_FEATURE_WIFI_BGN ? " 802.11bgn " : "",
           info.features & CHIP_FEATURE_BLE ? " BLE " : "",
           info.features & CHIP_FEATURE_BT ? " BT " : "",
           info.features & CHIP_FEATURE_EMB_FLASH ? " Embedded-Flash " : " External-Flash ",
           info.features & CHIP_FEATURE_EMB_PSRAM ? " Embedded-PSRAM" : ""
    );

    printf("EFuse MAC: %s\n", mac2String(ESP.getEfuseMac()).c_str());
    
    printf("Flash size: %d MB (mode: %s, speed: %d MHz)\n", ESP.getFlashChipSize() / (1024 * 1024), getFlashModeStr(), ESP.getFlashChipSpeed() / (1024 * 1024));
    printf("PSRAM size: %d MB\n", ESP.getPsramSize() / (1024 * 1024));

    printf("Sketch size: %d KB\n", ESP.getSketchSize() / (1024));
    printf("Sketch MD5: %s\n", ESP.getSketchMD5().c_str());

    return EXIT_SUCCESS;
}

static int restart(int argc, char** argv)
{
    printf("Restarting...");
    ESP.restart();
    return EXIT_SUCCESS;
}

static int meminfo(int argc, char** argv)
{
    uint32_t free = ESP.getFreeHeap() / 1024;
    uint32_t total = ESP.getHeapSize() / 1024;
    uint32_t used = total - free;

    printf("Heap: %d KB free, %d KB used, (%d KB total)\n", free, used, total);
    return EXIT_SUCCESS;
}

namespace ESP32Console::Commands
{
    const ConsoleCommand getRestartCommand()
    {
        return ConsoleCommand("restart", &restart, "Restart / Reboot the system");
    }

    const ConsoleCommand getSysInfoCommand()
    {
        return ConsoleCommand("sysinfo", &sysInfo, "Shows informations about the system like chip model and ESP-IDF version");
    }

    const ConsoleCommand getMemInfoCommand()
    {
        return ConsoleCommand("meminfo", &meminfo, "Shows information about heap usage");
    }
}