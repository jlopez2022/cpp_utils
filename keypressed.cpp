#include <iostream>
#include <Windows.h>
using namespace std;

bool keydown(int key)
{
	return (GetAsyncKeyState(key) & 0x8000) != 0;
}

int main()
{
	while (!keydown(VK_ESCAPE))
	{
		if (keydown(VK_UP))
			cout << "UP" << endl;
		else if (keydown(VK_DOWN))
			cout << "DOWN" << endl;
		else if (keydown(VK_LEFT))
			cout << "LEFT" << endl;
		else if (keydown(VK_RIGHT))
			cout << "RIGHT" << endl;
		else if (keydown('W'))
			cout << "W" << endl;
		else if (keydown('A'))
			cout << "A" << endl;
		Sleep(10);
	}

	return 0;
}