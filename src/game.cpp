#include "../include/game.h"
#include "grid.cpp"
#include "../include/position.h"
#include "../include/raylib.h"
#include <vector>

Game::Game(){
  grid = Grid();
  blocks = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  gameOver = false;
  score = 0;
  highScore = score;
  InitAudioDevice();
  music = LoadMusicStream("../sounds/tetris.mp3");
  rotateSound = LoadSound("../sounds/rotate.mp3");
  clearSound = LoadSound("../sounds/clear.mp3");
  PlayMusicStream(music);
}

Game::~Game(){
  UnloadSound(rotateSound);
  UnloadSound(clearSound);
  UnloadMusicStream(music);
  CloseAudioDevice();
}

Block Game::GetRandomBlock(){
  if (blocks.empty()) {
    blocks = GetAllBlocks();
  }

  int randomIndex = rand() % blocks.size();
  Block block = blocks[randomIndex];
  blocks.erase(blocks.begin() + randomIndex);
  return block;
}

std::vector<Block> Game::GetAllBlocks(){
  return {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw(){
  grid.Draw();
  currentBlock.Draw(11,11);
  switch (nextBlock.id) {
    case 3:   nextBlock.Draw(388 - 11, 420 + 20);       break;
    case 4:   nextBlock.Draw(388 - 15, 423);            break;
    default:  nextBlock.Draw(388, 420);                 break;
  }
}

void Game::HandleInput(){
  int keyPressed = GetKeyPressed();
  if (gameOver && keyPressed != 0) {
    gameOver = false;
    Reset();
  }
  switch (keyPressed) {
    case KEY_LEFT:
    case KEY_A:
    MoveBlockLeft();
    break;

    case KEY_RIGHT:
    case KEY_D:
    MoveBlockRight();
    break;

    case KEY_DOWN:
    case KEY_SPACE:
    case KEY_S:
    MoveBlockDown();
    UpdateScore(0,1);
    break;

    case KEY_UP:
    case KEY_R:
    RotateBlock();
    break;

    case KEY_BACKSPACE:
    Reset();
    break;
  }
}

void Game::MoveBlockLeft(){
  if (!gameOver){
    currentBlock.Move(0,-1);
    if (IsBlockOutside() || !BlockFits()) {
      currentBlock.Move(0,1);
      LockBlock();
    }
  }
}

void Game::MoveBlockRight(){
  if (!gameOver){
    currentBlock.Move(0,1);
    if (IsBlockOutside() || !BlockFits()) {
      currentBlock.Move(0,-1);
      LockBlock();
    }
  }
}

void Game::MoveBlockDown(){
  if (!gameOver){
    currentBlock.Move(1,0);
    if (IsBlockOutside() || !BlockFits()) {
      currentBlock.Move(-1,0);
      LockBlock();
    }
  }
}

bool Game::IsBlockOutside(){
  std::vector<Position> tiles = currentBlock.GetCellPosition();
  for (Position item : tiles){
    if (grid.isCellOutside(item.row, item.column)) return true;
  }
  return false;
}

void Game::RotateBlock(){
  if (!gameOver){
    if (!IsBlockOutside()) currentBlock.Rotate();
    else currentBlock.undoRotation();
  } else {
    PlaySound(rotateSound);
  }
}

void Game::LockBlock(){
  std::vector<Position> tiles = currentBlock.GetCellPosition();
  for (Position item : tiles){
    grid.grid[item.row][item.column] = currentBlock.id;
  }
  currentBlock = nextBlock;
  if (!BlockFits()) gameOver = true;
  nextBlock = GetRandomBlock();
  int rowsCleared = grid.ClearFullRows();
  if (rowsCleared != 0) {
    PlaySound(clearSound);
    UpdateScore(rowsCleared, 0);
  }
}

bool Game::BlockFits(){
  std::vector<Position> tiles = currentBlock.GetCellPosition();
  for (Position item : tiles){
    if (grid.isCellEmpty(item.row, item.column) == false) return false;
  }
  return true;
}

void Game::Reset(){
  grid.Initialize();
  blocks = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  if (highScore < score) highScore = score;
  score = 0;
}

void Game::UpdateScore(int linesCleared, int movedDownPoints){
  switch (linesCleared) {
    case 1: score += 100;
    break;
    case 2: score += 300;
    break;
    case 3: score += 500;
    default: break;
  }
  score += movedDownPoints;
}
