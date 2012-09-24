from subprocess import Popen
import subprocess
import os

units = [
	{"TestName" : "Standard Even Length"
	,"Test"     : "./chead EVEN"
	,"Result"   : "/************************************ EVEN ************************************\\\n|\n\******************************************************************************/\n"
	},

	{"TestName" : "Standard Odd Length"
	,"Test"      : "./chead ODD"
	,"Result"    :"/************************************* ODD ************************************\\\n|\n\\******************************************************************************/\n"
	}
	,
	{"TestName" : "Python Even Length"
	,"Test"      : "./chead -p EVEN"
	,"Result"    :"##################################### EVEN #####################################\n#\n################################################################################\n"
	}
	,
	{"TestName" : "Python Odd Length"
	,"Test"      : "./chead -p ODD"
	,"Result"    :"###################################### ODD #####################################\n#\n################################################################################\n"
	}
	,
	{"TestName" : "Python Small Width and Height"
	,"Test"      : "./chead -pwl 12 2 EVEN"
	,"Result"    : "### EVEN ###\n#          #\n#          #\n############\n"
	}
	,
	{"TestName" : "Standard Large Width and Height"
	,"Test"      : "./chead -wl 90 5 LONG TITLE"
	,"Result"    : "/************************************** LONG TITLE **************************************\\\n|                                                                                        |\n|                                                                                        |\n|                                                                                        |\n|                                                                                        |\n|                                                                                        |\n\\****************************************************************************************/\n"
	}
	,
	{"TestName" : "Standard Title Even"
	,"Test"      : "./chead -t EVEN"
	,"Result"    : "  //////////////////////////////////////////////////////////////////////////////\n //////////////////////////////////// EVEN //////////////////////////////////// \n//////////////////////////////////////////////////////////////////////////////  \n"
	}
	,
	{"TestName" : "Standard Title Odd"
	,"Test"      : "./chead -t ODD"
	,"Result"    : "  //////////////////////////////////////////////////////////////////////////////\n //////////////////////////////////// ODD ///////////////////////////////////// \n//////////////////////////////////////////////////////////////////////////////  \n"
	}

	,
	{"TestName" : "Python Title Even"
	,"Test"      : "./chead -tp EVEN"
	,"Result"    : "################################################################################\n##################################### EVEN #####################################\n################################################################################\n"
	}
	,
	{"TestName" : "Python Title Odd"
	,"Test"      : "./chead -tp ODD"
	,"Result"    : "################################################################################\n##################################### ODD ######################################\n################################################################################\n"
	}
	,
	{"TestName" : "Too many output flags error"
	,"Test"      : "./chead -ft Too many flags"
	,"Result"    : "You have set multiple output flags, only one is allowed\n"
	}
	,
	{"TestName" : "Too many aligns error"
	,"Test"      : "./chead -imr Too many flags"
	,"Result"    : "You have set multiple align flags for extended input, only one is allowed\n"
	}
]








def run (command):
	commands = command.split(" ")
	process = Popen(commands, stdout=subprocess.PIPE)
	exit_code = os.waitpid(process.pid, 0)
	output = process.communicate()[0]
	return output



#print "|--|\n",run("./chead HELLO WORLD"),"|--|"


OKGREEN = '\033[92m'
WARNING = '\033[93m'
FAIL = '\033[91m'
ENDC = '\033[0m'


def getTerminalSize():
    import os
    env = os.environ
    def ioctl_GWINSZ(fd):
        try:
            import fcntl, termios, struct, os
            cr = struct.unpack('hh', fcntl.ioctl(fd, termios.TIOCGWINSZ,
        '1234'))
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
	if run(unit["Test"]) == unit["Result"]:
		print unit["TestName"] + " " +("."*(width-11-len(unit["TestName"])) ) + OKGREEN + " [SUCESS]" + ENDC
	else:
		print unit["TestName"] + " " +("."*(width-11-len(unit["TestName"])) ) + FAIL + " [FAILED]" + ENDC


