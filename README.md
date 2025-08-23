# Quantum Cipher Project

A C++ implementation of a quantum-inspired binary cipher that transforms binary sequences using randomized bit-pair substitution.

## Overview

This project implements a cipher system that:
- Reads binary sequences from text files
- Uses random number generation to select bit-pair substitutions
- Converts encrypted binary sequences to decimal output
- Supports different modulo operations (128 and 64)

## Project Structure

```
Quantum/
├── CMakeLists.txt          # CMake build configuration
├── main.cpp                # Main program entry point
├── .gitignore              # Git ignore file
├── src/
│   └── chunk.h             # Header file containing cipher implementation
└── bitFiles/               # Directory containing cipher data files
    ├── flip.txt            # Bit-pair substitution lookup table
    ├── binSeq.txt          # Input binary sequences
    ├── binAlt.txt          # Alternative binary sequences
    ├── backup.txt          # Temporary backup file
    └── temp.txt            # Temporary processing file
```

## Prerequisites

- **C++ Compiler**: Supporting C++20 standard
- **CMake**: Version 3.30 or higher

### Required System Libraries
- `<fstream>` - File I/O operations
- `<cmath>` - Mathematical functions
- `<string>` - String manipulation
- `<bitset>` - Binary operations
- `<ctime>` - Time functions for random seed

## Installation & Setup

### 1. Clone the Repository
```bash
git clone <your-repo-url>
cd Quantum
```

### 2. Verify File Structure
Ensure your `bitFiles/` directory contains all required files:
- `flip.txt` - Must contain bit-pair combinations in format `1,0` or `0,1`
- `binSeq.txt` - Must contain binary sequences separated by spaces
- Empty files: `backup.txt`, `temp.txt`

### 3. Build the Project

#### Using CMake (Recommended)
```bash
mkdir build
cd build
cmake ..
make
```

#### Using CLion
1. Open the project folder in CLion
2. CLion will automatically detect the CMakeLists.txt
3. Build using Ctrl+F9 (Windows/Linux) or Cmd+F9 (Mac)

#### Using g++ directly
```bash
g++ -std=c++26 -o Quantum main.cpp
```

### 4. Run the Program
```bash
# If using CMake build
./build/Quantum

# If using CLion (from cmake-build-debug)
./cmake-build-debug/Quantum

# If compiled with g++
./Quantum
```

## File Specifications

### flip.txt Format
Each line should contain a bit pair separated by a comma:
```
1,0
0,1
0,1
...
```

### binSeq.txt Format
Binary sequences separated by spaces, organized in lines:
```
01010000 01101111 01101100 01111001
01110011 00100000 01110111 01100001
...
```

## How It Works

1. **Initialization**: Creates Quantum objects with different modulo values (128, 64)
2. **Random Selection**: Uses modulo arithmetic to randomly select bit-pairs from `flip.txt`
3. **Bit Substitution**: Replaces each bit in `binSeq.txt` with selected bit-pairs
4. **Processing**: Converts the modified binary sequences to decimal values
5. **Output**: Displays encrypted values as decimal numbers separated by periods

## Example Output
```
Modulo 128 Cypher:
80.111.108.121.98.105.117.
115.32.119.97.115.32.99.
111.114.114.101.99.

Modulo 64 Cypher:
[Different encrypted output based on 64-modulo selection]
```
### Key Classes
- **Abstract**: Pure virtual base class defining the cipher interface
- **Quantum**: Main implementation class handling file I/O and encryption

### Important Methods
- `createRandom()`: Generates random target for bit-pair selection
- `createPair()`: Reads and creates bit-pair from flip.txt
- `editFile()`: Performs the main encryption transformation
- `cypher()`: Orchestrates the complete encryption process

---

**Note**: This cipher is designed for educational purposes and may not provide cryptographically secure encryption for production use.
