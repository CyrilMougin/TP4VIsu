all:main

main:
	g++ main.cpp utils.cpp beach_line.cpp binary_search_tree.cpp glad/glad.c -lglfw -lGL -lX11 -lpthread -lXrandr -ldl -o TP3_exe
clean:
	rm TP3_exe
