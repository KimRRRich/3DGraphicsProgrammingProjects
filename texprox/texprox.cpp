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
  *  texprox.c
  *  The brief program illustrates use of texture proxies.
  *  This program only prints out some messages about whether
  *  certain size textures are supported and then exits.
  */

#include <stdlib.h>
#include <stdio.h>
#include <glut.h>

#ifdef GL_VERSION_1_1
void init(void)
{
    GLint proxyComponents;

    glTexImage2D(GL_PROXY_TEXTURE_2D, 0, GL_RGBA8,
        64, 64, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0,
        GL_TEXTURE_COMPONENTS, &proxyComponents);
    printf("proxyComponents are %d\n", proxyComponents);
    if (proxyComponents == GL_RGBA8)
        printf("proxy allocation succeeded\n");
    else
        printf("proxy allocation failed\n");

    glTexImage2D(GL_PROXY_TEXTURE_2D, 0, GL_RGBA16,
        2048, 2048, 0,
        GL_RGBA, GL_UNSIGNED_SHORT, NULL);
    glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0,
        GL_TEXTURE_COMPONENTS, &proxyComponents);
    printf("proxyComponents are %d\n", proxyComponents);
    if (proxyComponents == GL_RGBA16)
        printf("proxy allocation succeeded\n");
    else
        printf("proxy allocation failed\n");
}

void display(void)
{
    exit(0);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
#else
int main(int argc, char** argv)
{
    fprintf(stderr, "This program demonstrates a feature which is not in OpenGL Version 1.0.\n");
    fprintf(stderr, "If your implementation of OpenGL Version 1.0 has the right extensions,\n");
    fprintf(stderr, "you may be able to modify this program to make it run.\n");
    return 0;
}
#endif
