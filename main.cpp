#include <iostream>
#include <windows.h>

void getMousePosition(int& xPos, int& yPos) {
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	xPos = cursorPos.x;
	yPos = cursorPos.y;
}

void mouseLeftClick()
{
	INPUT Input = { 0 };

	// left down
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));

	// left up
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}

void mouseMoveTo(int ayy, int bee)
{
	//double screenRes_width = ::GetSystemMetrics(SM_CXSCREEN) - 1;
	//double screenRes_height = ::GetSystemMetrics(SM_CYSCREEN) - 1;
	//float factor = 65535.0f / screenRes_width;
	//std::cout << "\nfactor: " << factor;
	//----------------------------
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;

	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

	Input.mi.dx = ayy;
	Input.mi.dy = bee;

	::SendInput(1, &Input, sizeof(INPUT));
}

int main()
{
	//-----------Configuration part----------------
	int clickRate = 10; //Click rate in seconds
	//-----------End Configuration-----------------

	bool lockMode = false;
	int xCurrentPos = 0;
	int yCurrentPos = 0;
	bool stop = false;
	
	int time = 0;
	while (!stop) {
		Sleep(10);
		if (GetKeyState(VK_RSHIFT) & 0x8000) {
			lockMode = !lockMode;
		}
		//std::cout << "\nPosition x:" << xCurrentPos << " y:" << yCurrentPos;
		if (GetKeyState(VK_MENU) & 0x8000) {//Check if high-order bit is set (1 << 15)
			stop = true;
		} else {
			if (GetKeyState(VK_LBUTTON) & 0x8000) {
				std::cout << "\nLBUTTON pressed" << time;
			}
			if ((time%(clickRate*100) == 0) && !(GetKeyState(VK_LBUTTON) & 0x8000)) {
				getMousePosition(xCurrentPos, yCurrentPos);
				mouseMoveTo(63000, 60000); //Move mouse to the button we want to autoclick
				mouseLeftClick();
				mouseMoveTo(120000, 1000); //Move mouse to the top of the window we're working in
				mouseLeftClick(); //Click to make it active again
				double ratioX = 42.70;
				double ratioY = 76;
				//std::cout << "\nPosition x:" << xCurrentPos << " y:" << yCurrentPos;
				//std::cout << "\nx*ratio=" << xCurrentPos * ratioX << " y*ratio=" << yCurrentPos * ratioY;
				mouseMoveTo(xCurrentPos*ratioX, yCurrentPos*ratioY);
			}
			if (lockMode) {
				mouseMoveTo(30000, 30000);
			}
		}
		time++;
	}

	//system("pause");
	return 0;
}

