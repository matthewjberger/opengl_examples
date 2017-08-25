#version 330 core
layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_texCoord;

out vec2 f_texCoord;

// It is faster to calculate the mvp matrix on the cpu
// and send it to the shader program via a uniform
// than it is to calculate the mvp matrix on the gpu
// inside the shader
uniform mat4 mvpMatrix;

void main()
{
	gl_Position = mvpMatrix * vec4(v_position, 1.0f);
	f_texCoord = v_texCoord;
}
