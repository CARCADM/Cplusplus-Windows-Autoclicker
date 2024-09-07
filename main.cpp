#include "pch.h"
#include "MainClass.h"
#include <iostream>
#include <thread>

using namespace winrt;
using namespace Windows::Foundation;

// Turns the auto clicker on and off when the function is run
// Creates a new thread where the actual auto clicking is handled seperately
void ToggleAutoClicker() {
	if (autoClicking) {
		std::thread(AutoClicker).detach();
		std::cout << "Auto clicking started.\n";
	}
	else {
		std::cout << "Auto clicking stopped.\n";
	}
}

// The method to control the hotkey to enable and disable the auto clicker
void HotkeyThread() {
	// Registers the hotkey
	// NOTE: to change the hotkey button change the MOD_CONTROL or 0x59 parameter
	// Refer to https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerhotkey and https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes to set the custom hotkey
	RegisterHotKey(NULL, 1, MOD_CONTROL | 0x4000, 0x59);
	MSG msgX;

	// Constantly Checks if the hotkey is being pressed
	while (true) {
		if (GetMessage(&msgX, NULL, 0, 0) > 0) {
			if (msgX.message == WM_HOTKEY) {
				autoClicking = !autoClicking;
				ToggleAutoClicker();
			}
		}
	}
}

// The primary method within the code
int main() {
	std::thread t1(HotkeyThread);
	char command;
	int setSpacing;
	int setNewBurstRate;

	//Shows the user the list of avalible commands
	std::cout << "Auto Clicker\n";
	std::cout << "Commands\n";
	std::cout << "s: Start/Stop the program\n";
	std::cout << "g: Set the interval between each click\n";
	std::cout << "h: Sets the burst rate that happens every interval\n";
	std::cout << "q: Quit\n";
	std::cout << "\n(left ctrl + y enables/disables autoclicking)";

	//Collects the user input of the user into the comsole discluding any hotkey commands
	while (true) {
		std::cout << "Enter command: ";
		std::cin >> command;

		if (command == 's') {
			autoClicking = !autoClicking;
			if (autoClicking) {
				std::thread(AutoClicker).detach();
				std::cout << "Auto clicking started.\n";
			}
			else {
				std::cout << "Auto clicking stopped.\n";
			}
		}
		else if (command == 'g') {
			std::cout << "Set the new interval rate for the auto clicker 10 - 1000ms\n";
			std::cin >> setSpacing;
			SetInterval(setSpacing);
		}
		else if (command == 'h') {
			std::cout << "Set the new burst rate for the auto clicker\n";
			std::cin >> setNewBurstRate;
			SetBurstRate(setNewBurstRate);
		}
		else if (command == 'q') {
			std::cout << "Qutting...\n";
			break;
		}
		else {
			std::cout << "Unknown command.\n";
		}
	}
	t1.detach();
	return 0;
}
