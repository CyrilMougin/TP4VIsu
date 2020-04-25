cmake_minimum_required(VERSION 3.12)
project(EX4
	VERSION 1.0
	LANGUAGES C CXX
	DESCRIPTION "Client")

set(CXX_STANDARD 17)

add_subdirectory(build)

add_executable(TP4_exe main.cpp)

target_link_libraries(TP4_exe
	PRIVATE
		build
)