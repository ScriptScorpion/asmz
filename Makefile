CC := g++
CCF := -std=c++17 -O1
SOURCE := src/main.cpp src/compilation.cpp
OUTPUT := asmz 
default:
	@echo "select 1 option: install or compile"
install:
	@$(CC) $(CCF) $(SOURCE) -o $(OUTPUT)
	@cp -r $(OUTPUT) /usr/local/bin/
	@rm $(OUTPUT)

compile:
	@$(CC) $(CCF) $(SOURCE) -o $(OUTPUT)
