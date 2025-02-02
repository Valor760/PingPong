#version 450 core
layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 transform;
uniform mat4 model;

void main()
{
	// gl_Position = projection * transform * model * vec4(aPos, 1.0);
	gl_Position = projection * model * vec4(aPos, 1.0);
}