#include <stdarg.h>
#include <stdio.h>

// Raylib - game development library
#include "raylib.h"

// Game state structure - holds all game data
typedef struct {
  int waterLevel;        // Water level percentage (0-100)
  int temperatureLevel;  // Temperature level (follows water)
  Rectangle levelBar;    // Left sidebar indicator
  Rectangle reservoir;   // Main water tank
} GameState;

int main(void)
{
  // Initialize window and set frame rate
  InitWindow(1280, 720, "Aqua Land");
  SetTargetFPS(60);

  // Initialize game state with starting values
  GameState game = {
      .waterLevel = 20,
      .temperatureLevel = 20,
      .levelBar = {100, 200, 50, 300},
      .reservoir = {200, 200, 600, 300}};

  // Button definitions (x, y, width, height)
  Rectangle btnRain = {300, 550, 200, 60};
  Rectangle btnEvaporate = {550, 550, 200, 60};
  Rectangle btnReset = {800, 550, 200, 60};

  while (!WindowShouldClose()) {
    // Input handling - get mouse position and check clicks
    Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      if (CheckCollisionPointRec(mousePos, btnRain)) {
        game.waterLevel = (game.waterLevel < 100) ? game.waterLevel + 10 : 100;
      }
      if (CheckCollisionPointRec(mousePos, btnEvaporate)) {
        game.waterLevel = (game.waterLevel > 0) ? game.waterLevel - 10 : 0;
      }
      if (CheckCollisionPointRec(mousePos, btnReset)) {
        game.waterLevel = 20;
      }
    }

    // Drawing phase
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw title
    DrawText("Aqua Land", 50, 30, 50, SKYBLUE);

    // Determine level status and colors based on water level
    const char* statusText;
    Color statusColor;
    Color gradientStart, gradientEnd;

    if (game.waterLevel < 30) {
      statusText = "Nível: Crítico";
      statusColor = RED;
      gradientStart = (Color){231, 111, 81, 255};  // Red
      gradientEnd = (Color){244, 165, 132, 180};
    } else if (game.waterLevel < 60) {
      statusText = "Nível: Moderado";
      statusColor = (Color){244, 162, 97, 255};  // Orange
      gradientStart = (Color){244, 162, 97, 255};
      gradientEnd = (Color){255, 217, 125, 180};
    } else {
      statusText = "Nível: Bom";
      statusColor = (Color){107, 207, 127, 255};  // Green
      gradientStart = (Color){107, 207, 127, 255};
      gradientEnd = (Color){168, 230, 176, 180};
    }

    DrawText(statusText, 450, 120, 35, statusColor);

    // Draw level indicator bar (changes height and color with water level)
    DrawRectangleRounded(game.levelBar, 0.2f, 10, LIGHTGRAY);
    Rectangle filledBar = game.levelBar;
    float levelPercent = game.waterLevel / 100.0f;
    filledBar.y += filledBar.height * (1 - levelPercent);
    filledBar.height *= levelPercent;

    // Draw gradient manually using multiple segments
    int segments = 10;
    for (int i = 0; i < segments; i++) {
      float t = (float)i / segments;
      Color color = (Color){
          (unsigned char)(gradientStart.r + (gradientEnd.r - gradientStart.r) * t),
          (unsigned char)(gradientStart.g + (gradientEnd.g - gradientStart.g) * t),
          (unsigned char)(gradientStart.b + (gradientEnd.b - gradientStart.b) * t),
          (unsigned char)(gradientStart.a + (gradientEnd.a - gradientStart.a) * t)};
      Rectangle segment = {
          filledBar.x,
          filledBar.y + (filledBar.height * i / segments),
          filledBar.width,
          filledBar.height / segments + 1};
      DrawRectangleRec(segment, color);
    }
    DrawRectangleRoundedLines(filledBar, 0.2f, 10, gradientStart);

    // Draw percentage text below the bar
    char percentText[8];
    sprintf(percentText, "%d%%", game.waterLevel);
    DrawText(percentText, 110, 510, 20, statusColor);

    // Draw water reservoir tank
    DrawRectangleRounded(game.reservoir, 0.05f, 10, LIGHTGRAY);
    Rectangle waterFill = game.reservoir;
    float waterPercent = game.waterLevel / 100.0f;
    waterFill.y += waterFill.height * (1 - waterPercent);
    waterFill.height *= waterPercent;

    // Draw water gradient manually
    int waterSegments = 10;
    for (int i = 0; i < waterSegments; i++) {
      float t = (float)i / waterSegments;
      Color color = (Color){
          (unsigned char)(72 + (0 - 72) * t),
          (unsigned char)(202 - (202 - 150) * t),
          (unsigned char)(228 - (228 - 199) * t),
          255};
      Rectangle segment = {
          waterFill.x,
          waterFill.y + (waterFill.height * i / waterSegments),
          waterFill.width,
          waterFill.height / waterSegments + 1};
      DrawRectangleRec(segment, color);
    }
    DrawRectangleRoundedLines(waterFill, 0.05f, 10, (Color){14, 157, 164, 255});

    // Draw control buttons
    DrawRectangleRounded(btnRain, 0.2f, 10, SKYBLUE);
    DrawText("Chover", 350, 565, 20, DARKBLUE);

    DrawRectangleRounded(btnEvaporate, 0.2f, 10, GOLD);
    DrawText("Evaporar", 590, 565, 20, DARKBROWN);

    DrawRectangleRounded(btnReset, 0.2f, 10, LIME);
    DrawText("Reiniciar", 840, 565, 20, DARKGREEN);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}