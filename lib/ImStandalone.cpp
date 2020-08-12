#include "ImStandalone.h"

#include "imgui_impl_glfw.h"
#include "imgui_internal.h"

#include <iostream>
#include <utility>

namespace {
	void glfw_error_callback(int error, const char* description) {
		std::cerr << "GLFW Error " << error << ": " << description << std::endl;
	}
}

Standalone::Standalone(std::string title) : title(std::move(title)) {
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit()) {
		// Todo: Throw exception or something
	}

	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	// The window *HAS* to be 1 by 1 pixel large. GLFW will construct the smallest possible window.
	// This should guarantee that the ImGui Window does not fit into the original Window. Thus, a
	// new Window managed by ImGui will be created.
	window = glfwCreateWindow(1, 1, title.c_str(), nullptr, nullptr);

	if (window == nullptr) {
		// Todo: Throw exception or something
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (gladLoadGL() == 0) {
		std::cerr << "Failed to initialize OpenGL loader!" << std::endl;
		// Todo: Throw exception or something
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io	   = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable |
					 ImGuiConfigFlags_ViewportsEnable | ImGuiConfigFlags_DpiEnableScaleViewports |
					 ImGuiConfigFlags_DpiEnableScaleFonts;
	io.ConfigViewportsNoDefaultParent = true;

	ImGui::StyleColorsDark();
	ImGuiStyle& style	 = ImGui::GetStyle();
	style.WindowRounding = 0.0f;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

Standalone::~Standalone() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Standalone::run(const std::function<void(bool&)>& function) {
	if (glfwWindowShouldClose(window))
		return false;

	bool running = true;

	glfwPollEvents();

	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin(title.c_str(), &running);

	function(running);

	ImGui::End();

	ImGui::Render();

	glViewport(0, 0, display_w, display_h);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	GLFWwindow* backup_current_context = glfwGetCurrentContext();
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	glfwMakeContextCurrent(backup_current_context);

	glfwSwapBuffers(window);

	return running;
}
