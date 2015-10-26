//cliente
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SERV_ADDR 1981
//(IPPORT_RESERVED+1)
#define DATA "##--##--##----***----##--##--##"
void main(int argc, char** argv)
{
int sock;
struct sockaddr_in server;
struct hostent *hp, *gethostbyname();
if(argc < 2) {
printf("Uso: %s nombre_host\n",argv[0]);
exit(1);
}
sock= socket (PF_INET, SOCK_STREAM,0);
if(sock < 0){
perror("No se ha podido conseguir un socket :(");
exit(1);
}
server.sin_family=AF_INET;
hp=gethostbyname(argv[1]);
if(hp==0){
fprintf(stderr, "%s: No conozco a esa compu\n",argv[1]);
exit(2);
}
memcpy((char *)&server.sin_addr, (char *)hp->h_addr,hp->h_length);
server.sin_port=htons(SERV_ADDR);
if (connect(sock, (struct sockaddr *)&server,sizeof (server))<0){
perror("Conexion no aceptada!!!!");
exit(1);
}
if (write(sock, DATA,strlen(DATA)+1)<0)
perror("No he podido escribir el mensaje");
close(sock);
exit(0);
}