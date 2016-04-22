#include "client.h"

/**
 * Function that sets the field addr->sin_addr.s_addr from a host name 
 * address.
 * @param addr struct where to set the address.
 * @param host the host name to be converted
 * @return -1 if there has been a problem during the conversion process.
 */
int setaddrbyname(struct sockaddr_in *addr, char *host)
{
  struct addrinfo hints, *res;
  int status;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM; 
 
  if ((status = getaddrinfo(host, NULL, &hints, &res)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    return -1;
  }
  
  addr->sin_addr.s_addr = ((struct sockaddr_in *)res->ai_addr)->sin_addr.s_addr;
  
  freeaddrinfo(res);
    
  return 0;  
}

/**
 * Returns the port specified as an application parameter or the default port
 * if no port has been specified.
 * @param argc the number of the application arguments.
 * @param an array with all the application arguments.
 * @return  the port number from the command line or the default port if 
 * no port has been specified in the command line. Returns -1 if the application
 * has been called with the wrong parameters.
 */
int getPort(int argc, char* argv[])
{
  int param;
  int port = DEFAULT_PORT;

  optind=1;
  // We process the application execution parameters.
	while((param = getopt(argc, argv, "h:p:")) != -1){
		switch((char) param){
		  case 'h': break;
			case 'p':
			  // We modify the port variable just in case a port is passed as a 
			  // parameter
				port = atoi(optarg);
				break;
			default:
				printf("Parametre %c desconegut\n\n", (char) param);
				port = -1;
		}
	}
	
	return port;
}

/**
 * Returns the host name where the server is running.
 * @param argc the number of the application arguments.
 * @param an array with all the application arguments.
 * @Return Returns the host name where the server is running.<br />
 * Returns null if the application has been called with the wrong parameters.
 */
char * getHost(int argc, char* argv[])
{
  char * hostName = NULL;
  int param;
  
  optind=1;
    // We process the application execution parameters.
	while((param = getopt(argc, argv, "h:p:")) != -1){
		switch((char) param){
			case 'p': break;
			case 'h':
        hostName = (char*) malloc(sizeof(char)*strlen(optarg)+1);
				// Un cop creat l'espai, podem copiar la cadena
				strcpy(hostName, optarg);
				break;
			default:
				printf("Parametre %c desconegut\n\n", (char) param);
				hostName = NULL;
		}
	}
	
	printf("in getHost host: %s\n", hostName); //!!!!!!!!!!!!!!
	return hostName;
 }

void print_menu()
{
	printf("Browser menu: \n");
    printf(" 1.Peticio GET\n");
	printf(" 6.Sortir\n");
	printf("\n");
    printf("Selecciona una opcio: ");
}

void process_get_operation(int sock, char *hostName)
{
	char *buffer_out = malloc(MAX_REQUEST_SIZE);
	char *buffer_in = malloc(MAX_RESPONSE_SIZE);
    //char *ruta = malloc(MAX_PATH_SIZE);
	//printf("Introdueixi una ruta: \n");
	//scanf("%s", ruta);
    sprintf(buffer_out, "GET / HTTP/1.1\r\nHost: %s\r\n\r\n", hostName);
	send(sock, buffer_out, MAX_REQUEST_SIZE, 0);
		
	recv(sock, buffer_in, MAX_RESPONSE_SIZE, 0);
    printf("%s\n", buffer_in);

    //free(buffer_in); free(buffer_out);//free(ruta);
}


void process_exit_operation(int sock)
{
	close(sock);
	exit(0);
}


void process_menu_option(int s, char *hostName, int menu_option)
{
	switch(menu_option){
  		case MENU_OP_GET:
			process_get_operation(s, hostName);
			break;
        case MENU_OP_EXIT:
            process_exit_operation(s);
		default:
			printf("Invalid menu option\n");
	}
}

/**
 * Main
 */
int main(int argc, char *argv[]){

	int s, port;
    int menu_option = 0;
    char *hostName;
    struct sockaddr_in server;

	port = getPort(argc, argv);
	hostName = getHost(argc, argv);

	//Create socket
	s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(s < 0){
	perror("Could not create socket\n");
	return -1;
	}

	//Sockaddr_in strcuture
	server.sin_family = PF_INET;
	setaddrbyname(&server, hostName);
	server.sin_port = htons(port);

	if(connect(s, (struct sockaddr *)&server, sizeof(server)) < 0){
		perror("ERROR: Connected failed\n");
		return 1;
	}
	printf("Connected\n");

	do{
		print_menu();
		// getting the user input.
		scanf("%d",&menu_option);
		printf("\n\n"); 
	 	process_menu_option(s, hostName, menu_option);

  	}while(menu_option != MENU_OP_EXIT); //end while(opcio)

    



	return 1;
}
