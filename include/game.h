#pragma once
#include <vector>
#include "grid.h"
#include "../src/blocks.cpp"

class Game{
  public:
  Game();
  ~Game();
  void Draw();
  void HandleInput();
  void MoveBlockLeft();
  void MoveBlockRight();
  void MoveBlockDown();
  bool gameOver;
  int score;
  int highScore;
  Music music;

  private:
  Block GetRandomBlock();
  std::vector<Block> GetAllBlocks();
  bool IsBlockOutside();
  void RotateBlock();
  void LockBlock();
  bool BlockFits();
  void Reset();
  void UpdateScore(int linesCleared, int movedDownPoints);
  std::vector<Block> blocks;
  Block currentBlock;
  Block nextBlock;
  Grid grid;
  Sound rotateSound, clearSound;
};
