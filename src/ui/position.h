#ifndef _POSITION_H
#define _POSITION_H

class Position {
  public:
    bool left_shifted;
    bool top_shifted;

  public:
    Position(bool is_left_shifted, bool is_top_shifted);
};

#endif
