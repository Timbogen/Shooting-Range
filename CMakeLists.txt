cmake_minimum_required(VERSION 3.17)
project(ShootingRange)

# Set the CPP standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the conan libraries
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Add executable target and link the libraries
file(COPY rsc DESTINATION ${CMAKE_BINARY_DIR}/bin)
include_directories(include)
file(GLOB_RECURSE SOURCE "src/*.cpp" "include/*.h")
add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
