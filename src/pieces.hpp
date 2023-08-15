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

  void Move(Direction direction) {
    if(direction == Direction::DOWN) {
      ++position.y;
    }
    else if(direction == Direction::LEFT) {
      --position.x;
    }
    else if(direction == Direction::RIGHT) {
      ++position.x;
    }
    else if(direction == Direction::UP) {
      --position.y;
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


class Square : public Piece{
public:
  // [][]
  // [][]
  void Up() {
    points[0] = Point{0, 0};
    points[1] = Point{0, 1};
    points[2] = Point{1, 0};
    points[3] = Point{1, 1};
  }

  void Left() {
    Up();
  }

  void Down() {
    Up();
  }

  void Right() {
    Up();
  }
};

/*

class J {
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

private:
  std::array<Point, 4> points;
};

class L {
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

private:
  std::array<Point, 4> points;
};

class Line {
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

private:
  std::array<Point, 4> points;
};

class S {
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

private:
  std::array<Point, 4> points;
};

class T {
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

  void down() {
    //   []
    // [][][]
    points[0] = Point{0, 1};
    points[1] = Point{1, 0};
    points[2] = Point{1, 1};
    points[3] = Point{1, 2};
  }

  void right() {
    //   []
    // [][]
    //   []
    points[0] = Point{0, 1};
    points[1] = Point{1, 0};
    points[2] = Point{1, 1};
    points[3] = Point{2, 1};
  }

private:
  std::array<Point, 4> points;
};

class Z {
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

private:
  std::array<Point, 4> points;
};*/




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