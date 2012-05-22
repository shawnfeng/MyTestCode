CC=gcc
CCFLAGS=-c -Wall -g -fPIC
SHAREFLAG=-shared
AR=ar
RANLIB=ranlib
ARFLAGS=-crv

BECLEAN=*.o *~ *.a


ZOOKEEPERLIB=zookeeper_mt
ZOOKEEPERLIBPATH=/home/shawn/soft.compile/root/zookeeper-3.3.5-c/lib
ZOOKEEPERINCLUDE=/home/shawn/soft.compile/root/zookeeper-3.3.5-c/include/c-client-src

all:service

service:service.o
	$(CC) -o service service.o -L$(ZOOKEEPERLIBPATH) -l$(ZOOKEEPERLIB)

service.o:service.cc service.h
	$(CC) $(CCFLAGS) service.cc -I$(ZOOKEEPERINCLUDE)


.PHONY: clean cleanall
clean:
	rm -f $(BECLEAN)
cleanall:
	rm -f $(BECLEAN)