#include "Header.h"


void Camara::Posicionar_Camara(vector3d new_Posicion, vector3d new_Vista) {
	posicion = new_Posicion;
	vista = new_Vista;
}


void Camara::Mover_Camara(float velocidad) {

	//Obtengo vector de vista
	vector3d tempVector = vista - posicion;

	//Aumentamos un delta pequeño
	posicion.x = posicion.x + tempVector.x * velocidad;
	posicion.z = posicion.z + tempVector.z * velocidad;
	vista.x = vista.x + tempVector.x * velocidad;
	vista.z = vista.z + tempVector.z * velocidad;

	printf("Camara Movida A: %f, %f, %f\n", posicion.x, posicion.y, posicion.z);

}

void Camara::MoverLateralmente_Camara(float velocidad) {
	
	vector3d tempVector = vista - posicion;

	//Producto Cruz
	float strafex = arriba.y * tempVector.z - arriba.z * tempVector.y;
	float strafey = arriba.z * tempVector.x - arriba.x * tempVector.z;
	float strafez = arriba.x * tempVector.y - arriba.y * tempVector.x;

	printf("Strafe: %f, %f, %f\n", strafex, strafey, strafez);

	posicion.x = posicion.x + strafex * velocidad;
	posicion.z = posicion.z + strafez * velocidad;
	vista.x = vista.x + strafex * velocidad;
	vista.z = vista.z + strafez * velocidad;

	printf("Camara Movida Lateralmente A: %f, %f, %f\n", posicion.x, posicion.y, posicion.z);

}

void Camara::SubirBajar_Camara(float velocidad) {
	posicion.y = posicion.y + 1 * velocidad;
	vista.y = vista.y + 1 * velocidad;
}

void Camara::SubirBajarCircularmente_Camara(float velocidad) {
	//Obtengo vector de vista
	vector3d tempVector = vista - posicion;

	GLfloat r = sqrtf(pow(posicion.x, 2) + pow(posicion.y,2) + pow(posicion.z, 2));


	
	if (velocidad > 0) {
		if (posicion.y >= 0) {
			posicion.x = posicion.x + tempVector.x * velocidad;
			posicion.z = posicion.z + tempVector.z * velocidad;
			if (pow(r, 2) - pow(posicion.x, 2) - pow(posicion.z, 2) < 0) {
				posicion.y = 0;
			}
			else {
				posicion.y = sqrtf(pow(r, 2) - pow(posicion.x, 2) - pow(posicion.z, 2));
			}
		}
		else {
			posicion.x = posicion.x + tempVector.x * (-1)*velocidad;
			posicion.z = posicion.z + tempVector.z * (-1)*velocidad;

			if (pow(r, 2) - pow(posicion.x, 2) - pow(posicion.z, 2) < 0) {
				posicion.y = 0;
			}
			else {
				posicion.y = -sqrtf(pow(r, 2) - pow(posicion.x, 2) - pow(posicion.z, 2));
			}
		}
	}
	else {
		if (posicion.y <= 0) {
			posicion.x = posicion.x + tempVector.x * (-1)*velocidad;
			posicion.z = posicion.z + tempVector.z * (-1)*velocidad;

			if (pow(r, 2) - pow(posicion.x, 2) - pow(posicion.z, 2) < 0) {
				posicion.y = 0;
			}
			else {
				posicion.y = -sqrtf(pow(r, 2) - pow(posicion.x, 2) - pow(posicion.z, 2));
			}

			
		}
		else {
			posicion.x = posicion.x + tempVector.x * velocidad;
			posicion.z = posicion.z + tempVector.z * velocidad;

			if (pow(r, 2) - pow(posicion.x, 2) - pow(posicion.z, 2) < 0) {
				posicion.y = 0;
			}
			else {
				posicion.y = sqrtf(pow(r, 2) - pow(posicion.x, 2) - pow(posicion.z, 2));
			}
			
		}
	}

	printf("Camara Movida A: %f, %f, %f\n", posicion.x, posicion.y, posicion.z);
}

void Camara::Rotar_Camara(float velocidad) {

	//Obtengo vector de vista
	vector3d tempVector = vista - posicion;

	vista.z = posicion.z + sin(velocidad) * tempVector.x + cos(velocidad) * tempVector.z;
	vista.x = posicion.x + cos(velocidad) * tempVector.x - sin(velocidad) * tempVector.z;
	printf("Camara Rotada A: %f, %f, %f\n", vista.x, vista.y, vista.z);

}

void Camara::Mover_Raton(int ventanaAncho, int ventanaAlto) {

	//NO FUNCIONA BIEN!
	//REPARANDO FUNCIÓN LUEGO

	POINT posicionRaton;

	int mitad_x = ventanaAncho >> 1;
	int mitad_y = ventanaAncho >> 1;

	float angulo_y = 0.0f;
	float angulo_z = 0.0f;

	GetCursorPos(&posicionRaton);

	if (posicionRaton.x == mitad_x && posicionRaton.y == mitad_y) {
		//Si esto se cumple no hay movimiento
		return;
	}

	//Fijamos mouse en el centro de la pantalla
	SetCursorPos(mitad_x, mitad_y);

	angulo_y = (mitad_x - posicionRaton.x) / 1000;
	angulo_z = (mitad_x - posicionRaton.y) / 1000;

	vista.y += angulo_z * 2;

	if (vista.y - posicion.y > 8) {
		vista.y = posicion.y + 8;
	}

	if (vista.y - posicion.y < -8) {
		vista.y = posicion.y - 8;
	}

	Rotar_Camara(-angulo_y);
}

void Camara::ActualizaCamaraConGlut() {

	printf("Posicion Actualizada\n");
	gluLookAt(posicion.x, posicion.y, posicion.z, vista.x, vista.y, vista.z, arriba.x, arriba.y, arriba.z);
}
