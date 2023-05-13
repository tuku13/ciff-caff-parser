cmake_minimum_required(VERSION 3.25)
project(ciff_caff_parser)

set(CMAKE_CXX_STANDARD 23)

add_executable(parser main.cpp Caff.cpp Caff.h FileFormatException.h utils.h)
