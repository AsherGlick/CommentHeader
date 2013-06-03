/*************************** INITILIZE HEADER STYLES **************************\
| Include all of the header and title styles into the list of possible styles  |
| to choose from. In order to add  a new language you just need to set a new   |
| element of both the 'globalHeaderStyle' map and the 'globalTitleStyle' map   |
\******************************************************************************/
void initilizeHeaderStyles() {
  // C / C++ Styles
  #define _C 'C'
  globalHeaderStyle = headerStyles[_C] = headerStyle("/*","*","*\\","| "," |","\\*","*","*/");
  globalTitleStyle = titleStyles [_C] = titleStyle ("  /","/","/"," /","/","/","/","/","/ ","/","/","/  ");
  languageNames[_C] = "c++";
  languageDescription[_C] = "Format comments in a C/C++/Java style";
  languageAliases[_C] = {"c","java","javascipt","c#","go","actionscript"};

  //Python Header Style
  #define _PYTHON 'P'
  headerStyles[_PYTHON] = headerStyle("#","#","#","# "," #","#","#","#");
  titleStyles [_PYTHON] = titleStyle ("#","#","#","#","#","","","#","#","#","#","#");
  languageNames[_PYTHON] = "python";
  languageDescription[_PYTHON] = "Format comments in a Python style";
  languageAliases[_PYTHON] = {"shell","perl","ruby","php"};

  // LaTeX Header Style
  #define _LATEX 'X'
  headerStyles[_LATEX] = headerStyle("%","%","%","% "," %","%","%","%");
  titleStyles [_LATEX] = titleStyle (" %","%","% ","%%","%","","","%","%%"," %","%","% ");
  languageNames[_LATEX] = "latex";
  languageDescription[_LATEX] = "Format comments in a LaTeX style";
  languageAliases[_LATEX] = {"prolog","matlab","erlang"};

  //HTML Header Style
  #define _HTML 'H'
  headerStyles[_HTML] = headerStyle("<!--","-","+ "," | ","| "," +","-","-->");
  titleStyles[_HTML] = titleStyle("  <!--","-","-->"," <!--","-","-","-","-","--> ","<!--","-","-->  ");
  languageNames[_HTML] ="html";
  languageDescription[_HTML] = "Format Comments in HTML style";
  languageAliases[_HTML] = {"xml"};

  // No Border Style
  #define _NONE 'N'
  headerStyles[_NONE] = headerStyle(""," ","","","",""," ","");
  titleStyles[_NONE] = titleStyle(""," ","",""," ","",""," ","",""," ","");
  languageNames[_NONE] = "none";
  languageDescription[_NONE] = "Format the comment without a border";
  languageAliases[_NONE] = {"borderless"};

}

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