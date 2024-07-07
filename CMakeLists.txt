cmake_minimum_required(VERSION 3.10)

# Project name
project(Chess)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# file(GLOB STOCKFISH_SOURCES
#     external/Stockfish/src/*.cpp
#     external/Stockfish/src/syzygy/*.cpp
#     external/Stockfish/src/nnue/*.cpp
# )
# add_library(stockfish STATIC ${STOCKFISH_SOURCES})
# target_include_directories(stockfish PRIVATE external/Stockfish/src)

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

# Include directories
include_directories(
    include
    # external/Stockfish/src
    # external/Stockfish/src/syzygy
    # external/Stockfish/src/nnue
)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Add executable for stockfish
# add_executable(Stockfish ${STOCKFISH_SOURCES})
# target_include_directories(Stockfish PRIVATE external/Stockfish/src)

# Add executable for the main Chess project (assuming this is your main project)
add_executable(Chess ${SOURCES})
target_include_directories(Chess PRIVATE ${PROJECT_SOURCE_DIR}/include)
# target_link_libraries(Chess PRIVATE stockfish)

# Server executable
add_executable(server networking/server.cpp)
target_include_directories(server PRIVATE ${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})
target_link_libraries(server 
    PRIVATE ${Boost_LIBRARIES} 
    OpenSSL::SSL OpenSSL::Crypto
    # PRIVATE stockfish
)

# Client executable
add_executable(client networking/client.cpp)
target_include_directories(client PRIVATE ${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})
target_link_libraries(client 
    PRIVATE ${Boost_LIBRARIES} 
    OpenSSL::SSL OpenSSL::Crypto
    # PRIVATE stockfish
)

if(WIN32)
    target_link_libraries(server PRIVATE wsock32 ws2_32)
    target_link_libraries(client PRIVATE wsock32 ws2_32)
endif()
