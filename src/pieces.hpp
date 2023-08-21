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

  virtual void Up() {
    direction = Direction::UP;
  }
  virtual void Down() {
    direction = Direction::DOWN;
  }
  virtual void Left() {
    direction = Direction::LEFT;
  }
  virtual void Right() {
    direction = Direction::RIGHT;
  }

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

  void SetOrientation(Direction direction) {
    this->direction = direction;
    switch (direction) {
      case Direction::DOWN:
        Down();
      break;
      case Direction::LEFT:
        Left();
      break;
      case Direction::RIGHT:
        Right();
      break;
      case Direction::UP:
        Up();
      break;
    }

    for (auto & p : points) {
      p.x += position.x;
      p.y += position.y;
    }
  }

  void Rotate(Orientation orientation) {
    if (orientation == Orientation::CLOCKWISE) {
      switch (direction){
        case Direction::DOWN:
          SetOrientation(Direction::LEFT);
          break;
        case Direction::LEFT:
          SetOrientation(Direction::UP);
          break;
        case Direction::UP:
          SetOrientation(Direction::RIGHT);
          break;
        case Direction::RIGHT:
          SetOrientation(Direction::DOWN);
          break;
      }
    }

    else {
      switch (direction){
        case Direction::DOWN:
          SetOrientation(Direction::RIGHT);
          break;
        case Direction::RIGHT:
          SetOrientation(Direction::UP);
          break;
        case Direction::UP:
          SetOrientation(Direction::LEFT);
          break;
        case Direction::LEFT:
          SetOrientation(Direction::DOWN);
          break;
      }
    }
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
    Piece::Up();
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
    Piece::Up();
    points[0] = Point{0, 1};
    points[1] = Point{1, 1};
    points[2] = Point{2, 0};
    points[3] = Point{2, 1};
  }

  void Left() {
    // [][][]
    //     []
    Piece::Left();
    points[0] = Point{0, 0};
    points[1] = Point{0, 1};
    points[2] = Point{0, 2};
    points[3] = Point{1, 2};
  }

  void Down() {
    // [][]
    // []
    // []
    Piece::Down();
    points[0] = Point{0, 0};
    points[1] = Point{0, 1};
    points[2] = Point{1, 0};
    points[3] = Point{2, 0};
  }

  void Right() {
    // []
    // [][][]
    Piece::Right();
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
    Piece::Up();
    points[0] = Point{0, 0};
    points[1] = Point{1, 0};
    points[2] = Point{2, 0};
    points[3] = Point{2, 1};
  }

  void Left() {
    //     []
    // [][][]
    Piece::Left();
    points[0] = Point{0, 2};
    points[1] = Point{1, 0};
    points[2] = Point{1, 1};
    points[3] = Point{1, 2};
  }

  void Down() {
    // [][]
    //   []
    //   []
    Piece::Down();
    points[0] = Point{0, 0};
    points[1] = Point{0, 1};
    points[2] = Point{1, 1};
    points[3] = Point{2, 1};
  }

  void Right() {
    // [][][]
    // []
    Piece::Right();
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
    Piece::Up();
    points[0] = Point{0, 0};
    points[1] = Point{1, 0};
    points[2] = Point{2, 0};
    points[3] = Point{3, 0};
  }

  void Left() {
    // [][][][]
    Piece::Left();
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
    Piece::Up();
    points[0] = Point{0, 1};
    points[1] = Point{0, 2};
    points[2] = Point{1, 0};
    points[3] = Point{1, 1};
  }

  void Left() {
    // []
    // [][]
    //   []
    Piece::Left();
    points[0] = Point{0, 0};
    points[1] = Point{1, 0};
    points[2] = Point{1, 1};
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
    Piece::Up();
    points[0] = Point{0, 0};
    points[1] = Point{0, 1};
    points[2] = Point{0, 2};
    points[3] = Point{1, 1};
  }

  void Left() {
    // []
    // [][]
    // []
    Piece::Left();
    points[0] = Point{0, 0};
    points[1] = Point{1, 0};
    points[2] = Point{1, 1};
    points[3] = Point{2, 0};
  }

  void Down() {
    //   []
    // [][][]
    Piece::Down();
    points[0] = Point{0, 1};
    points[1] = Point{1, 0};
    points[2] = Point{1, 1};
    points[3] = Point{1, 2};
  }

  void Right() {
    //   []
    // [][]
    //   []
    Piece::Right();
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
    Piece::Up();
    points[0] = Point{0, 0};
    points[1] = Point{0, 1};
    points[2] = Point{1, 1};
    points[3] = Point{1, 2};
  }

  void Left() {
    //   []
    // [][]
    // []
    Piece::Left();
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

}