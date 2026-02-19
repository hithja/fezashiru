CXX := g++
CXX_FLAGS := -Iimgui -Iinclude -I/usr/local/include -L/usr/local/lib -lglfw3 -lGL -lpthread -llua
SRC := src/*.cpp src/*/*.cpp src/*/*/*.cpp
IMGUI_SRC :=  imgui/*.cpp imgui/misc/cpp/imgui_stdlib.cpp
GLAD_SRC := glad.c

default:
	$(CXX) $(SRC) $(GLAD_SRC) $(IMGUI_SRC) $(CXX_FLAGS) -o main