// This function should be able to run some program with some arguments and some stdin
#include <string>
#include <iostream>
/****************************** COPY TO CLIPBOARD *****************************\
| The copy to clipboard function takes in a string and coppies it to the       |
| user's clipboard automaticly using the program 'xclip'. If xclip is not      |
| installed then the funtion fails                                             |
\******************************************************************************/
int copyToClipboard(std::string contents)
{
    int fd1[2];
    pid_t pid;
    // Create a pipe
    if ( (pipe(fd1) < 0) ) return -2; // Pipe Error (parent)
    // fork into a new process
    if ( (pid = fork()) < 0 ) return -3; // Fork Error (parent)
    
    // Child process
    else  if (pid == 0) {
        close(fd1[1]);
        if (fd1[0] != STDIN_FILENO) {
            if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO) { return -5; // Dup2 error (Child)
            close(fd1[0]);
        }
        char *args[] = { (char*)"xclip" , (char*)"-sel", (char*)"clip", (char*)0};
        if ( execv("/usr/bin/xclip", args) < 0) return -4; //execv error (CHILD)
        return 0;
    }

    // PARENT process
    else {
        close(fd1[0]);
        if ( write(fd1[1], contents.c_str(), contents.size() ) != (int)contents.size() ) return -6; // WRITE ERROR FROM PIPE (PARENT)
        close(fd1[1]);
        return 0;
    }
    return 0;
}
/***************************** COPY FROM CLIPBOARD ****************************\
| This function takes what is coppied to the clipboard and returns it to the   |
| program to use at the title or the contents depending on if a title is       |
| given or not                                                                 |
\******************************************************************************/
std::string copyFromClipboard() {
    //int fd1[2];
    int fd2[2];
    pid_t pid;
    // Create a pipe
    //if ( (pipe(fd1) < 0) || (pipe(fd2) < 0) ) return -2; // Pipe Error (parent)
    if ( (pipe(fd2) < 0) ) return "PIPE ERROR (PARENT)"; // Pipe Error (parent)
    // fork into a new process
    if ( (pid = fork()) < 0 ) return "FORK ERROR (PARENT)"; // Fork Error (parent)
    // Child process
    else  if (pid == 0) {
        //close(fd1[1]);
        close(fd2[0]);

        /*if (fd1[0] != STDIN_FILENO) {
            if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO) {
                std::cerr << "CHILD: dup2 error to stdin" << std::endl;
            }
            close(fd1[0]);
        }*/

        
        if (fd2[1] != STDOUT_FILENO) {
            if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO) {
                std::cerr << "CHILD: dup2 error to stdout" << std::endl;
            }
            close(fd2[1]);
        }
        
        char *args[] = { (char*)"xclip" , (char*)"-out", (char*)0};
        if ( execv("/usr/bin/xclip", args) < 0) {
            std::cerr << "CHILD: system error" << std::endl;
            return "SYSTEM ERROR (CHILD)";
        }
        return "";
    }
    // PARENT process
    else {
        //close(fd1[0]);
        close(fd2[1]);
        //contents += char(0);
        //if ( write(fd1[1], contents.c_str(), contents.size() ) != (int)contents.size() ) {
        //    std::cerr << "PARENT: READ ERROR FROM PIPE" << std::endl;
        //}
        #define MAXLINE 100
        char line[MAXLINE];
        std::string output;
        int rv;
        if ( (rv = read(fd2[0], line, MAXLINE)) < 0 )
        {
            std::cerr << "READ ERROR FROM PIPE" << std::endl;
        }
        else if (rv == 0)
        {
            std::cerr << "Child Closed Pipe" << std::endl;
        }

        std::cout << "OUTPUT of PROGRAM B is: " << line;
        output += line;

        //close(fd1[1]);
        close(fd2[0]);
        return output;
    }


    return "YO IM THE CLIPBOARD";
}



