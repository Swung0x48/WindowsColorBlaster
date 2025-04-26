cmake_minimum_required(VERSION 3.16)
set (CMAKE_CXX_STANDARD 20)
set(PROJECT_NAME WindowsColorBlaster)
project(${PROJECT_NAME})

set(CMAKE_MODULE_PATH
  "${CMAKE_CURRENT_LIST_DIR}/buildsystems/cmake"
)

set(IMGUI_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/external/imgui)
set(IMPLOT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/external/implot)

find_package(ImGui REQUIRED)
find_package(ImPlot REQUIRED)

if (WIN32)
    set(OUTPUT_NAME_DX12 ${PROJECT_NAME}D3D12)
    add_executable(${OUTPUT_NAME_DX12} src/main_d3d12.cpp src/imcontext.cpp)
    target_link_libraries(${OUTPUT_NAME_DX12} ImGui)
    target_link_libraries(${OUTPUT_NAME_DX12} ImPlot)
    target_link_libraries(${OUTPUT_NAME_DX12} "d3d12.lib" "dxgi.lib" "d3dcompiler.lib")

    find_package(DirectX11)
    set(OUTPUT_NAME_DX11 ${PROJECT_NAME}D3D11)
    add_executable(${OUTPUT_NAME_DX11} src/main_d3d11.cpp src/imcontext.cpp
            src/canvas/canvas_d3d11.cpp
            src/canvas/canvas_d3d11.h)
    target_link_libraries(${OUTPUT_NAME_DX11} ImGui)
    target_link_libraries(${OUTPUT_NAME_DX11} ImPlot)
    target_link_libraries(${OUTPUT_NAME_DX11} ${DirectX11_LIBRARY})
endif()
