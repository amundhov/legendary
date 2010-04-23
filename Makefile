OBJS=engine.o msg.o glrender.o cube.o material.o rtt.o
CC=g++
CFLAGS=-c -DGLEW_STATIC  -g
WIN_LFLAGS=-mwindows -g
WIN_LIBS=-lglew32s -lopengl32
LIN_LFLAGS=-g
LIN_LIBS=-lX11 -lGLEW

Legendary.exe : $(OBJS) win.o
	$(CC) $(WIN_LFLAGS) $(OBJS) win.o $(WIN_LIBS) -o $@

legendary : $(OBJS) linux.o
	$(CC) $(LIN_LFLAGS) linux.o $(OBJS) $(LIN_LIBS) -o $@

engine.o : engine.cpp engine.h
	$(CC) $(CFLAGS) -o $@ engine.cpp
	
win.o : win.cpp engine.h win.h
	$(CC) $(CFLAGS) -o $@ win.cpp

material.o : material.cpp material.h
	$(CC) $(CFLAGS) -o $@ material.cpp
	
rtt.o : rtt.cpp rtt.h
	$(CC) $(CFLAGS) -o $@ rtt.cpp

linux.o : linux.cpp engine.h linux.h
	$(CC) $(CFLAGS) -o $@ linux.cpp
	
glrender.o : glrender.cpp glrender.h
	$(CC) $(CFLAGS) -o $@ glrender.cpp

cube.o : cube.cpp cube.h material.h rtt.h
	$(CC) $(CFLAGS) -o $@ cube.cpp
	
msg.o : msg.cpp msg.h
	$(CC) $(CFLAGS) -o $@ msg.cpp
	
clean:
	rm *.o Legendary.exe legendary debug.log


linux : legendary
.PHONY: linux
.PHONY: clean
