#include "Header.h"


Camara camara(
    vector3d(5.0f, 2.0f, 5.0f), //vector3d(15.0f, 5.0f, 15.0f),
    vector3d(2.0f, 2.0f, 2.0f), //vector3d(14.0f, 5.0f, 14.0f),
    vector3d(0.0f, 1.0f, 0.0f)
);

//Pajaro pajaro;
MotorPajaro motorPajaro;


int liberarCamara = 1;
int dimensionesVentana[] = { 800, 600 };

int main(int argc, char** argv) {


	iniciarProcesoGlut(argc, argv);
    return 0;
}

void iniciarProcesoGlut(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(dimensionesVentana[0], dimensionesVentana[1]);
	glutInitWindowPosition(200, 200);
	glutCreateWindow(argv[0]);
	glutDisplayFunc( RenderScene );
    glutReshapeFunc( ChangeSize );
    glutSpecialFunc( SpecialKeys );
    glutKeyboardFunc( NormalKeys );
    //glutMotionFunc(Motion);
   // glutPassiveMotionFunc( Motion );
    SetupRC();
    glutMainLoop();

}

void SetupRC()
{
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Set drawing color to green
    //glColor3f(0.0f, 1.0f, 0.0f);

    // Set color shading model to flat
    //glShadeModel(shademode);

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);


    glPolygonMode(GL_BACK, GL_LINE);
    //glPolygonMode(GL_BACK, GL_FILL);

    // Clockwise-wound polygons are front facing; this is reversed
    // because we are using triangle fans
    glFrontFace(GL_CW);

    glShadeModel(GL_FLAT);


  


    
}

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camara.ActualizaCamaraConGlut();
    dibujaLampara();
    dibujaGrid();
    //pajaro.dibujar();
    motorPajaro.dibujar();
    //creaParedesTechoPiso();
    SombraDeMiMundo();
    dibujarCubo();


    glutSwapBuffers();
    glFlush();
}

void ChangeSize(GLsizei w, GLsizei h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glOrtho (-100.0, 100.0, -100, 100, -270.0, 270.0);
    //glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    gluPerspective(45.0, (float)w/(float)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void SpecialKeys(int key, int x, int y) {
    GLfloat dx, dy,dz;
    float delta = 0.05;

    if (key == GLUT_KEY_LEFT){
        dx = -camara.posicion.z;
        dz = camara.posicion.x;

        GLfloat s = sqrtf(pow(camara.posicion.x,2) + pow(camara.posicion.y, 2) + pow(camara.posicion.z, 2));
        camara.posicion.x += camara.posicion.x + delta * dx;
        camara.posicion.z += camara.posicion.z + delta * dz;
        GLfloat s1 = sqrtf(pow(camara.posicion.x, 2) + pow(camara.posicion.y, 2) + pow(camara.posicion.z, 2))/ s;
        camara.posicion = camara.posicion / s1;
    }
    else if(key == GLUT_KEY_RIGHT) {
        dx = -camara.posicion.z;
        dz = camara.posicion.x;

        GLfloat s = sqrtf(pow(camara.posicion.x, 2) + pow(camara.posicion.y, 2) + pow(camara.posicion.z, 2));
        camara.posicion.x = camara.posicion.x - delta * dx;
        camara.posicion.z = camara.posicion.z - delta * dz;
        GLfloat s1 = sqrtf(pow(camara.posicion.x, 2) + pow(camara.posicion.y, 2) + pow(camara.posicion.z, 2)) / s;
        camara.posicion = camara.posicion / s1;
    }
    else if (key == GLUT_KEY_UP) {

        camara.SubirBajarCircularmente_Camara(VEL_CAMARA / 10);
     
        
    }
    else if (key == GLUT_KEY_DOWN) {

        camara.SubirBajarCircularmente_Camara(-VEL_CAMARA / 10);

    }

    glutPostRedisplay();

}

void NormalKeys(unsigned char key, int xmouse, int ymouse) {
    if(key == 'y') {
        if (liberarCamara) {
            liberarCamara = 0;
            printf("Camara Fija\n");
        }
        else {
            liberarCamara = 1;
            printf("Camara Liberada\n");
        }
    }
    else if (liberarCamara){
        if (key == 'w') {
            camara.Mover_Camara(VEL_CAMARA);
        }
        else if (key == 's') {
            camara.Mover_Camara(-VEL_CAMARA);
        }
        else if (key == 'a') {
            camara.MoverLateralmente_Camara(VEL_CAMARA);
        }
        else if (key == 'd') {
            camara.MoverLateralmente_Camara(-VEL_CAMARA);
        }
        else if (key == 'q') {
            camara.Rotar_Camara(-VEL_CAMARA);
        }
        else if (key == 'e') {
            camara.Rotar_Camara(VEL_CAMARA);
        }
        else if (key == 'r') {
            camara.SubirBajar_Camara(VEL_CAMARA);
        }
        else if (key == 'f') {
            camara.SubirBajar_Camara(-VEL_CAMARA);
        }
        else if (key ==  ' ') {
            //Reseteamos Posicion
            camara.Posicionar_Camara(
                vector3d(15.0f, 5.0f, 15.0f),
                vector3d(14.0f, 5.0f, 14.0f)
            );
        }
        else if (key == 'z') {
            motorPajaro.moverEnTiempo();
        }
    }

    glutPostRedisplay();
}


void dibujaLampara() {
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(15, 13, 15);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();

}

void creaParedesTechoPiso() {

    /*Crea Pared sobre Plano KY*/
    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_POLYGON);
    glVertex3f(0,0,0);
    glVertex3f(0, 0, 30);
    glVertex3f(0, 15, 30);
    glVertex3f(0, 15, 0);
    glEnd();
    glPopMatrix();


    /*Crea Pared sobre Plano XY*/
    glPushMatrix();
    glColor3f(0, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 15, 0);
    glVertex3f(30, 15, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    /*Crea Piso sobre Plano XK*/
    glPushMatrix();
    glColor3f(1, 0, 0.5);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(30, 0, 0);
    glVertex3f(30, 0, 30);
    glVertex3f(0, 0, 30);
    glEnd();
    glPopMatrix();

    /*Crea Techo sobre Plano XK en Y = 15*/
    glPushMatrix();
    glColor3f(1, 1, 0.5);
    glBegin(GL_POLYGON);
    glVertex3f(0, 15, 0);
    glVertex3f(0, 15, 30);
    glVertex3f(30, 15, 30);
    glVertex3f(30, 15, 0);
    glEnd();
    glPopMatrix();
}

void dibujaGrid() {
    for (float i = -500; i <= 500; i += 5)
    {
        glBegin(GL_LINES);
        glColor3ub(150, 190, 150);
        glVertex3f(-500, 0, i);
        glVertex3f(500, 0, i);
        glVertex3f(i, 0, -500);
        glVertex3f(i, 0, 500);
        glEnd();
    }
}

void dibujarCubo() {
    glPushMatrix();

    glTranslatef(5.0,5.0,5.0);

    dibujarCuadrado(
        0, 0, 0.5,
        0, 0, 0, 0,
        1, 0, 0
    );
    
    dibujarCuadrado(
        0, 0, -0.5,
        180, 0, 1, 0,
        0, 1, 0
    );

    dibujarCuadrado(
        0.5, 0, 0,
        90, 0, 1, 0,
        0, 0, 1
    );

    dibujarCuadrado(
        -0.5, 0, 0,
        -90, 0, 1, 0,
        0, 1, 1
    );

    dibujarCuadrado(
        0, 0.5, 0,
        -90, 1, 0, 0,
        1, 0, 1
    );
    
    dibujarCuadrado(
        0, -0.5, 0,
        90, 1, 0, 0,
        1, 1, 0
    );

    glPopMatrix();
}

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
) {
    glPushMatrix();
    glColor3f(colR, colG, colB);
    glTranslatef(transX, transY, transZ);
    glRotatef(rotAngle, rotX, rotY, rotZ);
    glBegin(GL_POLYGON);
    
    GLfloat vertices[][3] = {
        { -0.5, 0.5, 0},
        { 0.5, 0.5, 0 },
        { 0.5, -0.5, 0 },
        { -0.5, -0.5, 0 } 
    };

    for (int i = 0; i < 4; i++) {
        glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
    }
    glEnd();
    glPopMatrix();
}

void gltMakeShadowMatrix(GLfloat vPlaneEquation[], GLfloat vLightPos[], GLfloat destMat[]) {
    GLfloat dot;
    dot = vPlaneEquation[0] * vLightPos[0] + vPlaneEquation[1] * vLightPos[1] + vPlaneEquation[2] * vLightPos[2] + vPlaneEquation[3] * vLightPos[3];
    // Now do the projection
    // First column
    destMat[0] = dot - vLightPos[0] * vPlaneEquation[0];
    destMat[4] = 0.0f - vLightPos[0] * vPlaneEquation[1];
    destMat[8] = 0.0f - vLightPos[0] * vPlaneEquation[2];
    destMat[12] = 0.0f - vLightPos[0] * vPlaneEquation[3];
    // Second column
    destMat[1] = 0.0f - vLightPos[1] * vPlaneEquation[0];
    destMat[5] = dot - vLightPos[1] * vPlaneEquation[1];
    destMat[9] = 0.0f - vLightPos[1] * vPlaneEquation[2];
    destMat[13] = 0.0f - vLightPos[1] * vPlaneEquation[3];
    // Third Column
    destMat[2] = 0.0f - vLightPos[2] * vPlaneEquation[0];
    destMat[6] = 0.0f - vLightPos[2] * vPlaneEquation[1];
    destMat[10] = dot - vLightPos[2] * vPlaneEquation[2];
    destMat[14] = 0.0f - vLightPos[2] * vPlaneEquation[3];

    // Fourth Column
    destMat[3] = 0.0f - vLightPos[3] * vPlaneEquation[0];
    destMat[7] = 0.0f - vLightPos[3] * vPlaneEquation[1];
    destMat[11] = 0.0f - vLightPos[3] * vPlaneEquation[2];
    destMat[15] = dot - vLightPos[3] * vPlaneEquation[3];
}




void SombraDeMiMundo() {
    glPushMatrix();

    GLfloat coordPlano[4] = {0.0, 0.0, 1.0, 1};
    GLfloat coordLuz[] = {15.0, 13 ,15.0, -10};
    GLfloat matrizSombra[16];

    gltMakeShadowMatrix(coordPlano, coordLuz, matrizSombra);
    glMultMatrixf(matrizSombra);
    dibujarCuadrado(
        0, -0.5, 0,
        90, 1, 0, 0,
        0, 0, 0
    );
    
    glPopMatrix();
}