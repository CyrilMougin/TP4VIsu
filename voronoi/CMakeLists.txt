add_library(build
	beach_line.cpp
	beach_line.h
	edge.h
	event.h
	point.h		
	voronoi.cpp
	voronoi.h		)
	
target_include_directories(build
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		${Boost_INCLUDE_DIRS}
)