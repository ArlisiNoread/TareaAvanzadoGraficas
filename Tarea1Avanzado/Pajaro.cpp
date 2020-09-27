#include "Header.h"

void dibujarRectangulo(vector3d vertices[], vector3d color);


void Pajaro::dibujar() {
	
	/*Dibujo cuerpo*/
	dibujarRectangulo(
		new vector3d[4]{
			{2,1,-1},
			{2,1,1},
			{-2,1,1},
			{-2,1,-1}
		},
		vector3d(1, 117.0/255.0, 20.0/255.0)
	);
	dibujarRectangulo(
		new vector3d[4]{
			{-2,-1,-1},
			{-2,-1,1},
			{2,-1,1},
			{2,-1,-1}
		},
		vector3d(0.5, 117.0 / 255.0, 20.0 / 255.0)
	);
	dibujarRectangulo(
		new vector3d[4]{
			{-2,1,+1},
			{2,1,1},
			{2,-1,1},
			{-2,-1,1}
		},
		vector3d(1, 117.0 / 255.0, 20.0 / 255.0)
	);
	dibujarRectangulo(
		new vector3d[4]{
			{2,1,-1},
			{-2,1,-1},
			{-2,-1,-1},
			{2,-1,-1}
		},
		vector3d(1, 117.0 / 255.0, 20.0 / 255.0)
	);
	dibujarRectangulo(
		new vector3d[4]{
			{2,1,1},
			{2,1,-1},
			{2,-1,-1},
			{2,-1,1}
		},
		vector3d(0.9, 117.0 / 255.0, 20.0 / 255.0)
	);
	dibujarRectangulo(
		new vector3d[4]{
			{-2,1,-1},
			{-2,1,1},
			{-2,-1,1},
			{-2,-1,-1}
		},
		vector3d(0.9, 117.0 / 255.0, 20.0 / 255.0)
	);



	//Dibujo Cabeza
	glPushMatrix();
	glColor3f(0.3, 0.3, 1);
	glTranslated(3, 0, 0);
	glutSolidSphere(1, 10000, 10000);
	glPopMatrix();

	//Dibujo Ojos
	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslated(3.8, 0.5, 0.6);
	glutSolidSphere(0.18, 10000, 10000);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslated(3.8, 0.5, -0.6);
	glutSolidSphere(0.18, 10000, 10000);
	glPopMatrix();

	//Dibujo Pico
	glPushMatrix();
	glRotatef(90, 0.0, 1.0, 0.0);
	glTranslatef(0.0,0.0,3.9);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidCone(0.4,0.7, 500, 500);
	glPopMatrix();


	//Dibujo Alas
	glPolygonMode(GL_BACK, GL_FILL);
	glPushMatrix();
	glColor3f(161.0/255.0, 130.0/255.0, 98.0/255.0);
	glRotatef(-anguloAlas,1.0,0.0,0.0);
	glTranslatef(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-1.0,0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(-0.3, 0.0, 3.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(161.0 / 255.0, 130.0 / 255.0, 98.0 / 255.0);
	glRotatef(anguloAlas, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, -1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.3, 0.0, -3.5);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);

	glEnd();
	glPopMatrix();
	glPolygonMode(GL_BACK, GL_LINE);

}	

void dibujarRectangulo(vector3d vertices[], vector3d color) {
	glPushMatrix();
	glColor3f(color.x, color.y, color.z);
	glBegin(GL_POLYGON);
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glEnd();
	glPopMatrix();
}

void MotorPajaro::moverEnTiempo() {
	float deltaAlas = 1.5;
	float deltaAnguloRotacion = 1.5;

	//Actualizo ángulo de alas
	pajaro.anguloAlas += (direccionAlas) * deltaAlas;

	if (pajaro.anguloAlas >= 40.0 && direccionAlas == 1) {
		direccionAlas *= -1;
	}
	else if (pajaro.anguloAlas <= -40.0 && direccionAlas == -1) {
		direccionAlas *= -1;
	}

	anguloCircunferencia += deltaAnguloRotacion;
}

void MotorPajaro::dibujar() {
	glPushMatrix();
	glRotatef(-anguloCircunferencia, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, -radioCircunferencia);
	pajaro.dibujar();
	glPopMatrix();
}