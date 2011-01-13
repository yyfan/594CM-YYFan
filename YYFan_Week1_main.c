#include <stdlib.h>
#include <GLUT/glut.h>

float xRotated, yRotated, zRotated;
float keyRotateX, keyRotateY, KeyRotateZ;
float distX, distY, thrust;
float pos[] = {1.0, 1.0, 0.0, 1.0};

void myInit()
{	
	//	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	//	glShadeModel(GL_FLAT);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	float ambient[] = {1.0, 0.0, 0.0, 1.0};
	float diffuse[] = {0.0, 1.0, 0.0, 1.0};
	float specular[] = {0.0, 0.0, 1.0, 1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	
	float objectHighlights[]= {1.0f, 1.0f, 1.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_SPECULAR, objectHighlights);
	float specularExponent = 128.0;	
	glMaterialf(GL_FRONT, GL_SHININESS, specularExponent);
	
	//	glLightfv(GL_LIGHTING, GL_POSITION, pos);
	
}

void drawing1()
{
	glPushMatrix();
	glColor4f(0.77, 0.33, 0.79, 0.1);
	glTranslatef(4.0,0.0,0.0);		
	glutWireSphere(0.3, 5, 10);	
	glutSolidSphere(1.0, 50.0, 10.0);
	glPopMatrix();	
	
	glPushMatrix();
	glTranslatef(4.0,0.0,0.0);			
	glRotatef(xRotated,0.0,0.0,1.0);
	glTranslatef(2.0,0.0,0.0);	
	glLightfv(GL_LIGHTING, GL_POSITION, pos);	
	glutSolidSphere(0.3, 50, 10);	
	glPopMatrix();
	
}

void drawing2()
{
	glPushMatrix();
	glColor4f(0.5, 0.5, 0.5, 0.5);
	glTranslatef(-4.0,0.0,0.0);
	glRotatef(xRotated,0.0,1.0,0.0);
	glutSolidSphere(1.0, 50.0, 10.0	);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-4.0,0.0,0.0);			
	glRotatef(xRotated,0.0,1.0,0.0);	
	glTranslatef(2.0,0.0,0.0);	
	glutSolidSphere(0.3, 50, 10);
	glLightfv(GL_LIGHTING, GL_POSITION, pos);	
	glPopMatrix();
}

void coord()
{
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.5);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.5, 0.0);
	glEnd();
	glPopMatrix();
	
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	glTranslatef(0.0,0.0,-10.0);
	glTranslatef(distX,distY,thrust);
	glRotatef(keyRotateX, 1, 0, 0);
	glRotatef(keyRotateY, 0, 1, 0);
	glColor4f(0.7, 0.1, 0.3, 0.1);
	coord();
	drawing1();
	drawing2();
	glutSwapBuffers();
}

void Reshape(int x, int y)
{
	glViewport(0.0, 0.0, -10.0, 0.0);	
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	gluPerspective(60.0,(GLdouble)x/(GLdouble)y,1.0,100.0);
}

void Idle(void)
{
	xRotated += 0.1;
	yRotated += 0.1;
	zRotated += 0.1;
	//	Display();	
	glutPostRedisplay();
}


void inputKey(int key, int x, int y) {
	
	switch (key) {
		case GLUT_KEY_LEFT : 
			keyRotateY -= 1.0f;
			break;
		case GLUT_KEY_RIGHT : 
			keyRotateY += 1.0f;
			break;
		case GLUT_KEY_UP : 
			keyRotateX += 1.0f;
			break;
		case GLUT_KEY_DOWN : 
			keyRotateX -= 1.0f;
			break;
	}
}

void inputKeyboard(int keyboard, int x, int y) {
	
	switch (keyboard) {
		case 'a' : 
			distX -= 1.0f;
			break;
		case 'd' : 
			distX += 1.0f;
			break;
		case 'x' : 
			distY += 1.0f;
			break;
		case 'w' : 
			distY -= 1.0f;
			break;
		case 'r' :
			thrust += 1.0f;
			break;
		case 'f' :
			thrust -= 1.0f;
			break;
	}
}


int main (int argc, char **argv)
{
	glutInit(&argc, argv); // load texture, lighting
	glutInitWindowSize(400,300);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	
	glutCreateWindow("Homework#1");
	glutDisplayFunc(Display); // modelview		
	glutReshapeFunc(Reshape); // perspective projection "lens"
	glutIdleFunc(Idle);	
	glClearColor(0.0,0.0,0.0,0.0);
	
	glutSpecialFunc(inputKey);
	glutKeyboardFunc(inputKeyboard);
	
	myInit();
	
	glutMainLoop();
	return 0;
}

