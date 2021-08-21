# CMakeList.txt : CMake project for LEDControl69, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (LEDControl69 "LEDControl69.cpp" "LEDControl69.h" "Networking/ADDRESS_CONFIG.h" "Networking/e131_packet.cpp" "Networking/e131_packet.h" "Networking/ledcontrol.cpp" "Networking/ledcontrol.h" "Networking/udpsend_windows.cpp" "Networking/udpsend_windows.h" "Networking/ledcontrol_tests.cpp" "Networking/ledcontrol_tests.h" "Graphics/DomeViewer.cpp" "Graphics/DomeViewer.h" "Graphics/graphics_test.cpp" "Graphics/graphics_test.h" "Objects/node.h" "Objects/node.cpp" "Objects/strut.h" "Objects/strut.cpp" "Objects/graph.cpp" "Objects/graph.h" "Objects/dome.cpp" "Objects/dome.h" "Graphics/render.h" "Graphics/render.cpp" "Objects/led.cpp" "Objects/led.h")

# TODO: Add tests and install targets if needed.
find_package(Easy3D REQUIRED)
target_link_libraries(LEDControl69 easy3d::core easy3d::renderer easy3d::viewer easy3d::util) # you may request more modules (e.g., viewer, algo)
