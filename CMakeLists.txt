# cmake_minimum_required(VERSION 3.30)

# set(projectName run)
# set(CMAKE_CXX_FLAGS "-std=c++20")

# project(${projectName})

# find_package(SDL2 REQUIRED COMPONENTS SDL2)
# add_executable(${projectName} main.cpp)
# target_link_libraries(${projectName} PRIVATE SDL2::SDL2)

cmake_minimum_required(VERSION 3.22)

set(projectName run)

project(${projectName})
set(CMAKE_CXX_STANDARD 20)  # Use C++11 (or 14/17/20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)    # 强制要求
set(CMAKE_CXX_EXTENSIONS OFF)          # 不用 gnu++17，而是严格 c++17
set(CMAKE_OSX_ARCHITECTURES "arm64")


find_package(PkgConfig REQUIRED)

# 关键：加 IMPORTED_TARGET
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(EIGEN3 REQUIRED IMPORTED_TARGET eigen3)

add_executable(${projectName} 
    main.cpp
    class.cpp
    func.cpp
)
# 直接链接到 pkg-config 生成的 IMPORTED target
target_link_libraries(${projectName} PRIVATE PkgConfig::SDL2 PkgConfig::EIGEN3)