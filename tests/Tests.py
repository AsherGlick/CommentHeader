from subprocess import Popen
import subprocess
import fcntl
import termios
import struct
import os

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
     }
]


def run(command, cin=""):
    commands = command.split(" ")
    process = Popen(commands, stdout=subprocess.PIPE, stdin=subprocess.PIPE)
    if cin != "":
        output = process.communicate(input=cin)[0]
    else:
        #exit_code = os.waitpid(process.pid, 0)
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

    if run(unit["Test"], unit["Stdin"]) == unit["Result"]:
        print unit["TestName"] + " " + ("."*(width-11-len(unit["TestName"]))) + OKGREEN + " [SUCESS]" + ENDC
    else:
        print unit["TestName"] + " " + ("."*(width-11-len(unit["TestName"]))) + FAIL + " [FAILED]" + ENDC
        print run(unit["Test"], unit["Stdin"])
