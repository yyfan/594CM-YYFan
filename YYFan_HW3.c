/*
 *  YYFan_HW3.c
 *  XcodeGLUT
 *
 *  Created by Danny Fan on 1/26/11.
 *  Copyright 2011 UCSB. All rights reserved.
 *
 */

#include <stdlib.h>
#include <GLUT/glut.h>
#include <SOIL.h>
#include <math.h>
#include <stdio.h>

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

float vx, vy, vz;
//float v[]={0.0, 0.0, 0.0};

GLuint tex_2d;

///////////////////////////////////////////////////////// object loader /////////////////////////////////////////////////////////
int NUM_SIDES = 3;
float SCALE_VERTICES = .3; //1.0

float rotY = 0.0;
float transZ = -5.0;
int numVertices, numNormals, numTexCoords, numFaces;
struct p3f *vertices, *normals, *texcoords;
struct face *faces;


struct face {
	int numSides;
	int v1, t1, n1, v2, t2, n2, v3, t3, n3, v4, t4, n4;
};

struct p3f {
	float x;
	float y;
	float z;
};

void keyboard(unsigned char key, int x, int y);
void keySpecial(int key, int x, int y);
void idle(void);
void display(void);
void reshape(int width, int height);
void timer(int value);
void print_face(struct face f);
void print_faces(void);
void print_p3f(struct p3f p);
void scanVertex(char line[], float scale);
void scanNormal(char line[]);
void scanTexCoord(char line[]);
void scanFace(char line[], int numSides);


void print_p3f(struct p3f p) {
	printf("%f/%f/%f", p.x, p.y, p.z);
}

void print_faces() {
	printf("\n");
	int i;
	for (i = 0; i < numFaces; i++) {
		printf("face #%d:\n", i); print_face(faces[i]);
	}
}

void print_face(struct face f) {
	printf("\npt 1: v:"); print_p3f(vertices[f.v1]);
	printf(" t:"); print_p3f(texcoords[f.t1]);
	printf(" n:"); print_p3f(normals[f.n1]);
	printf("\npt 2: v:"); print_p3f(vertices[f.v2]);
	printf(" t:"); print_p3f(texcoords[f.t2]);
	printf(" n:"); print_p3f(normals[f.n2]);
	printf("\npt 3: v:"); print_p3f(vertices[f.v3]);
	printf(" t:"); print_p3f(texcoords[f.t3]);
	printf(" n:"); print_p3f(normals[f.n3]);
	printf("\n");
}

void scanVertex(char line[], float scale) {
	numVertices++;
	vertices = (struct p3f *)realloc (vertices, sizeof(struct p3f) * numVertices);
	float a, b, c;
	sscanf (line, "v %f %f %f", &a, &b, &c);
	struct p3f v;
	v.x = a * scale; v.y = b * scale; v.z = c * scale;
	vertices[numVertices - 1] = v; 
}

void scanTexCoord(char line[]) {
	numTexCoords++;
	texcoords = (struct p3f *)realloc (texcoords, sizeof(struct p3f) * numTexCoords);
	float a, b;
	sscanf (line, "vt %f %f", &a, &b);
	struct p3f tc;
	tc.x = a; tc.y = b; tc.z = 0.0;
	texcoords[numTexCoords - 1] = tc; 
}

void scanNormal(char line[]) {
	numNormals++;
	normals = (struct p3f *)realloc (normals, sizeof(struct p3f) * numNormals);
	float a, b, c;
	sscanf (line, "vn %f %f %f", &a, &b, &c);
	struct p3f n;
	n.x = a; n.y = b; n.z = c;
	normals[numNormals - 1] = n; 
}

void scanFace(char line[], int numSides) {
	numFaces++;
	faces = (struct face *) realloc(faces, sizeof(struct face) * numFaces);
	int v1, t1, n1, v2, t2, n2, v3, t3, n3, v4, t4, n4;
	if (numSides == 3) {
		sscanf (line, "f %i/%i/%i %i/%i/%i %i/%i/%i", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);
	} else {
		sscanf (line, "f %i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3, &v4, &t4, &n4);
	}
	struct face f;
	f.v1 = v1 - 1; f.v2 = v2 - 1; f.v3 = v3 - 1; f.v4 = v4 - 1; 
	f.t1 = t1 - 1; f.t2 = t2 - 1; f.t3 = t3 - 1; f.t4 = t4 - 1;
	f.n1 = n1 - 1; f.n2 = n2 - 1; f.n3 = n3 - 1; f.n4 = n4 - 1;
	f.numSides = numSides;
	faces[numFaces - 1] = f; 
}

void readFile(char* filename) {
	vertices = (struct p3f *) malloc (sizeof(struct p3f));
	normals = (struct p3f *) malloc (sizeof(struct p3f));
	texcoords = (struct p3f *) malloc (sizeof(struct p3f));
	faces = (struct face *) malloc (sizeof(struct face));
	
	FILE *file = fopen ( filename, "r" );
	if ( file != NULL )
	{
		char line[128]; 
		
		while(fgets(line, sizeof line, file) != NULL) {
			if (strncmp( line, "v ", 2) == 0) {
				scanVertex(line, SCALE_VERTICES);
			} else if (strncmp( line, "vt", 2) == 0) {
				scanTexCoord(line);
			} else if (strncmp( line, "vn", 2) == 0) {
				scanNormal(line);
			} else if (strncmp( line, "f ", 2) == 0) {
				scanFace(line, NUM_SIDES);
			}
		}
		fclose(file);
	}
	else {
		perror(filename);
	}
}

void displayFaces() {
	
	int i;
	for (i = 0; i < numFaces; i++) {
		struct face f = faces[i];
		
		glBegin(GL_TRIANGLES);
		
		//v1
		struct p3f n1 = normals[f.n1]; 
		struct p3f t1 = texcoords[f.t1]; 
		struct p3f p1 = vertices[f.v1]; 
		
		glNormal3f(n1.x, n1.y, n1.z);
		glTexCoord2f(t1.x, t1.y);  
		glVertex3f(p1.x, p1.y, p1.z);  
		
		//v2
		struct p3f n2 = normals[f.n2]; 
		struct p3f t2 = texcoords[f.t2]; 
		struct p3f p2 = vertices[f.v2]; 
		
		glNormal3f(n2.x, n2.y, n2.z);
		glTexCoord2f(t2.x, t2.y);
		glVertex3f(p2.x, p2.y, p2.z); 
		
		//v3
		struct p3f n3 = normals[f.n3];
		struct p3f t3 = texcoords[f.t3]; 
		struct p3f p3 = vertices[f.v3]; 
		
		glNormal3f(n3.x, n3.y, n3.z);
		glTexCoord2f(t3.x, t3.y);
		glVertex3f(p3.x, p3.y, p3.z);
		
		glEnd();  
	}
}

void display(void) {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glLightfv(GL_LIGHT0, GL_POSITION, position); // Note that glLightfv cannot be called inside a glBegin-glEnd block
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);	
	
	glTranslatef(0.0, 0.0, transZ);
	glRotatef(rotY, 0.0, 1.0, 0.0);
	
	displayFaces();
	
	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)width / (float) height, .01, 100.0);
}

void init(void) {
	
	glEnable(GL_LIGHTING);	// enable lighting
	glEnable(GL_LIGHT0);	// turn on LIGHT0
	glEnable(GL_NORMALIZE); 	// normalize normals
	glEnable(GL_DEPTH_TEST);	//depth test
	
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0,0.0,0.0,0.0);
	readFile("stairs.obj");
	//	print_faces();
}

void keyboard(unsigned char key, int x, int y) {
	printf("key pressed %c (%d) \n", key, key);
	
	switch(key) {
		case 'a':
			break;
			
		case 'b':
			break;
			
		case 'q': 
		case 27: //Escape key
			exit(0); 
	}
}

void keySpecial(int key, int x, int y) {  
	printf("special key pressed:< %c > \n", key);
	
	switch(key) {
		case GLUT_KEY_LEFT:
			break;
		case GLUT_KEY_RIGHT:
			break;
		case GLUT_KEY_UP:
			transZ += 0.1;
			break;
		case GLUT_KEY_DOWN:
			transZ -= 0.1;
			break;
		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;
		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
			break;
	}
}

void timer(int value) {
	rotY += 1.0;
	glutTimerFunc(1000/60,timer,0);
}

void idle(void) {
	glutPostRedisplay();
}

void mouseMoved(int x, int y) {
	printf("mouse at %i/%i\n", x, y);
}

///////////////////////////////////////////////////////// object loader end /////////////////////////////////////////////////////////

int main (int argc, char **argv)
{
	glutInit(&argc, argv); // load texture, lighting
	glutInitWindowSize(400,300);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	
	glutCreateWindow("Homework#3");
	glutDisplayFunc(display); // Display // modelview		
	glutReshapeFunc(reshape); // Reshape // perspective projection "lens"
	glutIdleFunc(idle);	
	//	glClearColor(0.0,0.0,0.0,0.0);
	
	glutSpecialFunc(keySpecial); // inputKey
	glutKeyboardFunc(keyboard); // inputKeyboard
	
	init();//	myInit();
	//	loadTexture();	
	
	glutTimerFunc(1000/60,timer,0);
	
	glutMainLoop();
	return 0;
}



