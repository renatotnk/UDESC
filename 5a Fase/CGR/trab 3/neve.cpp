// gcc neve.cpp -lglut -lGL -lGLU -o neve

#include <cstdlib>
#include <math.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glut.h>

#define NUM 4000
#define TEMPO_VIDA 1.0
#define GRAVIDADE -0.4
#define VELOCIDADE 2.5
#define Y_INICIAL 3.0
#define QUEDA 1.0
#define DEC_TEMPO_VIDA 0.006

int rotX = 0;
int rotY = 0;
GLUquadricObj *pObj;
float angle = 0.0;

typedef struct particula {
	double tempoVida;
	double morte;
	double x, y, z; 
	double velocidade;
	double radius;
	double gravidade;
    int vivo;
} Particula;

Particula particulas[NUM];


void initPart(int part, double gravidade, double velocidade) {
	particulas[part].tempoVida = (double) (8 + rand() % 4) / 10;
	particulas[part].morte = (double) (rand()%100) / 1002.0;
	particulas[part].gravidade = gravidade;
	particulas[part].x = (double) ((rand() % 100) - 60)/10;
	particulas[part].z = (double) ((rand() % 200) - 100)/10;
	particulas[part].y = Y_INICIAL;
	particulas[part].velocidade = velocidade;
    particulas[part].vivo = 0;
    //define o tamanho
    particulas[part].radius = (double)(13 + rand()%10)/1000;
}


void inicializa(int qtd, double  gravidade, double velocidade) {
	int i=0;

	for(i=0; i < qtd; i++) {
		initPart(i, gravidade, velocidade);
	}
}

void initVetPart(int qtd, double gravidade, double velocidade) {
	int i=0;

	for(i=0; i < qtd; i++) {
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
			glTranslatef(particulas[i].x, particulas[i].y, particulas[i].z);
			glutSolidSphere(particulas[i].radius, 10, 10);
		glPopMatrix();

        if (particulas[i].vivo) {
        	//direção de movimento
            int quedax = -5000 + rand() % 2000;
    		particulas[i].x += -particulas[i].velocidade / (QUEDA*quedax);
    		particulas[i].y += particulas[i].velocidade / (QUEDA*1000);
    		particulas[i].velocidade += particulas[i].gravidade;
    		particulas[i].tempoVida -= DEC_TEMPO_VIDA;
        }
        else {
            if (rand() % 100 < 2) {
                particulas[i].vivo = 1;
            }
        }

		if (particulas[i].tempoVida < 0.0) {
			initPart(i, gravidade, velocidade);
		}
	}
}



static void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	initVetPart(NUM, GRAVIDADE, VELOCIDADE);

	GLUquadricObj *pObj;
	pObj = gluNewQuadric();

	gluLookAt(0.0, 5.0, 2.0,
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0);

	angle += .5;

	glRotated(angle, 0, 0, 1);
	glColor3f(0.9, 0.9, 0.9);

	// PERNAS
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glutSolidSphere(0.70, 20, 20);
	glPopMatrix();

	// TRONCO
	glPushMatrix();
		glTranslatef(0.0, 0.0, 1.0);
		glutSolidSphere(0.50, 20, 20);
	glPopMatrix();

	// CABEÇA
	glPushMatrix();
		glTranslatef(0.0, 0.0, 1.75);
		glutSolidSphere(0.30, 20, 20);
	glPopMatrix();

	// OLHOS
	glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
		glTranslatef(0.1, 0.23, 1.90);
		glutSolidSphere(0.05, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.1, 0.23, 1.90);
		glutSolidSphere(0.05, 20, 20);
	glPopMatrix();

	// BRAÇO DIREITO
	glPushMatrix();
		glTranslatef(0.2,0.0,1.0);
		glRotatef(-90.0f, 8.0f, 0.0f, 8.0f);
		gluCylinder(pObj, 0.1, 0.03, 0.9, 20, 20);
    glPopMatrix();

    // BRAÇO ESQUERDO
  	glPushMatrix();
		glTranslatef(-0.2,0.0,1.0);
		glRotatef(-90.0f, 0.0f, 8.0f, 8.0f);
		gluCylinder(pObj, 0.1, 0.03, 0.9, 20, 20);
    glPopMatrix(); 

    // BOTÕES
    glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
		glTranslatef(0.0, 0.30, 1.4);
		glutSolidSphere(0.02, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 0.49, 1.15);
		glutSolidSphere(0.02, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 0.45, 0.8);
		glutSolidSphere(0.02, 20, 20);
	glPopMatrix();

	// NARIZ
	glColor3f(0.9, 0.2, 0.2);
	glPushMatrix();
		glTranslatef(0.0,0.15,1.77);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.1, 0.0, 0.3, 20, 20);
    glPopMatrix(); 

    // CHAPEU
	glColor3f(0.50, 0.16, 0.16);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 2.0);
		glRotatef(0.0, 1.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.2, 0.0, 0.3, 20, 20);
    glPopMatrix(); 

	glFlush();
	glutSwapBuffers();
}


int main (int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize(800,600);
    glutCreateWindow("Voce quer brincar na neve?");

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
