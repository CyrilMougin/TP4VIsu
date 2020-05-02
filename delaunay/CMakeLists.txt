add_library(delaunay
    delaunay.cpp
    delaunay.h
    edge.h
    point.h
    quadrilateral.h
	triangle.cpp
    triangle.h		)

target_include_directories(delaunay
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		${Boost_INCLUDE_DIRS}
)