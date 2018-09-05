#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
using namespace std;

char texto[30];
GLfloat win, r, g, b;
GLint view_w, view_h, tipo;
int xclick, yclick;

void display()
{
    glClearColor( 0, 0, 0, 1 );
    glClear( GL_COLOR_BUFFER_BIT );

    /*glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( -1.1, 1.1, -1.1, 1.1, -1, 1 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    const unsigned int gridSize = 50;
    glBegin(GL_LINES);
    for( unsigned int j = 0; j <= gridSize; ++j )
    {
        const float i = -1.0f + ( j * 2.0f/(gridSize) );
        glVertex2f(i, 1.0f);
        glVertex2f(i, -1.0f);
        glVertex2f(-1.0f, i);
        glVertex2f(1.0f, i);
    }
    glEnd();*/

    glutSwapBuffers();
}

void DesenhaQuadrado(int x1, int x2, int x3, int x4, int y1, int y2, int y3,int y4)
{
     glBegin(GL_QUADS);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glVertex2f(x4, y4);
     glEnd();
     glFlush();
}

void MemoriaFacil()
{
    int rodadas = 0, erros = 0, acertos = 0, cliques;
    //while (rodadas<5)
    //{
        cliques = 0;
        glColor3f(0.91f, 0.91f, 0.70f); 
        //Desenhar quadrados beges
        for(int j=0;j<6; j++)
        {
            for(int i=0; i<5; i++)
            {
                DesenhaQuadrado(25+(80*i),25+(80*i),15+(80*(i+1)),15+(80*(i+1)),80*(j+1),10+(80*j),10+(80*j),80*(j+1));   
            }
        }

        Sleep(2000);

        int quadrados [6][5];
        //Inicializar matriz equivalente aos quadrados com 0 ou 1 
        //No mínimo 5 e no máximo 10 quadrados poderão ser coloridos
        int x = 0; //número de quadrados coloridos
        while(x<5){
            for(int j=0;j<6; j++){
                for(int i=0; i<5; i++)
                {
                    if(x<10 && ((rand() % 10) > 5))
                    {
                        quadrados[j][i] = 1;
                        x++;
                    }
                    else if(quadrados[j][i]!=1)
                    {
                        quadrados[j][i] = 0;
                    }
                    
                }
            }
        }

        //Colorir os quadrados sorteados
        for(int j=0;j<6; j++){
            for(int i=0; i<5; i++)
            {
                if(quadrados[j][i])
                {
                    glColor3f(0.0f, 0.1f, 0.7f); 
                    DesenhaQuadrado(25+(80*i),25+(80*i),15+(80*(i+1)),15+(80*(i+1)),80*(j+1),10+(80*j),10+(80*j),80*(j+1)); 
                } 
            }
        }
        Sleep(5000);

        //Voltar cor para bege
        for(int j=0;j<6; j++){
            for(int i=0; i<5; i++)
            {
                if(quadrados[j][i])
                {
                    glColor3f(0.91f, 0.91f, 0.70f); 
                    DesenhaQuadrado(25+(80*i),25+(80*i),15+(80*(i+1)),15+(80*(i+1)),80*(j+1),10+(80*j),10+(80*j),80*(j+1)); 
                } 
            }
        }

        //Verificação de erros
        /*while(cliques<10)
        {
            int iclick = (xclick-25)/80, jclick = (yclick-10)/80;
            if(quadrados[iclick][jclick]==1)
            {
                acertos++;
                DesenhaQuadrado(25+(80*iclick),25+(80*iclick),15+(80*(iclick+1)),15+(80*(iclick+1)),80*(jclick+1),10+(80*jclick),10+(80*jclick),80*(jclick+1)); 
            }
            else
            {
                erros++;
            }
            cliques++;
        }*/
        //fazer logica para chamar handlemouse    
        rodadas++;
    //}
    //cout << "Erros " << erros << " Acertos " << acertos << endl;
}

void Desenha(void)
{
     glClear(GL_COLOR_BUFFER_BIT);

     switch(tipo)
     {
         case 1:
            MemoriaFacil();
            break;
     }
     glFlush();
     glutPostRedisplay();
}

void MenuMemoria(int op)
{
   switch(op) {
            case 00:
                tipo = 1;
                break;
            case 01:
                //chamar memoria dificil
                break;
    }
    glutPostRedisplay();
}

void MenuEmOrdem(int op)
{
   switch(op) {
            case 10:
                //chamar em ordem crescente
                break;
            case 11:
                //chamar em ordem decrescente
                break;
    }
    glutPostRedisplay();
}

// Gerenciamento do menu principal
void MenuPrincipal(int op)
{
    switch(op) {
            case 2:
                //chamar batalha naval
                break;
            case 3:
                glutDestroyWindow(glutGetWindow());;
                break;
    }
}

// Criacao do Menu
void CriaMenu()
{
    int menu,submenu1,submenu2;

    submenu1 = glutCreateMenu(MenuMemoria);
    glutAddMenuEntry("Facil",00);
    glutAddMenuEntry("Dificil",01);

    submenu2 = glutCreateMenu(MenuEmOrdem);
    glutAddMenuEntry("Crescente",10);
    glutAddMenuEntry("Decrescente",11);

    menu = glutCreateMenu(MenuPrincipal);
    glutAddSubMenu("Memoria",submenu1);
    glutAddSubMenu("Em Ordem",submenu2);
    glutAddMenuEntry("Batalha Naval", 2);
    glutAddMenuEntry("Sair", 3);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glFlush();
}

void Inicializa (void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    CriaMenu();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 450, 0, 500, -1, 1);

}

void HandleMouse(int button, int state, int x, int y)
{
    yclick = 500-y;
    xclick = x;
    cout << "x = " << x << "  y = " << y << endl;
    //int iclick = (xclick-25)/80, jclick = (yclick-10)/80;
    //cout << "i = " << iclick << " j = " << jclick << endl;
	//glutPostRedisplay();
}

int main(int argc, char** argv)
{
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     glutInitWindowSize(450,500);
     glutInitWindowPosition(10,10);
     glutCreateWindow("Primeiro Trabalho - Joguinhos simples");
     glutDisplayFunc(Desenha);
     glutMouseFunc(HandleMouse);
     //glutReshapeFunc(AlteraTamanhoJanela);
     //glutMotionFunc(MoveMouseBotaoPressionado);
     //glutPassiveMotionFunc(MoveMouse);
     //glutSpecialFunc(TeclasEspeciais);
     Inicializa();
     glutMainLoop();
}
