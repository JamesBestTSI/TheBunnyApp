# Set minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Set the project_name and version
project(BunnyApp VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(BunnyApp src/main.cpp src/Bunny.cpp src/BunnyManager.cpp)

# Add the targeted cpp features
target_compile_features(BunnyApp PUBLIC cxx_std_20)
