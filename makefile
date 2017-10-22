OBJS = MetaDataInfo.o ConfigFileInput.o main.o
FILESET = ConfigFileInput.hh ConfigFileInput.cc MetaDataInfo.hh MetaDataInfo.cc main.cpp
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

Sim01: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o Sim01 -lpthread
ConfigFileInput.o: ConfigFileInput.hh ConfigFileInput.cc
	$(CC) $(CFLAGS) ConfigFileInput.cc
MetaDataInfo.o: MetaDataInfo.hh MetaDataInfo.cc ConfigFileInput.hh PCB.hh MemoryFunction.hh 
	$(CC) $(CFLAGS) MetaDataInfo.cc
main.o:	main.cpp ConfigFileInput.hh  MetaDataInfo.hh PCB.hh
	$(CC) $(CFLAGS) main.cpp
Sim01_NelsonEugene.tar.gz: $(FILESET) MemoryFunction.hh PCB.hh makefile
	tar -cvzf $@ $^
clean:
	rm *.o Sim01
