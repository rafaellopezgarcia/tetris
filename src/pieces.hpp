#pragma once
#include <iostream>
#include <array>
#include "color.hpp"
#include "point.hpp"

namespace tetris {

enum class Direction{
  DOWN,
  LEFT,
  RIGHT,
  UP
};

enum class Orientation{
  COUNTERCLOCKWISE,
  CLOCKWISE
};

enum class PieceName{
  SQUARE,
  LINE,
  J,
  L,
  S,
  T,
  Z
};

class Piece{
public:
  Piece() : position(0,0), direction(Direction::UP), color(Color::BLUE) {
  }

  virtual void Up() = 0;
  virtual void Down() = 0;
  virtual void Left() = 0;
  virtual void Right() = 0;

  void Move(Direction direction) {
    if(direction == Direction::DOWN) {
      ++position.x;
    }
    else if(direction == Direction::LEFT) {
      --position.y;
    }
    else if(direction == Direction::RIGHT) {
      ++position.y;
    }
    else if(direction == Direction::UP) {
      --position.x;
    }

    for (auto & p : points) {
      if(direction == Direction::DOWN) {
        ++p.x;
      }
      else if(direction == Direction::LEFT) {
        --p.y;
      }
      else if(direction == Direction::RIGHT) {
        ++p.y;
      }
      else if(direction == Direction::UP) {
        --p.x;
      }
    }
  }

  void Rotate(Orientation orientation) {
    if (orientation == Orientation::CLOCKWISE) {
      int ix = (static_cast<int>(direction) + 1) % clockwise_direction.size();
      direction = clockwise_direction[ix];
    }
    else {
      int ix = (static_cast<int>(direction) - 1) % clockwise_direction.size();
      direction = clockwise_direction[ix];
    }
  }

  void CounterClockwiseRotation() {
    int ix = (static_cast<int>(direction) - 1) % clockwise_direction.size();
    direction = clockwise_direction[ix];
  }

  std::array<Point, 4> GetPoints() {
    return points;
  }

  Point GetPostition() {
    return position;
  }

protected:
  std::array<Point, 4> points;
private:
  Point position;
  Direction direction;
  Color color;
  std::array<Direction, 4> clockwise_direction{Direction::UP, Direction::LEFT, Direction::DOWN, Direction::RIGHT};
};

// . . . . y
// .
// .
// .
// x


class Square : public Piece {
public:
  // [][]
  // [][]
  void Up() override {
    points[0] = Point{0, 0};
    points[1] = Point{0, 1};
    points[2] = Point{1, 0};
    points[3] = Point{1, 1};
  }

  void Left() override {
    Up();
  }

  void Down() override {
    Up();
  }

  void Right() override {
    Up();
  }
};

class J : public Piece {
public:
  void Up() {
    //   []
    //   []
    // [][]
    points[0] = Point{0, 1};
    points[1] = Point{1, 1};
    points[2] = Point{2, 0};
    points[3] = Point{2, 1};
  }

  void Left() {
    // [][][]
    //     []
    points[0] = Point{0, 0};
    points[1] = Point{0, 1};
    points[2] = Point{0, 2};
    points[3] = Point{1, 2};
  }

  void Down() {
    // [][]
    // []
    // []
    points[0] = Point{0, 0};
    points[1] = Point{0, 1};
    points[2] = Point{1, 0};
    points[3] = Point{2, 0};
  }

  void Right() {
    // []
    // [][][]
    points[0] = Point{0, 0};
    points[1] = Point{1, 0};
    points[2] = Point{1, 1};
    points[3] = Point{1, 2};
  }
};

class L : public Piece {
public:
  void Up() {
    // []
    // []
    // [][]
    points[0] = Point{0, 0};
    points[1] = Point{1, 0};
    points[2] = Point{2, 0};
    points[3] = Point{2, 1};
  }

  void Left() {
    //     []
    // [][][]
    points[0] = Point{0, 2};
    points[1] = Point{1, 0};
    points[2] = Point{1, 1};
    points[3] = Point{1, 2};
  }

  void Down() {
    // [][]
    //   []
    //   []
    points[0] = Point{0, 0};
    points[1] = Point{0, 1};
    points[2] = Point{1, 1};
    points[3] = Point{2, 1};
  }

  void Right() {
    // [][][]
    // []
    points[0] = Point{0, 0};
    points[1] = Point{0, 1};
    points[2] = Point{0, 2};
    points[3] = Point{1, 0};
  }
};

class Line : public Piece {
public:
  void Up() {
    // []
    // []
    // []
    // []
    points[0] = Point{0, 0};
    points[1] = Point{1, 0};
    points[2] = Point{2, 0};
    points[3] = Point{2, 1};
  }

  void Left() {
    // [][][][]
    points[0] = Point{0, 0};
    points[1] = Point{0, 1};
    points[2] = Point{0, 2};
    points[3] = Point{0, 3};
  }

  void Down() {
    Up();
  }

  void Right() {
    Left();
  }
};

class S : public Piece {
public:
  void Up() {
    //   [][]
    // [][]
    points[0] = Point{0, 1};
    points[1] = Point{0, 2};
    points[2] = Point{1, 0};
    points[3] = Point{1, 1};
  }

  void Left() {
    // []
    // [][]
    //   []
    points[0] = Point{0, 0};
    points[1] = Point{1, 0};
    points[2] = Point{1, 2};
    points[3] = Point{2, 1};
  }

  void Down() {
    Up();
  }

  void Right() {
    Left();
  }
};

class T : public Piece {
public:
  void Up() {
    // [][][]
    //   []
    points[0] = Point{0, 0};
    points[1] = Point{0, 1};
    points[2] = Point{0, 2};
    points[3] = Point{1, 1};
  }

  void Left() {
    // []
    // [][]
    // []
    points[0] = Point{0, 0};
    points[1] = Point{1, 0};
    points[2] = Point{1, 1};
    points[3] = Point{2, 0};
  }

  void Down() {
    //   []
    // [][][]
    points[0] = Point{0, 1};
    points[1] = Point{1, 0};
    points[2] = Point{1, 1};
    points[3] = Point{1, 2};
  }

  void Right() {
    //   []
    // [][]
    //   []
    points[0] = Point{0, 1};
    points[1] = Point{1, 0};
    points[2] = Point{1, 1};
    points[3] = Point{2, 1};
  }
};

class Z : public Piece {
public:
  void Up() {
    // [][]
    //   [][]
    points[0] = Point{0, 0};
    points[1] = Point{0, 1};
    points[2] = Point{1, 1};
    points[3] = Point{1, 2};
  }

  void Left() {
    //   []
    // [][]
    // []
    points[0] = Point{0, 1};
    points[1] = Point{1, 0};
    points[2] = Point{1, 1};
    points[3] = Point{2, 0};
  }

  void Down() {
    Up();
  }

  void Right() {
    Left();
  }
};

/*
bool Move(Piece piece, Direction direction) {
  auto points = piece.points;
  bool valid_move = true;
  int cols;
  int rows;
  for (auto & p : points) {
    if(direction == Direction::DOWN) {
      ++p.y;
    }
    else if(direction == Direction::LEFT) {
      --p.x;
    }
    else if(direction == Direction::RIGHT) {
      ++p.x;
    }
    else if(direction == Direction::UP) {
      --p.y;
    }
    if (invalid_cell(p.x, p.y) or occupied_cell(p.x, p.y)) {
      valid_move = false;
      break;
    }
  }
  if (valid_move) {
    piece.points = points;
  }
  return valid_move;
}

void Rotate(Piece piece, Orientation orientation) {
  Move(piece, direction);
}*/

}