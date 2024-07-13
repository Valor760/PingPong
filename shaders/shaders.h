#pragma once

const char* s_fragment =
	"#version 450 core\n"
	"out vec4 FragColor;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
	"}\n"
;

const char* s_vertex =
	"#version 450 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"\n"
	"uniform mat4 projection;\n"
	"uniform mat4 transform;\n"
	"uniform mat4 model;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	// gl_Position = projection * transform * model * vec4(aPos, 1.0);\n"
	"	gl_Position = projection * model * vec4(aPos, 1.0);\n"
	"}\n"
;

