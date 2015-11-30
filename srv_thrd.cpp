//Servidor
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // <-- Inclye 'read', 'write' y 'close'
#include <pthread.h>// <-- Threads
#define STDOUT 1
#define SERV_ADDR 1234

#include <arpa/inet.h>

struct str_info {
    int         msgsock;        //int del socket a escuchar
    int         numThrd;        //# del thread
    pthread_t   thread_id;      //id del trhead
};

void * fnHilo (void * args);

int main(){     // <---{   void -> int }
    int rval;
    int sock,length, msgsock;
    int numThrd=0;
    int errorThrd=0;
    char buf[1024];
    struct str_info *infoThreads;
    struct sockaddr_in server;
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
        }else {/*do{
            memset(buf,0,sizeof buf);
            rval=read(msgsock, buf,1024); //   <--- 
            // ^ Se incluyo "unistd.h"
            if (rval<0) perror("Mensaje no leido..");
            else {
                write(STDOUT,buf,rval); //   <--- 
            }
        }while(rval>0);
            printf("\nCerrando la conexion......\n");
            close(msgsock);  //   <--- */
            numThrd++;
            infoThreads[numThrd].msgsock=msgsock;
            infoThreads[numThrd].numThrd=numThrd;
            
            errorThrd = pthread_create (&infoThreads[numThrd].thread_id, NULL, fnHilo, (void *)&infoThreads[numThrd]);
    
            if (errorThrd != 0){
                perror ("No puedo crear el thread"); // <---
                exit(-1);
            } 
        }
    }while(1);
    exit(0);
    return 0;
}

void * fnHilo (void * args){
    struct str_info *info = (str_info*)args;
    char buf[1024];
    int rval;
    //do{
        memset(buf,0,sizeof buf);
        rval=read(info->msgsock, buf,1024); //   <--- 
        // ^ Se incluyo "unistd.h"
        if (rval<0) perror("Mensaje no leido..");
        else {
            write(STDOUT,buf,rval); //   <--- 
            printf("\n Thread # %d",info->numThrd);
        }
    //}while(rval>0);
        printf("\nCerrando la conexion......\n");
        close(info->msgsock);  //   <--- 
}
