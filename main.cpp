/******************************************************************************\
|                                     ,,                                       |
|                    db             `7MM                                       |
|                   ;MM:              MM                                       |
|                  ,V^MM.    ,pP"Ybd  MMpMMMb.  .gP"Ya `7Mb,od8                |
|                 ,M  `MM    8I   `"  MM    MM ,M'   Yb  MM' "'                |
|                 AbmmmqMA   `YMMMa.  MM    MM 8M""""""  MM                    |
|                A'     VML  L.   I8  MM    MM YM.    ,  MM                    |
|              .AMA.   .AMMA.M9mmmP'.JMML  JMML.`Mbmmd'.JMML.                  |
|                                                                              |
|                                                                              |
|                                ,,    ,,                                      |
|                     .g8"""bgd `7MM    db        `7MM                         |
|                   .dP'     `M   MM                MM                         |
|                   dM'       `   MM  `7MM  ,p6"bo  MM  ,MP'                   |
|                   MM            MM    MM 6M'  OO  MM ;Y                      |
|                   MM.    `7MMF' MM    MM 8M       MM;Mm                      |
|                   `Mb.     MM   MM    MM YM.    , MM `Mb.                    |
|                     `"bmmmdPY .JMML..JMML.YMbmd'.JMML. YA.                   |
|                                                                              |
\******************************************************************************/
/******************************************************************************\
| Copyright (c) 2012, Asher Glick                                              |
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
#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include <map>
#include <vector>
using namespace std;



/***************************** HEADER STYLE CLASS *****************************\
| The header style class is a class for each of the different style of headers |
| for each different language. It allows an easy way of creating and           |
| classifying different 
\******************************************************************************/
class headerStyle {
  public:
    string _TOP_LEFT;
    string _TOP_FILL;
    string _TOP_RIGHT;
    
    string _LEFT_COLUMN;
    string _RIGHT_COLUMN;
    
    string _BOTTOM_LEFT;
    string _BOTTOM_FILL;
    string _BOTTOM_RIGHT;
};




void help();
string cHead(string title, headerStyle);
//string cTitle(string input, titlestyle);
//string htmlHead(string input);
//string pythonHead(string input);
//string pythonTitle(string input);
string signiture(string,string,string);
string bsd(string input,string top,string col,string mid);





/*
struct titleStyle {
  string outsideLeft[] = { "",  "",  "",  "",  ""  };
  string insideLeft[] =  { "", " ", " ", " ", "" };
  string insideRight[] = { "", " ", " ", " ", "" };
  string outsideRight[] ={ "",  "",  "",  "",  ""  };
  string filler[]       ={"*","*","*","*","*"}
};*/

headerStyle newHeader(string top_left, string top_fill, string top_right, string left_column, string right_column, string bottom_left, string bottom_fill, string bottom_right) {
  headerStyle theNewHeader;
  theNewHeader._TOP_LEFT     = top_left;
  theNewHeader._TOP_FILL     = top_fill;
  theNewHeader._TOP_RIGHT    = top_right;
  theNewHeader._LEFT_COLUMN  = left_column;
  theNewHeader._RIGHT_COLUMN = right_column;
  theNewHeader._BOTTOM_LEFT  = bottom_right;
  theNewHeader._BOTTOM_FILL  = bottom_fill;
  theNewHeader._BOTTOM_RIGHT = bottom_right;
  return theNewHeader;
}

/*titleStyle newTitle (, outsideLeft, insideLeft,) {

}*/






#define _PYTHON 'p'
#define _C      'c'
#define _HTML   'h'


map<char,headerStyle> headerStyles;
// C / C++ Header Style

void initilizeHeaderStyles() {
  headerStyles[_C]       = newHeader("/*","*","*\\",
                                    "|",      "|",
                                   "\\*","*","*/");
  //Python Header Style
  headerStyles[_PYTHON] = newHeader("#","#","#",
                                    "#",    "#",
                                    "#","#","#");
}



map<string, char> fullFlagCompression;

void initilizeFullFlags() {
  fullFlagCompression["c++"] = 'c';
}


/************ Flags ************

 h - help
 s - signiture
 f - function header
 t - section title
 b - bsd licence
 - - full tag (eg --help vs -h)

 i - append input to the arguments
 l - specify a custom character length for the title (default 80)

****************/

bool activateFlag ( char flag ) {
  switch ( flag ) {
          // Chose one of these, help will override everything
          case 'h':
            cout << "YOU HAVE ENTERED THE HELP MENU!" << endl;
            break;
          case 's':
            cout << "YOU HAVE ENABLED THE SIGNIGTURE OUTPUT" << endl;
            break;
          case 'f': 
            cout << "YOU HAVE ENABLED THE FUNCTION HEADER METHOD (DEFAULT)" << endl;
            break;
          case 't':
            cout << "YOU HAVE ENABLED THE TITLE HEADER METHOD" << endl;
            break;
          case 'b':
            cout << "YOU HAVE ENABLED THE OUTPUT OF THE BSD HEADER" << endl;
            break;
          // Choose as many of these as you want
          case 'i':
            cout << "YOU HAVE ENABLED EXTENDED INPUT MODE" << endl;
            break;
          }
  return false;
}



int main (int argv, char * argc[])
{
  // If there are no arguments, output the help screen
  if (argv <= 1)
  {
    help();
    return 0;
  }
  // create a vector of the arguments
  vector<string> arguments;
  for (int i = 0; i < argv; i++) {
    arguments.push_back(argc[i]);
  }

  // Loop throguh all of the arguments
  for (unsigned int i = 0; i < arguments.size(); i++) {
    // Check for flags
    if (arguments[i][0] == '-') {
      if (arguments[i][1] == '-') {
        cout << "FULL FLAG MODE" << endl;
        // TODO: Hardcode width and length
      }
 
      else {
        for (unsigned int j = i; j < arguments.size(); j++) {
          if (arguments[i][j] == 'w'){
            cout << "YOU HAVE DECIDED TO SPECIFY A CUSTOM WIDTH OF YOU TITLE" << endl;
          }
          else if( arguments[i][j] == 'l' ) {
            cout << "YOU HAVE DECIDED TO SPECIFY A CUSTOM LENGTH OF YOUR TITLE" << endl;
          }
          else if (activateFlag(argc[i][j])) break;
        }
      }
    }
    
    // Take all non flagged input and append it together
    else {
      
    }
  }
  // parse arguments into a string
  string input;
  if (argv > 2) {
    input = string(argc[2]);
    for (int i = 3; i < argv; i++) input += " "+string(argc[i]);
  }




  else input = "";

  // Check to see what type of headder needs to be generated
}

/*


 ##############################################################################
#####################################             ##############################
####################################  HELLO WORLD  #############################
#####################################             ##############################
 ##############################################################################


*/

    ////////////////////////////////////////////////////////////////////////////
   //////////////////////////                           ///////////////////////
  //////////////////////////  HELLO WORLD HOW ARE YOU  ///////////////////////
 //////////////////////////                           ///////////////////////
////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////               /////////////////////////////
  ////////////////////////////////  HELLO WORLD  /////////////////////////////
 ////////////////////////////////               /////////////////////////////
////////////////////////////////////////////////////////////////////////////

    /**************************************************************************/
   /*******************************               ****************************/
  /*******************************  HELLO WORLD  ****************************/
 /*******************************               ****************************/
/**************************************************************************/


/************************************ HELP ************************************\
|
\******************************************************************************/
void help()
{ /*
  // Version 1
  cout << "Comment Headder Function" << endl;
  cout << "--help will display a help message" << endl;
  cout << "-c [title] will give you a c headder" << endl;
  cout << "-ct [title] will give you a c title" << endl;
  cout << "-h [title] will give you an HTML headder" << endl;
  cout << "-p [title] will give you a python headder" << endl;
  cout << "-pt [title] will give you a python title" << endl;
  cout << "-sig will give you an asherglick signature" << endl;
  cout << "-psig will give you a python version of asherglick signature" << endl;
  cout << "-bsd [name] will give you the BSD licence by [name]" << endl;
  cout << "-pbsd [name] will give you a python version of the bsd licence" <<endl;
  cout << "-fsig will give you an Asher Glick signature and BSD Licence" << endl;
  cout << "-pfsig will give you an fsig for python" << endl;
  
  // Version 2
  cout << "Comment Headder Function" << endl;
  cout << " -T title" << endl;
  cout << " -H headder" << endl;
  cout << " -S signature" << endl;
  cout << " -L licence <style" << endl;
  cout << "  'bsd' BSDv2 licence" << endl;
  cout << "  'gpl' GPLv3 licence" << endl;
  cout << "" << endl;
  cout << " -c <title> c++ headder" << endl;
  cout << " -p <title> python headder" << endl;
  cout << " -h <title> html headder" << endl;
  cout << " -<number> go to the alternet version of that command" << endl;
  */

  // Version 3
  cout << "I am the version 3 help menu, still being completed" << endl;
  
}

/********************************** C HEADDER *********************************\
| The C headder function
\******************************************************************************/
string cHead (string input, string top, string col, string bot) {

  string topBegin = top.substr(0,4);
  string topFill = top.substr(5,1);
  string topEnd = top.substr(76,4);
  
  int half = (70-input.size())/2;
  string output;
  // Begin Comment
  output = topBegin;
  // Predicessing Marks
  for (int i = 0; i < half; i++) output += topFill;
  // Account for an odd number of Marks
  if (input.size()%2 == 1)output += topFill;
  // Add the title of the headder
  output += ' ' + input + ' ';
  // Prodceeding Marks
  for (int i = 0; i < half; i++) output += topFill;
  // Finish Tital Line
  output += topEnd+"\n";
  // Body
  output += col+"\n";
  // Footer Line
  output += bot;
  return output;
}
/****************************** C TITLE HEADDER *******************************\
| the C title generator 
\******************************************************************************/
string cTitle (string input) {
  int half = (76-input.size())/2;  
  string output;
  // Begin Comment
  output = "  //////////////////////////////////////////////////////////////////////////////\n ";
  // Predicessing Marks
  for (int i = 0; i < half; i++) output += '/';
  // Account for an odd number of Marks
  if (input.size()%2 == 1)output += '/';
  // Add the title of the headder
  output += ' ' + input + ' ';
  // Prodceeding Marks
  for (int i = 0; i < half; i++) output += '/';
  // Footer Line
  output += "\n//////////////////////////////////////////////////////////////////////////////";
  return output;
}

/**************************** PYTHON TITLE HEADDER ****************************\
|
\******************************************************************************/
string pythonTitle (string input) {
  int half = (78-input.size())/2;  
  string output;
  // Begin Comment
  output = "################################################################################\n";
  // Predicessing Marks
  for (int i = 0; i < half; i++) output += '#';
  // Account for an odd number of Marks
  if (input.size()%2 == 1)output += '#';
  // Add the title of the headder
  output += ' ' + input + ' ';
  // Prodceeding Marks
  for (int i = 0; i < half; i++) output += '#';
  // Footer Line
  output += "\n################################################################################";
  return output;
}

/******************************** MY SIGNITURE ********************************\
| Returns my signiture, it's nice and pretty :) it takes in top, bottom and    |
| column variables                                                             |
\******************************************************************************/
string signiture (string top, string col,string bot) {
  string sig = "";
  sig += top+"\n";
  sig += col+"                                     ,,                                       "+      col+"\n";
  sig += col+"                    db             `7MM                                       "+      col+"\n";
  sig += col+"                   ;MM:              MM                                       "+      col+"\n";
  sig += col+"                  ,V^MM.    ,pP\"Ybd  MMpMMMb.  .gP\"Ya `7Mb,od8                "+    col+"\n";
  sig += col+"                 ,M  `MM    8I   `\"  MM    MM ,M'   Yb  MM' \"'                "+    col+"\n";
  sig += col+"                 AbmmmqMA   `YMMMa.  MM    MM 8M\"\"\"\"\"\"  MM                    "+col+"\n";
  sig += col+"                A'     VML  L.   I8  MM    MM YM.    ,  MM                    "+      col+"\n";
  sig += col+"              .AMA.   .AMMA.M9mmmP'.JMML  JMML.`Mbmmd'.JMML.                  "+      col+"\n";
  sig += col+"                                                                              "+      col+"\n";
  sig += col+"                                                                              "+      col+"\n";
  sig += col+"                                ,,    ,,                                      "+      col+"\n";
  sig += col+"                     .g8\"\"\"bgd `7MM    db        `7MM                         "+   col+"\n";
  sig += col+"                   .dP'     `M   MM                MM                         "+      col+"\n";
  sig += col+"                   dM'       `   MM  `7MM  ,p6\"bo  MM  ,MP'                   "+     col+"\n";
  sig += col+"                   MM            MM    MM 6M'  OO  MM ;Y                      "+      col+"\n";
  sig += col+"                   MM.    `7MMF' MM    MM 8M       MM;Mm                      "+      col+"\n";
  sig += col+"                   `Mb.     MM   MM    MM YM.    , MM `Mb.                    "+      col+"\n";
  sig += col+"                     `\"bmmmdPY .JMML..JMML.YMbmd'.JMML. YA.                   "+     col+"\n";
  sig += col+"                                                                              "+      col+"\n";
  sig += bot;
  return sig;
}

/********************************* BSD2 / BSD *********************************\
| the BSD 2 licence, one of the best licences in my oppinion!                  |
\******************************************************************************/
string thisyear() {
  #define SECONDSPERYEAR 31556926
  #define EPOCH 1970
  unsigned long year = (time(NULL)/SECONDSPERYEAR)+EPOCH;
  stringstream ss;
  ss << year;
  return ss.str();
}

/******************************** BSD FUNCTION ********************************\
| This function prints out the BSD licence to the screen with the correct      |
| borders for the style of source code                                         |
\******************************************************************************/
string bsd(string name, string top, string col, string bot) {
  string year = thisyear();
  string owner = name;
  
  string output = col+" Copyright (c) "+year+", "+owner;
  for (int i = output.length(); i < 79; i++) {
    output += " ";
  }
  output += col+"\n";
  
  output =  top+"\n" + output;
  output += col+" All rights reserved.                                                         "+col+"\n";
  output += col+"                                                                              "+col+"\n";
  output += col+" Redistribution and use in source and binary forms, with or without           "+col+"\n";
  output += col+" modification, are permitted provided that the following conditions are met:  "+col+"\n";
  output += col+"                                                                              "+col+"\n";
  output += col+" * Redistributions of source code must retain the above copyright notice,     "+col+"\n";
  output += col+"   this list of conditions and the following disclaimer.                      "+col+"\n";
  output += col+" * Redistributions in binary form must reproduce the above copyright notice,  "+col+"\n";
  output += col+"   this list of conditions and the following disclaimer in the documentation  "+col+"\n";
  output += col+"   and/or other materials provided with the distribution.                     "+col+"\n";
  output += col+"                                                                              "+col+"\n";
  output += col+" THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\"  "+col+"\n";
  output += col+" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    "+col+"\n";
  output += col+" IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   "+col+"\n";
  output += col+" ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE    "+col+"\n";
  output += col+" LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR          "+col+"\n";
  output += col+" CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         "+col+"\n";
  output += col+" SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS     "+col+"\n";
  output += col+" INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      "+col+"\n";
  output += col+" CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)      "+col+"\n";
  output += col+" ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   "+col+"\n";
  output += col+" POSSIBILITY OF SUCH DAMAGE.                                                  "+col+"\n";
  output += bot;
  return output;
}
