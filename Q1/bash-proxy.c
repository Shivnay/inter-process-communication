#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/wait.h> 
#include <string>
//extract bash commands and place them in parallel arrays
string getCMD(string cmd_str,string *cmd_root) {

}
//extract bash command paramaters and place them in parallel arrays
string getParm(string cmd_str, string *cmd_parm) {

}
//return number of commands delimited by ';'
int getCMDCount(string cmd_str) {
    int num_cmd;
    char* cmd; 
    char* rest = cmd_str; 
    //count num commands
    while ((cmd = strtok_r(rest, " ", &rest))) 
        num_cmd++;
    
    return num_cmd;
}

int main(int argc, char *argv[]){ 
    pid_t pid; 
    int ret = 1; 
    int status; 
    //get total number of commands requested
    cont int MAX_COMMANDS = getCMDCount(argv[0]);
    //parallel arrays of commands and parameters
    string cmd_root[MAX_COMMANDS];
    string cmd_parm[MAX_COMMANDS];
    //populate commands and correspoding arguments
    //getCMD(argc, argv, cmd_root);
    
    // pid = fork(); 
    // if (pid == -1){ 
    //     //error occured 
    //     printf("can't fork, error occured\n"); 
    //     exit(EXIT_FAILURE); 
    // } else if (pid == 0){ 
    //     // child process created 
    //     // getpid() returns process id of calling process 
    //     printf("child process, pid = %u\n",getpid()); 
    //     // the argv list first argument should point to 
    //     // filename associated with file being executed 
    //     // the array pointer must be terminated by NULL 
    //     // pointer 
    //     char * argv_list[] = {"ls","-lart","/home",NULL}; 
    //     // the execv() only return if error occured. 
    //     // The return value is -1 
    //     execv("ls",argv_list); 
    //     exit(0); 
    // } else { 
    //     // a positive number is returned for the pid of 
    //     // parent process 
    //     // getppid() returns process id of parent of 
    //     // calling process 
    //     printf("parent process, pid = %u\n",getppid()); 
    //         // the parent process calls waitpid() on the child 
    //         // waitpid() system call suspends execution of 
    //         // calling process until a child specified by pid 
    //         // argument has changed state 
    //         // see wait() man page for all the flags or options 
    //         // used here 
    //         if (waitpid(pid, &status, 0) > 0) { 
                
    //             if (WIFEXITED(status) && !WEXITSTATUS(status)) 
    //                 printf("program execution successful\n"); 
                
    //             else if (WIFEXITED(status) && WEXITSTATUS(status)) { 
    //                 if (WEXITSTATUS(status) == 127) { 

    //                     // execv failed 
    //                     printf("execv failed\n"); 
    //                 } 
    //                 else
    //                     printf("program terminated normally,"
    //                     " but returned a non-zero status\n");				 
    //             } 
    //             else
    //             printf("program didn't terminate normally\n");			 
    //         } 
    //         else { 
    //         // waitpid() failed 
    //         printf("waitpid() failed\n"); 
    //         } 
    //     exit(0); 
    // } 
    return 0; 
} 
