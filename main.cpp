#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <ctime>
using namespace std;

GLint tipo;
int xclick, yclick;
int quadrados [10][8], erros = 0, acertos = 0, rodadas = 0, cliques = 10;
int bombas = 0, embarcacoes = 0, tabuleiro[40][40];
bool primeiro_desenho = true, clicado = false;
char texto[50];

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

void textDraw()
{
    glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3d(1, 1, 1);

    glPushMatrix();

	glRasterPos2f(150, 150);

	for (char *i = texto; *i != 0; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *i);

	glPopMatrix();

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

void MemoriaFacil(int x, int y)
{
    if(rodadas<5){
        TelaMemoriaFacil();
        if(cliques>0)
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
    }
    else
    {
        sprintf(texto, "Erros: %d Acertos: %d ",erros, acertos);
        textDraw();
        tipo = 0;
    }
    return;
}

void TelaMemoriaDificil()
{
    int num_coloridos = 0; 
    if (primeiro_desenho)
    {
        primeiro_desenho = false;
        glColor3f(0.91f, 0.91f, 0.70f); 
        for(int i=0;i<10; i++)
        {
            for(int j=0; j<8; j++)
            {
                DesenhaQuadrado(30+(49*j),30+(49*j),20+(49*(j+1)),20+(49*(j+1)),49*(i+1),10+(49*i),10+(49*i),49*(i+1));   
            }
        }
        Sleep(2000);
        for(int i=0;i<10; i++)
        {
            for(int j=0; j<8; j++)
            {
                if(num_coloridos<10 && ((rand() % 10) > 8))
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
        for(int i=0;i<10; i++)
        {
            for(int j=0; j<8; j++)
            {
                if(quadrados[i][j]==1)
                {
                    glColor3f(0.0f, 0.1f, 0.7f); 
                    DesenhaQuadrado(30+(49*j),30+(49*j),20+(49*(j+1)),20+(49*(j+1)),49*(i+1),10+(49*i),10+(49*i),49*(i+1));   
                } 
            }
        }
        Sleep(2000);
        for(int i=0;i<10; i++)
        {
            for(int j=0; j<8; j++)
            {
                if(quadrados[i][j]==1)
                {
                    glColor3f(0.91f, 0.91f, 0.70f); 
                    DesenhaQuadrado(30+(49*j),30+(49*j),20+(49*(j+1)),20+(49*(j+1)),49*(i+1),10+(49*i),10+(49*i),49*(i+1));   
                } 
            }
        }
    }
    else
    {
        for(int i=0;i<10; i++)
        {
            for(int j=0; j<8; j++)
            {
                if(quadrados[i][j]==2)
                {
                    glColor3f(0.0f, 0.1f, 0.7f); 
                    DesenhaQuadrado(30+(49*j),30+(49*j),20+(49*(j+1)),20+(49*(j+1)),49*(i+1),10+(49*i),10+(49*i),49*(i+1));   
                } 
                else
                {
                    glColor3f(0.91f, 0.91f, 0.70f); 
                    DesenhaQuadrado(30+(49*j),30+(49*j),20+(49*(j+1)),20+(49*(j+1)),49*(i+1),10+(49*i),10+(49*i),49*(i+1));   
                }
            }
        }
        glFlush();
    }
    return;
}

void MemoriaDificil(int x, int y)
{
    if(rodadas<5){
        TelaMemoriaDificil();
        if(cliques>0)
        {
            if(!primeiro_desenho)
            { 
                int j = (xclick-30)/49, i = (yclick-20)/49;
                cliques--;
                if(quadrados[i][j]==1)
                {
                    glColor3f(0.0f, 0.1f, 0.7f); 
                    DesenhaQuadrado(30+(49*j),30+(49*j),20+(49*(j+1)),20+(49*(j+1)),49*(i+1),10+(49*i),10+(49*i),49*(i+1));   
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
    }
    else
    {
        sprintf(texto, "Erros: %d Acertos: %d ",erros, acertos);
        textDraw();
        tipo = 0;
    }
    return;
}

void TelaBatalhaNaval()
{
    glColor3f(0.91f, 0.91f, 0.70f); 
    for(int i=0;i<40; i++)
    {
        for(int j=0; j<40; j++)
        {
            DesenhaQuadrado(5+(11*j),5+(11*j),2+(11*(j+1)),2+(11*(j+1)),11*(i+1),2+(11*i),2+(11*i),11*(i+1)); 
            tabuleiro[i][j] = 0;
        }
    }
    int col_rand,lin_rand, embarcacao_rand;
    while(bombas<10)
    {
        col_rand = (rand()%40);
        lin_rand = (rand()%40);
        tabuleiro[lin_rand][col_rand] = 1;
        glColor3f(0.91f, 0.0f, 0.0f); 
        DesenhaQuadrado(5+(11*col_rand),5+(11*col_rand),2+(11*(col_rand+1)),2+(11*(col_rand+1)),11*(lin_rand+1),2+(11*lin_rand),2+(11*lin_rand),11*(lin_rand+1)); 
        bombas++;
    }
    while(embarcacoes<10)
    {
        col_rand = (rand()%40);
        lin_rand = (rand()%40);
        if(tabuleiro[lin_rand][col_rand] != 1)
        {
            embarcacao_rand = rand()%4;
            /*switch(embarcacao_rand)
            {
                case 0: //Destroyer
                //se coluna menor que 40-length
                case 1: //Porta-aviões
                case 2: //Lança de ataque
                case 3: //Submarino
                case 4: //Corveta
            }*/
        }
    }
    
}

void Desenha(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    switch(tipo)
    {
    case 0: 
        sprintf(texto, " ");
        textDraw();
        break;
    case 1:
        TelaMemoriaFacil();
        break;
    case 2:
        TelaMemoriaDificil();
        break;
    case 5:
        TelaBatalhaNaval();
    }
    glFlush();
}

void MenuMemoria(int op)
{
   switch(op)
    {
        case 00:
            tipo = 1;
            erros = 0;
            acertos = 0; rodadas = 0;
            cliques = 10;
            primeiro_desenho = true;
            break;
        case 01:
            tipo = 2;
            erros = 0;
            acertos = 0; rodadas = 0;
            cliques = 10;
            primeiro_desenho = true;
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
    switch(op) 
    {
        case 2:
            tipo = 5;
            break;
        case 3:
            glutDestroyWindow(glutGetWindow());
            exit(0);
            break;
    }
    glutPostRedisplay();
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
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !clicado)
	{
		clicado = true;
		xclick = x;
		yclick = y;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && clicado)
	{
		clicado = false;
        xclick = x;
		yclick = 500-y;
        switch(tipo)
        {
            case 1:
                MemoriaFacil(xclick,yclick);;
                break;
            case 2:
                MemoriaDificil(xclick,yclick);
                break;
        }
	}
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