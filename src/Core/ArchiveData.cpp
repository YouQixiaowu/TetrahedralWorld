#include "pch.h"
#include "ArchiveData.h"
namespace tw
{
    static void loadFile(char* file)
    {
        std::ifstream infile(file, std::ios::binary);
        if (infile.is_open())
        {
            std::cout << "ll" << std::endl;
        }
        infile.seekg(0, std::ios::end);
        size_t length = infile.tellg();
        infile.seekg(0, std::ios::beg);
        char* buffer = new char[length];
        infile.read(buffer, length);
        infile.close();
    }
}