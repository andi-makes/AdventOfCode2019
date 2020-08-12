#pragma once

#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <functional>
#include <string>

class Standalone {
	GLFWwindow* window;

	std::string title;

public:
	explicit Standalone(std::string title);
	~Standalone();

	bool run(const std::function<void(bool&)>& function);
};