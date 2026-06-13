CC := g++
CCF := -std=c++17 -O1 -s
SOURCE := src/main.cpp src/compilation.cpp
OUTPUT := asmz 
default:
	@echo "select 1 option: install or compile"
install:
	@$(CC) $(CCF) $(SOURCE) -o $(OUTPUT)
	@mv $(OUTPUT) /usr/local/bin/

compile:
	@$(CC) $(CCF) $(SOURCE) -o $(OUTPUT)
