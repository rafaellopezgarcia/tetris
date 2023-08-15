#include <iostream>
#include "tetris.hpp"

int main() {
  tetris::Tetris tetris(10, 20);
  tetris.Run();
  return 0;
}