# Glad
add_library(
        glad
        glad/src/glad.c
)
target_include_directories(glad PUBLIC glad/include)

# Dear ImGui
add_library(imgui
        imgui/imgui.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_impl_glfw.cpp
        imgui/imgui_impl_opengl3.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_stdlib.cpp
        )
target_link_libraries(imgui PRIVATE glfw glad)
target_include_directories(imgui PUBLIC imgui)
