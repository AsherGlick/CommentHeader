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
#include <fstream>
#include <string>
#include <time.h>
#include <sstream>
#include <map>
#include <vector>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "headertitle.h"
#include "pipein.h"
using namespace std;

/////////////////////////////// GLOBAL VARIABLES /////////////////////////////////////////
headerStyle globalHeaderStyle;
titleStyle globalTitleStyle; 
#define _PYTHON 'P'
#define _C      'C'
#define _HTML   'H'
#define _LATEX  'X'
map<char,headerStyle> headerStyles;
map<char,titleStyle> titleStyles;
map<char,string> languageNames;
map<char,string> languageDescription;
// Output style flag
char outputFlag = 'f'; // defaults to the function header flag
bool outputFlagSet = false;
// Input flag
bool extendedInputFlag  = false;
char extendedInputAlign = 'l';
// The default title length
#define DEFAULT_TITLE_LENGTH 0
unsigned int titleLength = DEFAULT_TITLE_LENGTH;
#define DEFAULT_TITLE_WIDTH 80
unsigned int titleWidth = DEFAULT_TITLE_WIDTH;
map<string, char> fullFlagCompression;
bool xclipMode = false;



void help();
string headder(string title,string extendedInput);
string title (string title);
string signiture();
string bsd(string owner);


/*************************** INITILIZE HEADER STYLES **************************\
| Include all of the header and title styles into the list of possible styles  |
| to choose from. In order to add  a new language you just need to set a new   |
| element of both the 'globalHeaderStyle' map and the 'globalTitleStyle' map   |
\******************************************************************************/
void initilizeHeaderStyles() {
  //cout << "INTITILIZING THE HEADERS" << endl;
  // C / C++ Styles
  globalHeaderStyle = 
  headerStyles[_C] = headerStyle("/*","*","*\\",
                                 "| ",    " |",
                                "\\*","*","*/");
  globalTitleStyle = 
  titleStyles [_C] = titleStyle ("  /","/"            ,"/",
                                 " /","/","/","/","/","/ ",
                                 "/","/",            "/  ");
  languageNames[_C] = "C/C++";
  languageDescription[_C] = "Format comments in a C/C++/Java style";

  //Python Header Style
  headerStyles[_PYTHON] = headerStyle("#","#","#",
                                      "# ",    " #",
                                      "#","#","#");
  titleStyles [_PYTHON] = titleStyle ("#","#",          "#",
                                      "#","#","","","#","#",
                                      "#","#",          "#");
  languageNames[_PYTHON] = "Python";
  languageDescription[_PYTHON] = "Format comments in a Python style";

  // LaTeX Header Style
  headerStyles[_LATEX] = headerStyle("%","%","%",
                                     "% ",    " %",
                                     "%","%","%");
  titleStyles [_LATEX] = titleStyle (" %","%",          "% ",
                                     "%%","%","","","%","%%",
                                     " %","%",          "% ");
  languageNames[_LATEX] = "LaTeX";
  languageDescription[_LATEX] = "Format comments in a LaTeX style";

  //HTML Header Style
  headerStyles[_HTML] = headerStyle("<!--","-","+ ",
                                    " | " ,   "| ",
                                    " +"  ,"-","-->");
  titleStyles[_HTML] = titleStyle("  <!--","-","-->",
                                  " <!--","-","-","-","-","--> ",
                                  "<!--","-","-->  ");
  languageNames[_HTML] ="HTML / XML";
  languageDescription[_HTML] = "Format Comments in HTML style";

}

/**************************** INITILIZE FULL FLAGS ****************************\
| Add all of the full name alias functions to a list that can be parsed when   |
| the user is calling the funciton                                             |
\******************************************************************************/
void initilizeFullFlags() {
  fullFlagCompression["c++"] = 'c';
}

/******************************* ACTIVATE FLAGS *******************************\
| Given a specific character flag this functions changes internal variables to |
| change how the input / output works                                          |
|                                                                              |
| STATIC FLAGS                                                                 |
| h - help                                                                     |
| s - signiture                                                                |
| f - function header                                                          |
| t - section title                                                            |
| b - bsd licence                                                              |
| - - full tag (eg --help vs -h)                                    [External] |
| i - append input to the arguments                                            |
| m - align the extended input to the middle                                   |
| r - align the extended input to the right                                    |
| l - specify a custom character length for the title (default 80)  [External] |
\******************************************************************************/
bool activateFlag ( char flag ) {
  switch ( flag ) {
    // Chose one of these output flags, help will override everything
    case 'h':
    case 's':
    case 'b':
    case 't':
    case 'f':
      if (!outputFlagSet) { outputFlag = flag; outputFlagSet = true;}
      else {
        cout << "You have set multiple output flags, only one is allowed" << endl;
        exit (0);
      }
      return true;    
    // Choose as many of these as you want
    case 'i':
      //cout << "YOU HAVE ENABLED EXTENDED INPUT MODE" << endl;
      extendedInputFlag = true;
      return true;
    case 'r':
      extendedInputFlag = true;
      if (extendedInputAlign == 'l') extendedInputAlign = 'r';
      else {
        cout << "You have set multiple align flags for extended input, only one is allowed" << endl;
        exit (0);
      }
      return true;
    case 'm':
      extendedInputFlag = true;
      if (extendedInputAlign == 'l') extendedInputAlign = 'm';
      else {
        cout << "You have set multiple align flags for extended input, only one is allowed" << endl;
        exit (0);
      }
      return true;
    case 'v':
      xclipMode = true;
      return true;

  }

  // Find the flag in the language map
  map<char,headerStyle>::iterator it = headerStyles.find(flag);
  if (it != headerStyles.end()) {
    globalHeaderStyle = headerStyles[flag];
    globalTitleStyle = titleStyles[flag];
    return true;
  }

  return false;
}

// parse arguments into a string
string userInput = "";


/******************************* EXTENDED INPUT *******************************\
|
\******************************************************************************/
string captureExtendedInput() {
  string input;
  string output = "";
  while (getline(cin, input)) {
    if (input == "") return output;
    output += input + "\n";
  }
  return output;
}

/************************************ MAIN ************************************\
| The main function handles all of the arguments for parsing  
\******************************************************************************/
int main (int argv, char * argc[])
{
  initilizeHeaderStyles();
  initilizeFullFlags();

  string inputSpaces = ""; // used to append spaces after the first text argument

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
  for (unsigned int i = 1; i < arguments.size(); i++) {
    // Check to see if the input is a flag
    if (arguments[i][0] == '-') {
      // Check to see if the flag is a fulltext flag
      if (arguments[i][1] == '-') {
        string flag = arguments[i];
        flag = flag.substr(2,flag.size()-2);
        cout << "FULL FLAG SEARCHING FOR: " << flag << endl;
      }
      
      else {
        for (unsigned int j = 1; j < arguments[i].size(); j++) {
          // Grab arguments for width
          if (arguments[i][j] == 'w'){
            if (i+1 >= arguments.size()) {
              cout << "Error: You did not specify a width for your title after using the -w flag" << endl;
              return 0;
            }
            else { 
              titleWidth = atoi(arguments[i+1].c_str()); 
              arguments.erase (arguments.begin()+i+1);
            }
          }
          // Grab arguments for length
          else if( arguments[i][j] == 'l' ) {
            if (i+1 >= arguments.size()) {
              cout << "Error: You did not specify a length for your title after using the -l flag" << endl;
              return 0;
            }
            else { 
              titleLength = atoi(arguments[i+1].c_str()); 
              arguments.erase (arguments.begin()+i+1);
            }

          }
          else if (activateFlag(arguments[i][j])) {}
          else {
            cout << "Undefined flag: " << arguments[i][j] << endl;
          }
        }
      }
    }
    
    // Take all non flagged input and append it together
    else {
      userInput += inputSpaces + arguments[i];
      inputSpaces = " ";
    }
  }

  // A string for containing the extended input's data
  string extendedInputString = "";
  // Check for the input flag
  if (extendedInputFlag == true){
    extendedInputString = captureExtendedInput();
  }

  stringstream output;
  // Check to see what type of headder needs to be generated
  switch (outputFlag) {
    case 'h':
      help();
      break;
    case 's':
      output << signiture() << endl;
      break;
      //output << "The signiture and bsd functions will be implmented after extended input is implemented" << endl;
    case 'b':
      output << bsd(userInput) << endl;
      break;
    case 't':
      output << title(userInput) << endl;
      break;
    case 'f':
      output << headder(userInput,extendedInputString) << endl;
      break;
  }

  // check on stdout or xclip out
  if (xclipMode){
    //string execute = "echo \"" + output.str() + "\" | xclip -sel clip";
    copyToClipboard(output.str());
    //system(execute.c_str());
  }
  else {
    cout << output.str();
  }
}


/************************************ HELP ************************************\
| 
\******************************************************************************/
void help()
{ // VERSION 3
  string languageflags = "";
  map<char,headerStyle>::iterator it = headerStyles.begin();
  while (it != headerStyles.end()){
    languageflags +=it->first;
    it++;
  }
  cout << "usage: chead [-"+languageflags+"] [-hsbtf] [-v] [-imr]"<<endl;
  cout << "             [-l #] [-w #] <Input>[Input ...] " << endl;
  cout << "Modifying the size of the output" << endl;
  cout << "   l   Length       Change how many rows are formatted within the title" << endl;
  cout << "   w   Width        Chage how many colums the text box takes up defaults to 80" << endl;
  cout << endl;
  cout << "Output formats" << endl;
  cout << "   h   Help         Bring up this help menu" << endl;
  cout << "   s   Signature    Output your signature form sigfile correctly formatted" << endl;
  cout << "   b   BSD Licence  Output a BSD licence using your input as the copyright holder" << endl;
  cout << "   t   Title        Output a title style header" << endl;
  cout << "   f   Function     Output a function style header, default option" << endl;
  cout << "   v   Clipboard    Copy the output to the clipboard instead of stdout" << endl;
  cout << endl;
  cout << "Input formats" << endl;
  cout << "   i   Extended     Also accept input from stdin for the content" << endl;  
  cout << "   m   Middle       Extended input with each line aligned in the middle" << endl;
  cout << "   r   Right        Extended input with each line aligned to the right" << endl;
  cout << endl;
  cout << "Languages" << endl;
  //Dynamicly create the language section based on the languages initilized
  it = headerStyles.begin();
  while (it != headerStyles.end()){
    cout << "   " << it->first  << "   " << languageNames[it->first];
    for (int i = 0; i < (13-languageNames[it->first].length());i++)  cout << " ";
    cout << languageDescription[it->first] << endl;
    it++;
  }
}


vector<string> wrap (string text, unsigned int width) {
  vector<string> lines;
  int lastSplit = 0;
  // Split on newlines
  for (unsigned int i = 0; i < text.size(); i++){
    if (text[i] == '\n'){
      lines.push_back(text.substr(lastSplit,i-lastSplit));
      lastSplit = i+1;
    }
  }
  if (text.substr(lastSplit,text.size()-lastSplit) != "") lines.push_back(text.substr(lastSplit,text.size()-lastSplit));

  // Split lines that are too long
  vector<string> wrappedLines;
  for (unsigned int i = 0; i < lines.size(); i++) {
    while (lines[i].size() > width){
      int splitIndex = width;
      // Find the last space for a cleaner split
      for (int j = width-1; j >= 0; j--) {
        if (lines[i][j] == ' ') {
          splitIndex = j;
          break;
        }
      }

      wrappedLines.push_back(lines[i].substr(0,splitIndex));
      lines[i] = lines[i].substr(splitIndex+1, lines.size()-splitIndex);
    }
    wrappedLines.push_back(lines[i]);
  }
  return wrappedLines;
}

vector<string> align (string text, char position, unsigned int width) {

  vector <string> wrapped = wrap(text,width);

  for (unsigned int i = 0; i < wrapped.size(); i++) {
    unsigned int difference = width-wrapped[i].size();
    switch(position){
      case 'l':
        for (unsigned int j = 0; j < difference; j++) {
          wrapped[i] += " ";
        }
        break;
      case 'r':
        for (unsigned int j = 0; j < difference; j++) {
          wrapped[i] = " " + wrapped[i];
        }
        break;
      case 'm':
        unsigned int leftDifference = difference / 2;
        unsigned int rightDifference = difference - leftDifference;
        for (unsigned int j = 0; j < leftDifference; j++) {
          wrapped[i] = " " + wrapped[i];
        }
        for (unsigned int j = 0; j < rightDifference; j++) {
          wrapped[i] += " ";
        }

        break;
    }
  }
  return wrapped;
}

/*********************************** HEADDER **********************************\
| GENERAL HEADER FUNCTION
\******************************************************************************/
string headder (string input, string extendedInput) {
  string output = "";

  // Print Top Line
  int fillWidth = titleWidth - 2 - globalHeaderStyle._TOP_LEFT.size() - globalHeaderStyle._TOP_RIGHT.size() - input.size();
  int halfFillWidth = fillWidth/2;

  output += globalHeaderStyle._TOP_LEFT;
  for (int i = 0; i < fillWidth - halfFillWidth; i++) {
    output+=globalHeaderStyle._TOP_FILL;
  }
  output += " " + input + " ";
  for (int i = 0; i < halfFillWidth; i ++) {
    output += globalHeaderStyle._TOP_FILL;
  }
  output += globalHeaderStyle._TOP_RIGHT;

  output += "\n";

  // Print Text filled Rows
  int whitespaceLength = titleWidth - globalHeaderStyle._LEFT_COLUMN.size() - globalHeaderStyle._RIGHT_COLUMN.size();
  if (extendedInput != "") {

    vector<string> textLines = align(extendedInput,extendedInputAlign,whitespaceLength);

    for (unsigned int i = 0; i < textLines.size(); i++) {
      output += globalHeaderStyle._LEFT_COLUMN;
      output += textLines[i];
      output += globalHeaderStyle._RIGHT_COLUMN + "\n";
    }
  }
  // Print blank rows
  if (titleLength == 0 && extendedInput == "") output += globalHeaderStyle._LEFT_COLUMN + "\n";
  else {
    for (unsigned int i = 0; i < titleLength; i++ ) {
      
      output += globalHeaderStyle._LEFT_COLUMN;
      for (int j = 0; j < whitespaceLength; j++ ) {
        output += " ";
      }
      output += globalHeaderStyle._RIGHT_COLUMN + "\n";

    }
  }

  // Print Bottom Line
  output += globalHeaderStyle._BOTTOM_LEFT;
  int bottomWidth = titleWidth - globalHeaderStyle._BOTTOM_LEFT.size() - globalHeaderStyle._BOTTOM_RIGHT.size();
  for (int i = 0; i < bottomWidth; i++) {
    output += globalHeaderStyle._BOTTOM_FILL;
  }
  output += globalHeaderStyle._BOTTOM_RIGHT;
  
  return output;
}

/******************************* TITLE HEADDER ********************************\
| the C title generator 
\******************************************************************************/
string title (string input) {
  string output = "";
  // Begin Comment
  int headerLength = titleWidth - globalTitleStyle._TOP_LEFT.size() - globalTitleStyle._TOP_RIGHT.size();
  output += globalTitleStyle._TOP_LEFT;
  for (int i = 0; i < headerLength; i++) {
    output += globalTitleStyle._TOP_FILL;
  }
  output += globalTitleStyle._TOP_RIGHT;

  output += "\n";

  // Middle Row
  int midLength = titleWidth - input.size() - 2 - globalTitleStyle._MID_LEFT_START.size() - globalTitleStyle._MID_RIGHT_END.size() - globalTitleStyle._MID_LEFT_END.size() - globalTitleStyle._MID_RIGHT_START.size();
  int halfLength = midLength / 2;

  output += globalTitleStyle._MID_LEFT_START;
  for (int i = 0; i < halfLength; i++) {
    output += globalTitleStyle._MID_LEFT_FILL;
  }
  output += globalTitleStyle._MID_LEFT_END;
  output += " " + input + " ";
  output += globalTitleStyle._MID_RIGHT_START;
  for (int i = 0; i < midLength - halfLength; i++) {
    output += globalTitleStyle._MID_RIGHT_FILL;
  }
  output += globalTitleStyle._MID_RIGHT_END;
  output += "\n";

  // Footer Line
  int footerLength = titleWidth - globalTitleStyle._BOTTOM_LEFT.size() - globalTitleStyle._BOTTOM_RIGHT.size();
  output += globalTitleStyle._BOTTOM_LEFT;
  for (int i = 0; i < footerLength; i++) {
    output += globalTitleStyle._BOTTOM_FILL;
  }
  output += globalTitleStyle._BOTTOM_RIGHT;

  return output;
}

/******************************** MY SIGNITURE ********************************\
| Returns my signiture, it's nice and pretty :) it takes in top, bottom and    |////////////
| column variables                                                             |////////////
\******************************************************************************/
string signiture () {

  struct passwd *pw = getpwuid(getuid());
  const char *homedir = pw->pw_dir;
  string path = string(homedir) + "/.signaturesource";


  string signature = "";
  string line;
  ifstream myfile;
  myfile.open(path.c_str());
  if (myfile.is_open())
  {
    getline (myfile,line);
    signature += line;
    while ( myfile.good() )
    {
      getline (myfile,line);
      signature += '\n'+line;
    }
    myfile.close();
  }

  else {
    cerr << "Unable to open signature file" << endl;
    cerr << path << endl;
  }

  extendedInputAlign = 'm';
  return headder ("SIGNATURE", signature);
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
string bsd(string owner) {
  // Get the width to wrap
  int fillWidth = titleWidth - globalHeaderStyle._TOP_LEFT.size() - globalHeaderStyle._TOP_RIGHT.size();

  // Calculate the Current Year
  string year = thisyear();
  
  // Top Half of the licence
  string content = "Copyright (c) "+year+", "+owner+"\n";
  content += "All rights reserved.\n";
  content += " \n";
  content += "Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: \n";
  content += " \n";

  // Clauses
  string clause1 = "Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.\n";
  string clause2 = "Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.\n";
  
  // Wrap the clauses smaller for 'indentation'
  vector<string> wrappedClause1 = wrap(clause1, fillWidth-2);
  clause1 = "* " + wrappedClause1[0] + "\n";
  for (unsigned int i = 1; i < wrappedClause1.size(); i++) {
    clause1 += "  " + wrappedClause1[i] + "\n";
  }
  vector<string> wrappedClause2 = wrap(clause2, fillWidth-2);
  clause2 = "* " + wrappedClause2[0] + "\n";
  for (unsigned int i = 1; i < wrappedClause2.size(); i++) {
    clause2 += "  " + wrappedClause2[i] + "\n";
  }

  // The actual licence
  string licence = " \nTHIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\n";

  string fullLicence = content + clause1 + clause2 + licence;

  return headder ("LICENCE", fullLicence);
}