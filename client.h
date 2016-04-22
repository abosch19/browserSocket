#include <sys/socket.h>
#include <stdio.h> //scanf, printf
#include <stdlib.h> //
#include <string.h> //string
#include <netdb.h> //gethostbyname()
#include <unistd.h> //opt,args

#define MAX_RESPONSE_SIZE 1024*40
#define MAX_REQUEST_SIZE 40
#define MAX_PATH_SIZE 30

#define MENU_OP_GET 1
#define MENU_OP_EXIT 6

#define DEFAULT_PORT 80


/*
int setaddrbyname(struct sockaddr_in *addr, char *host);

int getPort(int argc, char* argv[]);

char * getHost(int argc, char* argv[])

void print_menu();

void process_get_operation(int sock);

void process_exit_operation(int sock);*/
