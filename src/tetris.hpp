#include <iostream>
#include <chrono>
#include <memory>
#include <thread>
#include <random>
#include <vector>

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
    piece = std::make_shared<Square>();
    piece->SetOrientation(directions[distrib_dir(gen)]);
    
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
    curs_set(0);
    screen.Add(piece);
    board.Add(piece->GetPoints());
    for (int i = 0; i < 500; ++i) {
      int c = getch();
      bool update_piece = false;
      switch (c) {
        case KEY_LEFT:
        TryToMove(Direction::LEFT);
        break;
        case KEY_RIGHT:
        TryToMove(Direction::RIGHT);
        break;
        case ' ':
        update_piece = !TryToMove(Direction::DOWN);
        break;
        case KEY_UP:
        TryToRotate(Orientation::COUNTERCLOCKWISE);
        break;
        case KEY_DOWN:
        TryToRotate(Orientation::CLOCKWISE);
        break;

      }
      screen.Refresh();
      //sleep_for(milliseconds(300));
      if (update_piece) {
        RemoveLines();
        piece = selector.Select();
        screen.Add(piece);
        board.Add(piece->GetPoints());
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
    screen.Remove(piece);
    board.Remove(piece->GetPoints());
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
    screen.Add(piece);
    board.Add(piece->GetPoints());
    return can_move;
  }

  bool TryToRotate(Orientation orientation) {
    bool can_rotate = true;
    screen.Remove(piece);
    board.Remove(piece->GetPoints());
    piece->Rotate(orientation);
    if (!CanMove()) {
      if (orientation == Orientation::CLOCKWISE) {
        piece->Rotate(Orientation::COUNTERCLOCKWISE);
      }
      else {
        piece->Rotate(Orientation::CLOCKWISE);
      }
      can_rotate = false;
    }
    screen.Add(piece);
    board.Add(piece->GetPoints());
    return can_rotate;
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

  void RemoveLines() {
    std::vector<int> row_status(board.GetLength(), true);

    for(const auto & p : piece->GetPoints()) {
      int col = 0;
      row_status[p.x] = false;
      for(int col = 0; col < board.GetWidth(); ) {
        if (board.FreeCell(p.x, col)) {
          row_status[p.x] = true;
          break;
        }
        ++col;
      }
    }
    int j = board.GetLength() - 1;
    for(int i = board.GetLength() - 1; i >= 0; --i) {
      if (!row_status[i]) {
        for (int col = 0; col < board.GetWidth(); ++col) {
          board.Remove(i, col);
          screen.Remove(i, col);
        }
      }
      else {
        if (i != j) {
          for (int col = 0; col < board.GetWidth(); ++col) {
            if (board.Get(i, col) != Color::NONE){
              board.Add(j, col);
              screen.Add(j, col);
            }
            board.Remove(i, col);
            screen.Remove(i, col);
          }
        }
        --j;
      }
    }

  }

};


}