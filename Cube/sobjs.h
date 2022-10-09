// DEFINE ONCE
#ifndef H_SOBJS
#define H_SOBJS

// Includes
// --EXTERNALS
#include "externals.h"

// Classes
class VAO {
private:
	// Variables
	GLuint ID;

public:
	// Constructors
	VAO();

	// Functions
	void AddAttribute(GLuint index, GLsizeiptr size, GLsizeiptr stride, GLsizeiptr offset);
	void Enable();
	void Disable();
	void Delete();
};

class OBO {
private:
	// Variables
	GLuint ID;
	GLenum Type;

public:
	// Constructors
	OBO(GLenum Type);

	// Functions
	void AssignData(const void* data, GLsizeiptr size);
	void Enable();
	void Disable();
	void Delete();
};

// endif
#endif