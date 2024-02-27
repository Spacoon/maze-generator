#include "App.h"

int main() {
	App a;
	while (a.IsRunning())
	{
		a.Update();
		a.Render();
	}
}

