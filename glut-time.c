#include <GL/glew.h>
#include <GL/glut.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WWIDTH 640
#define WHEIGHT 480

void display_callback(void);
void reshape_callback(int, int);
void keyboard_callback(unsigned char, int, int);
void special_callback(int, int, int);
void setShaders(void);
char *textFileRead(char *);

static float red = 0;
static float green = 0;
static float blue = 0;

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    int swidth, sheight;
    swidth = glutGet(GLUT_SCREEN_WIDTH);
    sheight = glutGet(GLUT_SCREEN_HEIGHT);

    glutInitWindowPosition((swidth - WWIDTH) / 2, (sheight - WHEIGHT) / 2);
    glutInitWindowSize(WWIDTH, WHEIGHT);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    int w = glutCreateWindow("Win! Dough.");

    glewInit();

    setShaders();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);

    /*glutDisplayFunc(display_callback);*/
    glutReshapeFunc(reshape_callback);
    glutIdleFunc(display_callback);
    glutKeyboardFunc(keyboard_callback);
    glutSpecialFunc(special_callback);

    glutMainLoop();

    return 0;
}

void display_callback(void)
{
    static float angle = 0;
    static int elapsed_old = 0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(0, 0, -1,
              0, 0,  0,
              0, 1,  0);

    glPushMatrix();

    glTranslatef(0, 0, 5);

    glRotatef(angle, 0.6, 0.9, 0.3);

    glPushMatrix();

    glTranslatef(-0.5, 0, 0);

    glBegin(GL_QUADS);
        glColor3f(red, green, blue);
        glVertex3f(0, 0.5, 0.5);
        glColor3f(red, green, blue);
        glVertex3f(0, 0.5, -0.5);
        glColor3f(red, green, blue);
        glVertex3f(0, -0.5, -0.5);
        glColor3f(red, green, blue);
        glVertex3f(0, -0.5, 0.5);
    glEnd();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(0.5, 0, 0);

    glBegin(GL_QUADS);
        glColor3f(green, red, blue);
        glVertex3f(0, 0.5, 0.5);
        glColor3f(green, red, blue);
        glVertex3f(0, 0.5, -0.5);
        glColor3f(green, red, blue);
        glVertex3f(0, -0.5, -0.5);
        glColor3f(green, red, blue);
        glVertex3f(0, -0.5, 0.5);
    glEnd();

    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);

    glPushMatrix();

    glTranslatef(-0.5, 0, 0);

    glBegin(GL_QUADS);
        glColor3f(blue, green, red);
        glVertex3f(0, 0.5, 0.5);
        glColor3f(blue, green, red);
        glVertex3f(0, 0.5, -0.5);
        glColor3f(blue, green, red);
        glVertex3f(0, -0.5, -0.5);
        glColor3f(blue, green, red);
        glVertex3f(0, -0.5, 0.5);
    glEnd();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(0.5, 0, 0);

    glBegin(GL_QUADS);
        glColor3f(red, blue, green);
        glVertex3f(0, 0.5, 0.5);
        glColor3f(red, blue, green);
        glVertex3f(0, 0.5, -0.5);
        glColor3f(red, blue, green);
        glVertex3f(0, -0.5, -0.5);
        glColor3f(red, blue, green);
        glVertex3f(0, -0.5, 0.5);
    glEnd();

    glPopMatrix();

    glPopMatrix();

    glPushMatrix();

    glRotatef(90, 0, 0, 1);

    glPushMatrix();

    glTranslatef(-0.5, 0, 0);

    glBegin(GL_QUADS);
        glColor3f(blue, blue, red);
        glVertex3f(0, 0.5, 0.5);
        glColor3f(blue, blue, red);
        glVertex3f(0, 0.5, -0.5);
        glColor3f(blue, blue, red);
        glVertex3f(0, -0.5, -0.5);
        glColor3f(blue, blue, red);
        glVertex3f(0, -0.5, 0.5);
    glEnd();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(0.5, 0, 0);

    glBegin(GL_QUADS);
        glColor3f(red, blue, red);
        glVertex3f(0, 0.5, 0.5);
        glColor3f(red, blue, red);
        glVertex3f(0, 0.5, -0.5);
        glColor3f(red, blue, red);
        glVertex3f(0, -0.5, -0.5);
        glColor3f(red, blue, red);
        glVertex3f(0, -0.5, 0.5);
    glEnd();

    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    int elapsed = glutGet(GLUT_ELAPSED_TIME);
    int delta = elapsed - elapsed_old;
    elapsed_old = elapsed;
    angle += 90 * (float)delta / 1000;

    glutSwapBuffers();
}

void reshape_callback(int width, int height)
{
    if (height == 0)
        height = 1;

    float ratio = 1.0 * width / height;

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glViewport(0, 0, width, height);

    gluPerspective(45, ratio, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
}

void keyboard_callback(unsigned char key, int x, int y)
{
    if (isgraph(key) || isblank(key)) {
        printf("\"%c\" was pressed. (Value: %d)\n", key, key);
    } else {
        printf("Key of value %d was pressed.\n", key);
    }
}

void special_callback(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_F1:
            red = 1.0;
            green = 0.0;
            blue = 0.0;
            break;
        case GLUT_KEY_F2:
            red = 0.0;
            green = 1.0;
            blue = 0.0;
            break;
        case GLUT_KEY_F3:
            red = 0.0;
            green = 0.0;
            blue = 1.0;
            break;
        default:
            red = (float)rand() / (float)RAND_MAX;
            green = (float)rand() / (float)RAND_MAX;
            blue = (float)rand() / (float)RAND_MAX;
    }

    printf("Special key value %d pressed.\n", key);
}

void setShaders() {
    GLuint v, f, p;
    char *fs, *vs;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);	

	vs = textFileRead("gluttest.vert");
	fs = textFileRead("gluttest.frag");

	const char * vv = vs;
	const char * ff = fs;

	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);

	free(vs);free(fs);

	glCompileShader(v);
	glCompileShader(f);

	p = glCreateProgram();

	glAttachShader(p,v);
	glAttachShader(p,f);

	glLinkProgram(p);
	glUseProgram(p);
}


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
