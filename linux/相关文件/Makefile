#thread_customer.o:thread_customer.c
#	gcc -I../include/ -Wall -g -c $<

SOURCE=$(wildcard *.c)
TARGET=$(patsubst %.c,%.o,$(SOURCE))

POOL_SERVER_START:$(TARGET)
	gcc $^ -lpthread -o $@

%.o:%.c
	gcc -I../include/ -Wall -g -c $<

clean:
	rm POOL_SERVER_START -rf
	rm $(TARGET) -rf
