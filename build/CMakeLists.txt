add_library(build
	beach_line.cpp
	binary_search_tree.cpp
	glad/glad.c
	utils.cpp		)
	
target_include_directories(build
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		${Boost_INCLUDE_DIRS}
)