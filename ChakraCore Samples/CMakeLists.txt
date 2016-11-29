
add_subdirectory("Hello World")

if(PC_GLFW_FOUND AND PC_GLEW_FOUND AND OpenGL_FOUND)
	add_subdirectory("OpenGL Engine")
endif()

