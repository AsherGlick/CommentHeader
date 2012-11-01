CommentHeader
=============
A quick script for creating nice looking comments in code  

Curent Supported Comments  
C / C++ / Java / Javascript  
python / bash / shell  

Coming Soon  
HTML / XML  





it is run with the arguments `./comment_header` Title With Spaces  
all but one space will be ignored if there are multiples in series  
`./commnet_header -h` will display a help message  
`./comment_header` with no argumetns will display a help message  
This will print a comment headder with the requested name  

Due to more interest in this project I may begin documenting this and writing it better


`/********************************* hellothere *********************************\`

`/*********************************** C-HEAD ***********************************\`

`/********************* this is a headder what do you think ********************\`



Getting started
---------------
If you just want to get the program installed download or clone the repo and run  

    make install

which will compile the program and move an executable to `/bin/chead`
if you do not have write permissions for `/bin` you may need to use

    sudo make install

After it is installed type `chead` to bring up the help menu

Some beginner commands to check out

	$ chead -f I am a function header
    /*************************** I am a function header ***************************\
	| 
	\******************************************************************************/
	$ chead -t I am a title
      //////////////////////////////////////////////////////////////////////////////
	 //////////////////////////////// I am a title //////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////  
    $ chead -fp Now I am in python
    ############################## Now I am in python ##############################
	# 
	################################################################################
    $ chead -tp I am in python too
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

Clipboard (via xclip)
---------------------