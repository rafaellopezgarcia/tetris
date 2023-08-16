#include <iostream>
#include "tetris.hpp"

int main() {
  tetris::Tetris tetris(10, 15);
  tetris.Run();
  return 0;
}