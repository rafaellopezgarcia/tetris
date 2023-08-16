#include <iostream>
#include <chrono>
#include <memory>
#include <thread>
#include <random>

#include "pieces.hpp"
#include "board.hpp"
#include "renderer.hpp"

namespace tetris {

class PieceSelector{
public:
  std::array<PieceName, 7> piece_names;
  std::array<Direction, 4> directions;
  PieceSelector () : gen(std::random_device{}()), distrib(0, 6), distrib_dir(0, 3) {
    piece_names = {PieceName::SQUARE, PieceName::LINE, PieceName::J, PieceName::L, PieceName::S, PieceName::T, PieceName::Z};
    directions = {Direction::DOWN, Direction::LEFT, Direction::RIGHT, Direction::UP};

    std::uniform_int_distribution<> distrib_dir(0, 3);
  }

  std::shared_ptr<Piece> Select() {
    switch (piece_names[distrib(gen)]) {
      case PieceName::SQUARE:
        piece = std::make_shared<Square>();
      break;
      case PieceName::LINE:
        piece = std::make_shared<Line>();
      break;
      case PieceName::J:
        piece = std::make_shared<J>();
      break;
      case PieceName::L:
        piece = std::make_shared<L>();
      break;
      case PieceName::S:
        piece = std::make_shared<S>();
      break;
      case PieceName::T:
        piece = std::make_shared<T>();
      break;
      case PieceName::Z:
        piece = std::make_shared<Z>();
      break;
    }

    switch (directions[distrib_dir(gen)]) {
      case Direction::DOWN:
        piece->Down();
      break;
      case Direction::LEFT:
        piece->Left();
      break;
      case Direction::RIGHT:
        piece->Right();
      break;
      case Direction::UP:
        piece->Up();
      break;
    }
    return piece;
  }

private:
  std::mt19937 gen;
  std::uniform_int_distribution<> distrib;
  std::uniform_int_distribution<> distrib_dir;
  std::shared_ptr<Piece> piece;
};

class Tetris {
public:
  Tetris(int width, int length) : width(width), length(length), board(width, length), screen(width, length) {
    screen.AddBorders();
  }

  void AddPiece() {
    piece = std::make_shared<Square>();
    piece->Up();
    screen.Refresh();
  }

  void Run() {
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    PieceSelector selector;
    piece = selector.Select();
    
    for (int i = 0; i < 100; ++i) {
      
      screen.Remove(piece);
      board.Remove(piece->GetPoints());
      bool update_piece = !TryToMove(Direction::DOWN);
      screen.Add(piece);
      board.Add(piece->GetPoints());
      screen.Refresh();

      sleep_for(milliseconds(300));
      if (update_piece) {
        piece = selector.Select();
      }
    }
  
    getch();
	  endwin();
  }

private:
  const int width;
  const int length;
  Board board;
  Screen screen;
  std::shared_ptr<Piece> piece;

  bool TryToMove(Direction direction) {
    bool can_move = true;
    piece->Move(direction);
    if (!CanMove()) {
      if (direction == Direction::DOWN) {
        piece->Move(Direction::UP);
      }
      if (direction == Direction::LEFT) {
        piece->Move(Direction::RIGHT);
      }
      if (direction == Direction::RIGHT) {
        piece->Move(Direction::LEFT);
      }
      if (direction == Direction::UP) {
        piece->Move(Direction::DOWN);
      }
      can_move = false;
    }
    return can_move;
  }

  bool CanMove() {
    bool can_move = true;
    for(const auto & p : piece->GetPoints()) {
      //std::cout << p.x << " " << p.y << std::endl;
      if (!board.ValidCell(p.x, p.y) or !board.FreeCell(p.x, p.y)) {
        can_move = false;
        break;
      }
    }
    return can_move;
  }
  
/*
 
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
*/
};


}