add_library(delaunay
    edge.h
    point.h
	test.cpp		)

target_include_directories(delaunay
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		${Boost_INCLUDE_DIRS}
)