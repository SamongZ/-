all : reader writer

reader : reader.o
	g++ -g -o reader reader.o
writer : writer.o
	g++ -g -o writer writer.o

reader.o : reader.cpp
	g++ -g -c reader.cpp
writer.o : writer.cpp
	g++ -g -c writer.cpp

clear:
	rm -rf *.o reader writer
