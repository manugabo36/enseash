#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>


int main() {

    struct timespec* TIME;
    time_t milli;
    clock_gettime(CLOCK_REALTIME,TIME);
    milli = TIME->tv_sec*1000;
    write(1,"\nBienvenue dans le Shell ENSEA\nPour quitter, tapez 'exit'.\n",strlen ("\nBienvenue dans le Shell ENSEA\nPour quitter, tapez 'exit'.\n"));
    //write the Welcome message


    char* input;
    int status;
    pid_t fpid;


    write(1,"enseash % ",strlen("enseash % "));
    while(1){
        //write a different message depending on the input message

        scanf("%s",input);
        if(strcmp(input,"fortune")==0){
            write(1,"Today is what happened to yesterday\n",strlen("Today is what happened to yesterday\n"));
            fpid=fork();

        }
        else if (strcmp(input,"exit")==0) { //quit the shell if the command is exit
            exit(0);
        }
        else{
            write(1 ,"Try again \n", strlen("Try again \n"));
            fpid=fork();

        }


        while((fpid = wait(&status)) != -1) {
            clock_gettime(CLOCK_REALTIME,TIME);
            milli = TIME->tv_sec*1000-milli;

            if(WIFEXITED(status)) {
                fprintf(stdout,"enseash [code:%d|%f ms] % ", WEXITSTATUS(status));}
            else if (WIFSIGNALED(status)) {
                fprintf(stdout,"enseash [sign:%d|%f] % ", WTERMSIG(status));}
        }
    }
}
