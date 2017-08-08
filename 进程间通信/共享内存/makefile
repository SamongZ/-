all : consumer producer

consumer : consumer.o
	g++ -g -o consumer consumer.o
producer : producer.o
	g++ -g -o producer producer.o

consumer.o : consumer.cpp shm_com.h
	g++ -g -c consumer.cpp
producer.o : producer.cpp shm_com.h
	g++ -g -c producer.cpp

clear:
	rm -rf *.o consumer producer
