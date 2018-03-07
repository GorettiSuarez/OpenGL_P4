#include <stdio.h>

#include <GL\glew.h>
#include <GL\freeglut.h>

float gl_ancho = 2.0, gl_alto = 2.0, gl_cerca = 0.0, gl_lejos = 4.0;
int w_ancho = 500, w_alto = 500;

void InitGlew() {

	GLenum glew_init = glewInit();
	if (glew_init != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_init));
	}
	else {
		fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	}
}

void Init() {
	if (gl_ancho / w_ancho != gl_alto / w_alto){
		fprintf(stderr, "La relación de aspecto no es correcta\n");
	}

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-gl_ancho / 2.0, gl_ancho / 2.0, -gl_alto / 2.0, gl_alto / 2.0, gl_cerca, gl_lejos); // espacio de trabajo
	//glFrustum(-gl_ancho/2.0, gl_ancho/2.0, -gl_alto/2.0, gl_alto/2.0, gl_cerca,gl_lejos);
}


void Display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra todo lo existente en el framebuffer

	glColor3f(1.0, 0.0, 0.0);

	glEnable(GL_POINT_SMOOTH);
	glPointSize(10.0f);

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(-0.5, 0.5);
		glVertex2f(-0.8, 0.8);
		glVertex2f(0.5, 0.5);
		glVertex2f(0.8, 0.8);
		glVertex2f(0.5, -0.5);
		glVertex2f(0.8, -0.8);
		glVertex2f(-0.5, -0.5);
		glVertex2f(-0.8, -0.8);
		glVertex2f(-0.5, 0.5);
		glVertex2f(-0.8, 0.8);
	glEnd();

	glFlush();

}

// cambio de dimensiones de la ventana, manteniendo la dimension de los objetos
void ReshapeSize(int ancho, int alto){

	float dx = gl_ancho;
	float dy = gl_alto;

	dx *= (float)ancho / (float)w_ancho;
	dy *= (float)alto / (float)w_alto;

	glViewport(0, 0, ancho, alto); // utiliza la totalidad de la ventana
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-dx / 2.0, dx / 2.0, -dy / 2.0, dy / 2.0, gl_cerca, gl_lejos); // espacio de trabajo
	//glFrustum(-dx / 2.0, dx / 2.0, -dy / 2.0, dy / 2.0, gl_cerca, gl_lejos);
	glutPostRedisplay();
}

int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(w_ancho, w_alto);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);

	glutCreateWindow("OpenGL Practica 4");
	InitGlew(); // despues de crear la primera ventana
	Init();
	glutDisplayFunc(Display); // registra la funcion de rendering 
	glutReshapeFunc(ReshapeSize);

	glutMainLoop(); // bucle principal

	return 0;
}