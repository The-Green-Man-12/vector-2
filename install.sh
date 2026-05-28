#!/bin/bash
set -e

echo "Downloading C++ file..."
curl -sSL https://raw.githubusercontent.com/The-Green-Man-12/vector-2/refs/heads/main/main.cpp -o main.cpp

echo "Compiling project..."
g++ main.cpp -o vector-2

echo "Running program..."
./vector-2
