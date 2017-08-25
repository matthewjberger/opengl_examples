cmake_minimum_required(VERSION 3.0)
project(EXAMPLE_skybox)

file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE SHADERS resources/shaders/*.glsl)

# Use file globs to create filters for Visual Studio
source_group("Headers" 		 FILES ${HEADERS})
source_group("Sources" 		 FILES ${SOURCES})
source_group("Shaders" 		 FILES ${SHADERS})
source_group("Core\\Headers" FILES ${CORE_HEADERS})
source_group("Core\\Sources" FILES ${CORE_SOURCES})
source_group("Core\\Glad"	 FILES ${GLAD_SOURCE})
source_group("Configs" 		 FILES ${CORE_CONFIGS})

include_directories(${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME}  ${CORE_HEADERS}
								${CORE_SOURCES}
								${CORE_CONFIGS}
								${GLAD_SOURCE}
								${HEADERS}
								${SOURCES}
								${SHADERS})

target_link_libraries(${PROJECT_NAME} ${CORE_LIBS})

# Output to bin directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/examples/${PROJECT_NAME})

# Visual Studio specific settings
# Requires CMake 3.8+
if(MSVC)

    # Set the working directory
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/examples/${PROJECT_NAME}/${CMAKE_BUILD_TYPE})

    # Hide the console in Visual Studio projects in debug and release
    set_target_properties(${PROJECT_NAME} PROPERTIES
		LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
		LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

    # Copy resources folder to output folder
	# This would be a good place to store shader source files and art assets
    add_custom_command(TARGET   ${PROJECT_NAME} POST_BUILD
                                COMMAND ${CMAKE_COMMAND} -E copy_directory
                                ${CMAKE_CURRENT_SOURCE_DIR}/resources
                                $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)
endif(MSVC)
