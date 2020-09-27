#pragma once

#include "glut.h"
#include <math.h>
#include <stdio.h>
#include <windows.h>					// Header File For Windows


#define VEL_CAMARA 0.05f

//Vector que me va a ser de utilidad para manejar datos
typedef struct vector3d
{

	float x, y, z;
	vector3d() {
		x = 0;
		y = 0;
		z = 0;
	}
	vector3d(float x_var, float y_var, float z_var) {
		x = x_var;
		y = y_var;
		z = z_var;
	}

	vector3d operator+(vector3d vector) {
		return vector3d(vector.x + x, vector.y + y, vector.z + z);
	}

	vector3d operator-(vector3d vector) {
		return vector3d(x - vector.x, y - vector.y, z - vector.z);
	}

	vector3d operator*(float escalar) {
		return vector3d(x * escalar, y * escalar, z * escalar);
	}

	vector3d operator/(float escalar) {
		return vector3d(x / escalar, y / escalar, z / escalar);
	}
} vector3d;


class Camara
{
	public:
		vector3d posicion;
		vector3d vista;
		vector3d arriba;
		Camara(vector3d pos, vector3d vis, vector3d arr) {
			posicion = pos;
			vista = vis;
			arriba = arr;

		}
		void Mover_Camara(float velocidad);
		void MoverLateralmente_Camara(float velocidad);
		void SubirBajar_Camara(float velocidad);
		void SubirBajarCircularmente_Camara(float velocidad);
		void Rotar_Camara(float velocidad);
		void Mover_Raton(int ventanaAncho, int ventanaAlto);
		void Posicionar_Camara(vector3d new_Posicion, vector3d new_Vista);
		void ActualizaCamaraConGlut();

};

class Pajaro
{
public:
	vector3d posicion;
	float anguloAlas = 0.0;
	Pajaro() {};
	Pajaro(vector3d pos) {
		posicion = pos;
	};
	void dibujar();
};

class MotorPajaro
{
public:
	int direccionAlas = 1;
	float radioCircunferencia = 10.0;
	float anguloCircunferencia = 0.0;
	Pajaro pajaro;
	MotorPajaro() {
		pajaro = Pajaro();
	};
	void moverEnTiempo();
	void dibujar();
};

void iniciarProcesoGlut(int, char**);
void SetupRC();
void RenderScene(void);
void creaParedesTechoPiso();
void SpecialKeys(int key, int x, int y);
void NormalKeys(unsigned char key, int xmouse, int ymouse);
void ChangeSize(GLsizei w, GLsizei h);
void dibujaGrid();
void dibujarCubo();
void dibujarCuadrado(
	GLfloat transX,
	GLfloat transY,
	GLfloat transZ,
	GLfloat rotAngle,
	GLfloat rotX,
	GLfloat rotY,
	GLfloat rotZ,
	GLfloat colR,
	GLfloat colG,
	GLfloat colB
);
void dibujaLampara();
void gltMakeShadowMatrix(GLfloat vPlaneEquation[], GLfloat vLightPos[], GLfloat destMat[]);
void SombraDeMiMundo();
