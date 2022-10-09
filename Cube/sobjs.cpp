// HEADER
#include "sobjs.h"

/*
	-- VAO --
*/

// Constructors
VAO::VAO() {
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
}

// Functions
void VAO::AddAttribute(GLuint index, GLsizeiptr size, GLsizeiptr stride, GLsizeiptr offset) {
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
	glEnableVertexAttribArray(index);
}
void VAO::Enable() {
	glBindVertexArray(ID);
}
void VAO::Disable() {
	glBindVertexArray(0);
}
void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}

/*
	-- OBO
*/
// Constructors
OBO::OBO(GLenum Type): Type(Type) {
	glGenBuffers(1, &ID);
}

// Functions
void OBO::AssignData(const void* data, GLsizeiptr size) {
	glBindBuffer(Type, ID);
	glBufferData(Type, size, data, GL_STATIC_DRAW);
}
void OBO::Enable() {
	glBindBuffer(Type, ID);
}
void OBO::Disable() {
	glBindBuffer(Type, 0);
}
void OBO::Delete() {
	glDeleteBuffers(1, &ID);
}