all: warchief

warchief: src/*
	g++ src/*.cc -lglut -lGL -lGLU -o warchief

.PHONY: all clean

clean:
	rm -f warchief
