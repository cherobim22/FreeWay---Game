
#include <stdio.h>
#include <stdlib.h> 
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include<math.h>

#define janela_altura 700 
#define janela_largura 1000 
#define PI 3.1416


//Functions
void rodovia();
void faixas();
int linhas(int x);
int conjuntoLinhas(int y);
float roda(float tx, float ty);
float roda1(float tx, float ty);
void carroRight(float tx, float ty);
void carroLeft(float tx, float ty);
void keyboard();
void jogador();
void anima(int valor);
void update(int valor);
void display(void);
void tela(GLsizei W, GLsizei h);
GLuint LoadTexture(const char * filename);

//Movimentos da bola
float tx0 = 500, tx1 = -500, tx2 = 500, tx3 = -500, tx4 = 500, tx5 = -500, tx6 = 500, tx7 = -500, tx8 = 500, tx9 = -500;//pos X
float ty0 = -225, ty1 = -175, ty2 = -125, ty3 = -75, ty4 = -25, ty5 = 25, ty6 = 75, ty7 = 125, ty8 = 175, ty9 = 225;//pos Y
float xTep0 = -4, xTep1 = 4, xTep2 = -6, xTep3 = 7, xTep4 = -4, xTep5 = 6, xTep6 = -7, xTep7 = 5, xTep8 = -4, xTep9 = 6;//vel
int interval = 200;
//jogador
float jx = -10, jy = -285, jcomp = 20, jalt = 20;
float T1x = 0, T1y = 0, Tcomp = 0, Talt = 0;

//Colisões
bool Colision(float Ax, float Ay, float Bx, float By, float Bcompr, float Baltu) {

	if (Ay < By) return false;
	else if (Ay > By + Baltu) return false;
	else if (Ax > Bx + Bcompr) return false;
	else if (Ax < Bx) return false;

	return true;
}
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	// suporte a janelas 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // PADRAO DE CORES 
	glutInitWindowSize(janela_largura, janela_altura); // tamanho da janela 
	glutInitWindowPosition(0, 0); // posicao que surge a janela 
	glutCreateWindow("CROSSY ROAD"); // cria janela 

	//glutFullScreen();
	//glutKeyboardFunc(&keyboard); // chama teclado 
	glutTimerFunc(250, update, 1);
	glutTimerFunc(150, anima, 1);
	glutReshapeFunc(tela); // configura a tela 
	glutDisplayFunc(display);
	glutMainLoop(); // redesenhar 	

	return(0);
}
void update(int value) {

	keyboard();
	glutTimerFunc(interval, update, 0);
	glutPostRedisplay();
}
void anima(int valor) {

	if (Colision(tx0, ty0, jx, jy, jcomp, jalt) == true) jy = -285;
	if (Colision(tx1, ty1, jx, jy, jcomp, jalt) == true) jy = -285;
	if (Colision(tx2, ty2, jx, jy, jcomp, jalt) == true) jy = -285;
	if (Colision(tx3, ty3, jx, jy, jcomp, jalt) == true) jy = -285;
	if (Colision(tx4, ty4, jx, jy, jcomp, jalt) == true) jy = -285;
	if (Colision(tx5, ty5, jx, jy, jcomp, jalt) == true) jy = -285;
	if (Colision(tx6, ty6, jx, jy, jcomp, jalt) == true) jy = -285;
	if (Colision(tx7, ty7, jx, jy, jcomp, jalt) == true) jy = -285;
	if (Colision(tx8, ty8, jx, jy, jcomp, jalt) == true) jy = -285;
	if (Colision(tx9, ty9, jx, jy, jcomp, jalt) == true) jy = -285;

	if (tx0 < -490)	tx0 = 500.0f;
	if (tx1 > 490) tx1 = -500.0f;
	if (tx2 < -490)	tx2 = 500.0f;
	if (tx3 > 490) tx3 = -500.0f;
	if (tx4 < -490)	tx4 = 500.0f;
	if (tx5 > 490) tx5 = -500.0f;
	if (tx6 < -490)	tx6 = 500.0f;
	if (tx7 > 490) tx7 = -500.0f;
	if (tx8 < -490)	tx8 = 500.0f;
	if (tx9 > 490) tx9 = -500.0f;

	tx0 += xTep0;
	tx1 += xTep1;
	tx2 += xTep2;
	tx3 += xTep3;
	tx4 += xTep4;
	tx5 += xTep5;
	tx6 += xTep6;
	tx7 += xTep7;
	tx8 += xTep8;
	tx9 += xTep9;

	glutPostRedisplay();
	glutTimerFunc(15, anima, 2);

}
void keyboard() {

	if (GetAsyncKeyState(VK_UP)) if (jy < 250) jy += 50;
	if (GetAsyncKeyState(VK_DOWN)) if (jy > -250) jy -= 50;
	if (GetAsyncKeyState(VK_RIGHT)) if (jx < 450) jx += 50;
	if (GetAsyncKeyState(VK_LEFT)) if (jx > -500) jx -= 50;

}

GLuint LoadTexture(const char * filename) {

	GLuint texture;

	int width, height;

	unsigned char * data;

	FILE * file;

#pragma warning(disable:4996)
	file = fopen(filename, "rb");
	if (file == NULL) return 0;
	width = 1024;
	height = 512;
	data = (unsigned char *)malloc(width * height * 3);
	//int size = fseek(file,);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;

	}


	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}

//LINHAS
int linhas(int x) {

	glPushMatrix();
	glTranslated(x, 0, 0);

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex2f(-470, 200);
	glVertex2f(-470, 205);
	glVertex2f(-440, 205);
	glVertex2f(-440, 200);
	glEnd();

	glPopMatrix();
	return true;
}
//CRIA LINHAS
int conjuntoLinhas(int y) {
	glPushMatrix();
	glTranslated(0, y, 0);

	linhas(0);
	linhas(60);
	linhas(120);
	linhas(180);
	linhas(240);
	linhas(300);
	linhas(360);
	linhas(420);
	linhas(480);
	linhas(540);
	linhas(600);
	linhas(660);
	linhas(720);
	linhas(780);
	linhas(840);
	linhas(900);
	linhas(960);

	glPopMatrix();
	return true;
}

//DEFINE POSIÇÃO DAS LINHAS
void faixas() {

	conjuntoLinhas(0);
	conjuntoLinhas(-50);
	conjuntoLinhas(-100);
	conjuntoLinhas(-150);
	conjuntoLinhas(-300);
	conjuntoLinhas(-350);
	conjuntoLinhas(-400);

}


//CENARIO
void rodovia() {

	//RUA
	glBegin(GL_QUADS);
	glColor3f(1, 0.86, 0.35);
	glVertex2f(-500, -250);
	glVertex2f(-500, 250);
	glVertex2f(500, 250);
	glVertex2f(500, -250);
	glEnd();

	//SAIDA
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.8, 0.2);
	glVertex2f(-500, 253);
	glVertex2f(-500, 350);
	glVertex2f(500, 350);
	glVertex2f(500, 253);
	glEnd();
	//ESCAPE
	glBegin(GL_QUADS);
	glColor3f(0.59, 0.29, 0);
	glVertex2f(-500, 10);
	glVertex2f(-500, -50);
	glVertex2f(500, -50);
	glVertex2f(500, 10);
	glEnd();

	//INICIO
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.8, 0.2);
	glVertex2f(-500, -253);
	glVertex2f(-500, -350);
	glVertex2f(500, -350);
	glVertex2f(500, -253);
	glEnd();



	faixas();

}


//JOGADOR
void jogador() {

	glPushMatrix();

	glBegin(GL_QUADS);
	glColor3f(0.96, 0.96, 0.96);
	glVertex2f(jx, jy + jalt);
	glVertex2f(jx + jcomp, jy + jalt);
	glVertex2f(jx + jcomp, jy);
	glVertex2f(jx, jy);
	glEnd();

	glTranslatef(jx, jy, 0);
	glTranslatef(-20, -25, 0);
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(0, 15);//leftBotton
	glColor3f(1, 1, 0);
	glVertex2f(20, 45);//leftTop
	glColor3f(1, 0, 1);
	glVertex2f(20, 25);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(40, 25);//leftBotton
	glColor3f(1, 1, 0);
	glVertex2f(40, 45);//leftTop
	glColor3f(1, 0, 1);
	glVertex2f(60, 15);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(25, 45);//leftBotton
	glVertex2f(30, 50);//leftTop
	glVertex2f(35, 45);
	glEnd();


	glPopMatrix();

}

//FUNÇÂO CARRO 
float roda(float tx, float ty) {

	glPushMatrix();

	GLfloat circ_pnt = 500;
	GLfloat ang, raioX = 4.0f, raioY = 4.0f;

	glTranslatef(tx, ty, 0);
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2f(cos(ang)*raioX, sin(ang)*raioY);
	}
	glEnd();

	glPopMatrix();
	return true;

}
float roda1(float tx, float ty) {

	glPushMatrix();

	GLfloat circ_pnt = 500;
	GLfloat ang, raioX = 4.0f, raioY = 4.0f;

	glTranslatef(tx, ty, 0);
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2f(cos(ang)*raioX, sin(ang)*raioY);
	}
	glEnd();

	glPopMatrix();
	return true;

}
void carroRight(float tx, float ty) {


	roda1(tx, ty);
	roda(tx + 20, ty);
	glPushMatrix();
	glTranslatef(tx - 15, ty - 10, 0);
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glVertex2f(10, 10);
	glVertex2f(10, 16);
	glVertex2f(45, 16);
	glVertex2f(45, 10);
	//Top Part
	glVertex2f(15, 16);
	glVertex2f(20, 20);
	glVertex2f(40, 20);
	glVertex2f(45, 16);
	glEnd();

	glPopMatrix();
}
void carroLeft(float tx, float ty) {


	roda1(tx, ty);
	roda(tx + 20, ty);
	glPushMatrix();
	glTranslatef(tx - 35, ty - 25, 0);
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glVertex2f(30, 25);
	glVertex2f(30, 31);
	glVertex2f(65, 31);
	glVertex2f(65, 25);
	//Top Part
	glBegin(GL_POLYGON);
	glVertex2f(30, 31);
	glVertex2f(35, 35);
	glVertex2f(60, 35);
	glVertex2f(60, 31);

	glEnd();





	glPopMatrix();
}

//TELA
void display() {

	glMatrixMode(GL_MODELVIEW); //coordenadas de desenho 
	glLoadIdentity();
	glClearColor(0, 0, 0, 1);

	glClear(GL_COLOR_BUFFER_BIT); // EXECUTA LIMPESA 
								  // Especificar o local aonde o desenho acontece: bem no centro da janela 
	glTranslatef(janela_largura / 2, janela_altura / 2, 0.0f);
	glViewport(0, 0, janela_largura, janela_altura);

	// execute o desenho 
	rodovia();
	jogador();

	carroRight(tx0, ty0);
	carroLeft(tx1, ty1);
	carroRight(tx2, ty2);
	carroLeft(tx3, ty3);
	carroLeft(tx5, ty5);
	carroRight(tx6, ty6);
	carroLeft(tx7, ty7);
	carroRight(tx8, ty8);
	carroLeft(tx9, ty9);
	glFlush();

}
void tela(GLsizei W, GLsizei h) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// cria a janela (esq, direita, embaixo, em cima) 
	gluOrtho2D(0, janela_largura, 0, janela_altura);
	glMatrixMode(GL_MODELVIEW);
}