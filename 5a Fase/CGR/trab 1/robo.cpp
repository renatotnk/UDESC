#include <cstdlib>
#include <math.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glut.h>

//usage : g++ gl.cpp -o gl -lGL -lGLU -lglut

float angle = 0.0;

static void display(){
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
	

   gluLookAt(0.0, 5.0, 1.0,
             0.0, 0.0, 1.0,
             0.0, 0.0, 1.0);

   angle += 0.5;

   glRotated(angle, 0, 0, 1);
   glColor3f(0.9, 0.9, 0.9);

   
   	//CORPO 
   	glColor3f(1.0, 0.5, 0.0);
	glPushMatrix();
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glTranslatef(0.0f, 0.0f, 0.7f);
		glScalef(0.4f, 0.4f, 1.0f);
		glutSolidSphere(0.6, 20, 20);
	glPopMatrix();

   	//BOTÕES
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
		glRotatef(0.0, 0.0, 0.0, 1.0);
		glTranslatef(0.0f, 0.2f, 1.0f);
		glScalef(1.0f, 1.0f, 0.5f);
		glutSolidSphere(0.05, 20, 20);
	glPopMatrix();
	
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
		glRotatef(0.0, 0.0, 0.0, 1.0);
		glTranslatef(0.0f, 0.2f, 0.7f);
		glScalef(1.0f, 1.0f, 0.5f);
		glutSolidSphere(0.05, 20, 20);
	glPopMatrix();

	
	// BRAÇO DIREITO
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
		glRotatef(0.0, 1.0, 1.0, 0.0);
		glTranslatef(0.4f, 0.0f, 1.0f);
		glScalef(1.5f, 0.5f, 0.5f);
		glutSolidCube(0.3);
	glPopMatrix();
	
	// BRAÇO ESQUERDO
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
		glRotatef(0.0, 1.0, 1.0, 0.0);
		glTranslatef(-0.4f, 0.0f, 1.0f);
		glScalef(1.5f, 0.5f, 0.5f);
		glutSolidCube(0.3);
	glPopMatrix();
	
	// PERNA ESQUERDA
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
		glRotatef(0.0, 1.0, 1.0, 0.0);
		glTranslatef(-0.1f, 0.0f, -0.1f);
		glScalef(0.5f, 0.5f, 1.7f);
		glutSolidCube(0.3);
	glPopMatrix();
	
	// PERNA DIREITA
		glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glRotatef(0.0, 1.0, 1.0, 0.0);
		glTranslatef(0.1f, 0.0f, -0.1f);
		glScalef(0.5f, 0.5f, 1.7f);
		glutSolidCube(0.3);
	glPopMatrix();

	// CABEÇA
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
		glRotatef(0.0, 1.0, 0.0, 1.0);
		glTranslatef(0.0f, 0.0f, 1.50f);
		glScalef(1.0f, 1.0f, 1.5f);
		glutSolidSphere(0.2, 20, 20);
	glPopMatrix();

	// OLHOS
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
		glRotatef(0.0, 0.0, 0.0, 1.0);
		glTranslatef(-0.08f, 0.2f, 1.50f);
		glScalef(1.0f, 1.0f, 0.5f);
		glutSolidSphere(0.05, 20, 20);
	glPopMatrix();

		glPushMatrix();
		glRotatef(0.0, 0.0, 0.0, 1.0);
		glTranslatef(0.08f, 0.2f, 1.50f);
		glScalef(1.0f, 1.0f, 0.5f);
		glutSolidSphere(0.05, 20, 20);
	glPopMatrix();

   glFlush();
   glutSwapBuffers();
}

int main (int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize(800,600);
    glutCreateWindow("HottoDoggu Robotto");

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
   
    glEnable(GL_COLOR_MATERIAL);	

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glutMainLoop();

    return 0;
}
