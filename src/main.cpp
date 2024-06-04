#include "LZW.h"
#include <iostream>
#include <string>
#include <vector>

#define io                             \
    std::ios_base::sync_with_stdio(0); \
    std::cin.tie(0);                   \
    std::cout.tie(0);

void printUsage()
{
    std::cout << "Usage:\n";
    std::cout << "  LZWCompressor compress <input_file> <output_file>\n";
    std::cout << "  LZWCompressor decompress <input_file> <output_file>\n";
}

int main(int argc, char *argv[])
{
    io;

    if (argc < 3)
    {
        printUsage();
        return 1;
    }

    std::string operation = argv[1];
    std::string inputFilePath = argv[2];
    std::string outputFilePath = argv[3];

    if (operation == "compress")
    {
        if (lzw::compress(inputFilePath, outputFilePath))
        {
            std::cout << "Compression successful.\n";
        }
        else
        {
            std::cerr << "Compression failed.\n";
            return 1;
        }
    }
    else if (operation == "decompress")
    {
        if (lzw::decompress(inputFilePath, outputFilePath))
        {
            std::cout << "Decompression successful.\n";
        }
        else
        {
            std::cerr << "Decompression failed.\n";
            return 1;
        }
    }
    else
    {
        printUsage();
        return 1;
    }

    return 0;
}
