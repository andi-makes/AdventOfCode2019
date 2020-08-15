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
        imgui/imgui_widgets.cpp
        imgui/misc/cpp/imgui_stdlib.cpp
        imgui/examples/imgui_impl_glfw.cpp
        imgui/examples/imgui_impl_opengl3.cpp
        )
target_link_libraries(imgui PRIVATE glfw glad)
target_include_directories(imgui PUBLIC imgui imgui/misc/cpp imgui/examples)

add_subdirectory(glfw)