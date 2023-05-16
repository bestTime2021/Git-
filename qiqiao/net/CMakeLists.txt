cmake_minimum_required(VERSION 3.10)

project(Demo)

########################
set(SRC_Files
	Channel.cc
	Poller.cc
	EventLoop.cc
   )
add_library(lib ${SRC_Files})

########################
add_executable(demo test.cc)
target_link_libraries(demo lib)

