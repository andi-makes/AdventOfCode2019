add_library(ImStandalone ImStandalone.cpp)
target_include_directories(ImStandalone PUBLIC .)
target_link_libraries(ImStandalone PUBLIC imgui glfw glad)
