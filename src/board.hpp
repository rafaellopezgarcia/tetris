#pragma once

#include <vector>
#include <array>
#include "point.hpp"


namespace tetris
{
class Board {

public:

  Board(int width, int length) : width(width), length(length) {

  }
  void Update(int x, int y, Color color) {
    board[x][y] = color; 
  }

  bool FreeCell(int x, int y) {
    
    return ValidCell(x, y) and board[x][y] == Color::BLACK;
  }

  bool ValidCell(int x, int y) {
    return x >= 0 and x < length and y >= 0 and y < width; 
  }

private:
  const int width;
  const int length;
  std::vector<std::vector<Color>> board;

};

} // namespace tetris

