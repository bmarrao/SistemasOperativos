//
// Created by tiagorodrigues on 23-04-2022.
// ./sdstore proc-file banana.txt bananacomp.txt bcompress nop gcompress encrypt nop
// ./sdstore status
//

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// ./sdstore proc-file <priority> samples/file-a outputs/file-a-output bcompress nop gcompress encrypt nop

//TODO Comunicação servidor para o cliente 
int main (int argc, char *argv[])
{
    char buffer[128];
    //sdsdstreijhyase proc-file banan.txt final alt1 alt2
    //argc 6
    //printf("%d aqui\n",argc);
    for (int i = 1; i < argc; i++)
    {
        strcat(buffer,argv[i]);
        //printf("%s %d aqui carai \n",argv[i],i);

        if (i != (argc-1)){
            strcat(buffer," ");
        }
        else strcat(buffer,"\0");
    }
    //printf("%sbuffer\n ",buffer);

    //printf("%s\n",buffer); //está a imprimir uma merda qualquer no inicio
    //printf("pipe open\n");
    int fd = open("contacto",O_WRONLY);
    write(fd,buffer,sizeof(buffer));
    close(fd);
    buffer[0] = '\0';
    unlink("contacto");

    int fd1 = open("id",O_RDONLY);
    char qualid[4];
    read(fd1,qualid,4);
    close(fd1);
    //TODO while que espera o concluded e cria um FIFO para o processo.
    //printf("pipe closed\n");
    

    char op[15];
    char c1[15] = "contacto";
    strcat(c1,qualid);
    printf("%s\n",c1);
    mkfifo(c1,0666);
    //int fd2 = open(c1,O_RDONLY);
    for(int x = 0;x!= 3;x++){
        int fd2 = open(c1,O_RDONLY);
        printf("%d ciclo\n",x);
        read(fd2,op,sizeof(op));
        close(fd2);
        printf("%s",op);
        memset(op,0,strlen(op));
    }
    close(fd1);
    unlink(c1);

    // int p1 = open("pending",O_RDONLY);
    // read(p1,op,15);
    // close(p1);
    // printf("%s\n",op);
    // unlink("pending");
    
    // memset(op,0,strlen(op));
    // int p2 = open("processing",O_RDONLY);
    // read(p2,op,15);
    // close(p2);
    // printf("%s\n",op);
    // unlink("processing");
    // memset(op,0,strlen(op));
    // int p3 = open("concluded",O_RDONLY);
    // read(p3,op,15);
    // close(p3);
    // printf("%s\n",op);
    // unlink("concluded");
    
    return 0;

}


























































