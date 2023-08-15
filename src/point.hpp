#pragma once

namespace tetris {

struct Point{
  Point() : x(0), y(0) {
  }
  Point(int x, int y) : x(x), y(y) {

  }
  int x;
  int y;
};

}
