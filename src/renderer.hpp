#pragma once
#include <vector>
#include <array>
#include <ncurses.h>

#include "pieces.hpp"

namespace tetris {
class Screen {
public:
  Screen(int width, int length) : width(width), length(length) {
    initscr();
    keypad(stdscr, TRUE);
    int row, col;
    getmaxyx(stdscr,row,col);
    xoffset = row /2 - length/2;
    yoffset = col / 2 - width;
  }

  void AddBorders() {
    for (int x = 0; x < length; ++x) {
      Add(x, -1);
      Add(x, width);
    }
    for(int y = -1; y <= width ; ++y) {
      Add(-1, y);
      Add(length, y);
    }
    refresh();
  }


  void Add(std::shared_ptr<Piece> & piece) {
    for(const auto & p : piece->GetPoints()) {
      Add(p.x, p.y);
    }
  }

  void Remove(std::shared_ptr<Piece> & piece) {
    for(const auto & p : piece->GetPoints()) {
      Remove(p.x, p.y);
    }
  }

  void Add(int x, int y) {
    mvprintw(xoffset + x , yoffset + y * 2, "[]");
  }

  void Remove(int x, int y) {
    mvprintw(xoffset + x , yoffset + y * 2, "  ");
  }

  void Refresh() {
    refresh();
    move(0,0);
  }


private:
  int xoffset;
  int yoffset;
  int width;
  int length;
  std::vector<std::vector<int>> screen;
};
} // namespace tetris