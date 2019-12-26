#include<windows.h>
#include<gl/glut.h>
#include<stdio.h> 

GLfloat light_position[] = { 1.0,1.0,1.0,0.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };
GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat Light_Model_Ambient[] = { 0.2, 0.2, 0.2, 1.0 };

void init() {
	glClearColor(0.75,0.75, 0.75, 0.75);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	GLfloat light_diffuse[] = { 1.0, 0.0,0.0,1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glTranslatef(0.0, -0.33, 0.0);
	glRotated(90, -1, 0, 0);
	glutSolidCone(0.3, 1.1, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.63, 0.0);
	glRotated(90, -1, 0, 0);
	glutSolidTorus(0.03, 0.12, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.78, 0.0);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 40, 50);
	glPopMatrix();
	// glFlush();
	
	glPushMatrix();
	glTranslatef(0.0, -0.33, 0.0);
	glRotated(90, -1, 0, 0);
	glutSolidTorus(0.065, 0.3, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glRotated(90, -1, 0, 0);
	GLUquadricObj *objCylinder = gluNewQuadric();
	gluCylinder(objCylinder, 0.09, 0.09, 0.62, 30, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.43, 0.0);
	glRotated(90, -1, 0, 0);
	glutSolidTorus(0.025, 0.1, 20, 20);
	glPopMatrix();
	glFlush();

}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-1.5, 1.5, -1.5*(GLfloat)h / (GLfloat)w, 1.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-1.5*(GLfloat)w / (GLfloat)h, 1.5*(GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("UglyRedChess");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
