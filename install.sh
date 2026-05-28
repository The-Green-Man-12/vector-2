#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

echo "🔍 Checking your system profile..."

# Function to check and install g++ on Linux/macOS
ensure_compiler() {
    if command -v g++ &> /dev/null; then
        echo "✅ g++ compiler is already installed."
        return 0
    fi

    echo "⚠️ g++ not found. Attempting to install..."

    # Detect Operating System
    OS="$(uname -s)"
    case "${OS}" in
        Linux*)
            if command -v apt-get &> /dev/null; then
                echo "📦 Debian/Ubuntu detected. Installing build-essential..."
                sudo apt-get update && sudo apt-get install -y build-essential
            elif command -v dnf &> /dev/null; then
                echo "📦 Fedora/RHEL detected. Installing Development Tools..."
                sudo dnf groupinstall -y "Development Tools"
            else
                echo "❌ Unsupported Linux package manager. Please install g++ manually."
                exit 1
            fi
            ;;
        Darwin*)
            echo "🍏 macOS detected. Installing Command Line Tools..."
            xcode-select --install
            echo "📢 Please follow the macOS prompt to finish installing. Re-run this script afterward."
            exit 0
            ;;
        *)
            echo "❌ OS environment not recognized. Please install g++ manually."
            exit 1
            ;;
    esac
}

# 1. Check and install compiler
ensure_compiler

# 2. Download the C++ file
echo "📥 Downloading source code..."
curl -sSL https://githubusercontent.com -o main.cpp

# 3. Compile the program
echo "🔨 Compiling project..."
g++ main.cpp -o vector_app

# 4. Run the program
echo "🚀 Running program..."
./vector_app
