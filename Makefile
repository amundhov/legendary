OBJS=engine.o msg.o win.o glrender.o cube.o 
CC=g++
CFLAGS=-c -DGLEW_STATIC  -g
LFLAGS=-mwindows -g
LIBS=-lglew32s -lopengl32

Engine.exe : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) $(LIBS) -o $@

engine.o : engine.cpp engine.h
	$(CC) $(CFLAGS) -o $@ engine.cpp
	
win.o : win.cpp engine.h win.h
	$(CC) $(CFLAGS) -o $@ win.cpp
	
glrender.o : glrender.cpp glrender.h
	$(CC) $(CFLAGS) -o $@ glrender.cpp

cube.o : cube.cpp cube.h
	$(CC) $(CFLAGS) -o $@ cube.cpp
	
msg.o : msg.cpp msg.h
	$(CC) $(CFLAGS) -o $@ msg.cpp
	
clean:
	rm *.o Engine.exe
