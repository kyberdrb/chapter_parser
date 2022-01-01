cmake_minimum_required(VERSION 3.17)
project(chapter_data_extractor)

set(CMAKE_CXX_STANDARD 14)

add_executable(chapter_data_extractor main.cpp Chapter.cpp Chapter.h Session.cpp Session.h Parser.cpp Parser.h Sessions.cpp Sessions.h App.cpp App.h)
