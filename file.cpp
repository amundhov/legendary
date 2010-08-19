#include "file.h"

#include <fstream>
#include <iostream>

using namespace std;

char *File::readFile(const char* filename)
{
    unsigned int length;
    char *buffer;

    ifstream file;
    file.open(filename, ios::binary);

    // get size
    file.seekg(0, ios::end);
    length = file.tellg();
    length++;
    file.seekg(0, ios::beg);

    buffer = new char[length];
    file.read(buffer, length);
    buffer[length-1] = (char)0x0;
    file.close();

    return buffer;
}

