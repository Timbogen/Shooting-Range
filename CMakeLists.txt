cmake_minimum_required(VERSION 3.17)
project(ShootingRange)

# Include the conan libraries
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Add executable target and link the libraries
file(COPY rsc DESTINATION ${CMAKE_BINARY_DIR}/bin)
include_directories(include)
file(GLOB_RECURSE SOURCE "src/*.cpp" "include/*.h")
add_executable(${PROJECT_NAME} ${SOURCE} include/console/Interpreter.h src/console/Interpreter.cpp include/console/Command.h src/console/Command.cpp)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
