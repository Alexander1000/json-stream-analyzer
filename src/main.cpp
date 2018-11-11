#include <iostream>
#include "cl.cpp"
#include <stdio.h>
#include <sys/stat.h>

#include "buffer/io_buffer.h"
#include "json/stream.h"

using namespace std;

#define ERROR_MISSING_INPUT -1
#define ERROR_STAT_INFO -2
#define ERROR_STAT_INVALID_MODE -3
#define ERROR_NOT_IMPLEMENT -4

#define ERROR_INVALID -255

void help()
{
    cout << "Help message for json-stream-analyzer:" << endl;
    cout << "-i [--input] - file for analyze" << endl;
    cout << "-h [--help] - this help message" << endl;
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
        cout << "Missing parameter value for -i [--input]" << endl;
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
    } else if(s.st_mode & S_IFREG) {
        cout << "starting analyze file" << endl;
        IOFileReader* file_buffer = new IOFileReader(inputPath);
        Stream* json_stream = new Stream(file_buffer);
        Pretty* json_pretty = new Pretty(json_stream);
        json_pretty->pretty();
    } else {
        return ERROR_STAT_INVALID_MODE;
    }

    return 0;
}
