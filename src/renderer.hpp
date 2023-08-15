#pragma once
#include <vector>

#include <ncurses.h>

class Screen {
public:
  Screen(int width, int length) : width(width), length(length) {
    initscr();
    int row, col;
    getmaxyx(stdscr,row,col);
    xoffset = row /2 - length/2;
    yoffset = col / 2 - width;
  }

  void AddBorders() {
    int x = 0, y = 0;
    for (x = 0; x < length; ++x) {
      Add(x, y);
      Add(x, y + width - 1);
    }
    for(int y = 0; y < width ; ++y) {
      Add(0, y);
      Add(length - 1, y);
    }
    refresh();
    getch();
	  endwin();
  }

  void Add(int x, int y) {
    mvprintw(xoffset + x, yoffset + y * 2, "[]");
  }

private:
  int xoffset;
  int yoffset;
  int width;
  int length;
  std::vector<std::vector<int>> screen;
};