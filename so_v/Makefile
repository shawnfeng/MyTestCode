# link 过程使用的名字 linkname
SO_LINK_NAME=libhello.so
SO_LINK_NAME_WORLD=libworld.so
# 执行过程中，程序应用库使用的名字，带库的主版本号 soname
# 如果执行过程中找不到这个库，会报
# error while loading shared libraries: libhello.so.0: cannot open shared object file: No such file or directory
SO_SONAME=$(SO_LINK_NAME).0
SO_SONAME_WORLD=$(SO_LINK_NAME_WORLD).0
# 库真正的名字 filename
SO_REAL_NAME=$(SO_SONAME).0.0
SO_REAL_NAME_WORLD=$(SO_SONAME_WORLD).0.0

# 在程序使用so的过程中替换so，会马上生效吗？
# 直接进行cp覆盖， Segmentation fault 了
# rm + cp 不崩溃， 替换的so不会生效，需要重新启动程序
# mv 不崩溃，替换的so不会生效，需要重新启动程序
# ==================================================
# .a .so测试部分
STLIB=libhello.a


# ==================================================
# 查看对库的依赖 ldd 之
MAINEXE=hw0
MAINSCRIP=$(MAINEXE).sh

# 用于测试链接.a/.so
MAIN_SH_ST=hw1
MAIN_ST=hw2

CC=gcc
CCFLAGS=-c -Wall -g -fPIC
SHAREFLAG=-shared
AR=ar
RANLIB=ranlib
ARFLAGS=-crv
# gcc 传递给链接器的参数，指定库的版本号 readelf -d *.so 查看之
LINKFLAG=-Wl,-soname,$(SO_SONAME)

BECLEAN=*.o *~ *.a

all:$(SO_LINK_NAME_WORLD) $(SO_LINK_NAME) $(MAINSCRIP) 

# 不编译libworld
# 这时候会发现报以下错误
# gcc -o hw main.o   -lhello -lworld -L.
# /usr/bin/ld: cannot find -lworld
# collect2: ld returned 1 exit status
# make: *** [hw] Error 1
# 虽然main中没有用到world也是需要这个库的
# 但是运行时候是不许要这个world库的，虽然加了-lworld，我们可以运行测试，或者readelf发现
all_exp_world:$(SO_LINK_NAME) $(MAINSCRIP) 
all_sh_st:$(MAIN_SH_ST)
all_st:$(MAIN_ST)

$(MAINSCRIP):$(MAINEXE)
	echo "#!/bin/sh" > $(MAINSCRIP)
	echo "export LD_LIBRARY_PATH='`pwd`'" >> $(MAINSCRIP)
	echo "./$(MAINEXE)" >> $(MAINSCRIP)
	chmod 700 $(MAINSCRIP)

# -lhello -L. -->链接的库，链接过程完成的，即使程序咩有真正用到这个库，也需要提供这个so
# 注意这里不能加-shared参数，-shared使用来生成动态库的，否则会报：
# Segmentation fault
$(MAINEXE):main.o
	$(CC) -o $(MAINEXE) main.o   -lhello -lworld -L.

# 只有.a则直接使用.a了
# 有so时候则先用so ，test：make   然后make all_sh_st
$(MAIN_SH_ST):$(STLIB) main.o
	$(CC) -o $(MAIN_SH_ST) main.o   -lhello -L.
# 不能用以下的方式直接引用
# /usr/bin/ld: cannot find -llibhello.a
# collect2: ld returned 1 exit status
#	$(CC) -o $(MAIN_SH_ST) main.o   -llibhello.a -L.

# 这种方式没有增加-l参数使用了.a和直接放.o没有什么区别
# 所以这种情况不管有没有so 都是使用的.a的
$(MAIN_ST):$(STLIB) main.o
	$(CC) -o $(MAIN_ST) main.o $(STLIB)

main.o:main.cpp hello.h
	$(CC) $(CCFLAGS) main.cpp

# 如果把hello.cpp中的hello函数实现去掉会报以下错误
# main.o: In function `main_hello()':
# /home/shawn/Ubuntu One/code.test/task/so_v/main.cpp:7: undefined reference to `hello()'
# collect2: ld returned 1 exit status
# make: *** [hw] Error 1
# 也就是会检查的
hello.o:hello.cpp hello.h
	$(CC) $(CCFLAGS) hello.cpp

world.o:world.cpp world.h
	$(CC) $(CCFLAGS) world.cpp


$(SO_REAL_NAME):hello.o
	$(CC) -o $(SO_REAL_NAME) $(SHAREFLAG) $(LINKFLAG) hello.o

$(SO_REAL_NAME_WORLD):world.o
	$(CC) -o $(SO_REAL_NAME_WORLD) $(SHAREFLAG) $(LINKFLAG) world.o

$(STLIB):hello.o
	$(AR) $(ARFLAGS) $(STLIB) hello.o
	$(RANLIB) $(STLIB)

$(SO_SONAME):$(SO_REAL_NAME)
	rm -f $(SO_SONAME)
	ln -s  $(SO_REAL_NAME) $(SO_SONAME)

$(SO_SONAME_WORLD):$(SO_REAL_NAME_WORLD)
	rm -f $(SO_SONAME_WORLD)
	ln -s  $(SO_REAL_NAME_WORLD) $(SO_SONAME_WORLD)


$(SO_LINK_NAME):$(SO_SONAME)
	rm -f $(SO_LINK_NAME)
	ln -s  $(SO_SONAME) $(SO_LINK_NAME)


$(SO_LINK_NAME_WORLD):$(SO_SONAME_WORLD)
	rm -f $(SO_LINK_NAME_WORLD)
	ln -s  $(SO_SONAME_WORLD) $(SO_LINK_NAME_WORLD)


.PHONY: clean cleanall
clean:
	rm -f $(BECLEAN)
cleanall:
	rm -f $(SO_SONAME) $(SO_LINK_NAME) $(SO_REAL_NAME) $(SO_SONAME_WORLD) $(SO_LINK_NAME_WORLD) $(SO_REAL_NAME_WORLD) $(MAINEXE) $(MAIN_SH_ST) $(MAIN_ST) $(MAINSCRIP) $(BECLEAN)