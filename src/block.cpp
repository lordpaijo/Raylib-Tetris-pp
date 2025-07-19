#include "../include/block.h"
#include "../include/position.h"
#include <vector>

Block::Block(){
  cellSize = 27;
  rotationState = 0;
  colors = GetCellColors();
  rowOffset = 0;
  columnOffset = 0;
}

void Block::Draw(int offset_x, int offset_y){
  std::vector<Position> tiles = GetCellPosition();
  for (Position item: tiles) {
    DrawRectangle(item.column * cellSize + offset_x, item.row * cellSize + offset_y, cellSize - 1, cellSize - 1, colors[id]);
  }
}

void Block::Move(int rows, int columns){
  rowOffset += rows;
  columnOffset += columns;
}

std::vector<Position> Block::GetCellPosition(){
  std::vector<Position> tiles = cells[rotationState];
  std::vector<Position> movedTiles;
  for (Position item: tiles){
    Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
    movedTiles.push_back(newPos);
  }
  return movedTiles;
}

void Block::Rotate(){
  rotationState++;
  if (rotationState == (int)cells.size()) rotationState = 0;
}

void Block::undoRotation(){
  rotationState--;
  if (rotationState == -1) rotationState = cells.size() - 1;
}
