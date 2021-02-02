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
#include "main.h"

#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "./headertitle.h"
#include "./pipein.h"
#include "./editables.h"

using namespace std;


headerStyle globalHeaderStyle;
titleStyle globalTitleStyle;
std::map<char, headerStyle> headerStyles;
std::map<char, titleStyle> titleStyles;
std::map<char, std::string> languageNames;
std::map<char, std::string> languageDescription;

// Output format flag
char outputFormatFlag = 'f';  // defaults to the function header flag
bool outputFormatFlagSet = false;

// Output open flag
char outputRightWallFlag = 'e'; // Defaults to enclosed
bool outputRightWallFlagSet = false;

// Input flag
char inputLocationFlag = 'i'; // defaults to gathering from stdin
bool inputLocationFlagSet = false;


char outputLocationFlag = 'o'; // Defaults to printing to stdout
bool outputLocationFlagSet = false;


char outputAlignmentFlag = 'n'; // Defaults to left aligned
bool outputAlignmentFlagSet = false;


// The default title length
unsigned int titleLength = DEFAULT_TITLE_LENGTH;
unsigned int titleWidth = DEFAULT_TITLE_WIDTH;
std::map<std::string, std::string> fullFlagCompression;

bool postArgParseHalt = false;

std::map<char, std::vector<std::string> > languageAliases;



/**************************** INITILIZE FULL FLAGS ****************************\
| Add all of the full name alias functions to a list that can be parsed when   |
| the user is calling the function                                             |
\******************************************************************************/
void initilizeFullFlags() {
  fullFlagCompression["length"] = "l";
  fullFlagCompression["width"] = "w";
  fullFlagCompression["help"] = "h";
  fullFlagCompression["signature"] = "s";
  fullFlagCompression["bsd-license"] = "b";
  fullFlagCompression["title"] = "t";
  fullFlagCompression["function"] = "f";
  fullFlagCompression["clipboard"] = "v";
  fullFlagCompression["extended"] = "i";
  fullFlagCompression["align-middle"] = "m";
  fullFlagCompression["align-right"] = "r";
}


/******************************* ACTIVATE FLAGS *******************************\
| Given a specific character flag this functions changes internal variables to |
| change how the input / output works                                          |
|                                                                              |
| STATIC FLAGS                                                                 |
| h - help                                                                     |
| s - signature                                                                |
| f - function header                                                          |
| t - section title                                                            |
| b - bsd license                                                              |
| - - full tag (eg --help vs -h)                                    [External] |
| i - append input to the arguments                                            |
| m - align the extended input to the middle                                   |
| r - align the extended input to the right                                    |
| l - specify a custom character length for the title (default 80)  [External] |
\******************************************************************************/
bool activateFlag(char flag) {
  switch ( flag ) {
    // Chose one of these output flags
    case 'h':
    case 's':
    case 'b':
    case 't':
    case 'f':
      if(outputFormatFlagSet) {
        cout << "You have set multiple output format flags, only one is allowed" << endl;
        postArgParseHalt = true;
      }
      outputFormatFlag = flag;
      outputFormatFlagSet = true;
      return true;
    
    // Choose edge closed pattern
    case 'g':
    case 'e':
      if(outputRightWallFlagSet) {
        cout << "You have set multiple bounding box flags, only one is allowed" << endl;
        postArgParseHalt = true;
      }
      outputRightWallFlag = flag;
      outputRightWallFlagSet = true;
      return true;

    // Choose input location
    case 'i':
    case 'a':
    case 'c':
      if(inputLocationFlagSet) {
        cout << "You have set multiple input location flags, only one is allowed" << endl;
        postArgParseHalt = true;
      }
      inputLocationFlag = flag;
      inputLocationFlagSet = true;
      return true;

    // Choose output alignment
    case 'r':
    case 'm':
    case 'n':
      if (outputAlignmentFlagSet) {
        cout << "You have set multiple output alignment flags, only one is allowed" << endl;
        postArgParseHalt = true;
      }
      outputAlignmentFlag = flag;
      outputAlignmentFlagSet = true;
      return true;

    // Choose output location
    case 'o':   
    case 'v':
      if (outputLocationFlagSet) {
        cout << "You have set multiple output location flags, only one is allowed" << endl;
        postArgParseHalt = true;
      }
      outputLocationFlag = flag;
      outputLocationFlagSet = true;
      return true;
  }

  // Find the flag in the language map
  map<char, headerStyle>::iterator it = headerStyles.find(flag);
  if (it != headerStyles.end()) {
    globalHeaderStyle = headerStyles[flag];
    globalTitleStyle = titleStyles[flag];
    return true;
  }

  return false;
}


/*************************** CAPTURE EXTENDED INPUT ***************************\
| This function takes the input from stdin and returns it once the input has   |
| been terminated or two newline characters are detected without any data      |
| between them                                                                 |
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


string stripTrailingSpaces(string withTrailingSpaces) {
  string withoutTrailingSpaces = "";
  int cutoff = withTrailingSpaces.size()-1;
  for (; cutoff >= 0; cutoff--) {
    if (withTrailingSpaces[cutoff] != ' ') {
      break;
    }
  }
  for (int i = 0; i <= cutoff; i++) {
    withoutTrailingSpaces += withTrailingSpaces[i];
  }

  return withoutTrailingSpaces;
}


/************************************ MAIN ************************************\
| The main function handles all of the arguments for parsing  
\******************************************************************************/
int main(int argv, char * argc[]) {
  initilizeHeaderStyles();
  initilizeFullFlags();

  // parse arguments into a string
  string userInput = "";

  // used to append spaces after the first text argument
  string inputSpaces = "";

  // If there are no arguments, output the help screen
  if (argv <= 1) {
    help();
    return 0;
  }

  // create a vector of the arguments
  vector<string> arguments;
  for (int i = 0; i < argv; i++) {
    arguments.push_back(argc[i]);
  }

  // Loop through all of the arguments
  for (unsigned int i = 1; i < arguments.size(); i++) {
    // Check to see if the input is a flag
    if (arguments[i][0] == '-') {
      // Check to see if the flag is a fulltext flag
      if (arguments[i][1] == '-') {
        string flag = arguments[i];
        flag = flag.substr(2, flag.size() - 2);
        string smallflag = fullFlagCompression[flag];
        if (smallflag == "") {
          cout << "Undefined Argument: " << flag << endl;
          postArgParseHalt = true;
          continue;
        }
        else {
          arguments[i] = "-"+smallflag;
        }
      }
      for (unsigned int j = 1; j < arguments[i].size(); j++) {
        // Grab arguments for width
        if (arguments[i][j] == 'w') {
          if (i+1 >= arguments.size()) {
            cout << "Error: You did not specify a width for your title after using the -w flag" << endl;
            postArgParseHalt = true;
          }
          else {
            titleWidth = atoi(arguments[i + 1].c_str());
            arguments.erase(arguments.begin()+i+1);
          }
        }
        // Grab arguments for length
        else if (arguments[i][j] == 'l') {
          if (i+1 >= arguments.size()) {
            cout << "Error: You did not specify a length for your title after using the -l flag" << endl;
            postArgParseHalt = true;
          }
          else {
            titleLength = atoi(arguments[i + 1].c_str());
            arguments.erase(arguments.begin() + i + 1);
          }
        }
        else if (activateFlag(arguments[i][j])) {}
        else {
          cout << "Undefined flag: " << arguments[i][j] << endl;
          postArgParseHalt = true;  // Stop the program after parsing inputs
        }
      }
    }

    // Take all non flagged input and append it together
    else {
      userInput += inputSpaces + arguments[i];
      inputSpaces = " ";
    }
  }

  // Kill the program if any undefined flags were found
  if (postArgParseHalt) {
    return 1;
  }

  // Prevent the extended input flag and the tital flag from both being active
  if (inputLocationFlagSet && outputFormatFlag != 'f') {
    // extendedInputFlag = false; // TODO should this be replaced?
    cout << "Warning: the input location flag is ignored becasue you are not creating a function title" << endl;
  }

  // A string for containing the extended input's data
  string extendedInputString = "";


  stringstream output;
  // Check to see what type of header needs to be generated
  switch (outputFormatFlag) {
    case 'h':
      help();
      break;
    case 's':
      output << signiture() << endl;
      break;
    case 'b':
      output << bsd(userInput) << endl;
      break;
    case 't':
      output << title(userInput) << endl;
      break;
    case 'f':

      // Check for the input flag
      if (inputLocationFlag == 'a') {
        extendedInputString = "I AM NOT PARSING FROM ARGS PROPERLY"; // TODO: PARSE FROM ARGS
      }
      else if (inputLocationFlag == 'i') {
        extendedInputString = captureExtendedInput();
      }
      else if (inputLocationFlag == 'c') {
        extendedInputString = copyFromClipboard();
      }

      output << headder(userInput, extendedInputString, outputRightWallFlag) << endl;
      break;

    default:
      cout << "ERROR: UNKNOWN FORMAT FLAG FOUND" << endl;
  }

  // Output the results to stdout or to xclip depending on the flag specified
  
  if (outputLocationFlag == 'v') {
    if (copyToClipboard(output.str()) == -1) {
      // Print the output to stdout if xclip is not found
      cout << output.str();
    }
  }
  else if (outputLocationFlag == 'o') {
    cout << output.str();
  }
  else {
    cout << "Invalid outputLocationFlag" << endl;
    cout << output.str();
  }
}


/************************************ HELP ************************************\
| This is the help function it displays all of the possible settings that can  |
| be activated in the code and presents them to the user. It will              |
| automatically generate the information for the languages it supports using   |
| the data specified when generating the settings for the language             |
\******************************************************************************/
void help() {
  string languageflags = "";
  map<char, headerStyle>::iterator it = headerStyles.begin();
  while (it != headerStyles.end()) {
    languageflags += it->first;
    it++;
  }
  cout << "usage: chead [-" + languageflags + "] [-hsbtf] [-ge] [-ov] [-ic] [-nmr]" << endl;
  cout << "             [-l #] [-w #] <Input> [Input ...] " << endl;
  cout << endl;

  cout << "Output Size and Shape" << endl;
  cout << " -l --lines         Change how many rows are formatted within the title" << endl;
  cout << " -w --width         Change how many columns the text box takes up defaults to 80" << endl;
  cout << endl;

  cout << "Output Formats" << endl;
  cout << " -h --help          Bring up this help menu" << endl;
  cout << " -s --signature     Output your signature form sigfile correctly formatted" << endl;
  cout << " -b --bsd-license   Output a BSD license using the input as the copyright holder" << endl;
  cout << " -t --title         Output a title style header" << endl;
  cout << " -f --function      Output a function style header, default option" << endl;
  cout << endl;

  cout << "Bounding Box Options" << endl;
  cout << " -g --hanging       Function Output: Leave right hand side hanging with no padding" << endl;
  cout << " -e --enclosed      Function Output: Pad right hand side with whitespace and decorations" << endl;
  cout << endl;

  cout << "Output Destinations" << endl;
  cout << " -o --stdout         Write the output to the terminal" << endl;
  cout << " -v --clipboard-out  Copy the output to the clipboard instead of stdout" << endl;
  cout << endl;

  cout << "Input Formats" << endl;
  cout << " -i --stdin         Parse title from args and content input from stdin" << endl;
  // cout << " -a --argument-only Parse title from first arg and content from remainder" << endl;
  cout << " -c --clipboard-in  Parse title from args and content from clipboard" << endl;
  cout << endl;

  cout << "Content Alignment" << endl;
  cout << " -n --left-align    Content aligned to the left" << endl;
  cout << " -m --middle-align  Content aligned to the middle" << endl;
  cout << " -r --right-align   Content alligned to the right" << endl;
  cout << endl;

  // Dynamically create the language section based on the languages initialized
  cout << "Languages" << endl;
  it = headerStyles.begin();
  while (it != headerStyles.end()) {
    cout << " -" << it->first  << " --" << languageNames[it->first];
    for (int i = 0; i < (14 - languageNames[it->first].length()); i++) {
      cout << " ";
    }
    cout << languageDescription[it->first] << endl;
    it++;
  }
}


/************************************ WRAP ************************************\
| This function takes in a string of text wraps it to a specified width by     |
| moving words that push a single line over that width to the next line. It    |
| returns a vector of strings each element containing one line                 |
\******************************************************************************/
vector<string> wrap(string text, unsigned int width) {
  vector<string> lines;
  int lastSplit = 0;
  // Split on newlines
  for (unsigned int i = 0; i < text.size(); i++) {
    if (text[i] == '\n') {
      lines.push_back(text.substr(lastSplit, i-lastSplit));
      lastSplit = i + 1;
    }
  }
  if (text.substr(lastSplit, text.size() - lastSplit) != "") {
    lines.push_back(text.substr(lastSplit, text.size() - lastSplit));
  }

  // Split lines that are too long
  vector<string> wrappedLines;
  for (unsigned int i = 0; i < lines.size(); i++) {
    while (lines[i].size() > width) {
      int splitIndex = width;
      // Find the last space to prevent splitting mid-word
      for (int j = width-1; j >= 0; j--) {
        if (lines[i][j] == ' ') {
          splitIndex = j;
          break;
        }
      }

      wrappedLines.push_back(lines[i].substr(0, splitIndex));
      lines[i] = lines[i].substr(splitIndex + 1, lines.size() - splitIndex);
    }
    wrappedLines.push_back(lines[i]);
  }

  // Return the lines
  return wrappedLines;
}


/************************************ ALIGN ***********************************\
| This function takes in a vector of strings and adds spaces to either side    |
| of the string so that it becomes of length 'width'. The spaces are added to  |
| the left, right, or both sides to center the text depending on the position  |
| variable                                                                     |
\******************************************************************************/
vector<string> align(string text, char position, unsigned int width) {
  vector<string> wrapped = wrap(text, width);

  for (unsigned int i = 0; i < wrapped.size(); i++) {
    unsigned int difference = width-wrapped[i].size();
    switch (position) {
      case 'n':
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


/*********************************** HEADER *******************F****************\
| The header function takes in a title and a content variables for the header  |
| to display. It then runs the wrap and align functions and returns the        |
| wrapped and aligned text surrounded by the box style set by the user         |
\******************************************************************************/
string headder(string input, string extendedInput, char outputRightWallFlag) {

  bool fillRightWall = true;
  if (outputRightWallFlag == 'g') {
    fillRightWall = false;
  }


  vector<string> output;

  // Print Top Line
  int fillWidth = titleWidth - 2 - globalHeaderStyle._TOP_LEFT.size() - globalHeaderStyle._TOP_RIGHT.size() - input.size();
  int halfFillWidth = fillWidth/2;
  string topLine = globalHeaderStyle._TOP_LEFT;
  for (int i = 0; i < fillWidth - halfFillWidth; i++) {
    topLine+=globalHeaderStyle._TOP_FILL;
  }
  topLine += " " + input + " ";
  for (int i = 0; i < halfFillWidth; i ++) {
    topLine += globalHeaderStyle._TOP_FILL;
  }
  topLine += globalHeaderStyle._TOP_RIGHT;
  // output += "\n";
  output.push_back(topLine);

  // Print Text filled Rows
  int whitespaceLength = titleWidth - globalHeaderStyle._LEFT_COLUMN.size() - globalHeaderStyle._RIGHT_COLUMN.size();
  if (extendedInput != "") {
    vector<string> textLines = align(extendedInput, outputAlignmentFlag, whitespaceLength);
    for (unsigned int i = 0; i < textLines.size(); i++) {
      string middleLine = globalHeaderStyle._LEFT_COLUMN;
      middleLine += textLines[i];
      if (fillRightWall) {
        middleLine += globalHeaderStyle._RIGHT_COLUMN;
      }
      // output += "\n";
      output.push_back(middleLine);
    }
  }

  // Print blank rows
  if (titleLength == 0 && extendedInput == "") {
    output.push_back(globalHeaderStyle._LEFT_COLUMN);
  }
  else {
    for (unsigned int i = 0; i < titleLength; i++) {
      string blankLine = globalHeaderStyle._LEFT_COLUMN;
      for (int j = 0; j < whitespaceLength; j++) {
        blankLine += " ";
      }
      blankLine += globalHeaderStyle._RIGHT_COLUMN;
      output.push_back(blankLine);
    }
  }

  // Print Bottom Line
  string bottomLine = globalHeaderStyle._BOTTOM_LEFT;
  int bottomWidth = titleWidth - globalHeaderStyle._BOTTOM_LEFT.size() - globalHeaderStyle._BOTTOM_RIGHT.size();
  for (int i = 0; i < bottomWidth; i++) {
    bottomLine += globalHeaderStyle._BOTTOM_FILL;
  }
  bottomLine += globalHeaderStyle._BOTTOM_RIGHT;

  output.push_back(bottomLine);



  string textOutput = "";

  for (int i = 0; i < output.size(); i++) {
    textOutput += stripTrailingSpaces(output[i]) + "\n";
  }

  // Return the result
  return textOutput;
}


/******************************** TITLE HEADER ********************************\
| The title header function acts in a similar to the regular header function   |
| but it does not take in any content and surrounds it with a different        |
| wrapper. No line wrapping or aligning is done because the title can only be  |
| one line long and is automatically centered                                  |
\******************************************************************************/
string title(string input) {

  // Begin Comment Row
  string topLine = "";
  int headerLength = titleWidth - globalTitleStyle._TOP_LEFT.size() - globalTitleStyle._TOP_RIGHT.size();
  topLine += globalTitleStyle._TOP_LEFT;
  for (int i = 0; i < headerLength; i++) {
    topLine += globalTitleStyle._TOP_FILL;
  }
  topLine += globalTitleStyle._TOP_RIGHT;

  // Middle Row
  string middleLine = "";
  int midLength = titleWidth - input.size() - 2 - globalTitleStyle._MID_LEFT_START.size() - globalTitleStyle._MID_RIGHT_END.size() - globalTitleStyle._MID_LEFT_END.size() - globalTitleStyle._MID_RIGHT_START.size();
  int halfLength = midLength / 2;

  middleLine += globalTitleStyle._MID_LEFT_START;
  for (int i = 0; i < halfLength; i++) {
    middleLine += globalTitleStyle._MID_LEFT_FILL;
  }
  middleLine += globalTitleStyle._MID_LEFT_END;
  middleLine += " " + input + " ";
  middleLine += globalTitleStyle._MID_RIGHT_START;
  for (int i = 0; i < midLength - halfLength; i++) {
    middleLine += globalTitleStyle._MID_RIGHT_FILL;
  }
  middleLine += globalTitleStyle._MID_RIGHT_END;

  // Footer Row
  string bottomLine = "";
  int footerLength = titleWidth - globalTitleStyle._BOTTOM_LEFT.size() - globalTitleStyle._BOTTOM_RIGHT.size();
  bottomLine += globalTitleStyle._BOTTOM_LEFT;
  for (int i = 0; i < footerLength; i++) {
    bottomLine += globalTitleStyle._BOTTOM_FILL;
  }
  bottomLine += globalTitleStyle._BOTTOM_RIGHT;

  string output = "";
  output += stripTrailingSpaces(topLine) + "\n";
  output += stripTrailingSpaces(middleLine) + "\n";
  output += stripTrailingSpaces(bottomLine) + "\n";

  return output;
}


/******************************** MY SIGNATURE ********************************\
| Returns my signature, it's nice and pretty :) it takes in top, bottom and    |////////////
| column variables                                                             |////////////
\******************************************************************************/
string signiture() {
  struct passwd *pw = getpwuid(getuid());
  const char *homedir = pw->pw_dir;
  string path = string(homedir) + "/.signaturesource";

  string signature = "";
  string line;
  ifstream myfile;
  myfile.open(path.c_str());
  if (myfile.is_open()) {
    getline(myfile, line);
    signature += line;
    while (myfile.good()) {
      getline(myfile, line);
      signature += '\n' + line;
    }
    myfile.close();
  }
  else {
    cout << "Unable to open signature file" << endl;
    cout << path;
    return "";
  }

  outputAlignmentFlag = 'm';
  return headder("SIGNATURE", signature, outputRightWallFlag);
}


/******************************* CALCULATE YEAR *******************************\
| This functions calculates the current year for use in the BSD license        |
| function                                                                     |
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
| This function prints out the BSD license to the screen with the correct      |
| borders for the language selected                                            |
\******************************************************************************/
string bsd(string owner) {
  // Get the width to wrap
  int fillWidth = titleWidth - globalHeaderStyle._TOP_LEFT.size() - globalHeaderStyle._TOP_RIGHT.size();

  // Calculate the Current Year
  string year = thisyear();

  // Top Half of the license
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

  // The actual license
  string license = " \nTHIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\n";

  string fullLicense = content + clause1 + clause2 + license;

  return headder("LICENSE", fullLicense, outputRightWallFlag);
}
