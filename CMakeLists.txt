cmake_minimum_required(VERSION 3.5)
project(cplus_pokesnake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp GraphicsGDI.cpp Graphics.h Resources.cpp Resources.h Renderer.cpp Renderer.h Game.cpp Game.h Input.cpp Input.h Level.cpp Level.h)
add_executable(cplus_PokeSnake ${SOURCE_FILES})