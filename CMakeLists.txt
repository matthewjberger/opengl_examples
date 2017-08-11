cmake_minimum_required(VERSION 3.0)
project(opengl_examples)

# Specify build type
IF(NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE Debug)
ENDIF(NOT CMAKE_BUILD_TYPE)

# Place targets into their own solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Ensure C++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

# GLFW build options
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(vendor/glfw)

# Assimp build options
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(vendor/assimp)

# Bullet build options
option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)
add_subdirectory(vendor/bullet)

# Freetype2 build options
add_subdirectory(vendor/freetype2)

# Boxer build options
add_subdirectory(vendor/boxer)

if(MSVC)
    # Set warning level 4 when using Visual Studio
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    # Set compiler flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    if(NOT WIN32)
        # GLAD requires libdl on Unix systems
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(core/
                    vendor/assimp/include/
					vendor/boxer/include/
                    vendor/bullet/src/
					vendor/freetype2/include/
                    vendor/glad/include/
                    vendor/glfw/include/
                    vendor/glm/
                    vendor/stb/)

# Create file globs
file(GLOB GLAD_SOURCE vendor/glad/src/glad.c)
file(GLOB_RECURSE CORE_HEADERS core/*.h)
file(GLOB_RECURSE CORE_SOURCES core/*.cpp)
file(GLOB PROJECT_CONFIGS 	CMakeLists.txt
							Readme.md
							.gitattributes
							.gitignore
							.gitmodules)

# Use file globs to create filters for Visual Studio
source_group("Headers" FILES ${CORE_HEADERS})
source_group("Sources" FILES ${CORE_SOURCES})
source_group("Configs" FILES ${CORE_CONFIGS})
source_group("Glad"	   FILES ${GLAD_SOURCE})

# GLFW_INCLUDE_NONE tells GLFW not to include OpenGL headers.
# This flag is used when using GLFW with an extension loading library.
add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

# Link dependencies
set( CORE_LIBS  assimp
				Boxer
				glfw
				freetype
				${GLFW_LIBRARIES}
    			${GLAD_LIBRARIES}
				BulletDynamics
				BulletCollision
				LinearMath )

# Add demo directories
add_subdirectory(examples/playground)
add_subdirectory(examples/triangle)
add_subdirectory(examples/triangle_rgba)
add_subdirectory(examples/rectangle)
add_subdirectory(examples/uniforms)
add_subdirectory(examples/textures)
add_subdirectory(examples/transformations)
