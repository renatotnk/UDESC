// gcc -o text textura.c `sdl-config --libs` -lGL -lGLU -lglut
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
 
/* screen width, height, and bit depth */
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP     16

/* Set up some booleans */
#define TRUE  1
#define FALSE 0

typedef struct ponto{
    float x,y,z;
}Ponto;

typedef struct face{
    int p1, p2, p3, p4;
}Face;

typedef struct normal{
    float x,y,z;
}Normal;

typedef struct objeto {
    int quantP, quantF, quantN;
    int maxQuantP, maxQuantF, maxQuantN;
    Ponto *pontos;
    Face *faces;
    Normal *normais;
}Objeto;

float anguloX = 0.0f, anguloY = 0.0f, anguloZ = 0.0f;
Objeto *ob;

void inicializaFaces(Face *f, int qf) {
    int i;
    for(i=0 ; i<qf ; i++) {
        f->p1 = -1;
        f->p2 = -1;
        f->p3 = -1;
        f->p4 = -1;
    }
}

void inicializaPontos(Ponto *p, int qp) {
    int i;
    for(i=0 ; i<qp ; i++) {
        p->x = -1;
        p->y = -1;
        p->z = -1;
    }
}

void inicializaNormais(Normal *pn, int qn) {
    int i;
    for(i=0 ; i<qn ; i++) {
        pn->x = -1;
        pn->y = -1;
        pn->z = -1;
    }
}

void mostraPontos(Objeto *ob) {
    int i;
    printf("Pontos:\n");
    for(i=0 ; i<ob->quantP ; i++) {
        printf("Ponto[%i] x=%f|y=%f|z=%f\n", i, (ob->pontos)[i].x, (ob->pontos)[i].y, (ob->pontos)[i].z);
    }
}

void mostraNormais(Objeto *ob) {
    int i;
    printf("Normais:\n");
    for(i=0 ; i<ob->quantN ; i++) {
        printf("Normal[%i] x=%f|y=%f|z=%f\n", i, (ob->normais)[i].x, (ob->normais)[i].y, (ob->normais)[i].z);
    }
}

void mostraFaces(Objeto *ob) {
    int i;
    printf("Faces:\n");
    for(i=0 ; i<ob->quantF ; i++) {
        printf("Face[%i] p1=%i|p2=%i|p3=%i|p4=%i\n", i, (ob->faces)[i].p1, (ob->faces)[i].p2, (ob->faces)[i].p3, (ob->faces)[i].p4);
    }
}



Objeto* criaObjeto() {
    Objeto *ob = malloc(sizeof(Objeto));
    ob->maxQuantF = 20;
    ob->maxQuantP = 20;
    ob->maxQuantN = 20;
    ob->quantF = 0;
    ob->quantP = 0;
    ob->quantN = 0;
    ob->pontos = malloc(ob->maxQuantP * sizeof(Ponto));
    ob->faces = malloc(ob->maxQuantF * sizeof(Face));
    ob->normais = malloc(ob->maxQuantN * sizeof(Normal));
    inicializaPontos(ob->pontos, ob->maxQuantP);
    inicializaFaces(ob->faces, ob->maxQuantF);
    inicializaNormais(ob->normais, ob->maxQuantN);
    return ob;
}

void destroiObjeto(Objeto *ob) {
    free(ob->pontos);
    free(ob->normais);
    free(ob->faces);
}

void inserePonto(Objeto *ob, float x, float y, float z) {
    (ob->pontos)[ob->quantP].x = x;
    (ob->pontos)[ob->quantP].y = y;
    (ob->pontos)[ob->quantP].z = z;
    ob->quantP++;
}

void insereNormal(Objeto *ob, float x, float y, float z) {
    (ob->normais)[ob->quantN].x = x;
    (ob->normais)[ob->quantN].y = y;
    (ob->normais)[ob->quantN].z = z;
    ob->quantN++;
}

void insereFace(Objeto *ob, int p1, int p2, int p3, int p4) {
    (ob->faces)[ob->quantF].p1 = p1;
    (ob->faces)[ob->quantF].p2 = p2;
    (ob->faces)[ob->quantF].p3 = p3;
    (ob->faces)[ob->quantF].p4 = p4;
    ob->quantF++;
}

void leOBJ(char *arqEntrada, Objeto *ob) {
    FILE *arq;
    char buffer[100];
    float x,y,z;
    int p1,p2,p3,p4;
    if((arq = fopen(arqEntrada, "r")) != NULL) {
        printf("Abriu arquivo\n");
        //leitura do arquivo
        while(feof(arq) == 0) {
            fscanf(arq, "%s", buffer);
            if(buffer[0] == 'v' && buffer[1] == '\0') {
                fscanf(arq, "%f", &x);
                fscanf(arq, "%f", &y);
                fscanf(arq, "%f", &z);
                //printf("Vertice x = %f | y = %f | z = %f\n", x, y, z);
                inserePonto(ob, x, y, z);
            }else if(buffer[0] == 'f' && buffer[1] == '\0'){//vertices
                fscanf(arq, "%s", buffer);
                p1 = (int)(buffer[0]-'0');
                fscanf(arq, "%s", buffer);
                p2 = (int)(buffer[0]-'0');
                fscanf(arq, "%s", buffer);
                p3 = (int)(buffer[0]-'0');
                fscanf(arq, "%s", buffer);
                p4 = (int)(buffer[0]-'0');
                //printf("Face p1 = %i | p2 = %i | p3 = %i | p4 = %i\n", p1, p2, p3, p4);
                insereFace(ob, p1, p2, p3, p4);
            }else if(buffer[0] == 'v' && buffer[1] == 'n' && buffer[2] == '\0') {
                fscanf(arq, "%f", &x);
                fscanf(arq, "%f", &y);
                fscanf(arq, "%f", &z);
                //printf("Normal x = %f | y = %f | z = %f\n", x, y, z);
                insereNormal(ob, x, y, z);
            }
            //printf("%--s \n", buffer);
        }
        fclose(arq);
        printf("fechou o arquivo\n");
    }else {
        printf("Nao conseguiu abrir o arquivo\n");
    }

}

/* This is our SDL surface */
SDL_Surface *surface;

/* Whether or not lighting is on */
int light = FALSE;

GLfloat xrot;      /* X Rotation */
GLfloat yrot;      /* Y Rotation */
GLfloat xspeed;    /* X Rotation Speed */
GLfloat yspeed;    /* Y Rotation Speed */
GLfloat z = -5.0f; /* Depth Into The Screen */

/* Ambient Light Values ( NEW ) */
GLfloat LightAmbient[]  = { 0.5f, 0.5f, 0.5f, 1.0f };
/* Diffuse Light Values ( NEW ) */
GLfloat LightDiffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
/* Light Position ( NEW ) */
GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };

GLuint filter;     /* Which Filter To Use */
GLuint texture[7]; /* Storage for 7 textures = 1 for box and 6 for skybox */


/* function to release/destroy our resources and restoring the old desktop */
void Quit( int returnCode )
{
    /* clean up the window */
    SDL_Quit( );

    /* and exit appropriately */
    exit( returnCode );
}

/* function to load in bitmap as a GL texture */
int LoadGLTextures( )
{
    int i;

    /* Status indicator */
    int Status = FALSE;

    /* Create storage space for the texture */
    SDL_Surface *TextureImage[7]; 

    glGenTextures( 7, texture );

    /* Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit */
    if (( TextureImage[0] = SDL_LoadBMP( "textura/tex0.bmp" ) )) {

	    /* Set the status to true */
	    Status = TRUE;

	    /* Load in texture 1 */
	    /* Typical Texture Generation Using Data From The Bitmap */
	    glBindTexture( GL_TEXTURE_2D, texture[0] );

	    /* Generate The Texture */
	    glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[0]->w,
			  TextureImage[0]->h, 0, GL_BGR,
			  GL_UNSIGNED_BYTE, TextureImage[0]->pixels );
	    
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			     GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			     GL_NEAREST );

    }

	if (( TextureImage[1] = SDL_LoadBMP( "textura/tex1.bmp" ) )) {
    	glBindTexture( GL_TEXTURE_2D, texture[1] );
	    glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[1]->w, TextureImage[1]->h, 0, GL_BGR, 
                  GL_UNSIGNED_BYTE, TextureImage[1]->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			     GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			     GL_NEAREST );
    }

	if (( TextureImage[2] = SDL_LoadBMP( "textura/tex2.bmp" ) )) {
    	glBindTexture( GL_TEXTURE_2D, texture[2] );
    	glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[2]->w, TextureImage[2]->h, 0, GL_BGR, 
                  GL_UNSIGNED_BYTE, TextureImage[2]->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			     GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			     GL_NEAREST );
    }

	if (( TextureImage[3] = SDL_LoadBMP( "textura/tex3.bmp" ) )) {
    	glBindTexture( GL_TEXTURE_2D, texture[3] );
    	glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[3]->w, TextureImage[3]->h, 0, GL_BGR, 
                  GL_UNSIGNED_BYTE, TextureImage[3]->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			     GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			     GL_NEAREST );
	}

	if (( TextureImage[4] = SDL_LoadBMP( "textura/tex4.bmp" ) )) {
    	glBindTexture( GL_TEXTURE_2D, texture[4] );
    	glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[4]->w, TextureImage[4]->h, 0, GL_BGR, 
                  GL_UNSIGNED_BYTE, TextureImage[4]->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			     GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			     GL_NEAREST );
	}

	if (( TextureImage[5] = SDL_LoadBMP( "textura/tex5.bmp" ) )) {
    	glBindTexture( GL_TEXTURE_2D, texture[5] );
    	glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[5]->w, TextureImage[5]->h, 0, GL_BGR, 
                  GL_UNSIGNED_BYTE, TextureImage[5]->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			     GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			     GL_NEAREST );
	}


    /* Free up any memory we may have used */
    for(i=0;i<6;i++)
    	if ( TextureImage[i] )
	    	SDL_FreeSurface( TextureImage[i] );

    return Status;
}

/* function to reset our viewport after a window resize */
int resizeWindow( int width, int height )
{
    /* Height / width ration */
    GLfloat ratio;
 
    /* Protect against a divide by zero */
    if ( height == 0 )
	height = 1;

    ratio = ( GLfloat )width / ( GLfloat )height;

    /* Setup our viewport. */
    glViewport( 0, 0, ( GLint )width, ( GLint )height );

    /* change to the projection matrix and set our viewing volume. */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    /* Set our perspective */
    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode( GL_MODELVIEW );

    /* Reset The View */
    glLoadIdentity( );

    return( TRUE );
}

/* function to handle key press events */
void handleKeyPress( SDL_keysym *keysym )
{
    switch ( keysym->sym )
	{
	case SDLK_ESCAPE:
	    /* ESC key was pressed */
	    Quit( 0 );
	    break;
	case SDLK_f:
	    /* 'f' key was pressed
	     * this pages through the different filters
	     */
/*	    filter = ( ++filter ) % 3;*/
	    break;
	case SDLK_l:
	    /* 'l' key was pressed
	     * this toggles the light
	     */
	    light = !light;
	    if ( !light )
		glDisable( GL_LIGHTING );
	    else
		glEnable( GL_LIGHTING );
	    break;
	case SDLK_PAGEUP:
	    /* PageUp key was pressed
	     * this zooms into the scene
	     */
	    z -= 0.02f;
	    break;
	case SDLK_PAGEDOWN:
	    /* PageDown key was pressed
	     * this zooms out of the scene
	     */
	    z += 0.02f;
	    break;
	case SDLK_UP:
	    /* Up arrow key was pressed
	     * this affects the x rotation
	     */
	    xspeed -= 0.05f;
	    break;
	case SDLK_DOWN:
	    /* Down arrow key was pressed
	     * this affects the x rotation
	     */
	    xspeed += 0.05f;
	    break;
	case SDLK_RIGHT:
	    /* Right arrow key was pressed
	     * this affects the y rotation
	     */
	    yspeed += 0.05f;
	    break;
	case SDLK_LEFT:
	    /* Left arrow key was pressed
	     * this affects the y rotation
	     */
	    yspeed -= 0.05f;
	    break;
	case SDLK_F1:
	    /* 'f' key was pressed
	     * this toggles fullscreen mode
	     */
	    SDL_WM_ToggleFullScreen( surface );
	    break;
	default:
	    break;
	}

    return;
}

/* general OpenGL initialization function */
int initGL( GLvoid )
{

    ob = criaObjeto();
    leOBJ("textura/texturaCGR.obj", ob);
    mostraPontos(ob);
    mostraNormais(ob);
    mostraFaces(ob);    
    /* Load in the texture */
    if ( !LoadGLTextures( ) )
	return FALSE;

    /* Enable Texture Mapping ( NEW ) */
    glEnable( GL_TEXTURE_2D );

    /* Enable smooth shading */
    glShadeModel( GL_SMOOTH );

    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    /* Depth buffer setup */
    glClearDepth( 1.0f );

    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );

    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    /* Setup The Ambient Light */
    glLightfv( GL_LIGHT1, GL_AMBIENT, LightAmbient );

    /* Setup The Diffuse Light */
    glLightfv( GL_LIGHT1, GL_DIFFUSE, LightDiffuse );

    /* Position The Light */
    glLightfv( GL_LIGHT1, GL_POSITION, LightPosition );

    /* Enable Light One */
    glEnable( GL_LIGHT1 );

    return( TRUE );
}

/* Here goes our drawing code */
int drawGLScene( GLvoid )
{
    /* These are to calculate our fps */
    static GLint T0     = 0;
    static GLint Frames = 0;

    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* Reset the view */
    glLoadIdentity( );
	glTranslatef (-1, -2, -7);//posicionar a imagem no centro
    /* Translate Into/Out Of The Screen By z */
    //glTranslatef( 0.0f, 0.0f, z );
	glTranslatef (0.90, 1.9, -2.1);
    glRotatef( xrot, 1.0f, 0.0f, 0.0f); /* Rotate On The X Axis By xrot */
    glRotatef( yrot, 0.0f, 1.0f, 0.0f); /* Rotate On The Y Axis By yrot */
    glTranslatef (-0.90, -1.9, 2.1);
	//glTranslatef( 0.0f, 0.0f, z );
	//drawSkyBox();

    /* Select A Texture */
    glBindTexture( GL_TEXTURE_2D, texture[0] );

    //**
    //glTranslatef (0, -2, -5);//posicionar a imagem no centro
	int i;
    for(i=0 ; i<ob->quantF ; i++) {
    	glBindTexture( GL_TEXTURE_2D, texture[i] );
        glBegin(GL_QUADS);
        glNormal3f( -1.0f, 0.0f, 0.0f );
        glTexCoord2f( 1.0f, 1.0f );glVertex3f(ob->pontos[ob->faces[i].p1-1].x, ob->pontos[ob->faces[i].p1-1].y, ob->pontos[ob->faces[i].p1-1].z);
        glTexCoord2f( 1.0f, 0.0f );glVertex3f(ob->pontos[ob->faces[i].p2-1].x, ob->pontos[ob->faces[i].p2-1].y, ob->pontos[ob->faces[i].p2-1].z);
        glTexCoord2f( 0.0f, 0.0f );glVertex3f(ob->pontos[ob->faces[i].p3-1].x, ob->pontos[ob->faces[i].p3-1].y, ob->pontos[ob->faces[i].p3-1].z);
        glTexCoord2f( 0.0f, 1.0f );glVertex3f(ob->pontos[ob->faces[i].p4-1].x, ob->pontos[ob->faces[i].p4-1].y, ob->pontos[ob->faces[i].p4-1].z);
        glEnd();
    }
    //glTranslatef (0, 2, 5);//voltar-- posicionar a imagem no centro
    //**
    /* Draw it to the screen */
    SDL_GL_SwapBuffers( );

    /* Gather our frames per second */
    Frames++;
    {
	GLint t = SDL_GetTicks();
	if (t - T0 >= 5000) {
	    GLfloat seconds = (t - T0) / 1000.0;
	    GLfloat fps = Frames / seconds;
	    printf("%d frames in %g seconds = %g FPS\n", Frames, seconds, fps);
	    T0 = t;
	    Frames = 0;
	}
    }

    xrot += xspeed*5; /* Add xspeed To xrot */
    yrot += yspeed*5; /* Add yspeed To yrot */

    return( TRUE );
}

int main( int argc, char **argv )
{
    /* Flags to pass to SDL_SetVideoMode */
    int videoFlags;
    /* main loop variable */
    int done = FALSE;
    /* used to collect events */
    SDL_Event event;
    /* this holds some info about our display */
    const SDL_VideoInfo *videoInfo;
    /* whether or not the window is active */
    int isActive = TRUE;

    /* initialize SDL */
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
	    fprintf( stderr, "Video initialization failed: %s\n",
		     SDL_GetError( ) );
	    Quit( 1 );
	}

    /* Fetch the video info */
    videoInfo = SDL_GetVideoInfo( );

    if ( !videoInfo )
	{
	    fprintf( stderr, "Video query failed: %s\n",
		     SDL_GetError( ) );
	    Quit( 1 );
	}

    /* the flags to pass to SDL_SetVideoMode */
    videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
    videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
    videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
    videoFlags |= SDL_RESIZABLE;       /* Enable window resizing */

    /* This checks to see if surfaces can be stored in memory */
    if ( videoInfo->hw_available )
	videoFlags |= SDL_HWSURFACE;
    else
	videoFlags |= SDL_SWSURFACE;

    /* This checks if hardware blits can be done */
    if ( videoInfo->blit_hw )
	videoFlags |= SDL_HWACCEL;

    /* Sets up OpenGL double buffering */
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    /* get a SDL surface */
    surface = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
				videoFlags );

    /* Verify there is a surface */
    if ( !surface )
	{
	    fprintf( stderr,  "Video mode set failed: %s\n", SDL_GetError( ) );
	    Quit( 1 );
	}

    /* initialize OpenGL */
    initGL( );

    /* resize the initial window */
    resizeWindow( SCREEN_WIDTH, SCREEN_HEIGHT );

    /* wait for events */
    while ( !done )
	{
	    /* handle the events in the queue */

	    while ( SDL_PollEvent( &event ) )
		{
		    switch( event.type )
			{
			case SDL_ACTIVEEVENT:
			    /* Something's happend with our focus
			     * If we lost focus or we are iconified, we
			     * shouldn't draw the screen
			     */
			    if ( event.active.gain == 0 )
				isActive = FALSE;
			    else
				isActive = TRUE;
			    break;			    
			case SDL_VIDEORESIZE:
			    /* handle resize event */
			    surface = SDL_SetVideoMode( event.resize.w,
							event.resize.h,
							16, videoFlags );
			    if ( !surface )
				{
				    fprintf( stderr, "Could not get a surface after resize: %s\n", SDL_GetError( ) );
				    Quit( 1 );
				}
			    resizeWindow( event.resize.w, event.resize.h );
			    break;
			case SDL_KEYDOWN:
			    /* handle key presses */
			    handleKeyPress( &event.key.keysym );
			    break;
			case SDL_QUIT:
			    /* handle quit requests */
			    done = 1;
			    break;
			default:
			    break;
			}
		}

	    /* draw the scene */
	    if ( isActive )
		drawGLScene( );
	}

    /* clean ourselves up and exit */
    Quit( 0 );

    /* Should never get here */
    return( 0 );
}
