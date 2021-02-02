/*********************************** LICENSE **********************************\
| Copyright (c) 2012-2021, Asher Glick                                         |
| All rights reserved.                                                         |
|                                                                              |
| Redistribution and use in source and binary forms, with or without           |
| modification, are permitted provided that the following conditions are met:  |
|                                                                              |
| * Redistributions of source code must retain the above copyright notice,     |
|   this list of conditions and the following disclaimer.                      |
| * Redistributions in binary form must reproduce the above copyright notice,  |
|   this list of conditions and the following disclaimer in the documentation  |
|   and/or other materials provided with the distribution.                     |
|                                                                              |
| THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  |
| AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    |
| IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   |
| ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE    |
| LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR          |
| CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         |
| SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS     |
| INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      |
| CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)      |
| ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   |
| POSSIBILITY OF SUCH DAMAGE.                                                  |
\******************************************************************************/

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
    std::ifstream xclipBinary("/usr/bin/xclip");
    if (!xclipBinary.good()){
        std::cout << "Error: Cannot Find XClip binary" << std::endl;
        return -1;
    }
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
            if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO) return -5; // Dup2 error (Child)
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

    std::ifstream xclipBinary("/usr/bin/xclip");
    if (!xclipBinary.good()){
        std::cout << "Error: Cannot Find XClip binary" << std::endl;
        return "";
    }

    int fd2[2];
    pid_t pid;
    // Create a pipe
    if ( (pipe(fd2) < 0) ) return "PIPE ERROR (PARENT)"; // Pipe Error (parent)
    // fork into a new process
    if ( (pid = fork()) < 0 ) return "FORK ERROR (PARENT)"; // Fork Error (parent)

    // Child process
    else  if (pid == 0) {

        close(fd2[0]);
        
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
        close(fd2[1]);

        #define LINEBUFFERSIZE 100
        char lineBuffer[LINEBUFFERSIZE];
        std::string output;
        int rv;

        while(true) {
            if ((rv = read(fd2[0], lineBuffer, LINEBUFFERSIZE)) < 0 ) {
                std::cerr << "READ ERROR FROM PIPE" << std::endl;
            }
            // Pipe Closed
            else if (rv == 0) {
                break;
            }

            std::string trimmedString(lineBuffer, rv);
            output += trimmedString;
        }

        close(fd2[0]);
        return output;
    }

    return ""; // Error.
}
