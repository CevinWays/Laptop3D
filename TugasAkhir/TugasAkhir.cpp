#include "stdafx.h"
#include <stdlib.h>
#include "glut.h"
#include "imageloader.h"

// Deklarasi Variabel
int w = 800, h = 500, z = -20, x1 = 0, y1 = 0, z1 = 0, sudut = 0,
x2 = 0, y2 = 0, z2 = 0, sudut2 = 0, x , y;

double xcahaya = 100, ycahaya = 100,
rpower = 0.4,
gpower = 0.4,
bpower = 0.4,
statuspower = 0,
_angle = 0,
_angle1 = 0,
_angle2 = 0,
_amb = 0
;

GLuint _textureId; //ID OpenGL untuk tekstur
				   //Membuat gambar menjadi tekstur kemudian berikan ID pada tekstur
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureId;
}

//load image bitmap file 1.bmp
void initRendering() {

	Image* image = loadBMP("1.bmp");
	_textureId = loadTexture(image);
	delete image;
}

// setting ukuran
void resize(int w1, int h1) {
	glViewport(0, 0, w1, h1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w1 / (float)h1, 1.0, 3000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// lighting
void init() {
	GLfloat LightSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat Shine[] = { 10 };

	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glMaterialfv(GL_FRONT, GL_SPECULAR, LightSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, Shine);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	return;
}

//  interaksi dengan keyboard
void myKeyboard(unsigned char key, int x, int y) {
	if (key == 'a') z += 5;
	else if (key == 'd') z -= 5;
	else if (key == 'x') {
		_angle += 5;
	}
	else if (key == 'y') {
		_angle1 += 5;
	}
	else if (key == 'z') {
		_angle2 += 5;
	}
	else if (key == 'X') {
		_angle -= 5;
	}
	else if (key == 'Y') {
		_angle1 -= 5;
	}
	else if (key == 'Z') {
		_angle2 -= 5;
	}
	else if (key == 'o' || key == 'O') {
		x2 = 1;
		y2 = 0;
		z2 = 0;
		if (sudut2 >= 0 && sudut2 < 120) {
			sudut2 += 1;
		}
		if (sudut2 == 100) {
			rpower = 0.4;
			gpower = 0.4;
			bpower = 0.4;
		}
	}
	else if (key == 'p' || key == 'P') {
		x2 = 1;
		y2 = 0;
		z2 = 0;
		if (sudut2 > 0 && sudut2 <= 120) {
			sudut2 -= 1;
		}
	}
	else if (key == '1') {
		if (statuspower == 0 && sudut2 < 100) {
			rpower = 1;
			gpower = 1;
			bpower = 1;
			statuspower = 1;
		}
		else {
			rpower = 0.4;
			gpower = 0.4;
			bpower = 0.4;
			statuspower = 0;
		}
	}
}

//deteksi tombol kiri dan kanan
void mySpecialKeyboard(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		glEnable(GL_LIGHTING);
		GLfloat global_ambient[] = { (_amb += 0.1),(_amb += 0.1),(_amb += 0.1),(_amb += 0.1) };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	}
	else if (key == GLUT_KEY_DOWN) {
		glEnable(GL_LIGHTING);
		GLfloat global_ambient[] = { (_amb -= 0.1),(_amb -= 0.1),(_amb -= 0.1),(_amb -= 0.1) };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	}

}



// ========================= Mulai membuat objek Laptop ====================
void balok(double panjang, double lebar, double tinggi) {
	glEnable(GL_COLOR_MATERIAL);
	glScalef(panjang, tinggi, lebar);
	glutSolidCube(1);
	glDisable(GL_COLOR_MATERIAL);
}

// Bentuk bagian layar
void layar() {
	glEnable(GL_COLOR_MATERIAL);
	glTranslated(0, 5, 0);
	glRotated(-120, 1, 0, 0);
	glTranslated(0, -5, 0);

	// dasar layar
	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	glColor3f(1, 1, 1);
	balok(10, 1, 10);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5, 5, 1.001);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5, -5, 1.001);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5, -5, 1.001);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5, 5, 1.001);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	// layar
	glPushMatrix();
	glTranslatef(0, 0.2, 0);
	glColor3f(rpower, gpower, bpower);
	balok(9, 0.01, 8);
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
}

// Bentuk Bagian Keyboard
void keyboa() {
	// keyboard bawah
	glPushMatrix();
	glTranslatef(0, 0, -0.5);
	glColor3f(0, 0, 0);
	balok(10, 1, 10);
	glPopMatrix();
	// mouse pad
	glPushMatrix();
	glTranslatef(0, -2.8, 0);
	glColor3f(0.8, 0.8, 0.8);
	balok(4, 0.01, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, -4.1, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(2, 0.01, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, -4.1, 0);
	glColor3f(0.32, 0.32, 0.32);
	balok(2, 0.01, 0.6);
	glPopMatrix();

	// alas keyboard
	glPushMatrix();
	glTranslatef(0, 1, 0);
	glColor3f(0.8, 0.8, 0.8);
	balok(9.2, 0.01, 4);
	glPopMatrix();

	// keyboard atas
	glPushMatrix();
	glTranslatef(-4.2, 2.7, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, 2.7, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.8, 2.7, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.1, 2.7, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.4, 2.7, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.4);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-0.7, 2.7, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2.7, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.7, 2.7, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.4, 2.7, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.1, 2.7, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.8, 2.7, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5, 2.7, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.2, 2.7, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.4);
	glPopMatrix();

	// keyboard atas 2
	glPushMatrix();
	glTranslatef(-4.2, 2.0, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, 2.0, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.8, 2.0, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.1, 2.0, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.4, 2.0, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.7, 2.0, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2.0, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.7, 2.0, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.4, 2.0, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.1, 2.0, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.15, 2.0, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(1.3, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.2, 2.0, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	// keyboard atas 3
	glPushMatrix();
	glTranslatef(-4, 1.2, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(1, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.1, 1.2, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.4, 1.2, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.7, 1.2, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1, 1.2, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.3, 1.2, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.4, 1.2, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.1, 1.2, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.8, 1.2, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2.5, 1.2, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3.35, 1.2, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.9, 0.15, 0.6);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(4.2, 1.2, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	// keyboard atas 4
	glPushMatrix();
	glTranslatef(-3.8, 0.4, 0);
	balok(1.4, 0.15, 0.6);
	glColor3f(0.4, 0.4, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.7, 0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.0, 0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.3, 0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.6, 0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, 0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.8, 0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.5, 0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(2.5, 0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(1.2, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5, 0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(4.2, 0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	// keyboard atas 5
	glPushMatrix();
	glTranslatef(-4.2, -0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, -0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.8, -0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.1, -0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-0.15, -0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(3, 0.15, 0.6);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.4, -0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.1, -0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.8, -0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5, -0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.2, -0.4, 0);
	glColor3f(0.4, 0.4, 0.4);
	balok(0.6, 0.15, 0.6);
	glPopMatrix();

	// Tombol power
	glPushMatrix();
	glTranslatef(4, 4, 0);
	glColor3f(rpower, gpower, bpower);
	balok(0.8, 0.15, 0.4);
	glPopMatrix();
}
// =========================End buat objek====================

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 0.5);
	glLoadIdentity();
	glTranslatef(0, -3, z);
	glScalef(0.8, 0.8, 0.8);
	glRotatef(_angle1, 0.0f, 2.0f, 0.0f);
	glRotatef(_angle, 2.0f, 0.0f, 0.0f);
	glRotatef(_angle2, 0.0f, 0.0f, 2.0f);


	glRotatef(-70, 1, 0, 0);

	GLfloat LightPosition[] = { xcahaya,ycahaya,100,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

	keyboa(); //panggil function buat laptop

	glTranslatef(0, 5, 0);
	glRotatef(sudut2, x2, y2, z2);
	glTranslatef(0, -5, 0);
	layar();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderScene(); //panggil function renderscene
	glutSwapBuffers();
}

// waktu animasi
void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(50, timer, 0);
}

//deteksi mouse
void mouse(int button, int state, int xmouse, int ymouse) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		x = xmouse - (w / 2);
		y = (h / 2) - ymouse;
		_angle2 += 5;
		rpower = 1;
		gpower = 0;
		bpower = 0;
	}
		
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		x = xmouse - (w / 2);
		y = (h / 2) - ymouse;
		_angle2 -= 5;
		rpower = 0;
		gpower = 1;
		bpower = 0;
	}

	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		x = xmouse - (w / 2);
		y = (h / 2) - ymouse;
		_angle -= 5;
		rpower = 0;
		gpower = 0;
		bpower = 1;
	}

}


// Fungsi Main
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(w, h);
	glutCreateWindow("3D");

	gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);
	glutMouseFunc(mouse);
	glutTimerFunc(50, timer, 0);
	init();
	initRendering();
	glutMainLoop();
}
