### 2nd Year – Computer Science Major Practical Work
# ENSEASH : ENSEA in the Shell

This project consists of developing a mini shell in C language to call programs and display their exit (or signal) code.

***
## question1

Display a Welcome message and the first prompt.

`write(1,message,strlen(message));` to disp the string `message` in the shell, where `1` refers to stdout (`0` for stdin, `2` for stderr).

***
## question2

Three step to code:

- scan the command(without arguments): `scanf("%s",input);` to save the entered text in a string `input`.

- execute the command: 

We misunderstood the statement at first, and then we corrected that in the final version of question5.

    char file[100] = "./";
    strcat(file,input);
    execlp(file,input,(char* )NULL);

With Clion, the repository seems to depend on the way we launch the project, if we just push the RUN button, it's in the cmake-build-debug folder,
and if we execute in the terminal, it's in the project folder.

It is safer to initialize `file` with `"./"` for program execution in order to differentiate with standard shell commands.
As a result, programs are supposed to be placed in the repository where the project is runned.

- print the prompt: same solution as question1.

***
## question3

    if (strcmp(input,"exit")==0) {exit(0);}

We quit the shell with the exit code `0` if the entered command is `"exit"`.

***
## question4

Display exit (or signal) code in the shell with the prompt.

We need to call `fork()` to duplicate the program execution process, then we can retrieve
the exit code with `WEXITSTATUS(status)` (or the signal code with `WTERMSIG(status)`) and display it.

    int status;
    pid_t fpid;

    [...] //program exectution and duplication of process

    while((fpid = wait(&status)) != -1) {	//prompt
        if(WIFEXITED(status)) {
            fprintf(stdout,"enseash [code:%d] % ", WEXITSTATUS(status));}
        else if (WIFSIGNALED(status)) {
            fprintf(stdout,"enseash [sign:%d] % ", WTERMSIG(status));}
    }

***
## question5

Add the execution time of the previous command in the prompt. 

We can use the `struct timespec` defined in `time.h`. It gives us the time with the seconds and the nanoseconds.

    struct timespec begin, end;
    long millis;       //initialize milliseconds timer
    while(1) {
        
            [...]       //case identification
    	clock_gettime(CLOCK_MONOTONIC, &begin);
            [...]		//exectute program, duplicate process

    	clock_gettime(CLOCK_MONOTONIC, &end);
       	millis = (end.tv_sec - begin.tv_sec) * 1000 + (end.tv_nsec - begin.tv_nsec) / 1000000; //milliseconds timer update
        	
       	while((fpid = wait(&status)) != -1) {	//prompt
       		if(WIFEXITED(status)) {
           			fprintf(stdout,"enseash [code:%d|%ld ms] % ", WEXITSTATUS(status),millis);}
       			else if (WIFSIGNALED(status)) {
          			fprintf(stdout,"enseash [sign:%d|%ld ms] % ", WTERMSIG(status),millis);}
    	}
    }


***
## question6

Treatment of commands with multiple arguments:
We have to split the entered string `input` with `" "` as delimiter.

        char* token;
        int argc = 1;
        char* argv[100];
   
        // get the first argument
        token = strtok(input, " ");
        argv[0] = token;
   
        // walk through other arguments
        while( token != NULL ) {
            token = strtok(NULL, " ");
            argv[argc] = token;
            argc++;
        }

And then we have just to execute commands with those arguments, using `execlp(argv[0],argv[0],...,(char *)NULL)`.