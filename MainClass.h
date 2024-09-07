#ifndef AUTOCLICKER_H
#define AUTOCLICKER_H

#include <Windows.h>

void SimulateMouseClick(int x, int y);
void AutoClicker();
void SetCurrentMousePosition(int& x, int& y);
void ToggleAutoClicker();
void HotkeyThread();
void SetInterval(int newInterval);
void SetBurstRate(int newBurstRate);

extern bool autoClicking;
extern int interval, x, y;

#endif // AUTOCLICKER_H