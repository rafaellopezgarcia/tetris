#pragma once

#include <vector>
#include <array>
#include "point.hpp"


namespace tetris
{
class Board {

public:

  Board(int width, int length) : width(width), length(length), 
                                 board(length, std::vector<Color>(width, Color::NONE)) {

  }
  void Update(int x, int y, Color color) {
    board[x][y] = color; 
  }

  bool FreeCell(int x, int y) {
    return ValidCell(x, y) and board[x][y] == Color::NONE;
  }

  bool ValidCell(int x, int y) {
    return x >= 0 and x < length and y >= 0 and y < width; 
  }

  void Add(const std::array<Point, 4> & points) {
    for(const auto & p : points) {
      Add(p.x, p.y);
    }
  }

  void Remove(const std::array<Point, 4> & points) {
    for(const auto & p : points) {
      Remove(p.x, p.y);
    }
  }

  void Add(int x, int y){
    board[x][y] = Color::GREEN;
  }

  void Remove(int x, int y){
    board[x][y] = Color::NONE;
  }

private:
  const int width;
  const int length;
  std::vector<std::vector<Color>> board;

};

} // namespace tetris

