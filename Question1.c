#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main() {

    write(1,"\nBienvenue dans le Shell ENSEA\nPour quitter, tapez 'exit'.\n",strlen ("\nBienvenue dans le Shell ENSEA\nPour quitter, tapez 'exit'.\n"));
    //write the Welcome message in the stdout buffer
    fflush(stdout);
}
