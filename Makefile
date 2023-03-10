# OBJS   代替  依赖文件
# CC     代替  gcc
# CFLAGS 代替  编译命令

# g++  ./main_client.cpp ./Client.cpp -o client
# g++  ./main_server.cpp ./Server.cpp -o server
OBJS=main.o server.o client.o
CC=g++
CFLAGS=-c -Wall -g

demo:$(OBJS)
	$(CC) $(OBJS) -o demo
main.o:main.cpp
	$(CC) main.cpp $(CFLAGS)  -o main.o
server.o:Server.cpp
	$(CC) Server.cpp $(CFLAGS) -o server.o
client.o:Client.cpp
	$(CC) Client.cpp $(CFLAGS) -o client.o

clean:
	rm *.o demo 
