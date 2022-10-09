// DEFINE ONCE
#ifndef H_SPROG
#define H_SPROG

// INCLUDES
// --EXTERNALS
#include "externals.h"

// Classes
class SProgram {
public:
	// Variables
	GLuint ID;

	// Constructors
	SProgram();

	// Functions
	void Enable();
	void Disable();
	void Delete();
};

// END DEFINITION
#endif