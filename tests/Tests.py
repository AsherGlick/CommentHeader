from subprocess import Popen
import subprocess
import fcntl
import termios
import struct
import os
from datetime import date

units = [

    {"TestName": "BreakPoint", "BreakTitle": "Standard Generators"},

    {"TestName": "Standard Even Length",
     "Test": "../bin/chead EVEN",
     "Stdin": "",
     "Result": "/************************************ EVEN ************************************\\\n"
               "| \n"
               "\\******************************************************************************/\n"
     },

    {"TestName": "Standard Odd Length",
     "Test": "../bin/chead ODD",
     "Stdin": "",
     "Result": "/************************************* ODD ************************************\\\n"
               "| \n"
               "\\******************************************************************************/\n"
     },

    {"TestName": "Python Even Length",
     "Test": "../bin/chead -P EVEN",
     "Stdin": "",
     "Result": "##################################### EVEN #####################################\n"
               "# \n"
               "################################################################################\n"
     },

    {"TestName": "Python Odd Length",
     "Test": "../bin/chead -P ODD",
     "Stdin": "",
     "Result": "###################################### ODD #####################################\n"
               "# \n"
               "################################################################################\n"
     },

    {"TestName": "BreakPoint", "BreakTitle": "Resizing Functions"},

    {"TestName": "Python Small Width and Height",
     "Test": "../bin/chead -Pwl 12 2 EVEN",
     "Stdin": "",
     "Result": "### EVEN ###\n"
               "#          #\n"
               "#          #\n"
               "############\n"
     },

    {"TestName": "Standard Large Width and Height",
     "Test": "../bin/chead -wl 90 5 LONG TITLE",
     "Stdin": "",
     "Result": "/************************************** LONG TITLE **************************************\\\n"
               "|                                                                                        |\n"
               "|                                                                                        |\n"
               "|                                                                                        |\n"
               "|                                                                                        |\n"
               "|                                                                                        |\n"
               "\\****************************************************************************************/\n"
     },

    {"TestName": "BreakPoint", "BreakTitle": "Title Functions"},

    {"TestName": "Standard Title Even",
     "Test": "../bin/chead -t EVEN",
     "Stdin": "",
     "Result": "  //////////////////////////////////////////////////////////////////////////////\n"
               " //////////////////////////////////// EVEN //////////////////////////////////// \n"
               "//////////////////////////////////////////////////////////////////////////////  \n"
     },

    {"TestName": "Standard Title Odd",
     "Test": "../bin/chead -t ODD",
     "Stdin": "",
     "Result": "  //////////////////////////////////////////////////////////////////////////////\n"
               " //////////////////////////////////// ODD ///////////////////////////////////// \n"
               "//////////////////////////////////////////////////////////////////////////////  \n"
     },

    {"TestName": "Python Title Even",
     "Test": "../bin/chead -tP EVEN",
     "Stdin": "",
     "Result": "################################################################################\n"
               "##################################### EVEN #####################################\n"
               "################################################################################\n"
     },

    {"TestName": "Python Title Odd",
     "Test": "../bin/chead -tP ODD",
     "Stdin": "",
     "Result": "################################################################################\n"
               "##################################### ODD ######################################\n"
               "################################################################################\n"
     },

    {"TestName": "BreakPoint", "BreakTitle": "Error Catching"},

    {"TestName": "Too many output flags error",
     "Test": "../bin/chead -ft Too many flags",
     "Stdin": "",
     "Result": "You have set multiple output flags, only one is allowed\n"
     },

    {"TestName": "Too many aligns error",
     "Test": "../bin/chead -imr Too many flags",
     "Stdin": "",
     "Result": "You have set multiple align flags for extended input, only one is allowed\n"
     },

    {"TestName": "BreakPoint", "BreakTitle": "Extended Input"},

    {"TestName": "Extended Input Basic",
     "Test": "../bin/chead -i EXTENDED INPUT",
     "Stdin": "hello world",
     "Result": "/******************************* EXTENDED INPUT *******************************\\\n"
               "| hello world                                                                  |\n"
               "\\******************************************************************************/\n"
     },

    {"TestName": "Extended Input Line Wrap",
     "Test": "../bin/chead -i WORD WRAP",
     "Stdin": "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras venenatis, mi vitae tempus "
              "aliquam, ligula metus tempor nisi, a aliquet lectus velit ut sem. Donec pharetra augue ac "
              "lacus sodales tincidunt. Sed felis enim, bibendum sit amet pharetra et, auctor nec dolor. "
              "Aliquam eu felis ut augue eleifend pharetra. In vitae lacus nec ligula interdum ultrices. "
              "Maecenas ullamcorper orci sed elit porttitor vestibulum ut eget odio. Nulla eleifend dolor "
              "ut tortor sagittis at venenatis lorem pharetra. Nam laoreet orci eget elit posuere ut "
              "pulvinar diam fermentum. Suspendisse nec facilisis metus. Maecenas mollis lacus ac neque "
              "sollicitudin vitae pharetra mi imperdiet. Praesent sit amet auctor nisi.",
     "Result": "/********************************** WORD WRAP *********************************\\\n"
               "| Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras venenatis, mi  |\n"
               "| vitae tempus aliquam, ligula metus tempor nisi, a aliquet lectus velit ut    |\n"
               "| sem. Donec pharetra augue ac lacus sodales tincidunt. Sed felis enim,        |\n"
               "| bibendum sit amet pharetra et, auctor nec dolor. Aliquam eu felis ut augue   |\n"
               "| eleifend pharetra. In vitae lacus nec ligula interdum ultrices. Maecenas     |\n"
               "| ullamcorper orci sed elit porttitor vestibulum ut eget odio. Nulla eleifend  |\n"
               "| dolor ut tortor sagittis at venenatis lorem pharetra. Nam laoreet orci eget  |\n"
               "| elit posuere ut pulvinar diam fermentum. Suspendisse nec facilisis metus.    |\n"
               "| Maecenas mollis lacus ac neque sollicitudin vitae pharetra mi imperdiet.     |\n"
               "| Praesent sit amet auctor nisi.                                               |\n"
               "\\******************************************************************************/\n"
     },

    {"TestName" : "Extended Input Line Wrap Middle",
     "Test": "../bin/chead -im WORD WRAP",
     "Stdin": "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras venenatis, mi vitae tempus "
              "aliquam, ligula metus tempor nisi, a aliquet lectus velit ut sem. Donec pharetra augue ac "
              "lacus sodales tincidunt. Sed felis enim, bibendum sit amet pharetra et, auctor nec dolor. "
              "Aliquam eu felis ut augue eleifend pharetra. In vitae lacus nec ligula interdum ultrices. "
              "Maecenas ullamcorper orci sed elit porttitor vestibulum ut eget odio. Nulla eleifend dolor "
              "ut tortor sagittis at venenatis lorem pharetra. Nam laoreet orci eget elit posuere ut "
              "pulvinar diam fermentum. Suspendisse nec facilisis metus. Maecenas mollis lacus ac neque "
              "sollicitudin vitae pharetra mi imperdiet. Praesent sit amet auctor nisi.",
     "Result": "/********************************** WORD WRAP *********************************\\\n"
               "| Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras venenatis, mi  |\n"
               "|  vitae tempus aliquam, ligula metus tempor nisi, a aliquet lectus velit ut   |\n"
               "|    sem. Donec pharetra augue ac lacus sodales tincidunt. Sed felis enim,     |\n"
               "|  bibendum sit amet pharetra et, auctor nec dolor. Aliquam eu felis ut augue  |\n"
               "|   eleifend pharetra. In vitae lacus nec ligula interdum ultrices. Maecenas   |\n"
               "| ullamcorper orci sed elit porttitor vestibulum ut eget odio. Nulla eleifend  |\n"
               "| dolor ut tortor sagittis at venenatis lorem pharetra. Nam laoreet orci eget  |\n"
               "|  elit posuere ut pulvinar diam fermentum. Suspendisse nec facilisis metus.   |\n"
               "|   Maecenas mollis lacus ac neque sollicitudin vitae pharetra mi imperdiet.   |\n"
               "|                        Praesent sit amet auctor nisi.                        |\n"
               "\\******************************************************************************/\n"
     },

    {"TestName": "Extended Input Line Wrap Right",
     "Test": "../bin/chead -ir WORD WRAP",
     "Stdin": "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras venenatis, mi vitae tempus "
              "aliquam, ligula metus tempor nisi, a aliquet lectus velit ut sem. Donec pharetra augue ac "
              "lacus sodales tincidunt. Sed felis enim, bibendum sit amet pharetra et, auctor nec dolor. "
              "Aliquam eu felis ut augue eleifend pharetra. In vitae lacus nec ligula interdum ultrices. "
              "Maecenas ullamcorper orci sed elit porttitor vestibulum ut eget odio. Nulla eleifend dolor "
              "ut tortor sagittis at venenatis lorem pharetra. Nam laoreet orci eget elit posuere ut "
              "pulvinar diam fermentum. Suspendisse nec facilisis metus. Maecenas mollis lacus ac neque "
              "sollicitudin vitae pharetra mi imperdiet. Praesent sit amet auctor nisi.",
     "Result": "/********************************** WORD WRAP *********************************\\\n"
               "|  Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras venenatis, mi |\n"
               "|    vitae tempus aliquam, ligula metus tempor nisi, a aliquet lectus velit ut |\n"
               "|        sem. Donec pharetra augue ac lacus sodales tincidunt. Sed felis enim, |\n"
               "|   bibendum sit amet pharetra et, auctor nec dolor. Aliquam eu felis ut augue |\n"
               "|     eleifend pharetra. In vitae lacus nec ligula interdum ultrices. Maecenas |\n"
               "|  ullamcorper orci sed elit porttitor vestibulum ut eget odio. Nulla eleifend |\n"
               "|  dolor ut tortor sagittis at venenatis lorem pharetra. Nam laoreet orci eget |\n"
               "|    elit posuere ut pulvinar diam fermentum. Suspendisse nec facilisis metus. |\n"
               "|     Maecenas mollis lacus ac neque sollicitudin vitae pharetra mi imperdiet. |\n"
               "|                                               Praesent sit amet auctor nisi. |\n"
               "\\******************************************************************************/\n"
     },

    {"TestName": "BreakPoint", "BreakTitle": "Clipboard Functions"},

    {"TestName": "Clipboard Copy (Run)",
     "Test": "../bin/chead -v To The clipboard",
     "Stdin": "",
     "Result": ""
     },

    {"TestName": "Clipboard Copy (Validate)",
     "Test": "xclip -out -selection clipboard",
     "Stdin": "",
     "Result": "/****************************** To The clipboard ******************************\\\n"
               "| \n"
               "\\******************************************************************************/\n"
     },

    {"TestName": "BreakPoint", "BreakTitle": "BSD License"},

    {"TestName": "Generic BSD",
     "Test": "../bin/chead -b Bugs Bunny",
     "Stdin": "",
     "Result": "/*********************************** LICENSE **********************************\\\n"
               "| Copyright (c) "+str(date.today().year)+", Bugs Bunny                                               |\n"
               "| All rights reserved.                                                         |\n"
               "|                                                                              |\n"
               "| Redistribution and use in source and binary forms, with or without           |\n"
               "| modification, are permitted provided that the following conditions are met:  |\n"
               "|                                                                              |\n"
               "| * Redistributions of source code must retain the above copyright notice,     |\n"
               "|   this list of conditions and the following disclaimer.                      |\n"
               "| * Redistributions in binary form must reproduce the above copyright notice,  |\n"
               "|   this list of conditions and the following disclaimer in the documentation  |\n"
               "|   and/or other materials provided with the distribution.                     |\n"
               "|                                                                              |\n"
               "| THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\"  |\n"
               "| AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    |\n"
               "| IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   |\n"
               "| ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE    |\n"
               "| LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR          |\n"
               "| CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         |\n"
               "| SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS     |\n"
               "| INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      |\n"
               "| CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)      |\n"
               "| ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   |\n"
               "| POSSIBILITY OF SUCH DAMAGE.                                                  |\n"
               "\\******************************************************************************/\n"
     },

    {"TestName": "BreakPoint", "BreakTitle": "Signature"},

    {"TestName": "Signature Missing - Setup",
     "Test": "/bin/bash backupSignature.sh",
     "Stdin": "",
     "Result": ""
     },

    {"TestName": "Signature Mission - Test",
     "Test": "../bin/chead -s",
     "Stdin": "",
     "Result": "Unable to open signature file\n" +
               os.path.expanduser("~")+"/.signaturesource\n"
     },

    {"TestName": "Signature Test - Setup",
     "Test": "/bin/bash createTempSignature.sh",
     "Stdin": "",
     "Result": ""
     },

    {"TestName": "Signature Mission - Test",
     "Test": "../bin/chead -s",
     "Stdin": "",
     "Result": "Totally works man"
     },

    {"TestName": "Signature Cleanup - Setup",
     "Test": "/bin/bash restoreSignature.sh",
     "Stdin": "",
     "Result": ""
     }, 
]


def run(command, cin="", waitForReply=True):
    output = ""
    commands = command.split(" ")
    process = Popen(commands, stdout=subprocess.PIPE, stdin=subprocess.PIPE)
    if cin != "":
        output = process.communicate(input=cin)[0]
    else:
        os.waitpid(process.pid, 0)
        if waitForReply:
            output = process.communicate()[0]
    return output

OKGREEN = '\033[92m'
WARNING = '\033[93m'
FAIL = '\033[91m'
ENDC = '\033[0m'


def getTerminalSize():
    env = os.environ

    def ioctl_GWINSZ(fd):
        try:
            cr = struct.unpack('hh', fcntl.ioctl(fd, termios.TIOCGWINSZ, '1234'))
        except:
            return None
        return cr
    cr = ioctl_GWINSZ(0) or ioctl_GWINSZ(1) or ioctl_GWINSZ(2)
    if not cr:
        try:
            fd = os.open(os.ctermid(), os.O_RDONLY)
            cr = ioctl_GWINSZ(fd)
            os.close(fd)
        except:
            pass
    if not cr:
        try:
            cr = (env['LINES'], env['COLUMNS'])
        except:
            cr = (25, 80)
    return int(cr[1]), int(cr[0])

(width, height) = getTerminalSize()
for unit in units:

    if unit["TestName"] == "BreakPoint":
        padding = " " * ((width - len(unit["BreakTitle"])) / 2)
        print padding+unit["BreakTitle"]+padding
        continue

    if unit["Result"] == "":
        run(unit["Test"], unit["Stdin"], False)
        print unit["TestName"] + " Completed -- no check"
    elif run(unit["Test"], unit["Stdin"]) == unit["Result"]:
        print unit["TestName"] + " " + ("."*(width-11-len(unit["TestName"]))) + OKGREEN + " [SUCESS]" + ENDC
    else:
        print unit["TestName"] + " " + ("."*(width-11-len(unit["TestName"]))) + FAIL + " [FAILED]" + ENDC
        print run(unit["Test"], unit["Stdin"])
        print unit["Result"]
