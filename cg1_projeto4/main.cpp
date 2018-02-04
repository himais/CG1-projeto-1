#include <windows.h>
#include <stdio.h>
#include <GL\glut.h>

//Constantes
#define CUBO 1
#define ESFERA 2
#define CONE 3
#define TORUS 4

//Variáveis
float angulo = 0.0, rot_b = 40.0;
float x, y, z;
GLfloat win, r, g, b;
GLint primitiva;

//Inicializa
void init(void){
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glLoadIdentity (); 		// carrega a matriz de identidade
   gluPerspective(1.0, 1.0, 1.0, 1.0);
   glMatrixMode (GL_MODELVIEW);

   primitiva = CUBO;

   r = 1.0f;
   g = 1.0f;
   b = 1.0f;

    x = 0.0f;
    y = 1.0f;
    z = 0.0f;
}

//Função para desenhar cubo
void desenhaCubo(void){
   glClear(GL_COLOR_BUFFER_BIT);

   glPushMatrix();
   glTranslatef (0.0, 0.0, -10.0);
   glRotatef (angulo, x, y, z);
   glutWireCube(3.0); //tamanho
   glPopMatrix();

   glFlush ();
}

//Função para desenhar esfera
void desenhaEsfera(void){
   glClear(GL_COLOR_BUFFER_BIT);

   glPushMatrix();
   glTranslatef (0.0, 0.0, -10.0);
   glRotatef (angulo, x, y, z);
   glutWireSphere(2.0, 20, 16); //raio, divisoes em torno e ao longo de z
   glPopMatrix();

   glFlush ();
}

//Função para desenhar cone
void desenhaCone(void){
   glClear(GL_COLOR_BUFFER_BIT);

   glPushMatrix();
   glTranslatef (0.0, 0.0, -10.0);
   //glRotatef (rot_b, 1.0, 1.0, 0.0);
   glRotatef (angulo, x, y, z);
   glutWireCone(2, 5, 30, 16); //raio, altura, divisoes
   glPopMatrix();

   glFlush ();
}


//Função para desenhar rosquinha
void desenhaTorus(void){
   glClear(GL_COLOR_BUFFER_BIT);
   y = 1.0;
   glPushMatrix();
   glTranslatef (0.0, 0.0, -10.0);
   glRotatef (angulo, x, y, z);
   glutWireTorus(1, 2, 20, 20); //raio, altura, divisoes
   glPopMatrix();

   glFlush ();
}

//Função callback chamada para fazer o desenho
void Desenha(void){
     //Define a cor corrente
     glColor3f(r,g,b);

     //Desenha uma forma
     switch (primitiva) {
            case CUBO:  desenhaCubo();
                            break;
            case ESFERA: desenhaEsfera();
                            break;
            case CONE:   desenhaCone();
                            break;
            case TORUS:  desenhaTorus();
                            break;
     }

     // Exibe a posição do mouse na janela
     //glColor3f(1.0f,1.0f,1.0f);
     //DesenhaTexto(texto);

     glutSwapBuffers();
}

// Gerenciamento do menu com as opções de cores
void MenuCor(int op){
   switch(op) {
            case 0:
                     r = 0.0f;
                     g = 0.0f;
                     b = 1.0f;
                     break;
            case 1:
                     r = 1.0f;
                     g = 0.0f;
                     b = 0.0f;
                     break;
            case 2:
                     r = 0.0f;
                     g = 1.0f;
                     b = 0.0f;
                     break;
    }
    glutPostRedisplay();
}

// Gerenciamento do menu com as opções de cores
void MenuPrimitiva(int op){
   switch(op) {
            case 0:
                     primitiva = CUBO;
                     break;
            case 1:
                     primitiva = ESFERA;
                     break;
            case 2:
                     primitiva = CONE;
                     break;
            case 3:
                     primitiva = TORUS;
                     break;
    }
    glutPostRedisplay();
}

//Gerenciamento do menu principal
void MenuPrincipal(int op){
}

//Criacao do Menu
void CriaMenu(){
    int menu,submenu1,submenu2;

    submenu1 = glutCreateMenu(MenuCor);
    glutAddMenuEntry("Azul",0);
    glutAddMenuEntry("Vermelho",1);
    glutAddMenuEntry("Verde",2);

    submenu2 = glutCreateMenu(MenuPrimitiva);
    glutAddMenuEntry("Cubo",0);
    glutAddMenuEntry("Esfera",1);
    glutAddMenuEntry("Cone",2);
    glutAddMenuEntry("Torus",3);

    menu = glutCreateMenu(MenuPrincipal);
    glutAddSubMenu("Cor",submenu1);
    glutAddSubMenu("Formas",submenu2);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y){
    if (button == GLUT_RIGHT_BUTTON)
         if (state == GLUT_DOWN)
            CriaMenu();

    glutPostRedisplay();
}

void TeclasEspeciais(int key, int x, int y){
	if(key == GLUT_KEY_UP){
		angulo += 5;
		x = 0.0f;
		y = 0.0f;
		z = 1.0f;
	}

	if(key == GLUT_KEY_DOWN){
        angulo -= 5;
		x = 0.0f;
		y = 0.0f;
		z = 1.0f;
	}

	if(key == GLUT_KEY_RIGHT){
		angulo += 5;
		x = 1.0f;
		y = 1.0f;
		z = 0.0f;
	}

	if(key == GLUT_KEY_LEFT){
        angulo -= 5;
		x = 1.0f;
		y = 1.0f;
		z = 0.0f;
	}

	glutPostRedisplay();
}

void GerenciaTeclado(unsigned char key, int x, int y){
	switch (key) {
	case 27:
		exit(1);

	}
	glutPostRedisplay();
}

void reshape (int w, int h){
   glLoadIdentity (); 		// carrega a matriz de identidade
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode (GL_MODELVIEW);
}



int main(){
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (400, 400);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Projeto 4 - Objetos 3D");
   glutDisplayFunc(Desenha);

   glutMouseFunc(GerenciaMouse);
   glutKeyboardFunc(GerenciaTeclado);
   glutSpecialFunc(TeclasEspeciais);
   init ();

   glutReshapeFunc(reshape);
   glutMainLoop();
}
