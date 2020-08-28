// gcc castelo.cpp -lglut -lGL -lGLU -o  prog

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

//usage : g++ gl.cpp -o gl -lGL -lGLU -lglut

int rotX = 0;
int rotY = 0;
int list;
GLUquadricObj *pObj;
float angle = 0.0;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    GLUquadricObj *pObj;
    pObj = gluNewQuadric();


    gluLookAt(0.0, 5.0, 2.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0);

	angle += .5;

	glRotated(angle, 0, 0, 1);

    //MURO FRENTE ESQ
    glColor3f(0.91, 0.76, 0.65);
    glPushMatrix();
        glTranslatef(0.5, -0.1, 0.3);
     	glScalef(2.5f, 1.0f, 2.5f);
        glutSolidCube(0.5);
    glPopMatrix();
    

    //MURO FRENTE DIR
    glColor3f(0.91, 0.76, 0.65);
    glPushMatrix();
        glTranslatef(-1.4, -0.1, 0.3);
     	glScalef(2.5f, 1.0f, 2.5f);
        glutSolidCube(0.5);
    glPopMatrix();

   //MURO LATERAL ESQ
    glColor3f(0.91, 0.76, 0.65);
    glPushMatrix();
        glTranslatef(1.0, -1.2, 0.3);
     	glScalef(1.0f, 5.5f, 2.5f);
        glutSolidCube(0.5);
    glPopMatrix();

   //MURO LATERAL DIR
    glColor3f(0.91, 0.76, 0.65);
    glPushMatrix();
        glTranslatef(-2.0, -1.2, 0.3);
     	glScalef(1.0f, 5.5f, 2.5f);
        glutSolidCube(0.5);
    glPopMatrix();

   //MURO FUNDO
    glColor3f(0.91, 0.76, 0.65);
    glPushMatrix();
        glTranslatef(-0.5, -3.0, 0.3);
     	glScalef(5.5f, 1.0f, 2.5f);
        glutSolidCube(0.5);
    glPopMatrix();
   

    //TORRE CENTRAL
    glColor3f(0.65, 0.50, 0.39);
    glPushMatrix();
        glTranslatef(1.0, 0.0, -0.3);    
        gluCylinder(pObj,0.4f,0.4f,1.5f,32,32);
    glPopMatrix();
    //TELHADO 
    glColor3f(0.52, 0.37, 0.26);
    glPushMatrix();
        glTranslatef(1.0, 0.0, 1.2);
        glutSolidCone(0.4, 1.0, 20, 16);
    glPopMatrix();

    //TORRE PRINCIPAL
    glColor3f(0.65, 0.50, 0.39);
    glPushMatrix();
        glTranslatef(-0.5, -1.5, -0.3);    
        gluCylinder(pObj,0.7f,0.4f,2.0f,32,32);
    glPopMatrix();
    //TELHADO 
    glColor3f(0.52, 0.37, 0.26);
    glPushMatrix();
        glTranslatef(-0.5, -1.5, 1.6);
        glutSolidCone(0.5, 1.0, 20, 16);
    glPopMatrix();



    //TORRE ESQUERDA
    glColor3f(0.65, 0.50, 0.39);
    glPushMatrix();
        glTranslatef(-0.4, -0.1, -0.3);    
        gluCylinder(pObj,0.5f,0.3f,1.5f,32,32);
    glPopMatrix();
    //TELHADO
    glColor3f(0.52, 0.37, 0.26);
    glPushMatrix();
        glTranslatef(-0.4, -0.1, 1.2);
        glutSolidCone (0.35, 0.5, 20, 16);
    glPopMatrix();

    //TORRE DIREITA
    glColor3f(0.65, 0.50, 0.39);
    glPushMatrix();
        glTranslatef(-2.0, 0.0, -0.3);    
        gluCylinder(pObj,0.4f,0.4f,1.5f,32,32);
    glPopMatrix();
    //TELHADO
    glColor3f(0.52, 0.37, 0.26); 
    glPushMatrix();
        glTranslatef(-2.0, 0.0, 1.2);
        glutSolidCone(0.4, 1.0, 20, 16);
    glPopMatrix();

    //TORRE FUNDO ESQ
    glColor3f(0.65, 0.50, 0.39);
    glPushMatrix();
        glTranslatef(-2.0, -3.0, -0.3);    
        gluCylinder(pObj,0.5f,0.5f,1.8f,32,32);
    glPopMatrix();
        //TELHADO
    glColor3f(0.52, 0.37, 0.26); 
    glPushMatrix();
        glTranslatef(-2.0, -3.0, 1.5);
        glutSolidCone(0.5, 1.0, 20, 16);
    glPopMatrix();

    //TORRE FUNDO DIR
    glColor3f(0.65, 0.50, 0.39);
    glPushMatrix();
        glTranslatef(1.0, -3.0, -0.3);    
        gluCylinder(pObj,0.5f,0.5f,1.8f,32,32);
    glPopMatrix();
        //TELHADO
    glColor3f(0.52, 0.37, 0.26); 
    glPushMatrix();
        glTranslatef(1.0, -3.0, 1.5);
        glutSolidCone(0.5, 1.0, 20, 16);
    glPopMatrix();

    
    glFlush();
    glutSwapBuffers();
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize(800,600);
    glutCreateWindow("CASTELO");

    glutDisplayFunc(display);
    glutIdleFunc( display );

    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat aspect = (GLfloat) 800 / 600;
    gluPerspective(45, aspect, 2.0f, 15.0f);
    glMatrixMode(GL_MODELVIEW);
    glShadeModel( GL_SMOOTH );
    glClearDepth( 1.0f );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    glClearColor(0.15, 0.15, 0.15, 1.0);

    GLfloat mat_shininess[] =  { 50.0 };
    GLfloat mat_specular[] =   { 0.75, 0.75, 0.75, 0.75 };

    GLfloat light_ambient[] =  {  0.5,  0.5,  0.5, 1.0 };
    GLfloat light_diffuse[] =  {  1.0,  1.0,  1.0, 1.0 };
    GLfloat light_specular[] = {  1.0,  1.0,  1.0, 1.0 };
    GLfloat light_position[] = {  10.0,  2.0,  10.0, 0.0 };

    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glutMainLoop();

    return 0;
}
