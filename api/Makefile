obj_dir = $(api_dir)/obj
obj = cpkg_api.o


all : $(obj)

cpkg_api.o : $(obj_dir) cpkg_api.c
	$(CC) -c cpkg_api.c -I $(lib_dir) -o $(obj_dir)/cpkg_api.o 

$(obj_dir) :
	mkdir -p $(obj_dir);