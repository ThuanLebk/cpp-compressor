#ifndef LZW_H
#define LZW_H

#include "main.h"

namespace lzw
{ /**
   * @brief Compresses a file using the LZW algorithm.
   *
   * @param inputFilePath Path to the input file to be compressed.
   * @param outputFilePath Path to the output compressed file.
   * @return true if compression was successful, false otherwise.
   */
    bool compress(const std::string &inputFilePath, const std::string &outputDirPath);

    /**
     * @brief Decompresses a file using the LZW algorithm.
     *
     * @param inputFilePath Path to the input compressed file.
     * @param outputFilePath Path to the output decompressed file.
     * @param extension The extension for the decompressed file (default is "bin").
     * @return true if decompression was successful, false otherwise.
     */
    bool decompress(const std::string &inputFilePath, const std::string &outputDirPath);

    /**
     * @brief Decompresses a vector of compressed data.
     *
     * @param compressedData Vector of compressed data.
     * @return Vector of decompressed data.
     */
    std::vector<int> compressData(const std::vector<unsigned char> &input);

    /**
     * @brief Decompresses a vector of compressed data.
     *
     * @param compressedData Vector of compressed data.
     * @return Vector of decompressed data.
     */
    std::vector<unsigned char> decompressData(const std::vector<int> &compressed);
}

#endif // LZW_H