// This function should be able to run some program with some arguments and some stdin


// program "/usr/bin/xclip"

#include <string>
#include <iostream>

#define MAXLINE 100
int copyToClipboard(std::string contents)
{
    int fd1[2];
    int fd2[2];
    pid_t pid;
    char line[MAXLINE];

    // Create a pipe
    if ( (pipe(fd1) < 0) || (pipe(fd2) < 0) )
    {
        std::cerr << "PIPE ERROR" << std::endl;
        return -2;
    }

    // fork into a new process
    if ( (pid = fork()) < 0 )
    {
        std::cerr << "FORK ERROR" << std::endl;
        return -3;
    }

    // Child process
    else  if (pid == 0)     // CHILD PROCESS
    {
        close(fd1[1]);
        close(fd2[0]);

        if (fd1[0] != STDIN_FILENO)
        {
            if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
            {
                std::cerr << "CHILD: dup2 error to stdin" << std::endl;
            }
            close(fd1[0]);
        }


        if (fd2[1] != STDOUT_FILENO)
        {
            if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
            {
                std::cerr << "CHILD: dup2 error to stdout" << std::endl;
            }
            close(fd2[1]);
        }
        

        //char *args[] = {"xclip","-sel","clip", (char*)0};
        char *args[] = {"xclip","-out", (char*)0};
        int execvReturn = execv("/usr/bin/xclip", args);
        //int execvReturn = execv("/bin/ls", args);
        if ( execvReturn < 0)
        {
            std::cerr << "CHILD: system error " << execvReturn << std::endl;
            return -4;
        }
        std::cout << "DONE" << std::endl;
        return 0;
    }
    // PARENT PROCESS
    else
    {
        int rv;
        close(fd1[0]);
        close(fd2[1]);

        if ( write(fd1[1], contents.c_str(), contents.size() ) != contents.size() )
        {
            std::cerr << "PARENT: READ ERROR FROM PIPE" << std::endl;
        }
        std::cout << "PRINTED THE CONTENTS" << std::endl;
        if ( (rv = read(fd2[0], line, MAXLINE)) < 0 )
        {
            std::cerr << "PARENT: READ ERROR FROM PIPE" << std::endl;
        }
        else if (rv == 0)
        {
            std::cerr << "PARENT: Child Closed Pipe" << std::endl;
            return 0;
        }

        std::cout << "PARENT: OUTPUT of PROGRAM B is: " << line;

        return 0;
    }
    return 0;
}