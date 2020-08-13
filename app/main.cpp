#include "ImStandalone.h"
#include "day1.h"
#include "imgui_stdlib.h"
#include "vm.h"

#include <filesystem>

int main() {
	Computer com;

	Standalone app{ "AoC 2019" };

	bool show_demo_window = false;
	bool show_file_popup  = false;

	while (app.run([&](bool& running) {
		auto& io = ImGui::GetIO();

		if (io.KeyCtrl && io.KeysDown[GLFW_KEY_W]) {
			running = false;
			return;
		} else if (io.KeyCtrl && io.KeysDown[GLFW_KEY_O] && !show_file_popup) {
			show_file_popup = true;
		}

		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("Files")) {
				if (ImGui::MenuItem("Load File", "Ctrl+O")) {
					show_file_popup = true;
				}

				if (ImGui::MenuItem("Exit", "Ctrl+W")) {
					running = false;
					return;
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Development")) {
				if (ImGui::MenuItem("Toggle Demo Window")) {
					show_demo_window = !show_demo_window;
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		if (ImGui::BeginTabBar("Days")) {
			if (ImGui::BeginTabItem("Computer")) {
				if (ImGui::CollapsingHeader("Memory")) {
					std::string fname;
					if (ImGui::InputText("##filename",
										 &fname,
										 ImGuiInputTextFlags_EnterReturnsTrue)) {
						com.load(std::filesystem::path(fname));
					}
					ImGui::SameLine();
					if (ImGui::Button("Load File")) {
						com.load(std::filesystem::path(fname));
					}

					ImGui::Text("Memory Size: %llu Integers", com.mem.size());
					ImGui::Separator();
					ImGui::Columns(8);
					for (size_t i = 0; i < com.mem.size(); i++) {
						ImGui::Text("%d", com.mem[i]);
						ImGui::NextColumn();
					}
					ImGui::Columns(1);
					ImGui::EndDragDropTarget();
					ImGui::Separator();
				}
				if (ImGui::CollapsingHeader("Control")) {
					if (ImGui::Button("Step")) {
						com.step();
					}
					ImGui::SameLine();
					if (ImGui::Button("Execute")) {
						com.execute();
					}
				}
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Day 1")) {
				{
					static int total_mass = -1;
					if (ImGui::Button("Compute##D1.1")) {
						total_mass = 0;
						for (auto mass : day1::masses) {
							total_mass += day1::fuel_per_module(mass);
						}
					}
					ImGui::SameLine();
					ImGui::Text("Total mass needed: %d!", total_mass);
				}
				{
					static int total_mass = -1;
					if (ImGui::Button("Compute##D1.2")) {
						total_mass = 0;
						for (auto mass : day1::masses) {
							total_mass += day1::fuel_per_module_part_2(mass);
						}
					}
					ImGui::SameLine();
					ImGui::Text("Total mass needed: %d!", total_mass);
				}

				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();

			ImGui::End();

			if (show_demo_window) {
				ImGui::ShowDemoWindow(&show_demo_window);
			}
		}
	}))
		;

	return 0;
}
