obj_dir = $(lib_dir)/obj
obj = ab_socket.o link_layer.o ip_layer.o mbuffer.o


all : $(obj_dir) $(obj)

ab_socket.o : ab_socket.c
	$(CC) -c ab_socket.c -o $(obj_dir)/ab_socket.o

link_layer.o : link_layer.c
	$(CC) -c link_layer.c -o $(obj_dir)/link_layer.o

ip_layer.o : ip_layer.c
	$(CC) -c ip_layer.c -o $(obj_dir)/ip_layer.o 

mbuffer.o : mbuffer.c
	$(CC) -c mbuffer.c -o $(obj_dir)/mbuffer.o

$(obj_dir) :
	mkdir -p $(obj_dir);