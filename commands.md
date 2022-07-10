# Included command reference

## Core commands (automatically loaded, when begin() is called)

* `help`: Show a list of all possible commands with descriptions
* `clear`: Clear terminal screen using ANSI commands (only working when using an ANSI compatible terminal)
* `echo`: Echo the parameter strings
* `history`: Show the recent command history
* `multiline_mode`: Switch multiline mode on or off. When it is on, lines get break into a second line, if it gets too long.
* `env`: List all environment variables
* `declare`: Change the value of an environment variable (syntax: `declare VARIABLE Value` or `declare VARIABLE "Long Value"`)

## System commands (loaded by calling registerSystemCommands())

* `sysinfo`: Prints info about the chip model, revision, ESP-IDF version, EFuse MAC, flash and PSRAM
* `restart`: Restarts the system
* `meminfo`: Show informations about used and free Heap

