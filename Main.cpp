#include "glut3.7.6/glut.h"
//#include <gl/GL.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#pragma comment(lib, "glut32.lib")

//for convenience
typedef float point[2];
using namespace std;
//recursive function
void Draw(point left_down, point right_down, int degree) {
	float size = right_down[0] - left_down[0];
	float size_new = size / 3;
	//If the function is not recursive
	if (degree == 1) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				//Coordinates of the fractal part
				point new_left_down = { left_down[0] + (size_new * i), left_down[1] + (size_new * j) };
				point new_left_up = { left_down[0] + (size_new * i), left_down[1] + size_new + (size_new * j) };
				point new_right_up = { left_down[0] + size_new + (size_new * i), left_down[1] + size_new + (size_new * j) };
				point new_right_down = { left_down[0] + size_new + (size_new * i), left_down[1] + (size_new * j) };
				if ((i != 1) || (j != 1)) {
					glBegin(GL_QUADS);
					glColor3f(1, 1, 1);
					glVertex2fv(new_left_down);
					glColor3f(1, 1, 1);
					glVertex2fv(new_left_up);
					glColor3f(1, 1, 1);
					glVertex2fv(new_right_up);
					glColor3f(1, 1, 1);
					glVertex2fv(new_right_down);
					glEnd();
				}
				else {
					//Draw a black square (center)
					glBegin(GL_QUADS);
					glColor3f(0.0f, 0.0f, 0.0f);
					glVertex2fv(new_left_down);
					glVertex2fv(new_left_up);
					glVertex2fv(new_right_up);
					glVertex2fv(new_right_down);
					glEnd();
				}
			}
		}
	}
	else {
		//If the function is recursive
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					//Coordinates of the fractal part
					point new_left_down = { left_down[0] + (size_new * i), left_down[1] + (size_new * j) };
					point new_left_up = { left_down[0] + (size_new * i), left_down[1] + size_new + (size_new *
				   j) };
					point new_right_up = { left_down[0] + size_new + (size_new * i), left_down[1] + size_new +
				   (size_new * j) };
					point new_right_down = { left_down[0] + size_new + (size_new * i), left_down[1] +
				   (size_new * j) };
					if ((i != 1) || (j != 1)) {
						//recursion
						Draw(new_left_down, new_right_down, degree - 1);
					}
					else {
						//draw an empty square (white)
						glBegin(GL_POLYGON);
						glColor3f(0.0f, 0.0f, 0.0f);
						glVertex2fv(new_left_down);
						glVertex2fv(new_left_up);
						glVertex2fv(new_right_up);
						glVertex2fv(new_right_down);
						glEnd();
					}
				}
			}
	}
}

//Screen display
void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	//coordinates of bottom faces
	point left_down = { -50, -50 };
	point right_down = { 50, -50 };
	//How many times to recurse
	int degree = 3;
	if (degree > 0)
		Draw(left_down, right_down, degree);
	glFlush();
}
//When resizing the window
void ChangeSize(GLsizei horizontal, GLsizei vertical) {
	//window aspect ratio
	GLfloat AspectRatio;
	//To avoid dividing by 0
	if (vertical == 0)
		vertical = 0.0001;
	//Setting the size of the Viewport window
	glViewport(0, 0, horizontal, vertical);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Determine the proportion
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	//keep the aspect ratio
	if (horizontal <= vertical)
		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0 * AspectRatio, 100.0 * AspectRatio, -100.0, 100.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutCreateWindow("Sierpinski Fractal. Kronos");
	//Screen display
	glutDisplayFunc(RenderScene);
	//When resizing the window
	glutReshapeFunc(ChangeSize);
	//Standard function to terminate the main
	glutMainLoop();
	return (0);
}