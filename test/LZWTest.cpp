#include "gtest/gtest.h"
#include "LZW.h"
#include <vector>
#include <string>
#include <fstream>

// Helper function to read a file into a vector of unsigned char
std::vector<unsigned char> readFile(const std::string &filePath)
{
    std::ifstream file(filePath, std::ios::binary);

    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file");
    }

    return std::vector<unsigned char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

// Helper function to write a vector of unsigned char to a file
void writeFile(const std::string &filePath, const std::vector<unsigned char> &data)
{
    std::ofstream file(filePath, std::ios::binary);
    file.write(reinterpret_cast<const char *>(data.data()), data.size());
}

// Test the compressData function
TEST(LZWCompressionTest, CompressDecompress)
{
    std::vector<unsigned char> input = {'h', 'e', 'l', 'l', 'o'};
    std::vector<int> compressed = lzw::compressData(input);
    std::vector<unsigned char> decompressed = lzw::decompressData(compressed);

    EXPECT_EQ(input, decompressed);
}

// Test with a PNG file
TEST(LZWCompressionTest, CompressDecompressPNG)
{
    std::string inputFilePath = "test_input/test.png";
    std::string compressedFilePath = "test_output/compressed_png.lzw";
    std::string decompressedFilePath = "test_output/test_decompressed.png";

    // Read input file
    std::vector<unsigned char> inputData = readFile(inputFilePath);

    // Compress the data
    std::vector<int> compressedData = lzw::compressData(inputData);

    // Write compressed data to file
    {
        std::ofstream outFile(compressedFilePath, std::ios::binary);
        for (int code : compressedData)
        {
            outFile.write(reinterpret_cast<const char *>(&code), sizeof(code));
        }
    }

    // Read compressed data from file
    std::vector<int> readCompressedData;
    {
        std::ifstream inFile(compressedFilePath, std::ios::binary);
        int code;
        while (inFile.read(reinterpret_cast<char *>(&code), sizeof(code)))
        {
            readCompressedData.push_back(code);
        }
    }

    // Decompress the data
    std::vector<unsigned char> decompressedData = lzw::decompressData(readCompressedData);

    // Write decompressed data to file
    writeFile(decompressedFilePath, decompressedData);

    // Read the decompressed file
    std::vector<unsigned char> outputData = readFile(decompressedFilePath);

    EXPECT_EQ(inputData, outputData);
}

// Test with a PDF file
TEST(LZWCompressionTest, CompressDecompressPDF)
{
    std::string inputFilePath = "test_input/test.pdf";
    std::string compressedFilePath = "test_output/compressed_pdf.lzw";
    std::string decompressedFilePath = "test_output/test_decompressed.pdf";

    // Read input file
    std::vector<unsigned char> inputData = readFile(inputFilePath);

    // Compress the data
    std::vector<int> compressedData = lzw::compressData(inputData);

    // Write compressed data to file
    {
        std::ofstream outFile(compressedFilePath, std::ios::binary);
        for (int code : compressedData)
        {
            outFile.write(reinterpret_cast<const char *>(&code), sizeof(code));
        }
    }

    // Read compressed data from file
    std::vector<int> readCompressedData;
    {
        std::ifstream inFile(compressedFilePath, std::ios::binary);
        int code;
        while (inFile.read(reinterpret_cast<char *>(&code), sizeof(code)))
        {
            readCompressedData.push_back(code);
        }
    }

    // Decompress the data
    std::vector<unsigned char> decompressedData = lzw::decompressData(readCompressedData);

    // Write decompressed data to file
    writeFile(decompressedFilePath, decompressedData);

    // Read the decompressed file
    std::vector<unsigned char> outputData = readFile(decompressedFilePath);

    EXPECT_EQ(inputData, outputData);
}
