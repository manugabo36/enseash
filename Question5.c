#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main() {
    char welcomeMsg[] = "\nBienvenue dans le Shell ENSEA\nPour quitter, tapez 'exit'.\n";
    write(1, welcomeMsg, strlen(welcomeMsg));
    //write the Welcome message

    char input[100];
    int status;
    pid_t fpid;
    char prompt[] = "enseash % ";
    char tryAgain[] = "Try again\n";
    char output[100];
    int ChildRun = 0;
    struct timespec begin, end;
    long millis;


    while(1) {
        //write a different message depending on the input message
        write(1, prompt, strlen(prompt));
        scanf("%s", input);

        if (strcmp(input, "fortune") == 0) {
            // child process
            clock_gettime(CLOCK_MONOTONIC, &begin);
            fpid = fork();
            if (fpid == 0) {
                char fortune[] = "Today is what happened to yesterday\n";
                write(1, fortune, strlen(fortune));
                exit(0); // End the child process with exit code 0
            }
            else if (fpid > 0) {
                ChildRun = 1;
            }
        }
        else if (strcmp(input, "exit") == 0) {
            sprintf(output, "enseash [code:0] % ");
            write(1, output, strlen(output));
            exit(0); //quit the shell if the command is "exit"
        }
        else {
            if (strcmp(input, "ls") == 0) { // Check if the command input is ls
                clock_gettime(CLOCK_MONOTONIC, &begin);
                fpid = fork();
                if (fpid == 0) {
                    execlp("/bin/ls", "ls", (char *)NULL);
                    exit(1); // code if there is an error computed
                }
                else if (fpid > 0) {
                    ChildRun = 1;
                }
            } else {
                // Unknown command inputted
                write(1, tryAgain, strlen(tryAgain));
            }
        }

        // Wait for all child process to end
        while ((fpid = wait(&status)) > 0) {
            clock_gettime(CLOCK_MONOTONIC, &end);
            // Give the duration of the process in ms
            millis = (end.tv_sec - begin.tv_sec) * 1000 + (end.tv_nsec - begin.tv_nsec) / 1000000;
            ChildRun = 0;
            if (WIFEXITED(status)) {
                int exit_status = WEXITSTATUS(status);
                sprintf(output, "enseash [code:%d|%ldms] % ", exit_status, millis);
                write(1, output, strlen(output));
            }
            else if (WIFSIGNALED(status)) {
                int exit_signal = WTERMSIG(status);
                sprintf(output, "enseash [sign:%d|%ldms] % ", exit_signal, millis);
                write(1, output, strlen(output));
            }
        }
    }
}
