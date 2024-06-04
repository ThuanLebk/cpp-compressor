#include "LZW.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stdexcept>

namespace lzw
{

    std::vector<int> compressData(const std::vector<unsigned char> &input)
    {
        std::unordered_map<std::string, int> dictionary;
        for (int i = 0; i < 256; ++i)
        {
            dictionary[std::string(1, i)] = i;
        }

        std::string w;
        std::vector<int> compressedOutput;
        int dictSize = 256;

        for (unsigned char c : input)
        {
            std::string wc = w + static_cast<char>(c);
            if (dictionary.count(wc))
            {
                w = wc;
            }
            else
            {
                compressedOutput.push_back(dictionary[w]);
                dictionary[wc] = dictSize++;
                w = std::string(1, c);
            }
        }

        if (!w.empty())
        {
            compressedOutput.push_back(dictionary[w]);
        }

        return compressedOutput;
    }

    std::vector<unsigned char> decompressData(const std::vector<int> &compressed)
    {
        std::unordered_map<int, std::string> dictionary;
        for (int i = 0; i < 256; ++i)
        {
            dictionary[i] = std::string(1, i);
        }

        std::string w(1, static_cast<char>(compressed[0]));
        std::vector<unsigned char> decompressedOutput(w.begin(), w.end());
        int dictSize = 256;

        for (size_t i = 1; i < compressed.size(); ++i)
        {
            int k = compressed[i];
            std::string entry;
            if (dictionary.count(k))
            {
                entry = dictionary[k];
            }
            else if (k == dictSize)
            {
                entry = w + w[0];
            }
            else
            {
                throw std::runtime_error("Invalid compressed code.");
            }

            decompressedOutput.insert(decompressedOutput.end(), entry.begin(), entry.end());

            dictionary[dictSize++] = w + entry[0];
            w = entry;
        }

        return decompressedOutput;
    }

    bool compress(const std::string &inputFilePath, const std::string &outputFilePath)
    {
        std::ifstream inputFile(inputFilePath, std::ios::binary);
        if (!inputFile)
        {
            std::cerr << "Unable to open input file: " << inputFilePath << std::endl;
            return false;
        }

        std::vector<unsigned char> inputData((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
        inputFile.close();

        std::vector<int> compressedData = compressData(inputData);

        std::ofstream outputFile(outputFilePath, std::ios::binary);
        if (!outputFile)
        {
            std::cerr << "Unable to open output file: " << outputFilePath << std::endl;
            return false;
        }

        for (int code : compressedData)
        {
            outputFile.write(reinterpret_cast<const char *>(&code), sizeof(code));
        }
        outputFile.close();

        std::cout << "Compression complete: " << outputFilePath << std::endl;
        return true;
    }

    bool decompress(const std::string &inputFilePath, const std::string &outputFilePath)
    {
        std::ifstream inputFile(inputFilePath, std::ios::binary);
        if (!inputFile)
        {
            std::cerr << "Unable to open input file: " << inputFilePath << std::endl;
            return false;
        }

        std::vector<int> compressedData;
        int code;
        while (inputFile.read(reinterpret_cast<char *>(&code), sizeof(code)))
        {
            compressedData.push_back(code);
        }
        inputFile.close();

        try
        {
            std::vector<unsigned char> decompressedData = decompressData(compressedData);

            std::ofstream outputFile(outputFilePath, std::ios::binary);
            if (!outputFile)
            {
                std::cerr << "Unable to open output file: " << outputFilePath << std::endl;
                return false;
            }

            outputFile.write(reinterpret_cast<const char *>(decompressedData.data()), decompressedData.size());
            outputFile.close();

            std::cout << "Decompression complete: " << outputFilePath << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Decompression error: " << e.what() << std::endl;
            return false;
        }

        return true;
    }

} // namespace lzw
