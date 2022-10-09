// Includes
// --EXTERNALS
#include "externals.h"
// --ENGINE
#include "sprog.h"
#include "sobjs.h"

// Variables
GLFWwindow* window;

// Functions
int crash(const char* msg);
void init();

// Entry Point
int main(int argc, char* argv[]) {
	// Starting
	init();

	// Making the shader
	SProgram sProgram = SProgram();

	// Object
	GLfloat verts[] = {
		//	LOCATION		||		COLOR

		// --FRONT
		-0.5f, -0.5f, +0.5f,		1,0,0,		// 0
		+0.5f, -0.5f, +0.5f,		0,1,0,		// 1
		+0.5f, +0.5f, +0.5f,		0,0,1,		// 2
		-0.5f, +0.5f, +0.5f,		1,0,1,		// 3

		// --BACK
		-0.5f, -0.5f, -0.5f,		1,0,0,		// 4
		+0.5f, -0.5f, -0.5f,		0,1,0,		// 5
		+0.5f, +0.5f, -0.5f,		0,0,1,		// 6
		-0.5f, +0.5f, -0.5f,		1,0,1,		// 7

	};
	GLuint indic[] = {
		// --FRONT
		0,1,3,
		3,1,2,

		// --Back
		4,5,7,
		7,5,6,

		// --TOP
		7,6,3,
		3,6,2,

		// --BOTTOM
		4,5,0,
		0,5,1,

		// --LEFT
		4,0,7,
		7,0,3,

		// --RIGHT
		5,1,6,
		6,1,2
	};

	// Making VAO
	VAO vao = VAO();
	OBO vbo = OBO(GL_ARRAY_BUFFER);
	OBO ebo = OBO(GL_ELEMENT_ARRAY_BUFFER);

	// Binding
	vao.Enable();

	// Buffer -- VBO
	vbo.AssignData(&verts, sizeof(verts));

	// Buffer -- EBO
	ebo.AssignData(&indic, sizeof(indic));

	// Pointers
	vao.AddAttribute(0, 3, 6, 0);
	vao.AddAttribute(1, 3, 6, 3);

	// Unbinding
	vao.Disable();
	vbo.Disable();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Things
	float rotation = 0.0f;

	// Game loop
	while (!glfwWindowShouldClose(window)) {
		// Polling events
		glfwPollEvents();

		// Clearing screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Game & Render Code..
		// --ROTATING
		rotation += 1.0f;

		// --PROGRAM
		sProgram.Enable();
		// --ARRAY
		vao.Enable();
		// --3D
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.5f, 1.0f, 0.25f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.5f));
		proj = glm::perspective(glm::radians(75.0f), (float)(S_WIDTH / S_HEIGHT), 0.1f, 100.0f);
		int transLoc = glGetUniformLocation(sProgram.ID, "trans");
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(proj * view * model));
		// --DRAWING
		glDrawElements(GL_TRIANGLES, sizeof(indic)/sizeof(int), GL_UNSIGNED_INT, 0);
		// --END
		vao.Disable();
		sProgram.Disable();
		
		// Display screen
		glfwSwapBuffers(window);
	}
	
	// Cleanup
	vbo.Delete();
	vao.Delete();
	ebo.Delete();
	sProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();

	// Quit
	return 0;
}

// DEFINING FUNCTIONS
int crash(const char* msg) {
	glfwTerminate();
	throw(msg);
	exit(EXIT_FAILURE);
	return -1;
}
void init() {
	// Start GLFW
	if (!glfwInit()) {
		crash("Failed to start GLFW.\n");
	}

	// Creating window
	window = glfwCreateWindow(
		S_WIDTH, S_HEIGHT,
		"Cube Demo",
		NULL, NULL
	);

	// Was the window created successfully?
	if (window == NULL) {
		crash("Failed to create GLFWwindow.\n");
	}

	// Setting the window as the main window.
	glfwMakeContextCurrent(window);

	// GLEW stuff
	if (glewInit() != GLEW_OK) {
		crash("Failed to start GLEW.\n");
	}

	// Setting OpenGL stuff
	// --ENABLING
	glEnable(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	// --VIEWPORT
	glViewport(0,0, S_WIDTH,S_HEIGHT);
	// --COLOR
	glClearColor(0,0,0, 1);
	glClearDepth(1);
}