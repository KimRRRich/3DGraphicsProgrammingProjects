// stencil.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
/*
 * Copyright (c) 1993-2003, Silicon Graphics, Inc.
 * All Rights Reserved
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright
 * notice and this permission notice appear in supporting documentation,
 * and that the name of Silicon Graphics, Inc. not be used in
 * advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS" AND
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION, LOSS OF
 * PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF THIRD
 * PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN ADVISED OF
 * THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE POSSESSION, USE
 * OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor clauses
 * in the FAR or the DOD or NASA FAR Supplement.  Unpublished - rights
 * reserved under the copyright laws of the United States.
 *
 * Contractor/manufacturer is:
 *	Silicon Graphics, Inc.
 *	1500 Crittenden Lane
 *	Mountain View, CA  94043
 *	United State of America
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

 /*
  *  stencil.c
  *  This program demonstrates use of the stencil buffer for
  *  masking nonrectangular regions.
  *  Whenever the window is redrawn, a value of 1 is drawn
  *  into a diamond-shaped region in the stencil buffer.
  *  Elsewhere in the stencil buffer, the value is 0.
  *  Then a blue sphere is drawn where the stencil value is 1,
  *  and yellow torii are drawn where the stencil value is not 1.
  */
#include <stdlib.h>
#include <glut.h>
#include<math.h>


#define YELLOWMAT   1
#define BLUEMAT 2
#define PI 3.1415926

void init(void)
{
    GLfloat yellow_diffuse[] = { 0.7, 0.7, 0.0, 1.0 };
    GLfloat yellow_specular[] = { 1.0, 1.0, 1.0, 1.0 };//设置材质，

    GLfloat blue_diffuse[] = { 0.1, 0.1, 0.7, 1.0 };
    GLfloat blue_specular[] = { 0.1, 1.0, 1.0, 1.0 };

    GLfloat position_one[] = { 1.0, 1.0, 1.0, 0.0 };//光源位置

    glNewList(YELLOWMAT, GL_COMPILE);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, yellow_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 64.0);
    glEndList();

    glNewList(BLUEMAT, GL_COMPILE);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, blue_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, blue_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 45.0);
    glEndList();

    glLightfv(GL_LIGHT0, GL_POSITION, position_one);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    glClearStencil(0x0);
    glEnable(GL_STENCIL_TEST);//模板测试打开
}

/* Draw a sphere in a diamond-shaped section in the
 * middle of a window with 2 torii.
 */
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* draw blue sphere where the stencil is 1 */
    glStencilFunc(GL_EQUAL,0x0, 0x2);//mask的值和模板的值是否相等
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);//不会更改模板的值
    glCallList(BLUEMAT);
    glutSolidSphere(0.5, 15, 15);

    /* draw the tori where the stencil is not 1 */
    glStencilFunc(GL_EQUAL, 0x0, 0x1);//在模板外才能显示
    glPushMatrix();
    glRotatef(45.0, 0.0, 0.0, 1.0);
    glRotatef(45.0, 0.0, 1.0, 0.0);
    glCallList(YELLOWMAT);
    glutSolidTorus(0.275, 0.85, 15, 15);
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glutSolidTorus(0.275, 0.85, 15, 15);
    glPopMatrix();
    glPopMatrix();
    glFlush();
}

/*  Whenever the window is reshaped, redefine the
 *  coordinate system and redraw the stencil area.
 */
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    /* create a diamond shaped stencil area */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        gluOrtho2D(-3.0, 3.0, -3.0 * (GLfloat)h / (GLfloat)w,
            3.0 * (GLfloat)h / (GLfloat)w);
    else
        gluOrtho2D(-3.0 * (GLfloat)w / (GLfloat)h,
            3.0 * (GLfloat)w / (GLfloat)h, -3.0, 3.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_STENCIL_BUFFER_BIT);//模板buffer都倾城0
    glStencilFunc(GL_ALWAYS, 0x1, 0x1);//所有情况都能通过测试，
    //glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);//修改方式都是替换，用参考值替换原来的值
    glStencilOp(GL_INCR, GL_INCR, GL_INCR);
    glBegin(GL_TRIANGLES);
    glVertex2f(0, 1);
    glVertex2f(-1, -0.5);
    glVertex2f(1, -0.5);


	/*glVertex2f(-0.5, 1.0);
	glVertex2f(-0.5, -1.0);
	glVertex2f(0.5, -1.0);
	glVertex2f(0.5,1.0);*/
	
    glEnd();
    //glStencilOp(GL_INCR, GL_INCR, GL_INCR);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, -1);
	glVertex2f(-1, 0.5);
	glVertex2f(1, 0.5);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 3.0, 7.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    }
}

/* Main Loop
 * Be certain to request stencil bits.
 */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB
        | GLUT_DEPTH | GLUT_STENCIL);//模板buffer,和深度buffer类似，每个像素都有一个对应的值
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

int main()
{
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
