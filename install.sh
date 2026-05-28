#!/bin/bash

# 1. Exit immediately if any command fails
set -e

# 2. Define the cleanup function for temporary files
cleanup() {
    echo "Cleaning up temporary files..."
    rm -f main.cpp
}
trap cleanup EXIT

# 3. Download the C++ file
echo "📥 Downloading source code..."
curl -sSO https://raw.githubusercontent.com/The-Green-Man-12/vector-2/refs/heads/main/main.cpp

# 4. Check if g++ is installed
if ! command -v g++ &> /dev/null; then
    echo "Error: g++ compiler is not installed."
    echo "Please install GCC/g++ and try again."
    exit 1
fi

# 5. Compile the program
echo "Compiling project..."
g++ main.cpp -o vector-2

# 6. Run the program
echo "Running program..."
./vector-2
