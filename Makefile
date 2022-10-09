$(CC) = gcc
$(CXX) = gcc

target = cpkg
api_obj = 
lib_obj = ab_socket.o

${target} : main.o ${api_obj} ${lib_obj}
	CC ${obj} -o ${target}

main.o : main.c
	CC -c main.c -o main.o

ab_socket.o : ab_socket.c
	CC -c ab_socket.c -o ab_socket.o