#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <ctime>
using namespace std;

GLint tipo;
int xclick = -1, yclick = -1;
int quadrados [10][8], erros = 0, acertos = 0, rodadas = 0, cliques, num_coloridos;
int bombas = 0, embarcacoes = 0, tabuleiro[40][40], vidas = 3;
int numeros [15][2], qtd_numeros, posicoes[15][2], aparece = 0, numeros_imprimir[15];
bool primeiro_desenho = true, clicado = false, ganhou = true, crescente;
float cor_r, cor_g, cor_b;
char texto[50];

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
    cout << texto << endl;
    glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3d(1, 1, 1);

    glPushMatrix();
	    glRasterPos2f(150, 150);
        for (char *i = texto; *i != 0; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *i);
	glPopMatrix();

	glFlush();
    tipo = 0;
}

void TelaMemoriaFacil()
{
    num_coloridos = 0; 
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
        cor_r = cor_g = cor_b = 1;
        while(cor_r>0.9 && cor_g>0.9 && cor_b>0.7)
        {
            cor_r = (rand())/(float(RAND_MAX)+1.0);
            cor_g = (rand())/(float(RAND_MAX)+1.0);
            cor_b = (rand())/(float(RAND_MAX)+1.0);
        }
        
        while(num_coloridos<5)
        {    
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
        }
        cliques = num_coloridos;
        for(int i=0;i<6; i++)
        {
            for(int j=0; j<5; j++)
            {
                if(quadrados[i][j]==1)
                {
                    glColor3f(cor_r, cor_g, cor_b); 
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
                    glColor3f(cor_r, cor_g, cor_b); 
                    DesenhaQuadrado(25+(80*j),25+(80*j),15+(80*(j+1)),15+(80*(j+1)),80*(i+1),10+(80*i),10+(80*i),80*(i+1)); 
                } 
                else
                {
                    glColor3f(0.91f, 0.91f, 0.70f); 
                    DesenhaQuadrado(25+(80*j),25+(80*j),15+(80*(j+1)),15+(80*(j+1)),80*(i+1),10+(80*i),10+(80*i),80*(i+1)); 
                }
            }
        }
    }
    glFlush();
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
                int j = (x-25)/80, i = (y-10)/80;
                cliques--;
                if(quadrados[i][j]==1)
                {
                    glColor3f(cor_r, cor_g, cor_b); 
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
            primeiro_desenho = true;
            rodadas++;
            xclick = yclick = -1;
            glutPostRedisplay();
        }
    }
    else
    {
        sprintf(texto, "Erros: %d Acertos: %d ",erros, acertos);
        textDraw();
    }
    return;
}

void TelaMemoriaDificil()
{
    num_coloridos = 0; 
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
        cor_r = cor_g = cor_b = 1;
        while(cor_r>0.9 && cor_g>0.9 && cor_b>0.7)
        {
            cor_r = (rand())/(float(RAND_MAX)+1.0);
            cor_g = (rand())/(float(RAND_MAX)+1.0);
            cor_b = (rand())/(float(RAND_MAX)+1.0);
        }
        while(num_coloridos<5)
        {
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
        }
        cliques = num_coloridos;
        for(int i=0;i<10; i++)
        {
            for(int j=0; j<8; j++)
            {
                if(quadrados[i][j]==1)
                {
                    glColor3f(cor_r, cor_g, cor_b); 
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
                    glColor3f(cor_r, cor_g, cor_b); 
                    DesenhaQuadrado(30+(49*j),30+(49*j),20+(49*(j+1)),20+(49*(j+1)),49*(i+1),10+(49*i),10+(49*i),49*(i+1));   
                } 
                else
                {
                    glColor3f(0.91f, 0.91f, 0.70f); 
                    DesenhaQuadrado(30+(49*j),30+(49*j),20+(49*(j+1)),20+(49*(j+1)),49*(i+1),10+(49*i),10+(49*i),49*(i+1));   
                }
            }
        }
    }
    glFlush();
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
                int j = (x-30)/49, i = (y-20)/49;
                cliques--;
                if(quadrados[i][j]==1)
                {
                    glColor3f(cor_r, cor_g, cor_b); 
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
            primeiro_desenho = true;
            rodadas++;
            xclick = yclick = -1;
            glutPostRedisplay();
        }
    }
    else
    {
        sprintf(texto, "Erros: %d Acertos: %d ",erros, acertos);
        textDraw();
    }
    return;
}

void TelaEmOrdem()
{
    if(primeiro_desenho)
    {  
        primeiro_desenho = false;  
        int cont = 0;
        qtd_numeros = ((rand()%15)+1);
        char texto[2];
        for(int i=0; i<qtd_numeros; i++)
        {
            numeros_imprimir[i] = numeros[i][0] = (rand()%100);
            numeros[i][1] = 0;
        }

        for(int i=0; i<5; i++)
        {
            for(int j=0;j<3;j++)
            {
                posicoes[cont][0] = 50+(i*50);
                posicoes[cont][1] = 450-(j*50);
                sprintf(texto, "%d",numeros[cont][0]);
                glPushMatrix();
                    glRasterPos2f(50+(i*50),450-(j*50));
                    for (char *x = texto; *x != 0; x++)
                        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *x);
                glPopMatrix();
                cont++;
                if (cont==qtd_numeros){ break;} 
            }
            if (cont==qtd_numeros){ break;}
        }
        glFlush();
        Sleep(2000);
        glClear(GL_COLOR_BUFFER_BIT);
        for(int i=0;i<qtd_numeros;i++)
        {
            int x = posicoes[i][0];
            int y = posicoes[i][1];
            DesenhaQuadrado(x,x,x+40,x+40,y+40,y,y,y+40);
        }

    }
    else
    {
        for(int i=0;i<qtd_numeros;i++)
        {
            int x = posicoes[i][0];
            int y = posicoes[i][1];
            if(numeros[i][1]==0)
                DesenhaQuadrado(x,x,x+40,x+40,y+40,y,y,y+40);
            else
            {
                sprintf(texto, "%d",numeros_imprimir[i]);
                glPushMatrix();
                    glRasterPos2f(x,y);
                    for (char *n = texto; *n != 0; n++)
                        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *n);
                glPopMatrix();
            }
        }   
    }
    
}

void EmOrdem(int x, int y)
{
    ganhou = true;
    TelaEmOrdem();
    for(int i=0;i<qtd_numeros;i++)
    {
        if(numeros[i][1]==0)
        {
            ganhou = false;
            break;
        } 
    }
    if(ganhou)
    {
        sprintf(texto, "Voce conseguiu!!!");
        textDraw();
    }
    else
    {
        int numero, posicao;
        if(crescente)
        {
            numero = 1000;
            for(int i=0;i<qtd_numeros;i++)
            {
                if(numeros[i][0]<=numero)
                {
                    numero = numeros[i][0];
                }
            }
            for(int i=0;i<qtd_numeros;i++)
            {
                if(x>=posicoes[i][0] && x<=posicoes[i][0]+40 && y>=posicoes[i][1] && y<=posicoes[i][1]+40)
                {
                    if(numero==numeros[i][0])
                    {
                        numeros[i][0] = 1000;
                        numeros[i][1] = 1;
                        glutPostRedisplay();
                    }
                }
            }
            
        }
        else
        {
            numero = -1;
            for(int i=0;i<qtd_numeros;i++)
            {
                if(numeros[i][0]>=numero)
                {
                    numero = numeros[i][0];
                }
            } 
            for(int i=0;i<qtd_numeros;i++)
            {
                if(x>=posicoes[i][0] && x<=posicoes[i][0]+40 && y>=posicoes[i][1] && y<=posicoes[i][1]+40)
                {
                    if(numero==numeros[i][0])
                    {
                        numeros[i][0] = -1;
                        numeros[i][1] = 1;
                        glutPostRedisplay();
                    }
                }
            }
        }
    }
}

void TelaBatalhaNaval()
{
    if(primeiro_desenho)
    {
        primeiro_desenho = false;
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
        
        while(embarcacoes<10)
        {
            col_rand = (rand()%40);
            lin_rand = (rand()%40);
            embarcacao_rand = rand()%4;
            switch(embarcacao_rand)
            {
                case 0: //Destroyer
                    if(lin_rand<40 && col_rand<35 && tabuleiro[lin_rand][col_rand] == 0
                    && tabuleiro[lin_rand][col_rand+1] == 0 && tabuleiro[lin_rand-1][col_rand+1] == 0
                    && tabuleiro[lin_rand-1][col_rand+1] == 0 && tabuleiro[lin_rand-1][col_rand+2] == 0
                    && tabuleiro[lin_rand-1][col_rand+3] == 0)
                    {
                        tabuleiro[lin_rand][col_rand] = tabuleiro[lin_rand][col_rand+1] =tabuleiro[lin_rand-1][col_rand+1] = 1;
                        tabuleiro[lin_rand-1][col_rand+1] = tabuleiro[lin_rand-1][col_rand+2]=tabuleiro[lin_rand-1][col_rand+3] = 1;
                        embarcacoes++;
                    }
                case 1: //Porta-aviões
                    if(lin_rand>0 && col_rand<34 && tabuleiro[lin_rand][col_rand] == 0
                    && tabuleiro[lin_rand][col_rand+1] == 0 && tabuleiro[lin_rand][col_rand+2]== 0
                    && tabuleiro[lin_rand][col_rand+3] == 0 && tabuleiro[lin_rand-1][col_rand+2] == 0 && tabuleiro[lin_rand-1][col_rand+3] == 0
                    && tabuleiro[lin_rand-1][col_rand+4] == 0 && tabuleiro[lin_rand-1][col_rand+5] == 0)
                    {
                        tabuleiro[lin_rand][col_rand] = tabuleiro[lin_rand][col_rand+1] = tabuleiro[lin_rand][col_rand+2] = 1;
                        tabuleiro[lin_rand][col_rand+3] = tabuleiro[lin_rand-1][col_rand+2] = tabuleiro[lin_rand-1][col_rand+3] = 1;
                        tabuleiro[lin_rand-1][col_rand+4] = tabuleiro[lin_rand-1][col_rand+5] = 1;
                        embarcacoes++;
                    }
                case 2: //Lança de ataque
                    if(lin_rand>0 && col_rand<37 &&  tabuleiro[lin_rand][col_rand] == 0
                    && tabuleiro[lin_rand][col_rand+1] == 0 && tabuleiro[lin_rand-1][col_rand+2] == 0)
                    {   
                        tabuleiro[lin_rand][col_rand] = tabuleiro[lin_rand][col_rand+1] = tabuleiro[lin_rand-1][col_rand+2]= 1;
                        embarcacoes++;
                    }
                case 3: //Submarino
                    if(lin_rand<39 && col_rand<35 && tabuleiro[lin_rand][col_rand] == 0 && tabuleiro[lin_rand][col_rand+1] == 0
                    && tabuleiro[lin_rand][col_rand+2] == 0 && tabuleiro[lin_rand][col_rand+3] == 0
                    && tabuleiro[lin_rand][col_rand+4] == 0 && tabuleiro[lin_rand+1][col_rand+2] == 0)
                    {
                        tabuleiro[lin_rand][col_rand] = tabuleiro[lin_rand][col_rand+1] = tabuleiro[lin_rand][col_rand+2] = 1;
                        tabuleiro[lin_rand][col_rand+3] = tabuleiro[lin_rand][col_rand+4] = tabuleiro[lin_rand+1][col_rand+2] = 1;
                        embarcacoes++;
                    }
                case 4: //Corveta
                    if(lin_rand>0 && col_rand<38 && tabuleiro[lin_rand][col_rand] == 0 && tabuleiro[lin_rand][col_rand+1] == 0
                    && tabuleiro[lin_rand-1][col_rand+1] == 0)
                    {
                        tabuleiro[lin_rand][col_rand] = tabuleiro[lin_rand][col_rand+1] = tabuleiro[lin_rand-1][col_rand+1]= 1;
                        embarcacoes++;
                    }
            }
        }
        while(bombas<10)
        {
            col_rand = (rand()%40);
            lin_rand = (rand()%40);
            if(tabuleiro[lin_rand][col_rand]!=1)
            {
                tabuleiro[lin_rand][col_rand] = 2;
                bombas++;
            }
        } 
    }
    else
    {
        for(int i=0;i<40; i++)
        {
            for(int j=0; j<40; j++)
            {
                if(tabuleiro[i][j]==3)
                {
                    glColor3f(0.0f, 0.0f, 0.9f); 
                    DesenhaQuadrado(5+(11*j),5+(11*j),2+(11*(j+1)),2+(11*(j+1)),11*(i+1),2+(11*i),2+(11*i),11*(i+1)); 
                } 
                else if(tabuleiro[i][j]==4)
                {
                    glColor3f(0.9f, 0.f, 0.0f); 
                    DesenhaQuadrado(5+(11*j),5+(11*j),2+(11*(j+1)),2+(11*(j+1)),11*(i+1),2+(11*i),2+(11*i),11*(i+1)); 
                }
                else
                {
                    glColor3f(0.91f, 0.91f, 0.70f); 
                    DesenhaQuadrado(5+(11*j),5+(11*j),2+(11*(j+1)),2+(11*(j+1)),11*(i+1),2+(11*i),2+(11*i),11*(i+1)); 
                }
            }
        }
    }
    glFlush();
    return;
}

void BatalhaNaval(int x, int y)
{
    ganhou = true;
    TelaBatalhaNaval();
    for(int i=0; i<40; i++)
    {
        for(int j=0; j<40; j++)
        {
            if(tabuleiro[i][j] == 1)
            {
                ganhou = false;
                j = 40;
                i = 40;
            } 
        }
    }
    if(!ganhou)
    {
        if(!primeiro_desenho)
        { 
            int j = (x-5)/11, i = (y-2)/11;
            if(tabuleiro[i][j]==1)
            {
                tabuleiro[i][j] = 3; 
                glColor3f(0.0f, 0.0f, 0.9f); 
                DesenhaQuadrado(5+(11*j),5+(11*j),2+(11*(j+1)),2+(11*(j+1)),11*(i+1),2+(11*i),2+(11*i),11*(i+1)); 
            }
            else if(tabuleiro[i][j]==2)
            {
                tabuleiro[i][j] = 4; 
                vidas--;
                glColor3f(0.9f, 0.f, 0.0f); 
                DesenhaQuadrado(5+(11*j),5+(11*j),2+(11*(j+1)),2+(11*(j+1)),11*(i+1),2+(11*i),2+(11*i),11*(i+1)); 
            } 
            glFlush();
        }     
    }
    else
    {
        sprintf(texto, "Game Over - Voce ganhou");
        textDraw();
        tipo = 0;
    }
    if (vidas == 0)
    {
        sprintf(texto, "Game Over - Voce perdeu");
        textDraw();
        //tipo = 0;
    }
    return;
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
            MemoriaFacil(xclick, yclick);
            break;
        case 2:
            MemoriaDificil(xclick,yclick);
            break;
        case 3:
            EmOrdem(xclick,yclick);
            break;
        case 4:
            EmOrdem(xclick,yclick);
            break;
        case 5:
            BatalhaNaval(xclick,yclick);
            break;
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
            primeiro_desenho = true;
            break;
        case 01:
            tipo = 2;
            erros = 0;
            acertos = 0; rodadas = 0;
            primeiro_desenho = true;
            break;
    }
    xclick = yclick = -1;
    glutPostRedisplay();
}

void MenuEmOrdem(int op)
{
   switch(op) {
            case 10:
                tipo = 3;
                primeiro_desenho = true;
                crescente = true;
                break;
            case 11:
                tipo = 4;
                primeiro_desenho = true;
                crescente = false;
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
            vidas = 3;
            primeiro_desenho = true;
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
    xclick = x;
    yclick = 500 - y;
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
    Inicializa();
    glutMainLoop();
}