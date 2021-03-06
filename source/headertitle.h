/******************************************************************************\
| Copyright (c) 2012-2021, Asher Glick                                         |
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
#ifndef __HEADERTITLE_H__
#define __HEADERTITLE_H__

#include <string>

/***************************** HEADER STYLE CLASS *****************************\
| The header style class is a class for each of the different style of headers |
| for each different language. It allows an easy way of creating and           |
| classifying different 
\******************************************************************************/
class headerStyle {
  public:
    headerStyle ();
    headerStyle (
      std::string top_left,
      std::string top_fill,
      std::string top_right,
      std::string left_column,
      std::string right_column,
      std::string bottom_left,
      std::string bottom_fill,
      std::string bottom_right
    );

    std::string _TOP_LEFT;
    std::string _TOP_FILL;
    std::string _TOP_RIGHT;
    
    std::string _LEFT_COLUMN;
    std::string _RIGHT_COLUMN;
    
    std::string _BOTTOM_LEFT;
    std::string _BOTTOM_FILL;  
    std::string _BOTTOM_RIGHT;
};


/********************************* TITLE STYLE ********************************\
| The title stule class is a class for each of the differnet styles of titles  |
| each one stores the beginning, end, and fill characters for each language    |
| the titleStyle represents                                                    |
\******************************************************************************/
class titleStyle {
  public:
    titleStyle();

    titleStyle(
      std::string topleft,
      std::string topfill,
      std::string topright,
      std::string midleftstart,
      std::string midleftfill,
      std::string midleftend,
      std::string midrightstart,
      std::string midrightfill,
      std::string midrightend,
      std::string bottomleft,
      std::string bottomfill,
      std::string bottomright
    );

    std::string _TOP_LEFT;
    std::string _TOP_FILL;
    std::string _TOP_RIGHT;

    std::string _MID_LEFT_START;
    std::string _MID_LEFT_FILL;
    std::string _MID_LEFT_END;

    std::string _MID_RIGHT_START;
    std::string _MID_RIGHT_FILL;
    std::string _MID_RIGHT_END;

    std::string _BOTTOM_LEFT;
    std::string _BOTTOM_FILL;
    std::string _BOTTOM_RIGHT;
};

#endif