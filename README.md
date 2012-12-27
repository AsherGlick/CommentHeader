CommentHeader
=============
A quick script for creating nice looking comments in code  

Curent Supported Comments  
`C` C / C++ / Java / Javascript  
`P` Python / Bash / Shell  
`H` HTML / XML / Coldfusion  
`X` Latex  
`N` None / Borderless 


Getting started
---------------
If you just want to get the program installed download or clone the repo or download the files and run  

    make install

This will compile the program and move an executable to `/user/bin/chead`
if you do not have write permissions for `/user/bin` you may need to use

    sudo make install

After it is installed type `chead` into your terminal to bring up the help menu


Beginning Commands
------------------
Some beginner commands to check out

	$ chead -f I am a function header
    /*************************** I am a function header ***************************\
	| 
	\******************************************************************************/

	$ chead -t I am a title
      //////////////////////////////////////////////////////////////////////////////
	 //////////////////////////////// I am a title //////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////  
    
    $ chead -P -f Now I am in python
    ############################## Now I am in python ##############################
	# 
	################################################################################
    
    $ chead -Pt I am in python too
    ################################################################################
	############################## I am in python too ##############################
	################################################################################

Modifying the size
------------------
You can modify the size (columns and rows) of the output using the `-l` and `-w` flags  
`chead -l 10 -w 20`  
`chead -lw 10 20`  
`chead -wl 20 10`  

Extended input mode
-------------------
  i   Extended     Also accept input from stdin for the content
  m   Middle       Extended input with each line aligned in the middle
  r   Right        Extended input with each line aligned to the right


Clipboard (via xclip)
---------------------
 v   Clipboard    Copy the output to the clipboard instead of stdout

Usage
------------
usage: chead [-CHNPX] [-hsbtf] [-v] [-imr]
             [-l #] [-w #] <Input>[Input ...] 


Output formats
  h   Help         Bring up this help menu
  s   Signature    Output your signature form sigfile correctly formatted
  b   BSD License  Output a BSD license using the input as the copyright holder
  t   Title        Output a title style header
  f   Function     Output a function style header, default option
 
Supported Languages
  C   C/C++        Format comments in a C/C++/Java style
  H   HTML / XML   Format Comments in HTML style
  N   None         Format the comment without a border
  P   Python       Format comments in a Python style
  X   LaTeX        Format comments in a LaTeX style