#include <string>
#include <iostream>
#include <map>

#include "GLAD/includes/glad.h"
#include <GLFW/includes/glfw3.h>

#include "Math.hpp"
#include "Core/App.hpp"
#include "Threading/PoolSystem.hpp"

using namespace std;
using namespace Core::myMath;

int main()
{
	Core::App::p_AppSettings = {
		2400, 
		1200,
		4, 
		5,
		(char*)"Engine",
	};

	Core::App app;
	app.Init();
	app.Update();
	
	return 0;
}