//Servidor
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // <-- Inclye 'read', 'write' y 'close'
#define STDOUT 1
#define SERV_ADDR 1234


#include <arpa/inet.h>

int main(){     // <---{   void -> int }
    int rval;
    int sock,length, msgsock;
    struct sockaddr_in server;
    char buf[1024];
    sock=socket(PF_INET, SOCK_STREAM, 0);
    
    if(sock <0){
        perror("NO hay socket de escucha");
        exit(1);
    }
    
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=htonl(INADDR_ANY);
    server.sin_port=htons(SERV_ADDR);
    
    if( bind(sock,(struct sockaddr *)&server,sizeof server) < 0 ){//*
        perror("direccion no asignada");
        exit(1);
    }
    
    listen(sock,1);
    
    do{
        //msgsock=accept( sock, (struct sockaddr *)0, (int *)0 ); //Tamaño de la estructura sockaddr
        msgsock=accept( sock, (struct sockaddr *)0, (socklen_t *)0 ); //   <---
        if (msgsock ==-1){
            perror("Conexion no aceptada!!!!!!!!!!!!!!\n");
        }else do{
            memset(buf,0,sizeof buf);
            rval=read(msgsock, buf,1024); //   <--- 
            // ^ Se incluyo "unistd.h"
            if (rval<0) perror("Mensaje no leido..");
            else {
                write(STDOUT,buf,rval); //   <--- 
                //char  peer_addr_str[ INET_ADDRSTRLEN ];
                char * peer_addr_str;
                //inet_ntop( AF_INET, &server, peer_addr_str, INET_ADDRSTRLEN );
                peer_addr_str = inet_ntoa(server.sin_addr);
                printf("\n %s\n",peer_addr_str);
                
                /*char *some_addr;
                some_addr = inet_ntoa(server.sin_addr); // return the IP
                printf("\n %s\n", some_addr); // prints "10.0.0.1"*/
            }
            //else write(STDOUT,(const void*)&server.sin_addr,rval); //   <--- 
        }while(rval>0);
            printf("\nCerrando la conexion......\n");
            close(msgsock);  //   <--- 
    }while(1);
    exit(0);
    return 0;
}