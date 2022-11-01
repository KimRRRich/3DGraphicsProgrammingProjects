#include <stdlib.h>
#include <stdio.h>
#include <math.h>



#define GLEW_STATIC
#include <glew.h>
//#include <GL.h>

#define GLUT_DISABLE_ATEXIT_HACK
#include <glut.h>

#pragma comment (lib, "glew32s.lib")

#define BUFFER_OFFSET(offset) ((GLvoid*)(NULL + offset))
#define NumberOf(array) (sizeof(array) / sizeof(array[0]))

#define M_PI 3.1415926



typedef struct {

	GLfloat x, y, z;

}vec3;


typedef struct {

	vec3 xlate;
	GLfloat angle;
	vec3 axis;

}XForm;



enum { Cube, Cone, NumVAOs };
GLuint VAO[NumVAOs];
GLenum PrimType[NumVAOs];
GLsizei NumElements[NumVAOs];

XForm xform[NumVAOs] = {

	{{-2.0, 0.0, 0.0}, 0.0, {0.0, 1.0, 0.0}},
	{{0.0, 0.0, 2.0}, 0.0, {1.0, 0.0, 0.0}}

};

GLfloat Angle = 0.0;



void init()

{

	enum { Vertices, Colors, Elements, NumVBOs };
	GLuint buffers[NumVBOs];
	glGenVertexArrays(NumVAOs, VAO);



	{

		GLfloat cubeVerts[][3] = {

			{ -1.0, -1.0, -1.0},
			{ -1.0, -1.0,  1.0},
			{ -1.0,  1.0, -1.0},
			{ -1.0,  1.0,  1.0},
			{  1.0, -1.0, -1.0},
			{  1.0, -1.0,  1.0},
			{  1.0,  1.0, -1.0},
			{  1.0,  1.0,  1.0},

		};



		GLfloat cubeColors[][3] = {

			{ 0.0, 0.0, 0.0},

			{ 0.0, 0.0, 1.0},

			{ 0.0, 1.0, 0.0},

			{ 0.0, 1.0, 1.0},

			{ 1.0, 0.0, 0.0},

			{ 1.0, 0.0, 1.0},

			{ 1.0, 1.0, 0.0},

			{ 1.0, 1.0, 1.0},

		};



		GLubyte cubeIndices[] = {

			0, 1, 3, 2,

			4, 6, 7, 5,

			2, 3, 7, 6,

			0, 4, 5, 1,

			0, 2, 6, 4,

			1, 5, 7, 3

		};



		glBindVertexArray(VAO[Cube]);

		glGenBuffers(NumVBOs, buffers);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[Vertices]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);

		glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));

		glEnableClientState(GL_VERTEX_ARRAY);



		glBindBuffer(GL_ARRAY_BUFFER, buffers[Colors]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors, GL_STATIC_DRAW);

		glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));

		glEnableClientState(GL_COLOR_ARRAY);



		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[Elements]);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);



		PrimType[Cube] = GL_QUADS;

		NumElements[Cube] = NumberOf(cubeIndices);

	}



	{

		int i, idx;

		float dTheta;

#define NumConePoints 36



		GLfloat coneVerts[NumConePoints + 1][3] = {

			{ 0.0, 0.0, 1.0}

		};



		GLfloat coneColors[NumConePoints + 1][3] = {

			{ 1.0, 1.0, 1.0}

		};



		GLubyte coneIndices[NumConePoints + 1];



		dTheta = 2 * M_PI / (NumConePoints - 1);



		idx = 1;

		for (i = 0; i < NumConePoints; ++i, ++idx) {

			float theta = i * dTheta;

			coneVerts[idx][0] = cos(theta);

			coneVerts[idx][1] = sin(theta);

			coneVerts[idx][2] = 0.0;



			coneColors[idx][0] = cos(theta);

			coneColors[idx][1] = sin(theta);

			coneColors[idx][2] = 0.0;



			coneIndices[idx] = idx;

		}

		glBindVertexArray(VAO[Cone]);

		glGenBuffers(NumVBOs, buffers);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[Vertices]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(coneVerts), coneVerts, GL_STATIC_DRAW);

		glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));

		glEnableClientState(GL_VERTEX_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[Colors]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(coneColors), coneColors, GL_STATIC_DRAW);

		glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));

		glEnableClientState(GL_COLOR_ARRAY);



		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[Elements]);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(coneIndices), coneIndices, GL_STATIC_DRAW);



		PrimType[Cone] = GL_TRIANGLE_FAN;

		NumElements[Cone] = NumberOf(coneIndices);

	}

	glEnable(GL_DEPTH_TEST);

}



void display()

{

	int i;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glRotatef(Angle, 0.0, 1.0, 0.0);



	for (i = 0; i < NumVAOs; ++i) {

		glPushMatrix();



		glTranslatef(xform[i].xlate.x, xform[i].xlate.y, xform[i].xlate.z);

		glRotatef(xform[i].angle, xform[i].axis.x, xform[i].axis.y, xform[i].axis.z);

		glBindVertexArray(VAO[i]);

		glDrawElements(PrimType[i], NumElements[i], GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));



		glPopMatrix();

	}

	glPopMatrix();

	glutSwapBuffers();

}



int main(int argv, char** argc)

{

	

	glutInit(&argv, argc);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(500, 500);

	glutInitWindowPosition(100, 100);

	glutCreateWindow("MyWindow");
	glewExperimental = GL_TRUE;
	glewInit();



	init();


	glutDisplayFunc(display);



	glutMainLoop();

	return 0;

}