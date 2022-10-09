export CC = gcc
export CXX = gcc
export AR = ar

target = cpkg
export api_dir = $(shell pwd)/api
export lib_dir = $(shell pwd)/lib
api = cpkg-api
lib = cpkg-lib

${target} : main.o libcpkg.a
	$(CC) main.o -L . -lcpkg -o ${target}

main.o : main.c
	$(CC) -c main.c -I $(api_dir) -I $(lib_dir) -o main.o

libcpkg.a : ${api} ${lib}
	$(AR) rc libcpkg.a $(api_dir)/obj/*.o $(lib_dir)/obj/*.o

$(api) :
	make -C api

$(lib) : 
	make -C lib

.PHONY : clean

clean :
	bash -c "cd $(api_dir)/obj; rm -f *.o;"
	bash -c "cd $(lib_dir)/obj; rm -f *.o;"
	bash -c "rm main.o; rm libcpkg.a"
