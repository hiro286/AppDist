/*Práctica 3: Programación cliente-servidor sobre TCP | UDP
Con el código visto en clases sobre servidores TCP – UDP se deberá pasar a su cuenta y compilar para verificar su funcionamiento.*/
//Servidor
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STDOUT 1
#define SERV_ADDR 1234
void main()
{
int rval;
int sock,length, msgsock;
struct sockaddr_in server;
char buf[1024];
sock=socket(PF_INET, SOCK_STREAM, 0);
if(sock <0)
{
perror("NO hay socket de escucha");
exit(1);
}
server.sin_family=AF_INET;
server.sin_addr.s_addr=htonl(INADDR_ANY);
server.sin_port=htons(SERV_ADDR);
if(bind(sock,(struct sockaddr *)&server,sizeof server)<0)
{
perror("direccion no asignada");
exit(1);
}
listen(sock,1);
do{
msgsock=accept(sock, (struct sockaddr *)0,(int *) 0);
if (msgsock ==-1){
perror("Conexion no aceptada!!!!!!!!!!!!!!\n");
}else do{
memset(buf,0,sizeof buf);
rval=read(msgsock, buf,1024);
if (rval<0)perror("Mensaje no leido..");
else write(STDOUT,buf,rval);
}while(rval>0);
printf("\nCerrando la conexion......\n");
close(msgsock);
}while(1);
exit(0);
}