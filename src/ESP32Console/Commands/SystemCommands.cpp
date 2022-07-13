#include "./SystemCommands.h"
#include "ESP32Console.h"
#include <Arduino.h>
#include <esp_partition.h>
#include <esp_ota_ops.h>
#include <esp_system.h>
#include <core_version.h>

//For XSTR macros
#include <xtensa/xtruntime.h>

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

static const char* getResetReasonStr()
{
    switch(esp_reset_reason()) {
        case ESP_RST_BROWNOUT:
            return "Brownout reset (software or hardware)";
        case ESP_RST_DEEPSLEEP:
            return "Reset after exiting deep sleep mode";
        case ESP_RST_EXT:
            return "Reset by external pin (not applicable for ESP32)";
        case ESP_RST_INT_WDT:
            return "Reset (software or hardware) due to interrupt watchdog";
        case ESP_RST_PANIC:
            return "Software reset due to exception/panic";
        case ESP_RST_POWERON:
            return "Reset due to power-on event";
        case ESP_RST_SDIO:
            return "Reset over SDIO";
        case ESP_RST_SW:
            return "Software reset via esp_restart";
        case ESP_RST_TASK_WDT:
            return "Reset due to task watchdog";
        case ESP_RST_WDT:
            return "ESP_RST_WDT";
        
        case ESP_RST_UNKNOWN:
        default:
            return "Unknown";
    }
}

static int sysInfo(int argc, char **argv)
{
    esp_chip_info_t info;
    esp_chip_info(&info);

    printf("ESP32Console version: %s\n", ESP32CONSOLE_VERSION);
    printf("Arduino Core version: %s (%x)\n", XTSTR(ARDUINO_ESP32_GIT_DESC), ARDUINO_ESP32_GIT_VER);
    printf("ESP-IDF Version: %s\n", ESP.getSdkVersion());

    printf("\n");
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

    #ifndef CONFIG_APP_REPRODUCIBLE_BUILD
    printf("Compilation datetime: " __DATE__ " "  __TIME__ "\n");
    #endif

    
    printf("\nReset reason: %s\n", getResetReasonStr());

    printf("\n");
    printf("CPU temperature: %.01f °C\n", temperatureRead());

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
    uint32_t min = ESP.getMinFreeHeap() / 1024;

    printf("Heap: %u KB free, %u KB used, (%u KB total)\n", free, used, total);
    printf("Minimum free heap size during uptime was: %u KB\n", min);
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