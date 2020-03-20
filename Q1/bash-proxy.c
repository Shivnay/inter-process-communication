#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/wait.h> 
#include <string.h>  
#include <stdbool.h>

//approved bash commands
bool validateCMD(char cmd[]) {
    
    if (strcmp(cmd, "/bin/mkdir") == 0)
        return true;
    if (strcmp(cmd, "/bin/ls") == 0)
        return true;
    if (strcmp(cmd, "/bin/cp") == 0)
        return true;
    if (strcmp(cmd, "/bin/mv") == 0)
        return true;
    if (strcmp(cmd, "/bin/vi") == 0)
        return true;
    else
        return false;
}

int main(int argc, char *argv[]) { 
    pid_t pid; 
    int ret = 1; 
    int status; 
    //extract command root
    char* cmd_raw = argv[1];
    char* cmd = malloc(strlen(cmd_raw)+1+5); /* make space for the new string (should check the return value ...) */
    strcpy(cmd, "/bin/"); /* copy name into the new var */
    strcat(cmd, cmd_raw); /* add the extension */;

    if (validateCMD(cmd)) {
        //extract command parameters
        int PARMCOUNT = argc;
        //make sure arguments provided
        if (PARMCOUNT != 0) {
            char* parm[PARMCOUNT];
            //fill parmater array in complience with execv argument standard
            for (int index = 0; index < argc; index++)
                parm[index] = argv[index+1];
            //assign numm to end of argument list
            parm[PARMCOUNT-1] = NULL;
            //create child process to run command
            pid = fork(); 
            if (pid == -1) { 
                //error occured 
                printf("can't fork, error occured\n"); 
                exit(EXIT_FAILURE); 
            } else if (pid == 0) { 
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
            }
        } else 
            printf("no arguments provided\n");
    } else 
        printf("bash: command not supported.\n");
    
    return 0; 
} 
