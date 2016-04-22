CC = gcc
CFLAGS = -Wall

all: rConfApp
	
rConfApp: 
	$(CC) $(CFLAGS) client.c -o client
			
clean:
	rm client

					
					
