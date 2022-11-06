/*


  Simple Demo for GLSL 2.0

  www.lighthouse3d.com

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <glut.h>
#include "textfile.h"


GLuint v, f, f2, p,lightposition, color1, color2,color3,color4;
float lpos[4] = { 1,0.5,1,0 };

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = 1.0 * w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);


}


void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0,
		0.0, 0.0, -1.0,
		0.0f, 1.0f, 0.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	glutSolidTeapot(1);

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
}


void setShaders() {

	 

	char* vs = NULL, * fs = NULL, * fs2 = NULL;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);
	f2 = glCreateShader(GL_FRAGMENT_SHADER);


	vs = textFileRead("toon.vert");
	fs = textFileRead("toon.frag");
	fs2 = textFileRead("toon2.frag");

	

	const char* ff = fs;
	const char* ff2 = fs2;
	const char* vv = vs;

	

	glShaderSource(v, 1, &vv, NULL);
	glShaderSource(f, 1, &ff, NULL);
	glShaderSource(f2, 1, &ff2, NULL);
	

	//v.setUniform("Material.Kd", 0.9f, 0.5f, 0.3f);

	free(vs); free(fs);

	glCompileShader(v);
	glCompileShader(f);
	glCompileShader(f2);

	p = glCreateProgram();
	glAttachShader(p, f);
	glAttachShader(p, f2);
	glAttachShader(p, v);



	glLinkProgram(p);
	glUseProgram(p);

	lightposition = glGetUniformLocation(p, "lightposition");
	color1 = glGetUniformLocation(p, "color1");
	color2 = glGetUniformLocation(p, "color2");
	color3 = glGetUniformLocation(p, "color3");
	color4 = glGetUniformLocation(p, "color3");
	glUniform3f(lightposition, lpos[0], lpos[1], lpos[2]);
	glUniform4f(color1, 0.1, 0.8, 0.8,1.0);
	glUniform4f(color2, 0.5, 0.5, 0.4,1.0);
	glUniform4f(color3, 0.25, 0.25, 0.2, 1.0);
	glUniform4f(color4, 0.1, 0.1, 0.1, 1.0);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 640);
	glutCreateWindow("MM 2004-05");
	const GLubyte* OpenGLVersion = glGetString(GL_VERSION); //返回当前OpenGL实现的版本号  
	printf("OpenGL实现的版本号：%s\n", OpenGLVersion);
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	//	glEnable(GL_CULL_FACE);

	glewInit();
	if (glewIsSupported("GL_VERSION_2_0"))
		printf("Ready for OpenGL 2.0\n");
	else {
		printf("OpenGL 2.0 not supported\n");
		exit(1);
	}
	setShaders();

	glutMainLoop();

	// just for compatibiliy purposes
	return 0;
}

