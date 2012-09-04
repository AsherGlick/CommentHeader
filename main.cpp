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
using namespace std;

void help();
string cHead(string input, string top, string col, string bot);
string cTitle(string input);
string htmlHead(string input);
string pythonHead(string input);
string pythonTitle(string input);
string signiture(string,string,string);
string bsd(string input,string top,string col,string mid);

string cppTop    = "/******************************************************************************\\";
string pythonTop = "################################################################################";
string htmlTop   = "<!------------------------------------------------------------------------------"; 

string cppColumn = "|";
string pythonColumn = "#";
string htmlColumn = "|";

string cppBottom = "\\******************************************************************************/";
string pythonBottom = "################################################################################";
string htmlBottom   = "------------------------------------------------------------------------------->";



int main (int argv, char * argc[])
{
  // check input functions
  if (argv <= 1)
  {
    help();
    return 0;
  }
  if (string(argc[1]) == "--h" || string(argc[1]) == "--help")
  {
    help();
    return 0;
  }
  // parse arguments into a string
  string input;
  if (argv > 2) {
    input = string(argc[2]);
    for (int i = 3; i < argv; i++) input += " "+string(argc[i]);
  }
  else input = "";
  // Check to see what type of headder needs to be generated
  if (string(argc[1]) == "-c")         cout << cHead(input,cppTop   ,cppColumn   ,cppBottom)    << endl; // C / C++ HEADDER
  else if (string(argc[1]) == "-h")    cout << cHead(input,htmlTop  ,htmlColumn  ,htmlBottom)   << endl; // HTML HEADDER
  else if (string(argc[1]) == "-p")    cout << cHead(input,pythonTop,pythonColumn,pythonBottom) << endl; // Python HEADDER
  
  
  else if (string(argc[1]) == "-ct")   cout << cTitle(input) << endl; // C / C++ TITLE HEADDER
  else if (string(argc[1]) == "-pt")   cout << pythonTitle(input) << endl; // Python TITLE HEADDER
  else if (string(argc[1]) == "-sig")  cout << signiture(cppTop,cppColumn,cppBottom) << endl; // Asher Glick Signiture
  else if (string(argc[1]) == "-psig") cout << signiture(pythonTop,pythonColumn,pythonBottom) << endl; // python formatted signature
  else if (string(argc[1]) == "-bsd")  cout << bsd(input,cppTop,cppColumn,cppBottom) << endl; // default bsd licence
  else if (string(argc[1]) == "-pbsd") cout << bsd(input,pythonTop,pythonColumn,pythonBottom) << endl;
  else if (string(argc[1]) == "-fsig") cout << signiture(cppTop,cppColumn,cppBottom) << endl << bsd("Asher Glick",cppTop,cppColumn,cppBottom) << endl; // Signature and licence
  //else if (string(argc[1]) == "-pfsig") cout << pythonSigniture() << pbsd(2,"Asher Glick") << endl; // 
  else { // Defaut to c headder
    string input = string(argc[1]);
    for (int i = 2; i < argv; i++) input += " "+string(argc[i]);
    cout << cHead(input,cppTop,cppColumn,cppBottom) << endl;
  }
}

  /****************************************************************************/
 /****************************************************************************/
/****************************************************************************/

  //////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


/************************************ HELP ************************************\
|
\******************************************************************************/
void help()
{
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
  
  // new style
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
