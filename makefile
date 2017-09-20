CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

p1:	MetaDataInfo.o MetaDataInfoNode.o ConfigFileInputNode.o ConfigFileInput.o main.o
	$(CC) $(LFLAGS) ConfigFileInputNode.o ConfigFileInput.o MetaDataInfo.o MetaDataInfoNode.o main.o -o p1
ConfigFileInput.o: ConfigFileInput.hh ConfigFileInput.cc ConfigFileInputNode.hh LinkedList.hh
	$(CC) $(CFLAGS) ConfigFileInput.cc
ConfigFileInputNode.o:	ConfigFileInputNode.cc ConfigFileInputNode.hh
	$(CC) $(CFLAGS) ConfigFileInputNode.cc
MetaDataInfoNode.o: MetaDataInfoNode.hh MetaDataInfoNode.cc
	$(CC) $(CFLAGS) MetaDataInfoNode.cc
MetaDataInfo.o: MetaDataInfo.hh MetaDataInfo.cc MetaDataInfoNode.hh LinkedQueue.hh ConfigFileInput.hh
	$(CC) $(CFLAGS) MetaDataInfo.cc
main.o:	main.cpp ConfigFileInput.hh  MetaDataInfo.hh
	$(CC) $(CFLAGS) main.cpp