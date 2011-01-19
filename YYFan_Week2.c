#include <stdlib.h>
#include <GLUT/glut.h>

float Rot;
float keyRotateX, keyRotateY, KeyRotateZ;
float distX, distY, thrust;
// define the light model
float position[] = {1.0, 1.0, 1.0, 1.0};// if the last value != 0, then light is "positional"
float ambient[] = {1.0, 0.0, 0.0, 1.0};
float diffuse[] = {0.0, 1.0, 0.0, 1.0};
float specular[] = {0.0, 0.0, 1.0, 0.0};

float objectHighlights[]= {0.1f, 0.1f, 0.1f, 1.0f};
float specularExponent = 64.0;	
float objectHighlights2[]= {0.0f, 0.3f, 0.3f, 1.0f};
float specularExponent2 = 128.0;
float objectHighlights3[]= {0.5f, 0.0f, 0.5f, 1.0f};
float specularExponent3 = 256.0;	
float objectHighlights4[]= {0.7f, 0.7f, 0.0f, 1.0f};
float specularExponent4 = 512.0;

//Spotlight properties

float light_position[] = { 50.0, 100.0, -50.0, 1.0 };
float light_spot_direction[] = { 0.0, 0.0, -1.0};
float light_spot_cutoff[] = { 25.0 };
float light_spot_exp[] = { 2.0 };

float light_position2[] = { 50.0, -100.0, -50.0, 1.0 };
float light_spot_direction2[] = { 0.0, 0.0, -1.0};
float light_spot_cutoff2[] = { 25.0 };
float light_spot_exp2[] = { 5.0 };

//Define GLfloat arrays to hold material data
float mat_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
float mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };

float mat_ambient1[] = { 0.9, 0.3, 0.3, 1.0 };
float mat_diffuse1[] = { 0.9, 0.8, 0.8, 1.0 };
float mat_specular1[] = { 0.9, 1.0, 1.0, 1.0 };

float mat_ambient2[] = { 0.3, 0.8, 0.3, 1.0 };
float mat_diffuse2[] = { 0.8, 0.8, 0.8, 1.0 };
float mat_specular2[] = { 1.0, 0.8, 1.0, 1.0 };

float mat_ambient3[] = { 0.3, 0.3, 0.7, 1.0 };
float mat_diffuse3[] = { 0.8, 0.8, 0.7, 1.0 };
float mat_specular3[] = { 1.0, 1.0, 0.7, 1.0 };

//Shininess will be an array of length 1
float mat_shininess[] = { 50.0 };
float mat_shininess1[] = { 25.0 };
float mat_shininess2[] = { 75.0 };
float mat_shininess3[] = { 100.0 };

//float direction = {0.0, -1.0, 0.0};

void myInit()
{	
	glEnable(GL_LIGHTING);	// enable lighting
	glEnable(GL_LIGHT0);	// turn on LIGHT0
	glEnable(GL_NORMALIZE); 	// normalize normals
	glEnable(GL_DEPTH_TEST);	//depth test
}

void drawing1()
{
	glPushMatrix();
	glTranslatef(1.0,0.0,0.0);		
	glutSolidCube(0.5);
	glPopMatrix();	
	
	glPushMatrix();
	glTranslatef(1.0,0.0,0.0);			
	glRotatef(Rot,1.0,0.0,0.0);
	glTranslatef(0.0,0.0,1.0);			
	glutSolidCube(0.2);	
	glPopMatrix();
	
}

void drawing2()
{
	glPushMatrix();
	glTranslatef(-1.0,0.0,0.0);
	glutSolidCube(0.5);	
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-1.0,0.0,0.0);			
	glRotatef(Rot,0.0,0.0,1.0);	
	glTranslatef(1.0,0.0,0.0);	
	glRotatef(Rot,0.0,1.0,0.0);	
	glutSolidCube(0.3);		
	glPopMatrix();
}

void QuadMountain()
{
	// 1-3-5-7
	// | | | |
	// 0-2-4-6
	glNormal3f(-0.02, 0.04, -0.02);
	glBegin(GL_QUAD_STRIP);	
	glVertex3f(0.0, 0.1, 0.2); // 0
	glVertex3f(0.0, 0.0, 0.0); // 1
	glVertex3f(0.2, 0.0, 0.2); // 2
	glVertex3f(0.2, 0.1, 0.0); // 3
	glEnd();
	glNormal3f(0.0,0.04,0.02);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(0.2, 0.0, 0.2); // 2
	glVertex3f(0.2, 0.1, 0.0); // 3
	glVertex3f(0.4, 0.0, 0.2); // 4
	glVertex3f(0.4, 0.1, 0.0); // 5
	glEnd();	
	glNormal3f(0.04, 0.04, 0.02);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(0.4, 0.0, 0.2); // 4
	glVertex3f(0.4, 0.1, 0.0); // 5
	glVertex3f(0.6, 0.0, 0.2); // 6
	glVertex3f(0.6, -0.1, 0.0); // 7
	glEnd();
	
	//	glBegin(GL_TRIANGLE_STRIP);	
}

void TriMountain()
{
	//	 1 - 3 - 5 - 7
	//  / \ / \ / \ /
	// 0 - 2 - 4 - 6
	glNormal3f(0.02, 0.04, 0.02);
	glBegin(GL_TRIANGLE_STRIP);	
	glVertex3f(0.0, 0.1, 0.2); // 0
	glVertex3f(0.0, 0.0, 0.0); // 1
	glVertex3f(0.2, 0.0, 0.2); // 2
	glEnd();
	glNormal3f(-0.02,0.04,0.02);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0.0, 0.0, 0.0); // 1	
	glVertex3f(0.2, 0.0, 0.2); // 2
	glVertex3f(0.2, 0.1, 0.0); // 3
	glEnd();	
	glNormal3f(0.0, 0.04, 0.02);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0.2, 0.0, 0.2); // 2
	glVertex3f(0.2, 0.1, 0.0); // 3	
	glVertex3f(0.4, 0.0, 0.2); // 4
	glEnd();
	glNormal3f(0.0, 0.04, 0.02);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0.2, 0.1, 0.0); // 3		
	glVertex3f(0.4, 0.0, 0.2); // 4
	glVertex3f(0.4, 0.1, 0.0); // 5
	glEnd();
	glNormal3f(0.0, 0.04, 0.02);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0.4, 0.0, 0.2); // 4
	glVertex3f(0.4, 0.1, 0.0); // 5
	glVertex3f(0.6, 0.0, 0.2); // 6
	glEnd();
	glNormal3f(0.04, 0.04, -0.02);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0.4, 0.1, 0.0); // 5
	glVertex3f(0.6, 0.0, 0.2); // 6
	glVertex3f(0.6, -0.1, 0.0); // 7
	glEnd();
	
	//	glBegin(GL_TRIANGLE_STRIP);	
}

void SpotLightPrimitive(){
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION , light_spot_direction);
	//	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF , 25.0);
	glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT , light_spot_exp);
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	
	glutSolidSphere(0.3, 64, 64);
	glPopMatrix();
	
	glPushMatrix();	
	glLightfv(GL_LIGHT0, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION , light_spot_direction2);
	//	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF , 25.0);
	glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT , light_spot_exp2);
	glRotatef(Rot,1.0,0.0,0.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess1);
	
	glutSolidTorus(0.1, 0.5, 64, 64);
	glPopMatrix();
	
	glPushMatrix();			
	glRotatef(Rot,0.0,1.0,0.0);	
	glLightfv(GL_LIGHT0, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION , light_spot_direction2);
	//	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF , 25.0);
	glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT , light_spot_exp2);
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess2);
	
	glutSolidTorus(0.1, 0.5, 64, 64);
	glPopMatrix();
	
	glPushMatrix();			
	glRotatef(Rot,0.0,0.0,1.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION , light_spot_direction2);
	//	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF , 25.0);
	glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT , light_spot_exp2);
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess3);
	
	glutSolidTorus(0.1, 0.5, 64, 64);
	glPopMatrix();
}

void sun()
{		
	glPushMatrix();			
	glRotatef(Rot,0.0,0.0,1.0);	
	glTranslatef(1.0,0.0,0.0);		
	glutSolidSphere(0.05, 64, 64);
		glLightfv(GL_LIGHT0, GL_POSITION, position); // Note that glLightfv cannot be called inside a glBegin-glEnd block
	//	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient); 
	//	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	//	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
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
//	glLightfv(GL_LIGHT0, GL_POSITION, position); // Note that glLightfv cannot be called inside a glBegin-glEnd block
//	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient); 
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);	
	
//	coord();
//	drawing1();
//	drawing2();
//	sun();	
//	QuadMountain();	
//	TriMountain();
	SpotLightPrimitive();
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
	Rot += 0.1;
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
	glutCreateWindow("Homework#2");
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

