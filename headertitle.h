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
#include <string>
/***************************** HEADER STYLE CLASS *****************************\
| The header style class is a class for each of the different style of headers |
| for each different language. It allows an easy way of creating and           |
| classifying different 
\******************************************************************************/
class headerStyle {
  public:
    headerStyle () {
      _TOP_LEFT     = "";
      _TOP_FILL     = " ";
      _TOP_RIGHT    = "";
      _LEFT_COLUMN  = "";
      _RIGHT_COLUMN = "";
      _BOTTOM_LEFT  = "";
      _BOTTOM_FILL  = " ";
      _BOTTOM_RIGHT = "";
    }
    headerStyle (std::string top_left, std::string top_fill, std::string top_right, std::string left_column, std::string right_column, std::string bottom_left, std::string bottom_fill, std::string bottom_right) {
      _TOP_LEFT     = top_left;
      _TOP_FILL     = top_fill;
      _TOP_RIGHT    = top_right;
      _LEFT_COLUMN  = left_column;
      _RIGHT_COLUMN = right_column;
      _BOTTOM_LEFT  = bottom_left;
      _BOTTOM_FILL  = bottom_fill;
      _BOTTOM_RIGHT = bottom_right;
    }
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
    titleStyle() {

    }

    titleStyle(std::string topleft,std::string topfill,std::string topright,std::string midleftstart,std::string midleftfill,std::string midleftend,std::string midrightstart,std::string midrightfill,std::string midrightend,std::string bottomleft,std::string bottomfill,std::string bottomright) {
      _TOP_LEFT = topleft;
      _TOP_FILL = topfill;
      _TOP_RIGHT = topright;

      _MID_LEFT_START = midleftstart;
      _MID_LEFT_FILL = midleftfill;
      _MID_LEFT_END = midleftend;

      _MID_RIGHT_START = midrightstart;
      _MID_RIGHT_FILL = midrightfill;
      _MID_RIGHT_END = midrightend;

      _BOTTOM_LEFT = bottomleft;
      _BOTTOM_FILL = bottomfill;
      _BOTTOM_RIGHT = bottomright;
    }

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