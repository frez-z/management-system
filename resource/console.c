// Created by farez
#include <windows.h>
#include <time.h>

HANDLE wHnd;    // Handle to write to the console. (using windows api)

void createConsoleWindow(short width, short length){
    // Set up the handles for writing:
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND consoleWindow = GetConsoleWindow();

    SMALL_RECT windowSize = {0 , 0 , width, length}; // window size
    COORD coord = {width + 1, length + 1}; // buffer size
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize); // set window size
    SetConsoleScreenBufferSize(wHnd, coord); // set buffer size same as window size
    ShowScrollBar(consoleWindow, SB_BOTH, 0); // disable scroll bar

    // disable maximize and minimize button
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

void moveCursor(short x, short y){
    COORD coord = {x , y};
    SetConsoleCursorPosition(wHnd, coord);
}

void delay(int millisecond){
    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + millisecond);
}