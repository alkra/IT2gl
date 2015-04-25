#ifndef TESTS_H
#define TESTS_H

/* Ce fichier contient des macros et la constante teapot pour mener des tests
 * de débogage. */


#define TEST
#define TEST_PROJECTION glOrtho(-10, 10, -10, 10, -10, 10);
#define TEST_DESSIN_REPERE \
    glPushMatrix();\
    glTranslatef(2, 1, 1);\
    glBegin(GL_LINES);\
    glColor3f(1, 0, 0);\
    glVertex3f(0, 0, 0);\
    glVertex3f(1, 0, 0);\
    \
    glColor3f(0, 1, 0);\
    glVertex3f(0, 0, 0);\
    glVertex3f(0, 1, 0);\
    \
    glColor3f(0, 0, 1);\
    glVertex3f(0, 0, 0);\
    glVertex3f(0, 0, 1);\
    glEnd();\
    glPopMatrix();

#endif // TESTS_H
