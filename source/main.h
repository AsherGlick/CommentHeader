#ifndef __MAIN_H__
#define __MAIN_H__

#include "./headertitle.h"

#include <map>
#include <vector>
#include <string>

/////////////////////////////// GLOBAL VARIABLES /////////////////////////////////////////
extern headerStyle globalHeaderStyle;
extern titleStyle globalTitleStyle;
extern std::map<char, headerStyle> headerStyles;
extern std::map<char, titleStyle> titleStyles;
extern std::map<char, std::string> languageNames;
extern std::map<char, std::string> languageDescription;

// The default title length
#define DEFAULT_TITLE_LENGTH 0
extern unsigned int titleLength;
#define DEFAULT_TITLE_WIDTH 80
extern unsigned int titleWidth;
extern std::map<std::string, std::string> fullFlagCompression;
extern bool xclipMode;

extern bool postArgParseHalt;



void help();
std::string headder(std::string title, std::string extendedInput, char outputRightWallFlag);
std::string title(std::string title);
std::string signiture();
std::string bsd(std::string owner);

extern std::map<char, std::vector<std::string> > languageAliases;

#endif