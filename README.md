# LZW Compressor

This project implements a basic LZW (Lempel-Ziv-Welch) compression algorithm. Below are the instructions to set up and run the project.

## Setting Up the Project

1. Clone the repository and initialize submodules:

    ```bash
    git clone https://github.com/ThuanLebk/cpp-compressor.git
    cd cpp-compressor
    ```

2. Update the `googletest` entry in `.gitmodules` file to change the URL for the googletest submodule:

    ```bash
    [submodule "googletest"]
	    path = googletest
	    url = https://github.com/google/googletest.git
    ```

3. Update the submodule with the new URL:

    ```bash
    git submodule sync
    git submodule update --init --recursive
    ```

## Building the Project

1. Navigate to the `googletest` directory and build the project:

    ```bash
    cd googletest
    cmake .
    make
    ```

2. Go back to the `build` directory at top-level:

    ```bash
    cd ..
    cd build
    ```

3. Run CMake to generate the build files and then build the project:

    ```bash
    cmake ..
    make
    ```

## Running the Tests and the Compressor

1. To run the tests:

    ```bash
    ./bin/LZWTests
    ```

2. To compress a file:

    ```bash
    ./bin/LZWCompressor [input-file-path] [output-file-path]
    ```

Replace `[input-file-path]` and `[output-file-path]` with the actual file paths.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any changes or additions.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.
