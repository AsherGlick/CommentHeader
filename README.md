CommentHeader
=============
A quick script for creating nice looking comments in code  

--------------------------------------------------------------------------------

Cheat Sheet

Current Supported Languages     | Output modes       | Input Modes         | Output Modifications
--------------------------------|--------------------|---------------------|---------------------
`C` C / C++ / Java / Javascript | `h` Help           | `i` Left aligned    | `v` Copy To Clipboard
`P` Python / Bash / Shell       | `s` Signature      | `r` Right Aligned   | `l` Length of Title
`H` HTML / XML / Coldfusion     | `b` BSD License    | `m` Middle Aligned  | `w` Width of Title
`X` Latex                       | `t` Title                              
`N` None / Borderless           | `f` Function   

--------------------------------------------------------------------------------


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

	$ echo 'Hello world' | chead -i I am Hello World
	/****************************** I am Hello World ******************************\
	| Hello World                                                                  |
	\******************************************************************************/


Modifying the size
------------------
You can modify the Length (number of rows) and Width (number of columns) of the output using the Length `l <number>` and Width `w <number>` flags  
`chead -l 10 -w 20`  
`chead -lw 10 20`  
`chead -wl 20 10`  

	$ chead -l 5 -w 20 IM A BOX
	/**** IM A BOX ****\
	|                  |
	|                  |
	|                  |
	|                  |
	|                  |
	\******************/



Extended input mode
-------------------
`i` Wrap Input from stdin and align it to the left
`m` Wrap input from stdin and aling it to the middle
`r` Wrap input 

	$ chead -i Default Aligned
	I am aligned by default to the left

	/******************************* Default Aligned ******************************\
	| I am aligned by default to the left                                          |
	\******************************************************************************/

	$ echo 'I am aligned by default to the left' | chead -i Default Aligned
	/******************************* Default Aligned ******************************\
	| I am aligned by default to the left                                          |
	\******************************************************************************/

	$ echo 'I am aligned to the right' | chead -r Right Aligned
	/******************************** Right Aligned *******************************\
	|                                                    I am aligned to the right |
	\******************************************************************************/

	$ echo 'I am aligned to the middle' | chead -m Middle Aligned
	/******************************* Middle Aligned *******************************\
	|                          I am aligned to the middle                          |
	\******************************************************************************/

Clipboard (via xclip)
---------------------
`v`   Clipboard - Copy the output to the clipboard instead of stdout

    $ echo 'To the clip board I go!' | chead -Piv From the clipboard
    $ xclip -out -selection clipboard
    ############################## From the clipboard ##############################
    # To the clip board I go!                                                      #
    ################################################################################

Signature
---------
The signature file is stored at `~/signaturesource`. An easy way to generate your own signature is using the online app [taag](http://patorjk.com/software/taag/#p=display&f=Georgia11&t=Signature%0A). If you would like to generate your signature via the terminal you can use `FIGlet` which taag is based off of. All of the fonts can be downloaded at [java.de](http://www.jave.de/figlet/fonts.html). [(Direct Download Link)](http://www.jave.de/figlet/figletfonts40.zip)

    $ chead -s
    /********************************** SIGNATURE *********************************\
    |                                      ,,                                      |
    |                     db             `7MM                                      |
    |                    ;MM:              MM                                      |
    |                   ,V^MM.    ,pP"Ybd  MMpMMMb.  .gP"Ya `7Mb,od8               |
    |                  ,M  `MM    8I   `"  MM    MM ,M'   Yb  MM' "'               |
    |                  AbmmmqMA   `YMMMa.  MM    MM 8M""""""  MM                   |
    |                 A'     VML  L.   I8  MM    MM YM.    ,  MM                   |
    |               .AMA.   .AMMA.M9mmmP'.JMML  JMML.`Mbmmd'.JMML.                 |
    |                                                                              |
    |                                                                              |
    |                                  ,,    ,,                                    |
    |                      .g8"""bgd `7MM    db        `7MM                        |
    |                    .dP'     `M   MM                MM                        |
    |                    dM'       `   MM  `7MM  ,p6"bo  MM  ,MP'                  |
    |                    MM            MM    MM 6M'  OO  MM ;Y                     |
    |                    MM.    `7MMF' MM    MM 8M       MM;Mm                     |
    |                    `Mb.     MM   MM    MM YM.    , MM `Mb.                   |
    |                      `"bmmmdPY .JMML..JMML.YMbmd'.JMML. YA.                  |
    |                                                                              |
    \******************************************************************************/

BSD License Output
------------------
The BSD licence function will generate a 2 clause BSD licence wrapped with the specified border using the input as the copyright holder and the current year as the date.

    $ chead -b Bugs Bunny
    /*********************************** LICENSE **********************************\
    | Copyright (c) 2013, Bugs Bunny                                               |
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

Usage
------------
usage: chead [-CHNPX] [-hsbtf] [-v] [-imr] [-l #] [-w #] <Input>[Input ...] 


Output formats
`h`   Help                                                                     
`s`   Signature    Output your signature form sigfile correctly formatted      
`b`   BSD License  Output a BSD license using the input as the copyright holder
`t`   Title        Output a title style header                                 
`f`   Function     Output a function style header, default option              
 

Want to Help Out
----------------
There are few things that still need work
- Install Packages for linux flavors
- Testing and configurations for MacOS
- Testing and configurations for Windows
- Unit tests, unit tests, unit tests


License
=======
Copyright (c) 2012, Asher Glick                                                 
All rights reserved.                                                            
                                                                                
Redistribution and use in source and binary forms, with or without              
modification, are permitted provided that the following conditions are met:     
                                                                                
* Redistributions of source code must retain the above copyright notice, this   
  list of conditions and the following disclaimer.                              
* Redistributions in binary form must reproduce the above copyright notice,     
  this list of conditions and the following disclaimer in the documentation     
  and/or other materials provided with the distribution.                        
                                                                                
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED   
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE          
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE    
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL      
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR      
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER      
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,   
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.            