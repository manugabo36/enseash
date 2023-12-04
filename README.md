### 2nd Year – Computer Science Major Practical Work
# ENSEASH : ENSEA in the Shell

This project consists of developing a mini shell in C language to call programs and display their exit(or signal) code.

***
## question1

Just display a Welcome message and the first prompt.

`write(1,message,strlen(message));` to disp the string `message` in the shell, where `1` refers to stdout (`0` for stdin, `2` for stderr).

***
## question2

Three step to code:

- scan the command(without arguments): `scanf("%s",input);` to save the entered text in a string `input`.


- execute the command: 

`char file[100] = "./";`

`strcat(file,input);`

`execlp(file,input,(char* )NULL);`

With Clion, the repository seems to depend on the way we launch the project, if we just push the RUN button, it's in the cmake-build-debug folder,
and if we execute in the terminal, it's in the project folder.

It is safer to initialize `file` with `"./"` for program execution in order to differentiate with shell command.

We misunderstood the statement at first, and then we corrected that in the final version of question4.

- print the prompt: same solution as question1.

***
## question3

We exit the shell with the exit code 0 if the entered command is "exit".

***
## question4

***
## question5

***
## question6
