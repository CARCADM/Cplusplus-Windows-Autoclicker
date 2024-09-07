#include "pch.h"
#include "MainClass.h"
#include "Windows.h"
#include <iostream>
#include <thread>

#pragma once
HINSTANCE hInst;
bool autoClicking = false;
bool autoClickingR = false;
int interval = 10, x = 500, y = 500, burstRate = 1;

// Actually performs the simulated mouse click
void SimulateMouseClick(int x, int y) {
	SetCursorPos(x, y);

	INPUT input[2] = {};

	input[0].type = INPUT_MOUSE;
	input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	input[1].type = INPUT_MOUSE;
	input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

	SendInput(2, input, sizeof(INPUT));
}

// Activates the click function including the interval only while autoclicking
void AutoClicker() {
	while (autoClicking) {
		SetCurrentMousePosition(x, y);
		for (int i = 0; i < burstRate; i++) {
			SimulateMouseClick(x, y);
		}
		Sleep(interval);
	}
}

// Sets x and y to the current x and y position of the mouse pointer
void SetCurrentMousePosition(int& x, int& y)
{
	POINT p;
	if (GetCursorPos(&p)) {
		x = p.x;
		y = p.y;
	}
}

void SetInterval(int newInterval) {
	interval = newInterval;
}

void SetBurstRate(int newBurstRate) {
	burstRate = newBurstRate;
}

