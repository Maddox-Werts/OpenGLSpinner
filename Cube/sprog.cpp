// HEADER
#include "sprog.h"

// Constructors
SProgram::SProgram() {
	std::string vertCode =
		"#version 410 core\n"
		"layout (location=0) in vec3 iPos;\n"
		"layout (location=1) in vec3 iCol;\n"
		"out vec3 oColor;\n"
		"uniform mat4 trans;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = trans * vec4(iPos, 1.0);\n"
		"	oColor = iCol;\n"
		"}\n";

	std::string fragCode =
		"#version 410 core\n"
		"in vec3 oColor;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(oColor, 1.0f);\n"
		"}\n";

	// String -> Const Char
	const char* vertSrc = vertCode.c_str();
	const char* fragSrc = fragCode.c_str();

	// Making shaders
	GLuint vertShdr = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShdr, 1, &vertSrc, NULL);
	glCompileShader(vertShdr);

	GLuint fragShdr = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShdr, 1, &fragSrc, NULL);
	glCompileShader(fragShdr);

	// Making shader program
	ID = glCreateProgram();

	// Attaching shaders & linking
	glAttachShader(ID, vertShdr);
	glAttachShader(ID, fragShdr);
	glLinkProgram(ID);

	// Cleanup
	glDeleteShader(vertShdr);
	glDeleteShader(fragShdr);
}

// Functions
void SProgram::Enable() {
	glUseProgram(ID);
}
void SProgram::Disable() {
	glUseProgram(0);
}
void SProgram::Delete() {
	glDeleteProgram(ID);
}