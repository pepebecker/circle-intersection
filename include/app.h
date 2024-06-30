#ifndef __APP_H__
#define __APP_H__

#include <stdint.h>
#include "macros.h"

void start();

IMPORT_FUNC("print")
void println(const char* message);

IMPORT_FUNC("init")
void init();

IMPORT_FUNC("sqrt")
double sqrt(double x);

IMPORT_FUNC("createWindow")
void createWindow(const char* title, int32_t width, int32_t height);

IMPORT_FUNC("runGameLoop")
void runGameLoop(void (*gameLoop)(float), void (*onQuit)());

IMPORT_FUNC("setDrawColor")
void setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

IMPORT_FUNC("clearScreen")
void clearScreen();

IMPORT_FUNC("drawCircle")
void drawCircle(int32_t x, int32_t y, int32_t radius);

IMPORT_FUNC("drawLine")
void drawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1);

IMPORT_FUNC("destroyWindow")
void destroyWindow();

IMPORT_FUNC("setOnMouseMove")
void setOnMouseMove(void (*onMouseMove)(int x, int y));

#endif // __APP_H__

