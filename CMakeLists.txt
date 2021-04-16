# CMakeList.txt : CMake project for Game-of-Life, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Game-of-Life")

# Specify the C++ standard
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED True)

# Mark the build as an executable file on Linux/Unix
set (MainOrWinMain "")
if (UNIX AND NOT APPLE)
	set (CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -no-pie")
else()
	set (MainOrWinMain "WIN32")
endif()

# Add include and link directories
include_directories("${PROJECT_SOURCE_DIR}/include")

if (WIN32)
	include_directories("${PROJECT_SOURCE_DIR}/include/msvc")
endif()

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})

# link_directories("${PROJECT_SOURCE_DIR}/lib/vc142_x64_dll")

# Compile definitions required by wxWidgets
add_compile_definitions("UNICODE" "_UNICODE" "wxMSVC_VERSION_AUTO" "WXUSINGDLL")

# Add source to this project's executable.
add_executable (Game-of-Life ${MainOrWinMain} "Game-of-Life.cpp"  "source/LifeBoard.cpp" "source/LifeBoard.h" "source/LifeBoardLogic.cpp" "source/LifeBoardLogic.h" "source/DrawBoard.cpp" "source/DrawBoard.h")

target_link_libraries(Game-of-Life ${wxWidgets_LIBRARIES})

# TODO: Add tests and install targets if needed.
