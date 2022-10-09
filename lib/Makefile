CC = gcc
CXX = gcc
AR = ar

target = cpkg-lib.a
obj_dir = obj
obj = ab_socket.o link_layer.o ip_layer.o

$(target) : $(obj)
	mkdir -p $(obj_dir)
	$(AR) rcs $(target) $(obj_dir)/*.o

ab_socket.o : ab_socket.c
	$(CC) -c ab_socket.c -o $(obj_dir)/ab_socket.o

link_layer.o : link_layer.c
	$(CC) -c link_layer.c -o $(obj_dir)/link_layer.o

ip_layer.o : ip_layer.c 
	$(CC) -c ip_layer.c -o $(obj_dir)/ip_layer.o 

