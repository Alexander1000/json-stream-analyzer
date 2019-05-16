#include <iostream>
#include "cl.cpp"
#include <sys/stat.h>

#include "buffer/io_buffer.h"
#include "json/stream.h"

#define ERROR_MISSING_INPUT (-1)
#define ERROR_STAT_INFO (-2)
#define ERROR_STAT_INVALID_MODE (-3)
#define ERROR_NOT_IMPLEMENT (-4)

void help()
{
    std::cout << "Help message for json-stream-analyzer:" << std::endl;
    std::cout << "-i [--input] - file for analyze" << std::endl;
    std::cout << "-h [--help] - this help message" << std::endl;
}

int main(int argc, char* argv[])
{
    CommandLine commandLine(argc, argv);

    if (commandLine.is("-h") || commandLine.is("--help")) {
        help();
        return 0;
    }

    if (!commandLine.is("-i") && !commandLine.is("--input")) {
        help();
        return ERROR_MISSING_INPUT;
    }

    char* inputPath = NULL;

    if (commandLine.is("-i")) {
        inputPath = commandLine.get("-i");
    } else if (commandLine.is("--input")) {
        inputPath = commandLine.get("--input");
    }

    if (inputPath == NULL) {
        std::cout << "Missing parameter value for -i [--input]" << std::endl;
        return ERROR_MISSING_INPUT;
    }

    struct stat s;
    int checkStat = stat(inputPath, &s);

    if (checkStat != 0) {
        cout << "Undefined errors: " << checkStat << endl;
        return ERROR_STAT_INFO;
    }

    if (s.st_mode & S_IFDIR) {
        cout << "is a directory" << endl;
        return ERROR_NOT_IMPLEMENT;
    }

    if(s.st_mode & S_IFREG) {
        std::cout << "starting analyze file" << std::endl;
        IOFileReader* file_buffer = new IOFileReader(inputPath);
        Stream* json_stream = new Stream(file_buffer);
        Pretty* json_pretty = new Pretty(json_stream);
        json_pretty->pretty();
    } else {
        return ERROR_STAT_INVALID_MODE;
    }

    return 0;
}
