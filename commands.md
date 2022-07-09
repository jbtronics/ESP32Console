# Included command reference

## Core commands (automatically loaded, when begin() is called)

* `help`: Show a list of all possible commands with descriptions
* `clear`: Clear terminal screen using ANSI commands (only working when using an ANSI compatible terminal)
* `echo`: Echo the parameter strings


## System commands (loaded by calling registerSystemCommands())

* `sysinfo`: Prints info about the chip model, revision, ESP-IDF version, EFuse MAC, flash and PSRAM
* `restart`: Restarts the system
* `meminfo`: Show informations about used and free Heap

