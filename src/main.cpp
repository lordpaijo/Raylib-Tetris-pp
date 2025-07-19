#include "../include/game.h"
#include "../include/raylib.h"
#include "game.cpp"
#include <cstdio>


Color Suface0 = Color{48, 52, 70, 255};
double lastUpdateTime = 0;

bool EventTriggered(double interval){
  double CurrentTime = GetTime();
  if (CurrentTime - lastUpdateTime >= interval){
    lastUpdateTime = CurrentTime;
    return true;
  };
  return false;
}

int main()
{
  const int screenWidth = 760;
  const int screenHeight = 835;

  InitWindow(screenWidth, screenHeight, "Tetris++ by LordPaijo");
  SetTargetFPS(120);

  Game game = Game();
  Font font = LoadFontEx("../font/Blox2.ttf", 64, 0, 0);

  while (!WindowShouldClose())
  {
    UpdateMusicStream(game.music);
    game.HandleInput();
    if (EventTriggered(0.230)) game.MoveBlockDown();

    BeginDrawing();
    ClearBackground(BaseC);

    DrawTextEx(font, "Score", {560,15}, 38, 2, WHITE);
    DrawTextEx(font, "High Score", {560,160}, 38, 2, WHITE);
    DrawTextEx(font, "Next", {560,315}, 38, 2, WHITE);
    if (game.gameOver) DrawTextEx(font, "GAME\nOVER", {560,565}, 40, 2, RED);

    char scoreText[10];
    sprintf(scoreText,"%d", game.score);

    char highScoreText[10];
    sprintf(highScoreText,"%d", game.highScore);

    Vector2 scoreSize = MeasureTextEx(font, scoreText, 38, 2);

    DrawTextEx(font, "Game by\nLordPaijo\n\nOn\ngithub.com/ \nlordpaijo", {565,screenHeight-200}, 28, 2, WHITE);
    DrawRectangleRounded({560, 65, 140, 60}, 0.3, 6, frappe.FrappeSurface0);
    DrawTextEx(font, scoreText, {540 + (170 - scoreSize.x)/2,75}, 38, 2, WHITE);
    DrawRectangleRounded({560, 215, 140, 60}, 0.3, 6, frappe.FrappeSurface0);
    DrawTextEx(font, highScoreText, {540 + (170 - scoreSize.x)/2, 225}, 38, 2, WHITE);
    DrawRectangleRounded({560, 360, 170, 180}, 0.3, 6, frappe.FrappeSurface1);

    game.Draw();

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
