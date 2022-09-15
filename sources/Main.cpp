#include <string>
#include <iostream>
#include <map>

#include "GLAD/includes/glad.h"
#include <GLFW/includes/glfw3.h>

#include "Math.hpp"
#include "Core/App.hpp"
#include "Utils/Threading/PoolSystem.hpp"

using namespace std;
using namespace Core::myMath;

int main()
{
	Core::App app;
	app.Init();
	app.Update();
	
	return 0;
}