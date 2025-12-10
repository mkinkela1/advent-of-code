#!/bin/bash

# Script to compile and run C++ files with library support
# Usage: run_cpp.sh <directory> <filename> <filenameWithoutExt>

if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <directory> <filename> <filenameWithoutExt>"
    exit 1
fi

DIR="$1"
FILENAME="$2"
FILENAME_WITHOUT_EXT="$3"

# Change to the directory
cd "$DIR" || exit 1

# Find Z3 library path
Z3_PATH=""
if [ -d z3 ]; then
    Z3_PATH="z3"
elif [ -d ../../libs/z3 ]; then
    Z3_PATH="../../libs/z3"
elif [ -d ../libs/z3 ]; then
    Z3_PATH="../libs/z3"
elif [ -d ../../../libs/z3 ]; then
    Z3_PATH="../../../libs/z3"
fi

# Build compilation command
COMPILE_CMD="g++ -std=c++20 -O3 $FILENAME"

# Add Z3 library if found
if [ -n "$Z3_PATH" ]; then
    COMPILE_CMD="$COMPILE_CMD -I $Z3_PATH/include -L $Z3_PATH/bin -lz3 -Wl,-rpath,\"@loader_path/$Z3_PATH/bin\""
fi

COMPILE_CMD="$COMPILE_CMD -o $FILENAME_WITHOUT_EXT"

# Compile
eval "$COMPILE_CMD" || exit 1

# Fix library paths on macOS if Z3 is used
if [ -n "$Z3_PATH" ]; then
    if otool -L "$FILENAME_WITHOUT_EXT" 2>/dev/null | grep -q libz3.dylib; then
        install_name_tool -change libz3.dylib "@loader_path/$Z3_PATH/bin/libz3.dylib" "$FILENAME_WITHOUT_EXT" 2>/dev/null || true
    fi
fi

# Run the executable
./"$FILENAME_WITHOUT_EXT"

