#include "headertitle.h"

headerStyle::headerStyle () {
  _TOP_LEFT     = "";
  _TOP_FILL     = " ";
  _TOP_RIGHT    = "";
  _LEFT_COLUMN  = "";
  _RIGHT_COLUMN = "";
  _BOTTOM_LEFT  = "";
  _BOTTOM_FILL  = " ";
  _BOTTOM_RIGHT = "";
}

headerStyle::headerStyle (
  std::string top_left,
  std::string top_fill,
  std::string top_right,
  std::string left_column,
  std::string right_column,
  std::string bottom_left,
  std::string bottom_fill,
  std::string bottom_right
) {
  _TOP_LEFT     = top_left;
  _TOP_FILL     = top_fill;
  _TOP_RIGHT    = top_right;
  _LEFT_COLUMN  = left_column;
  _RIGHT_COLUMN = right_column;
  _BOTTOM_LEFT  = bottom_left;
  _BOTTOM_FILL  = bottom_fill;
  _BOTTOM_RIGHT = bottom_right;
}



titleStyle::titleStyle(){}

titleStyle::titleStyle(
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
) {
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