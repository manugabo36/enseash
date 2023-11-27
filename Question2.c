#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main() {

    write(1,"\nBienvenue dans le Shell ENSEA\nPour quitter, tapez 'exit'.\n",strlen ("\nBienvenue dans le Shell ENSEA\nPour quitter, tapez 'exit'.\n"));
    //write the Welcome message


    char* input;

    while(1){
        scanf("%s",input);
        if(strcmp(input,"fortune")==0){     //write a different message depending on the input message
            write(1,"Today is what happened to yesterday\n",strlen("Today is what happened to yesterday\n"));
        }
        else{write(1 ,"Try again \n", strlen("Try again \n"));
        }

    }

}
