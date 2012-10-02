// This function should be able to run some program with some arguments and some stdin
#include <string>
#include <iostream>

int copyToClipboard(std::string contents)
{
    int fd1[2];
    //int fd2[2];
    pid_t pid;
    // Create a pipe
    //if ( (pipe(fd1) < 0) || (pipe(fd2) < 0) ) return -2; // Pipe Error (parent)
    if ( (pipe(fd1) < 0) ) return -2; // Pipe Error (parent)
    // fork into a new process
    if ( (pid = fork()) < 0 ) return -3; // Fork Error (parent)
    // Child process
    else  if (pid == 0) {
        close(fd1[1]);
        //close(fd2[0]);

        if (fd1[0] != STDIN_FILENO) {
            if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO) {
                std::cerr << "CHILD: dup2 error to stdin" << std::endl;
            }
            close(fd1[0]);
        }

        /*
        if (fd2[1] != STDOUT_FILENO) {
            if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO) {
                std::cerr << "CHILD: dup2 error to stdout" << std::endl;
            }
            close(fd2[1]);
        }*/
        
        char *args[] = { (char*)"xclip" , (char*)"-sel", (char*)"clip", (char*)0};
        if ( execv("/usr/bin/xclip", args) < 0) {
            std::cerr << "CHILD: system error" << std::endl;
            return -4;
        }
        return 0;
    }
    // PARENT process
    else {
        close(fd1[0]);
        //close(fd2[1]);
        //contents += char(0);
        if ( write(fd1[1], contents.c_str(), contents.size() ) != (int)contents.size() ) {
            std::cerr << "PARENT: READ ERROR FROM PIPE" << std::endl;
        }
        close(fd1[1]);
        //close(fd2[0]);
        return 0;
    }
    return 0;
}
std::string copyFromClipboard() {
    return "YO IM THE CLIPBOARD";
}