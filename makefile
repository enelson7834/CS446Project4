OBJS = MetaDataInfo.o MetaDataInfoNode.o ConfigFileInputNode.o ConfigFileInput.o main.o
FILESET = ConfigFileInput.hh ConfigFileInput.cc ConfigFileInputNode.hh ConfigFileInputNode.cc MetaDataInfo.hh MetaDataInfo.cc MetaDataInfoNode.hh MetaDataInfoNode.cc LinkedList.hh LinkedQueue.hh Node.hh main.cpp
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

Sim01: $(OBJS)
	$(CC) $(LFLAGS) ConfigFileInputNode.o ConfigFileInput.o MetaDataInfo.o MetaDataInfoNode.o main.o -o Sim01
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
Sim01_NelsonEugene.tar.gz: $(FILESET) refman.pdf
	tar -cvzf $@ $^
clean:
	rm *.o Sim01