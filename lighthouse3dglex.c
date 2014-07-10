
/*
  Simple Demo for GLSL
  www.lighthouse3d.com
  
  tweaked a bit by andy
*/

#include "GL/glew.h"

#ifdef __linux__
#include <GL/glut.h>
#endif

#ifdef __APPLE__
#include <glut.h>
#endif

#ifdef _WIN32
#include "glut.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////

char *textFileRead(char *fn)
{
	FILE *fp;
	char *content = NULL;

	int count=0;

	if (fn != NULL) {
		fp = fopen(fn,"rt");

		if (fp != NULL) {
      
      fseek(fp, 0, SEEK_END);
      count = ftell(fp);
      rewind(fp);

			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	
	if (content == NULL)
	   {
	   fprintf(stderr, "ERROR: could not load in file %s\n", fn);
	   exit(1);
	   }
	return content;
}

///////////////////////////////////////////////////////////////////////           

int textFileWrite(char *fn, char *s)
{
        FILE *fp;
        int status = 0;

        if (fn != NULL) {
                fp = fopen(fn,"w");

                if (fp != NULL) {
                        
                        if (fwrite(s,sizeof(char),strlen(s),fp) == strlen(s))
                                status = 1;
                        fclose(fp);
                }
        }
        return(status);
}   

///////////////////////////////////////////////////////////////////////

GLuint v,f,p;
float lpos[4] = {1.0, 0.5, 1.0, 0.0};

///////////////////////////////////////////////////////////////////////

void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

///////////////////////////////////////////////////////////////////////

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0,0.0,5.0, 
		      0.0,0.0,-1.0,
			  0.0f,1.0f,0.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	glutSolidTeapot(1);

	glutSwapBuffers();
}

///////////////////////////////////////////////////////////////////////

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27) 
		exit(0);
}

///////////////////////////////////////////////////////////////////////

void setShaders()
{
	char *vs,*fs;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);

    // older syntax
	//v = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	//f = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

	vs = textFileRead("./toon.vert");
	fs = textFileRead("./toon.frag");

	const char * ff = fs;
	const char * vv = vs;

	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);

    // older syntax
	//glShaderSourceARB(v, 1, &vv,NULL);
	//glShaderSourceARB(f, 1, &ff,NULL);

	free(vs);free(fs);

	glCompileShader(v);
	glCompileShader(f);

    // older syntax
	//glCompileShaderARB(v);
	//glCompileShaderARB(f);

	p = glCreateProgram();

    // older syntax
	//p = glCreateProgramObjectARB();

	glAttachShader(p,f);
	glAttachShader(p,v);
	
    // older syntax
	//glAttachObjectARB(p,f);
	//glAttachObjectARB(p,v);

	glLinkProgram(p);
	
	// comment out this line to not use the shader
	glUseProgram(p);

    // older syntax
	//glLinkProgramARB(p);
	//glUseProgramObjectARB(p);
}

///////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("GLSL");

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0,0.0,0.0,1.0);

	glewInit();
	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
		printf("Ready for GLSL\n");
	else {
		printf("No GLSL support\n");
		exit(1);
	}

	setShaders();

	glutMainLoop();
	return 0;
}
