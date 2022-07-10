#include "./VFSCommands.h"
#include <Arduino.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "ESP32Console/Helpers/PWDHelpers.h"

#include "kilo/kilo.h"

char *canonicalize_file_name(const char *path);

int cat(int argc, char **argv)
{
    if (argc == 1)
    {
        fprintf(stderr, "You have to pass at least one file path!\n");
        return EXIT_SUCCESS;
    }

    for (int n = 1; n < argc; n++)
    {
        char filename[PATH_MAX];
        // We have manually do resolving of . and .., as VFS does not do it
        ESP32Console::console_realpath(argv[n], filename);

        FILE *file = fopen(filename, "r");
        if (file == nullptr)
        {
            fprintf(stderr, "%s %s : %s\n", argv[0], filename,
                    strerror(errno));
            return errno;
        }

        int chr;
        while ((chr = getc(file)) != EOF)
            fprintf(stdout, "%c", chr);
        fclose(file);
    }

    return EXIT_SUCCESS;
}

int pwd(int argc, char **argv)
{
    printf("%s\n", ESP32Console::console_getpwd());
    return EXIT_SUCCESS;
}

int cd(int argc, char **argv)
{
    const char *path;

    if (argc != 2)
    {
        path = getenv("HOME");
        if (!path)
        {
            fprintf(stderr, "No HOME env variable set!\n");
            return EXIT_FAILURE;
        }
    }
    else
    {
        path = argv[1];
    }

    // Check if target path is a file
    char resolved[PATH_MAX];
    ESP32Console::console_realpath(path, resolved);
    FILE *file = fopen(resolved, "r");

    // If we can open it, then we can not chdir into it.
    if (file)
    {
        fclose(file);
        fprintf(stderr, "Can not cd into a file!\n");
        return 1;
    }

    if (ESP32Console::console_chdir(path))
    {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return 1;
    }

    const char *pwd = ESP32Console::console_getpwd();

    // Check if the new PWD exists, and show a warning if not
    DIR *dir = opendir(pwd);
    if (dir)
    {
        closedir(dir);
    }
    else if (ENOENT == errno)
    {
        fprintf(stderr, "Choosen directory maybe does not exists!\n");
    }

    return EXIT_SUCCESS;
}

int ls(int argc, char **argv)
{
    char *inpath;
    if (argc == 1)
    {
        inpath = (char *)".";
    }
    else if (argc == 2)
    {
        inpath = argv[1];
    }
    else
    {
        printf("You can pass only one filename!\n");
        return 1;
    }

    char path[PATH_MAX];
    ESP32Console::console_realpath(inpath, path);

    DIR *dir = opendir(path);
    if (!dir)
    {
        fprintf(stderr, "Could not open filepath: %s\n", strerror(errno));
        return 1;
    }

    struct dirent *d;
    while ((d = readdir(dir)) != NULL)
    {
        printf("%s\n", d->d_name);
    }

    closedir(dir);
    return EXIT_SUCCESS;
}

int mv(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Syntax is mv [ORIGIN] [TARGET]\n");
        return 1;
    }

    char old_name[PATH_MAX], new_name[PATH_MAX];

    // Resolve arguments to full path
    ESP32Console::console_realpath(argv[1], old_name);
    ESP32Console::console_realpath(argv[2], new_name);

    // Do rename
    if (rename(old_name, new_name))
    {
        printf("Error moving: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int cp(int argc, char **argv)
{
    //TODO: Shows weird error message
    if (argc != 3)
    {
        fprintf(stderr, "Syntax is cp [ORIGIN] [TARGET]\n");
        return 1;
    }

    char old_name[PATH_MAX], new_name[PATH_MAX];

    // Resolve arguments to full path
    ESP32Console::console_realpath(argv[1], old_name);
    ESP32Console::console_realpath(argv[2], new_name);

    // Do copy
    FILE *origin = fopen(old_name, "r");
    if (!origin)
    {
        fprintf(stderr, "Error opening origin file: %s\n", strerror(errno));
        return 1;
    }

    FILE *target = fopen(new_name, "w");
    if (!target)
    {
        fclose(origin);
        fprintf(stderr, "Error opening target file: %s\n", strerror(errno));
        return 1;
    }

    int buffer;

    // Clear existing errors
    auto error = errno;

    while ((buffer = getc(origin)) != EOF)
    {
        if(fputc(buffer, target) == EOF) {
            fprintf(stderr, "Error writing: %s\n", strerror(errno));
            fclose(origin); fclose(target);
            return 1;
        }
    }

    error = errno;
    if (error && !feof(origin))
    {
        fprintf(stderr, "Error copying: %s\n", strerror(error));
        fclose(origin);
        fclose(target);
        return 1;
    }

    fclose(origin);
    fclose(target);

    return EXIT_SUCCESS;
}

int rm(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "You have to pass exactly one file. Syntax rm [FIILE]\n");
        return EXIT_SUCCESS;
    }

    char filename[PATH_MAX];
    ESP32Console::console_realpath(argv[1], filename);

    if(unlink(filename)) {
        fprintf(stderr, "Error deleting %s: %s\n", filename, strerror(errno));
    }

    return EXIT_SUCCESS;
}

int rmdir(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "You have to pass exactly one file. Syntax rmdir [FIILE]\n");
        return EXIT_SUCCESS;
    }

    char filename[PATH_MAX];
    ESP32Console::console_realpath(argv[1], filename);

    if(rmdir(filename)) {
        fprintf(stderr, "Error deleting %s: %s\n", filename, strerror(errno));
    }

    return EXIT_SUCCESS;
}

namespace ESP32Console::Commands
{
    const ConsoleCommand getCatCommand()
    {
        return ConsoleCommand("cat", &cat, "Show the content of one or more files.");
    }

    const ConsoleCommand getPWDCommand()
    {
        return ConsoleCommand("pwd", &pwd, "Show the current working dir");
    }

    const ConsoleCommand getCDCommand()
    {
        return ConsoleCommand("cd", &cd, "Change the working directory");
    }

    const ConsoleCommand getLsCommand()
    {
        return ConsoleCommand("ls", &ls, "List the contents of the given path");
    }

    const ConsoleCommand getMvCommand()
    {
        return ConsoleCommand("mv", &mv, "Move the given file to another place or name");
    }

    const ConsoleCommand getCPCommand()
    {
        return ConsoleCommand("cp", &cp, "Copy the given file to another place or name");
    }

    const ConsoleCommand getRMCommand()
    {
         return ConsoleCommand("rm", &rm, "Permanenty deletes the given file.");
    }

    const ConsoleCommand getRMDirCommand()
    {
        return ConsoleCommand("rmdir", &rmdir, "Permanenty deletes the given folder. Folder must be empty!");
    }

    const ConsoleCommand getEditCommand()
    {
        return ConsoleCommand("edit", &ESP32Console::Kilo::kilo, "Edit files");
    }
}