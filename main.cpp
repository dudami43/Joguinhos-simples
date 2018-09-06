#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <ctime>
using namespace std;

char texto[30];
GLint tipo;
int xclick, yclick;
int quadrados [6][5], erros = 0, acertos = 0, rodadas = 0, cliques = 10;
bool primeiro_desenho = true;


void display()
{
    glClearColor( 0, 0, 0, 1 );
    glClear( GL_COLOR_BUFFER_BIT );
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

void TelaMemoriaFacil()
{
    int num_coloridos = 0; 
    if (primeiro_desenho)
    {
        primeiro_desenho = false;
        glColor3f(0.91f, 0.91f, 0.70f); 
        for(int i=0;i<6; i++)
        {
            for(int j=0; j<5; j++)
            {
                DesenhaQuadrado(25+(80*j),25+(80*j),15+(80*(j+1)),15+(80*(j+1)),80*(i+1),10+(80*i),10+(80*i),80*(i+1));   
            }
        }
        Sleep(2000);
        for(int i=0;i<6; i++)
        {
            for(int j=0; j<5; j++)
            {
                if(num_coloridos<10 && ((rand() % 10) > 5))
                {
                    quadrados[i][j] = 1;
                    num_coloridos++;
                }
                else
                {
                    quadrados[i][j] = 0;
                }
                
            }
        }   
        for(int i=0;i<6; i++)
        {
            for(int j=0; j<5; j++)
            {
                if(quadrados[i][j]==1)
                {
                    glColor3f(0.0f, 0.1f, 0.7f); 
                    DesenhaQuadrado(25+(80*j),25+(80*j),15+(80*(j+1)),15+(80*(j+1)),80*(i+1),10+(80*i),10+(80*i),80*(i+1)); 
                } 
            }
        }
        Sleep(2000);
        for(int i=0;i<6; i++)
        {
            for(int j=0; j<5; j++)
            {
                if(quadrados[i][j]==1)
                {
                    glColor3f(0.91f, 0.91f, 0.70f); 
                    DesenhaQuadrado(25+(80*j),25+(80*j),15+(80*(j+1)),15+(80*(j+1)),80*(i+1),10+(80*i),10+(80*i),80*(i+1)); 
                } 
            }
        }
    }
    else
    {
        for(int i=0;i<6; i++)
        {
            for(int j=0; j<5; j++)
            {
                if(quadrados[i][j]==2)
                {
                    glColor3f(0.0f, 0.1f, 0.7f); 
                    DesenhaQuadrado(25+(80*j),25+(80*j),15+(80*(j+1)),15+(80*(j+1)),80*(i+1),10+(80*i),10+(80*i),80*(i+1)); 
                } 
                else
                {
                    glColor3f(0.91f, 0.91f, 0.70f); 
                    DesenhaQuadrado(25+(80*j),25+(80*j),15+(80*(j+1)),15+(80*(j+1)),80*(i+1),10+(80*i),10+(80*i),80*(i+1)); 
                }
            }
        }
        glFlush();
    }
    return;
}

void MemoriaFacil()
{
    if(rodadas<5){
        TelaMemoriaFacil();
        if(cliques>1)
        {
            if(!primeiro_desenho)
            { 
                int j = (xclick-25)/80, i = (yclick-10)/80;
                cliques--;
                if(quadrados[i][j]==1)
                {
                    glColor3f(0.0f, 0.1f, 0.7f); 
                    DesenhaQuadrado(25+(80*j),25+(80*j),15+(80*(j+1)),15+(80*(j+1)),80*(i+1),10+(80*i),10+(80*i),80*(i+1));
                    quadrados[i][j] = 2; 
                    acertos++;
                }
                else
                {
                    erros++;
                }
                glFlush();
            }
        }
        else
        {
            cliques = 10;
            primeiro_desenho = true;
            rodadas++;
        }
        //Acaba após 5 rodadas
        //Contabiliza mais erros que o esperado
        //O último quadrado clicado da ultima rodada fica azul na proxima rodada
    }
    else
    {
        cout << "Erros: " << erros << " Acertos: " << acertos << endl;
    }
    return;
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
}

int main(int argc, char** argv)
{
    srand(time(NULL));
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