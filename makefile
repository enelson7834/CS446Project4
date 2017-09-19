CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

p1:	ConfigFileInputNode.o ConfigFileInput.o main.o
	$(CC) $(LFLAGS) ConfigFileInputNode.o ConfigFileInput.o main.o -o p1
ConfigFileInput.o: ConfigFileInput.hh ConfigFileInput.cc ConfigFileInputNode.hh LinkedList.hh
	$(CC) $(CFLAGS) ConfigFileInput.cc
ConfigFileInputNode.o:	ConfigFileInputNode.cc ConfigFileInputNode.hh
	$(CC) $(CFLAGS) ConfigFileInputNode.cc
main.o:	main.cpp ConfigFileInputNode.hh 
	$(CC) $(CFLAGS) main.cpp