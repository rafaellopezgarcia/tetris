#include <iostream>
#include <memory>
#include "pieces.hpp"
#include "board.hpp"
#include "renderer.hpp"


namespace tetris {

class Tetris {
public:
  Tetris(int width, int length) : width(width), length(length), board(width, length), screen(width, length) {
    screen.AddBorders();
  }

  void Run() {
    std::shared_ptr<Piece> piece = std::make_shared<Square>();
  }

private:
  const int width;
  const int length;
  Board board;
  Screen screen;
  
/*
  void Run() {
    Piece piece;
    while(true) {
      if(!TryToMove(piece, Direction::DOWN)){
        piece = NewPiece();
      }
    }
  }
  Piece NewPiece() {

  }

  bool TryToMove(Piece piece, Direction direction) {
    bool can_move = true;
    piece.Move(direction);
    if (!CanMove(piece)) {
      if (direction == Direction::DOWN) {
        piece.Move(Direction::UP);
      }
      if (direction == Direction::LEFT) {
        piece.Move(Direction::RIGHT);
      }
      if (direction == Direction::RIGHT) {
        piece.Move(Direction::LEFT);
      }
      if (direction == Direction::UP) {
        piece.Move(Direction::DOWN);
      }
      can_move = false;
    }
    return can_move;
  }

  bool TryToRotate(Piece piece, Orientation orientation) {
    bool can_rotate = true;
    piece.Rotate(orientation);
    if (!CanMove(piece)) {
      if (orientation == Orientation::CLOCKWISE) {
        piece.Rotate(Orientation::COUNTERCLOCKWISE);
      }
      else {
        piece.Rotate(Orientation::CLOCKWISE);
      }
      can_rotate = false;
    }
    return can_rotate;
  }


  bool CanMove(Piece piece) {
    bool can_move = true;
    for(auto p : piece.points) {
      if (!board.FreeCell(p.x, p.y)) {
        can_move = false;
        break;
      }
    }
    return can_move;
  }
  void Collapses() {
    
  }
  
  Board board;
*/
};


}