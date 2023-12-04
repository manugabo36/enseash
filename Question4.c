#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

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

    while(1) {
        //write a different message depending on the input message

        write(1, prompt, strlen(prompt));
        scanf("%s", input);

        if (strcmp(input, "fortune") == 0) {
            // child process
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
                fpid = fork();
                if (fpid == 0) {
                    execlp("/bin/ls", "ls", (char *)NULL);
                    exit(1); // code if there is an error computed
                }
                else if (fpid > 0) {
                    ChildRun = 1;
                }
            } else {
                // Unknow command inputted
                write(1, tryAgain, strlen(tryAgain));
            }
        }


        // Wait for all child process to end
        while ((fpid = wait(&status)) > 0) {
            ChildRun = 0;
            if (WIFEXITED(status)) {
                int exit_status = WEXITSTATUS(status);
                sprintf(output, "enseash [code:%d] % ", exit_status);
                write(1, output, strlen(output));
            }
            else if (WIFSIGNALED(status)) {
                int exit_signal = WTERMSIG(status);
                sprintf(output, "enseash [sign:%d] % ", exit_signal);
                write(1, output, strlen(output));
            }
        }
    }
}
