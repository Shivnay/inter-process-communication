#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/wait.h> 
#include <string.h>  
#include <stdbool.h>

//approved bash commands
bool validateCMD(char* cmd) {
    if (cmd == "mkdir")
        return true;
    else if (cmd == "ls")
        return true;
     else if (cmd == "cp")
        return true;
     else if (cmd == "mv")
        return true;
    else if (cmd == "vi")
        return true;
     else
        return false;
}

int main(int argc, char *argv[]){ 
    pid_t pid; 
    int ret = 1; 
    int status; 
    //extract command root
    char* cmd  = argv[1];
    if (validateCMD(cmd)) {
        //extract command parameters
        int PARMCOUNT = argc - 2;
        //make sure arguments provided
        if (PARMCOUNT != 0) {
            char* parm[PARMCOUNT];
            //fill parmater array
            for (int index = 2; index < argc; index++)
                parm[index-2] = argv[index];
            //create child process to run command
            pid = fork(); 
            if (pid == -1){ 
                //error occured 
                printf("can't fork, error occured\n"); 
                exit(EXIT_FAILURE); 
            } else if (pid == 0){ 
                // child process created 
                printf("child process, pid = %u\n",getpid()); 
                //execute command
                execv(cmd,parm); 
                exit(0); 
            } else { 
                // a positive number is returned for the pid of parent process 
                printf("parent process, pid = %u\n",getppid()); 
                // check execution and child process state
                if (waitpid(pid, &status, 0) > 0) { 
                    //successful execution
                    if (WIFEXITED(status) && !WEXITSTATUS(status)) 
                        printf("program execution successful\n"); 
                    //error might have occured
                    else if (WIFEXITED(status) && WEXITSTATUS(status)) { 
                        //execution failed
                        if (WEXITSTATUS(status) == 127) { 
                            // execv failed 
                            printf("execv failed\n"); 
                        } else
                            printf("program terminated normally, but returned a non-zero status\n");				 
                    } else
                        printf("program didn't terminate normally\n");			 
                } else
                    printf("waitpid() failed\n"); 

                exit(0); 
            } else 
                printf("bash command not supported");
        } else 
            printf("no arguments provided \n");
    }
    
    return 0; 
} 
