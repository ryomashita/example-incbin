cmake_minimum_required(VERSION 3.10)
project(example-incbin C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Create executable
add_executable(incbin_demo
    src/main.c
)

# Ensure the sample.txt file is copied to the build directory
configure_file(sample.txt sample.txt COPYONLY)
