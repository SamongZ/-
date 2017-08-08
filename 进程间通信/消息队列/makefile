all : msg_rcv msg_snd

msg_rcv : msg_rcv.o
	g++ -g -o msg_rcv msg_rcv.o
msg_snd : msg_snd.o
	g++ -g -o msg_snd msg_snd.o
msg_rcv.o : msg_rcv.cpp
	g++ -g -c msg_rcv.cpp
msg_snd.o : msg_snd.cpp
	g++ -g -c msg_snd.cpp

clear:
	rm -rf *.o msg_rcv msg_snd
