
#include <stdio.h>
#include <stdlib.h>
#include <gl/glew.h>
#include <glut.h>

static const GLfloat vertex_positions[] =
{
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f
};
static const GLfloat vertex_colors[] =
{
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
};

const char* vs = { "#version 130 \n"
"attribute vec3 vpos;"
"attribute vec4 vcolor;"
"uniform vec4 color;"
"void main()"
"{"
"	gl_Position = ftransform();"
"}" };

const char* fs = { "#version 130 \n"
"uniform vec4 color;"
"void main()"
"{"
"	gl_FragColor = color;"
"} "
};

GLuint vao, vbo;
GLuint p;


void printProgramInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten = 0;
	char* infoLog;
	glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);
	if (infologLength > 0)
	{
		infoLog = (char*)malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("printProgramInfoLog: %s\n", infoLog);
		free(infoLog);
	}
	else {
		printf("Program Info Log: OK\n");
	}
}


void setShaders()
{
	GLuint v = glCreateShader(GL_VERTEX_SHADER);
	GLuint f = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(v, 1, &vs, NULL);
	glShaderSource(f, 1, &fs, NULL);

	glCompileShader(v);
	glCompileShader(f);

	p = glCreateProgram();
	glAttachShader(p, f);
	glAttachShader(p, v);

	glLinkProgram(p);

	printProgramInfoLog(v);
	printProgramInfoLog(f);
	printProgramInfoLog(p);

	glUseProgram(p);
}



void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions) + sizeof(vertex_colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_positions), vertex_positions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_positions), sizeof(vertex_colors), vertex_colors);

	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glColorPointer(4, GL_FLOAT, 0, (const GLvoid*)sizeof(vertex_positions));
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(vertex_positions));
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
}
void display(void)
{
	static float red_color[] = { 1.0, 0.0, 0.0, 1.0 };
	static float green_color[] = { 0.0, 1.0, 0.0, 1.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLint loc = glGetUniformLocationARB(p, "color");
	glUniform4fvARB(loc, 1, red_color);
	glUseProgram(p);
	glBindVertexArray(vao);
	glDrawArrays(GL_QUADS, 0, 4);
	glUniform4fvARB(loc, 1, green_color);
	glutSolidSphere(0.5, 30, 20);
	glFlush();
}
void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float a = (float)w / h;
	if (w <= h)
		glOrtho(-2.5, 2.5, -2.5 * a, 2.5 * a, -10.0, 10.0);
	else
		glOrtho(-2.5 * a, 2.5 * a, -2.5, 2.5, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("example");

	glewInit();

	//if (glewIsSupported("GL_VERSION_2_0"))
	//	printf("Ready for OpenGL 2.0\n");
	//else {
	//	printf("OpenGL 2.0 not supported\n");
	//	exit(1);
	//}
	setShaders();
	init();
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
