#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_TIROS 10

//estruturas
typedef struct inimigos {
       /*
       pos : posição, lim : limite, esc : escala, vel : velocidade
       tipo 1 : inimigo 1
       tipo 2 : inimigo 2
       tipo 3 : inimigo 3
       */
       int tipo,morto;
       float vel;
       GLfloat posx,posy,limx,limy,escx,escy;
} Inimigos;

typedef struct tiros {
       int ativo; //tiro na tela
       GLfloat posx,posy; //posições x e y no plano cartesiano
} Tiros;

typedef struct tanque {
       int atingido,vidas; //tiro na tela
       GLfloat posx,limx,escx; //posições x e y no plano cartesiano
} Tanque;

typedef struct vitamina {
       int ativo; //tiro na tela
       float vel;
       GLfloat posx,posy,escx; //posições x e y no plano cartesiano
} Vitamina;
//fim estruturas

//variáveis
Inimigos **inimigos;
Tiros **tiros;
Tanque *tanque;
Vitamina **vitaminas;
GLint id_window;
GLfloat win,vidax=0,lado=-1;
int var1,var2,i,j,k,MAX_INIMIGOS=15,MAX_VITAMINAS=3,NUM_INIMIGOS=4;
//fim variáveis

//protótipos das funções
Inimigos* cria_inimigo(int tipo);
Tiros* cria_tiro();
Tanque* inicializa_tanque();
Vitamina* cria_vitamina();
void GerenciaMouse(GLint button, GLint state, GLint x, GLint y);
void CriaMenu(void);
void MenuPrincipal(GLint op);
void MenuVInimigos(GLint op);
void MenuNVitaminas(GLint op);
void MenuNInimigos(GLint op);
void GerenciaTeclado(unsigned char key, int x, int y);
void TeclasEspeciais(int key, int x, int y);
void Timer(int value);
void AlteraTamanhoJanela(GLsizei w, GLsizei h);
void Inicializa(void);
void Desenha(void);
void DesenhaTanque();
void inimigo2(int tipo);
void DesenhaInimigo2(int tipo);
void inimigo1(int tipo) ;
void DesenhaInimigo1(int tipo);
void inimigo3(int tipo);
void DesenhaInimigo3(int tipo);
void inimigo4(int tipo);
void DesenhaInimigo4(int tipo);
void DesenhaTiro(GLfloat x,GLfloat y);
void DesenhaQuadrado(int tipo);
void DesenhaFim();
void DesenhaVida();
void DesenhaVitamina(GLfloat x,GLfloat y);
void DesenhaParabens();
//fim protótipos

void DesenhaParabens()
{
       glColor3f(0.2f, 0.2f, 1.0f);
       //P
       glBegin(GL_LINE_LOOP);
                   glVertex2f(0,-1); glVertex2f(0,1); glVertex2f(2,1); glVertex2f(2,0); glVertex2f(0,0);
       glEnd();
       //A
       glBegin(GL_LINE_LOOP);
                   glVertex2f(3,-1); glVertex2f(3,1); glVertex2f(5,1); glVertex2f(5,-1); glVertex2f(5,0); glVertex2f(3,0);
       glEnd();
       //R
       glBegin(GL_LINE_LOOP);
                   glVertex2f(6,-1); glVertex2f(6,1); glVertex2f(8,1); glVertex2f(8,0); glVertex2f(6,0); glVertex2f(8,-1); glVertex2f(6,0);
       glEnd();
       //A
       glBegin(GL_LINE_LOOP);
                   glVertex2f(9,-1); glVertex2f(9,1); glVertex2f(11,1); glVertex2f(11,-1); glVertex2f(11,0); glVertex2f(9,0);
       glEnd();
       //B
       glBegin(GL_LINE_LOOP);
                   glVertex2f(12,-1); glVertex2f(12,1); glVertex2f(14,1); glVertex2f(14,0); glVertex2f(12,0); glVertex2f(14,0); glVertex2f(14,-1);
       glEnd();
       //É
       glBegin(GL_LINES);
                   glVertex2f(15,-1); glVertex2f(15,1); glVertex2f(15,1); glVertex2f(17,1); glVertex2f(15,0); glVertex2f(17,0); glVertex2f(15,-1); glVertex2f(17,-1); glVertex2f(16,2); glVertex2f(17,2.5); 
       glEnd();
       //N
       glBegin(GL_LINE_LOOP);
                   glVertex2f(18,-1); glVertex2f(18,1); glVertex2f(20,-1); glVertex2f(20,1); glVertex2f(20,-1); glVertex2f(18,1);
       glEnd();
       //S
       glBegin(GL_LINE_LOOP);
                   glVertex2f(21,-1); glVertex2f(23,-1); glVertex2f(23,0); glVertex2f(21,0); glVertex2f(21,1); glVertex2f(23,1); glVertex2f(21,1); glVertex2f(21,0); glVertex2f(23,0); glVertex2f(23,-1);
       glEnd();
}

void DesenhaVitamina(GLfloat x,GLfloat y)
{
       glColor3f(0.5f, 0.5f, 1.0f);
       glBegin(GL_POLYGON);
                   glVertex2f(-2+x,-1+y);
                   glVertex2f(0+x,2+y);
                   glVertex2f(2+x,-1+y);
       glEnd();
       
       glBegin(GL_POLYGON);
                   glVertex2f(-2+x,1+y);
                   glVertex2f(0+x,-2+y);
                   glVertex2f(2+x,1+y);
       glEnd();
}

void DesenhaVida()
{
       glColor3f(1.0f, 0.5f, 0.0f);
       glBegin(GL_POLYGON);
                   glVertex2f(-1+vidax,-1);
                   glVertex2f(-2+vidax,0);
                   glVertex2f(-1+vidax,1);
                   glVertex2f(1+vidax,1);
                   glVertex2f(2+vidax,0);
                   glVertex2f(1+vidax,-1);
       glEnd();
}

void DesenhaFim()
{
       glColor3f(0.2f, 0.2f, 1.0f);
       glBegin(GL_LINES);
                   glVertex2f(-3,-1);
                   glVertex2f(-3,1);
                   glVertex2f(-3,1);
                   glVertex2f(-1,1);
                   glVertex2f(-3,0);
                   glVertex2f(-1,0);
                   glVertex2f(0,-1);
                   glVertex2f(0,1);
                   glVertex2f(0,1.3);
                   glVertex2f(0,1.4);
                   glVertex2f(1,-1);
                   glVertex2f(1,1);
                   glVertex2f(1,1);
                   glVertex2f(2,0);
                   glVertex2f(2,0);
                   glVertex2f(3,1);
                   glVertex2f(3,1);
                   glVertex2f(3,-1);
       glEnd();
}

void DesenhaQuadrado(int tipo)
{
       glBegin(GL_POLYGON);
                   glVertex2f(0,1);
                   glVertex2f(1,1);
                   glVertex2f(1,0);
                   glVertex2f(0,0);
       glEnd();
}


void DesenhaTiro(GLfloat x,GLfloat y)
{
       glColor3f(1.0f, 0.0f, 0.0f);
       glBegin(GL_POLYGON);
                   glVertex2f(0.5+x,0+y);
                   glVertex2f(0+x,-0.5+y);
                   glVertex2f(-0.5+x,0+y);
                   glVertex2f(0+x,0.5+y);
       glEnd();
}

void DesenhaInimigo4(int tipo)
{
       glColor3f(0.0f, 1.0f, 0.5f);
       glBegin(GL_POLYGON);
                   glVertex2f(0,-1);
                   glVertex2f(0,0);
                   glVertex2f(1,4);
                   glVertex2f(1,4);
                   glVertex2f(3,3);
                   glVertex2f(3,3);
                   glVertex2f(4,2);
                   glVertex2f(4,2);
       glEnd();


       glBegin(GL_POLYGON);
                   glVertex2f(0,-1);
                   glVertex2f(0,0);
                   glVertex2f(-1,4);
                   glVertex2f(-1,4);
                   glVertex2f(-3,3);
                   glVertex2f(-3,3);
                   glVertex2f(-4,2);
                   glVertex2f(-4,2);
       glEnd();
}

void inimigo4(int tipo) {
           glPushMatrix();
           glScalef(0.5,0.5,0);
           glTranslatef(0+inimigos[tipo]->posx,15+inimigos[tipo]->posy,0);
           DesenhaInimigo4(tipo);
           
           //pontos pretos no inimigo para modelar
           //detalhes inimigo
           glColor3f(0.0f, 0.0f, 0.0f);
           glPushMatrix();
           glTranslatef(1,0,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-2,0,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(0,-2,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-1,-2,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           glColor3f(0.0f, 1.0f, 0.5f);
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(1,-2,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(0,-3,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(2,-3,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(3,-4,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-2,-2,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-1,-3,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-3,-3,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-4,-4,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           glPopMatrix();
}

void DesenhaInimigo3(int tipo)
{
       glColor3f(0.0f, 1.0f, 0.0f);
       glBegin(GL_POLYGON);
                   glVertex2f(0,-1);
                   glVertex2f(0,0);
                   glVertex2f(0,4);
                   glVertex2f(3,4);
                   glVertex2f(3,3);
                   glVertex2f(5,3);
                   glVertex2f(5,2);
                   glVertex2f(6,2);
                   glVertex2f(6,1);
                   glVertex2f(7,1);
                   glVertex2f(7,0);
                   glVertex2f(8,0);
                   glVertex2f(8,-1);
       glEnd();
       
       glBegin(GL_POLYGON);
                   glVertex2f(3,-1);
                   glVertex2f(6,-1);
                   glVertex2f(6,-2);
                   glVertex2f(3,-2);
       glEnd();
       
       glBegin(GL_POLYGON);
                   glVertex2f(0,-1);
                   glVertex2f(0,0);
                   glVertex2f(0,4);
                   glVertex2f(-3,4);
                   glVertex2f(-3,3);
                   glVertex2f(-5,3);
                   glVertex2f(-5,2);
                   glVertex2f(-6,2);
                   glVertex2f(-6,1);
                   glVertex2f(-7,1);
                   glVertex2f(-7,0);
                   glVertex2f(-8,0);
                   glVertex2f(-8,-1);
       glEnd();
       
       glBegin(GL_POLYGON);
                   glVertex2f(-3,-1);
                   glVertex2f(-6,-1);
                   glVertex2f(-6,-2);
                   glVertex2f(-3,-2);
       glEnd();
}

void inimigo3(int tipo) {
           glPushMatrix();
           glScalef(0.4,0.4,0);
           glTranslatef(0+inimigos[tipo]->posx,25+inimigos[tipo]->posy,0);
           DesenhaInimigo3(tipo);
           
           //pontos pretos no inimigo para modelar
           //detalhes inimigo
           glColor3f(0.0f, 0.0f, 0.0f);
           glPushMatrix();
           glTranslatef(1,0,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-2,0,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(4,0,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-5,0,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           glColor3f(0.0f, 1.0f, 0.0f);
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(4,-3,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(0,-2,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-1,-2,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-5,-3,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           glPopMatrix();
}

void DesenhaInimigo1(int tipo)
{
       //1º quadrante
       glColor3f(1.0f, 1.0f, 0.0f);
       glBegin(GL_POLYGON);
                   glVertex2f(0,-1);
                   glVertex2f(0,4);
                   glVertex2f(1,4);
                   glVertex2f(1,3);
                   glVertex2f(2,3);
                   glVertex2f(2,2);
                   glVertex2f(3,2);
                   glVertex2f(3,1);
                   glVertex2f(4,1);
                   glVertex2f(4,-1);
       glEnd();
       //4º quadrante
       glBegin(GL_POLYGON);
                   glVertex2f(0,-4);
                   glVertex2f(0,-1);
                   glVertex2f(2,-1);
                   glVertex2f(2,-2);
                   glVertex2f(3,-2);
                   glVertex2f(3,-3);
                   glVertex2f(4,-3);
                   glVertex2f(4,-4);
       glEnd();
       //2º quadrante
       glBegin(GL_POLYGON);
                   glVertex2f(0,-1);
                   glVertex2f(0,4);
                   glVertex2f(-1,4);
                   glVertex2f(-1,3);
                   glVertex2f(-2,3);
                   glVertex2f(-2,2);
                   glVertex2f(-3,2);
                   glVertex2f(-3,1);
                   glVertex2f(-4,1);
                   glVertex2f(-4,-1);
       glEnd();
       //3º quadrante
       glBegin(GL_POLYGON);
                   glVertex2f(0,-4);
                   glVertex2f(0,-1);
                   glVertex2f(-2,-1);
                   glVertex2f(-2,-2);
                   glVertex2f(-3,-2);
                   glVertex2f(-3,-3);
                   glVertex2f(-4,-3);
                   glVertex2f(-4,-4);
       glEnd();
}

void inimigo1(int tipo) {
           glPushMatrix();
           glScalef(0.5,0.5,0);
           glTranslatef(0+inimigos[tipo]->posx,15+inimigos[tipo]->posy,0);
           DesenhaInimigo1(tipo);
           //pontos pretos no inimigo para modelar
           //detalhes inimigo
           glColor3f(0.0f, 0.0f, 0.0f);
           glPushMatrix();
           glTranslatef(1,0,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(1,-3,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(2,-4,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(0,-2,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(0,-4,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();

           //detalhes inimigo
           glColor3f(0.0f, 0.0f, 0.0f);
           glPushMatrix();
           glTranslatef(-2,0,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-2,-3,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-3,-4,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-1,-2,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-1,-4,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();

           glPopMatrix();
}

void DesenhaInimigo2(int tipo) {
       glColor3f(1.0f, 0.0f, 1.0f);
       glBegin(GL_POLYGON);
                   glVertex2f(1,-2);
                   glVertex2f(1,3);
                   glVertex2f(1,4);
                   glVertex2f(2,4);
                   glVertex2f(2,3);
                   glVertex2f(3,3);
                   glVertex2f(3,2);
                   glVertex2f(4,2);
                   glVertex2f(4,-2);
       glEnd();
       
       glBegin(GL_POLYGON);
                   glVertex2f(4,-1);
                   glVertex2f(4,4);
                   glVertex2f(5,4);
                   glVertex2f(5,-1);
       glEnd();
       
       glBegin(GL_POLYGON);
                   glVertex2f(-1,-2);
                   glVertex2f(-1,2);
                   glVertex2f(1,2);
                   glVertex2f(1,-2);
       glEnd();
       
       glBegin(GL_POLYGON);
                   glVertex2f(-1,-2);
                   glVertex2f(-1,3);
                   glVertex2f(-1,4);
                   glVertex2f(-2,4);
                   glVertex2f(-2,3);
                   glVertex2f(-3,3);
                   glVertex2f(-3,2);
                   glVertex2f(-4,2);
                   glVertex2f(-4,-2);
       glEnd();
       
       glBegin(GL_POLYGON);
                   glVertex2f(-4,-1);
                   glVertex2f(-4,4);
                   glVertex2f(-5,4);
                   glVertex2f(-5,-1);
       glEnd();
}

void inimigo2(int tipo) {
           glPushMatrix();
           glScalef(0.5,0.5,0);
           glTranslatef(0+inimigos[tipo]->posx,25+inimigos[tipo]->posy,0);
           DesenhaInimigo2(tipo);
           
           //pontos pretos no inimigo para modelar
           //detalhes inimigo
           glColor3f(0.0f, 0.0f, 0.0f);
           glPushMatrix();
           glTranslatef(1,0,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-2,0,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(1,3,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(4,3,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(2,2,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(3,1,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-2,3,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-5,3,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-3,2,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
                   
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-4,1,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           glColor3f(1.0f, 0.0f, 1.0f);
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(2,-3,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(3,-4,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(2,3,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-3,-3,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-4,-4,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           //detalhes inimigo
           glPushMatrix();
           glTranslatef(-3,3,0);
           DesenhaQuadrado(tipo);
           glPopMatrix();
           
           glPopMatrix();
}

void DesenhaTanque()
{
         glColor3f(0.8f, 0.8f, 0.8f);
         glLineWidth(2);
         glBegin(GL_LINE_LOOP);
                   glVertex2f(-1.5,-1);
                   glVertex2f(-1.5,1);
                   glVertex2f(-1,1);
                   glVertex2f(-1,0.75);
                   glVertex2f(1,0.75);
                   glVertex2f(1,1);
                   glVertex2f(1.5,1);
                   glVertex2f(1.5,-1);
                   glVertex2f(1,-1);
                   glVertex2f(1,-0.75);
                   glVertex2f(-1,-0.75);
                   glVertex2f(-1,-1);
                   glVertex2f(-1.5,-1);
          glEnd();
         
         glColor3f(0.5f, 0.5f, 0.5f);
         glBegin(GL_POLYGON);
                   glVertex2f(-0.75,-0.5);
                   glVertex2f(-0.75,0.5);
                   glVertex2f(0.75,0.5);
                   glVertex2f(0.75,-0.5);
         glEnd();
         
         glColor3f(0.5f, 0.5f, 0.5f);
         glBegin(GL_POLYGON);
                   glVertex2f(-0.25,0.5);
                   glVertex2f(-0.25,2);
                   glVertex2f(0.25,2);
                   glVertex2f(0.25,0.5);
         glEnd();
}

// Callback chamada para fazer o desenho
void Desenha(void)
{
           glMatrixMode(GL_MODELVIEW);
           glLoadIdentity();
                              
           glClear(GL_COLOR_BUFFER_BIT);
           
           //se estiver vivo
           if(tanque->vidas>0) {
               //desenha tanque
               glPushMatrix();
               glScalef(2,2,0);
               glTranslatef(tanque->posx,-8,0);
               DesenhaTanque();
               glPopMatrix();
               //desenha vidas
               for(i=0; i<tanque->vidas*5; i+=5) {
                  glPushMatrix();
                  glScalef(0.5,0.5,0);
                  glTranslatef(-37+i,-38,0);
                  DesenhaVida();
                  glPopMatrix();
               }
               //desenha vitaminas
               for(i=0;i<MAX_VITAMINAS;i++) {
                   if(vitaminas[i]->ativo==1) {
                      glPushMatrix();
                      glScalef(0.5,0.5,0);
                      DesenhaVitamina(vitaminas[i]->posx,vitaminas[i]->posy);
                      glPopMatrix();
                   }
               }
               //desenha inimigos se estiverem vivos
               i=0;
               for(j=0;j<MAX_INIMIGOS;j++) {
                   if(inimigos[j]->morto==0) {                                                    
                     switch(inimigos[j]->tipo) {
                         case 1: inimigo1(j); break;
                         case 2: inimigo2(j); break;
                         case 3: inimigo3(j); break;
                         case 4: inimigo4(j); break;
                     }                     
                   }
                   else {
                     i++;
                     inimigos[j]->posy=30;
                     inimigos[j]->posx=rand()%35*lado;
                     lado*=-1;
                   }
               }
               //se todos inimigos estiverem mortos, exibe PARABENS na tela
               if(i==MAX_INIMIGOS) {
                   glPushMatrix();
                   glScalef(1,1,0);
                   glTranslatef(-12,0,0);
                   DesenhaParabens();
                   glPopMatrix();
               }
               //desenha tiros
               for(j=0;j<MAX_TIROS;j++) {
                   if(tiros[j]->ativo==1)
                       DesenhaTiro(tiros[j]->posx,tiros[j]->posy);
               }
               
               //desenha linha divisória
               glLineWidth(2);
               glColor3f(0.8f, 0.8f, 0.8f);
               glBegin(GL_LINE_LOOP);
                       glVertex2i(-20,-18);
                       glVertex2i(20,-18);
               glEnd();
          }//se estiver morto
           else {
                glPushMatrix();
                glScalef(3,3,0);
                DesenhaFim();
                glPopMatrix();
           }
           glutSwapBuffers();
}

// Responsável pelas inicializações
void Inicializa(void)
{
           // Set clear color to blue
           glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

           win = 20;

             //alocaçao e criação dos objetos
             inimigos=(Inimigos**)malloc(MAX_INIMIGOS*sizeof(Inimigos*));
             vitaminas=(Vitamina**)malloc(MAX_VITAMINAS*sizeof(Vitamina*));
             tiros=(Tiros**)malloc(MAX_TIROS*sizeof(Tiros*));
             for(i=0;i<MAX_TIROS;i++)
                 tiros[i]=cria_tiro();
             for(i=0;i<MAX_INIMIGOS;i++)
                 inimigos[i]=cria_inimigo((rand()%NUM_INIMIGOS)+1);
             for(i=0;i<MAX_VITAMINAS;i++)
                 vitaminas[i]=cria_vitamina();
             tanque=inicializa_tanque();

           // ** Faça aqui a inicialização das variáveis globais
               
           printf(" Setas para esquerda e para direita: movimentam o tanque.");
           printf("\n A: Atirar");
           printf("\n F2: Novo Jogo");
           printf("\n ESC: Sair");
           printf("\n Botao direito do mouse: Opcoes avancadas.");
}

// Callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
            // Especifica o tamanho da Viewport 
            glViewport(0, 0, w, h);

            // Inicializa o sistema de coordenadas
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            // Estabelece o volume de visualização (left, right, bottom, top)
            gluOrtho2D (-win, win, -win, win);
}

void novoJogo();
// Callback chamada de acordo com um  "idle" 
void Timer(int value)
{
     //tanque capturou vitamina ?
     for(i=0;i<MAX_VITAMINAS;i++) {
         if(vitaminas[i]->posx*vitaminas[i]->escx >= tanque->escx*tanque->posx-tanque->limx &&
            vitaminas[i]->posx*vitaminas[i]->escx <= tanque->escx*tanque->posx+tanque->limx &&
            vitaminas[i]->posy <= -23 && vitaminas[i]->ativo==1) {
            tanque->vidas++;
            vitaminas[i]->ativo=0;
         }
         else {
             //desce vitamina no eixo y
             vitaminas[i]->posy-=vitaminas[i]->vel;
             if(vitaminas[i]->posy <= -34) {
                  vitaminas[i]->posy=rand()%200+30;
                  vitaminas[i]->posx=rand()%35*lado;
                  lado*=-1;
             }
         }
     }
     
     for(i=0;i<MAX_INIMIGOS;i++) {                
         if(tanque->atingido==0) {    
                 //inimigo i atingiu tanque ?
                  switch(inimigos[i]->tipo) {
                     case 1: var1=-19; break;
                     case 2: var1=-23; break;
                     case 3: var1=-21; break;
                     case 4: var1=-19; break;
                 }
                 if((((inimigos[i]->posx*inimigos[i]->escx)-inimigos[i]->limx > tanque->escx*tanque->posx-tanque->limx &&
                      (inimigos[i]->posx*inimigos[i]->escx)-inimigos[i]->limx < tanque->escx*tanque->posx+tanque->limx) ||
                     ((inimigos[i]->posx*inimigos[i]->escx)+inimigos[i]->limx > tanque->escx*tanque->posx-tanque->limx &&
                      (inimigos[i]->posx*inimigos[i]->escx)+inimigos[i]->limx < tanque->escx*tanque->posx+tanque->limx)) &&
                    (inimigos[i]->posy*inimigos[i]->escy)-inimigos[i]->limy < var1) {
                    tanque->vidas--; tanque->atingido++;
                 }
         }
         else {
             tanque->atingido++;
             if(tanque->atingido>8*MAX_INIMIGOS) tanque->atingido=0;
         }
         
         //desce inimigo na tela
         switch(inimigos[i]->tipo) {
             case 1: var1=-48; break;
             case 2: var1=-58; break;
             case 3: var1=-68; break;
             case 4: var1=-48; break;
         }
         inimigos[i]->posy-=inimigos[i]->vel;
         if(inimigos[i]->posy <= var1) {
              inimigos[i]->posy=rand()%200+30;
              inimigos[i]->posx=rand()%35*lado;
              lado*=-1;
         }
         
         //acertou o inimigo k com tiro j?
         for(k=0;k<MAX_INIMIGOS;k++) {
             switch(inimigos[k]->tipo) {
                 case 1: var1=4; var2=10; break;
                 case 2: var1=9; var2=18; break;
                 case 3: var1=7; var2=14; break;
                 case 4: var1=4; var2=10; break;
             }
             for(j=0;j<MAX_TIROS;j++) {
                 if(tiros[j]->posx >= (inimigos[k]->posx*inimigos[k]->escx)-inimigos[k]->limx &&
                    tiros[j]->posx <= (inimigos[k]->posx*inimigos[k]->escx)+inimigos[k]->limx &&
                    tiros[j]->posy >= (inimigos[k]->posy*inimigos[k]->escy)+var1 &&
                    tiros[j]->posy <= (inimigos[k]->posy*inimigos[k]->escy)+var2) {
                   inimigos[k]->morto=1;
                   tiros[j]->ativo=0;
                   tiros[j]->posy=-100;
                 }
             }
         }
     }
     
     //se o tiro foi disparado e não atingiu o teto da tela, sobe mais (incrementa eixo y do tiro). Senão, desaparece.
     for(i=0;i<MAX_TIROS;i++) {
         if(tiros[i]->ativo==1) {
           if(tiros[i]->posy<15)
             tiros[i]->posy+=2;
           else {
             tiros[i]->ativo=0;
             tiros[i]->posy=-100;
           }
         }
     }
     
     glutPostRedisplay();
     glutTimerFunc(120,Timer, 1);
}
//reorganiza as variáveis para novo jogo
void novoJogo() {
    vidax=0; 
    lado=-1;
    tanque->posx=0;
    tanque->vidas=3;
    tanque->atingido=0;
    
    for(i=0;i<MAX_INIMIGOS;i++) {
       inimigos[i]->posx=rand()%35*lado;
       inimigos[i]->posy=rand()%200+30;;
       inimigos[i]->morto=0;
    }
    for(i=0;i<MAX_TIROS;i++) {
       tiros[i]->posx=rand()%35*lado;
       tiros[i]->posy=rand()%200+30;;
       tiros[i]->ativo=0;
    }
    for(i=0;i<MAX_VITAMINAS;i++) {
       vitaminas[i]->posx=rand()%35*lado;
       vitaminas[i]->posy=rand()%200+30;;
       vitaminas[i]->ativo=1;
    }
}

// Callback chamada quando as teclas especiais são pressionadas
void TeclasEspeciais(int key, int x, int y)
{
             // Move a base
	         if(key == GLUT_KEY_LEFT) {
	           if(tanque->posx>-8.5 && tanque->posx<=8.5)
                 tanque->posx-=0.5;
             }
             if(key == GLUT_KEY_RIGHT) {
               if(tanque->posx>=-8.5 && tanque->posx<8.5)
                 tanque->posx+=0.5;
             }
             if(key == GLUT_KEY_F2) {
                 novoJogo();
             }          
             glutPostRedisplay();
}
//gerenciamento do teclado
void GerenciaTeclado(unsigned char key, int x, int y)
{
    switch (key) {
            case 27:
                 glutDestroyWindow(id_window);
                 exit(1);
            case 'a': 
            case 'A':
               for(i=0;i<MAX_TIROS;i++) {
                   if(tiros[i]->ativo==0) {
                       tiros[i]->ativo=1;
                       tiros[i]->posx=tanque->posx*tanque->escx;
                       tiros[i]->posy=-11;
                       break;
                   }
               }
               break;
    }
    glutPostRedisplay();
}

//Gerenciamento do menu com as opções de cores           
//a variavel op é setada qdo uma opção do submenu for selecionada (a glut faz isso)
//menu número de inimigos
void MenuNInimigos(GLint op)
{
      switch(op)
     {
            case 0: MAX_INIMIGOS=15; break;
            case 1: MAX_INIMIGOS=20; break;
            case 2: MAX_INIMIGOS=25; break;
     }
     inimigos=(Inimigos**)realloc(inimigos,MAX_INIMIGOS*sizeof(Inimigos*));
     for(i=0;i<MAX_INIMIGOS;i++)                           
         inimigos[i]=cria_inimigo((rand()%NUM_INIMIGOS)+1);
     novoJogo();                                                           
     // reexibe a janela para mostrar a alteração
     glutPostRedisplay();
}
//menu número vitaminas
void MenuNVitaminas(GLint op)
{
      switch(op)
     {
            case 0: MAX_VITAMINAS=3; break;
            case 1: MAX_VITAMINAS=4; break;
            case 2: MAX_VITAMINAS=5; break;
     }
     vitaminas=(Vitamina**)realloc(vitaminas,MAX_VITAMINAS*sizeof(Vitamina*));
     for(i=0;i<MAX_VITAMINAS;i++)
         vitaminas[i]=cria_vitamina();
     novoJogo();  
     // reexibe a janela para mostrar a alteração
     glutPostRedisplay();
}
//menu variedade de inimigos
void MenuVInimigos(GLint op)
{
      switch(op)
     {
            case 0: NUM_INIMIGOS=1; break;
            case 1: NUM_INIMIGOS=2; break;
            case 2: NUM_INIMIGOS=3; break;
            case 3: NUM_INIMIGOS=4; break;
     }
     for(i=0;i<MAX_INIMIGOS;i++)
     { free(inimigos[i]); inimigos[i]=cria_inimigo((rand()%NUM_INIMIGOS)+1); }
     novoJogo();
     // reexibe a janela para mostrar a alteração
     glutPostRedisplay();
}

// Gerenciamento do menu principal           
//a variável op é setada quando uma opção do menu principal for selecionada
void MenuPrincipal(GLint op)
{
	if (op==3)
	{
		//destroindo a janela
		glutDestroyWindow(id_window);
		//terminando o programa
		exit(0);
	}
}

// Criacao do Menu
void CriaMenu(void) 
{
    GLint menu,submenu1,submenu2,submenu3;
    //criando submenu, quando uma de suas opçõesfor selecionada 
    //a função MenuCor será executada. 
	
    //glutCreatMenu retorna um inteiro que identifica o submenu.
    submenu1 = glutCreateMenu(MenuNInimigos);
    glutAddMenuEntry("15",0);	//adicionando a opção 0 ao submenu
    glutAddMenuEntry("20",1);
    glutAddMenuEntry("25",2);
    submenu2 = glutCreateMenu(MenuNVitaminas);
    glutAddMenuEntry("3",0);
    glutAddMenuEntry("4",1);
    glutAddMenuEntry("5",2);
    submenu3 = glutCreateMenu(MenuVInimigos);
    glutAddMenuEntry("1",0);
    glutAddMenuEntry("2",1);
    glutAddMenuEntry("3",2);
    glutAddMenuEntry("4",3);

    //criando o menu principal. Quando uma opção deste for selecionada
    //a função MenuPrincipal será executada. 
    //glutCreateMenu retorna um inteiro que identifica o menu
    menu = glutCreateMenu(MenuPrincipal); 
    glutAddSubMenu("Número de inimigos",submenu1); 	//adicionando o submenu1
    glutAddSubMenu("Número de Vitaminas",submenu2);
    glutAddSubMenu("Variedade de Inimigos",submenu3);
    glutAddMenuEntry("Sair",3);	//adicionando uma opção no menu principal
    
    //o botão que fará o menu aparecer é o botão direito do mouse
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Função callback chamada para gerenciar eventos do mouse.
//Qualquer evento ocorrido com o mouse executa esta função.
void GerenciaMouse(GLint button, GLint state, GLint x, GLint y)
{        
	if (button == GLUT_RIGHT_BUTTON)  //botão direito
        if (state == GLUT_DOWN)  //botão apertado
            CriaMenu();     
	glutPostRedisplay();	//reexibe a janela corrente
}
//inicialização do inimigo de acordo com o tipo
Inimigos* cria_inimigo(int tipo) {
    Inimigos *inimigo=(Inimigos*)malloc(sizeof(Inimigos));
    switch(tipo) {
        case 1:
             inimigo->tipo=1;
             inimigo->posx=rand()%35*lado;
             inimigo->posy=rand()%200+30;
             inimigo->limx=2;
             inimigo->limy=2;
             inimigo->escx=0.5;
             inimigo->escy=0.5;
             inimigo->vel=1.5;
             inimigo->morto=0;
             lado*=-1;
        break;
        case 2:
             inimigo->tipo=2;
             inimigo->posx=rand()%35*lado;
             inimigo->posy=rand()%200+30;
             inimigo->limx=2.5;
             inimigo->limy=2.5;
             inimigo->escx=0.5;
             inimigo->escy=0.5;
             inimigo->vel=3;
             inimigo->morto=0;
             lado*=-1;
        break;
        case 3:
             inimigo->tipo=3;
             inimigo->posx=rand()%35*lado;
             inimigo->posy=rand()%200+30;
             inimigo->limx=3.2;
             inimigo->limy=3.2;
             inimigo->escx=0.4;
             inimigo->escy=0.4;
             inimigo->vel=4.5;
             inimigo->morto=0;
             lado*=-1;
        break;
        case 4:
             inimigo->tipo=4;
             inimigo->posx=rand()%35*lado;
             inimigo->posy=rand()%200+30;
             inimigo->limx=2;
             inimigo->limy=2;
             inimigo->escx=0.5;
             inimigo->escy=0.5;
             inimigo->vel=1.5;
             inimigo->morto=0;
             lado*=-1;
        break;
    }
    return inimigo;
}
//inicialização do tiro
Tiros* cria_tiro() {
    Tiros *tiro=(Tiros*)malloc(sizeof(Tiros));
    tiro->ativo=0;
    tiro->posx=0;
    tiro->posy=-100;
    return tiro;
}
//inicialização do tanque
Tanque* inicializa_tanque() {
    Tanque *tanque=(Tanque*)malloc(sizeof(Tanque));
    tanque->vidas=3;
    tanque->atingido=0;
    tanque->posx=0;
    tanque->limx=3;
    tanque->escx=2;
    return tanque;
}
//inicialização da vitamina
Vitamina* cria_vitamina() {
    Vitamina *vitamina=(Vitamina*)malloc(sizeof(Vitamina));
    vitamina->ativo=1;
    vitamina->vel=1.5;
    vitamina->posx=rand()%35*lado;
    vitamina->posy=rand()%200+30;
    vitamina->escx=0.5;
    return vitamina;
}

// Programa principal
int main(void)
{             
             glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
             glutInitWindowSize(400,400);
             glutInitWindowPosition(10,10);
             id_window=glutCreateWindow("Trabalho CG - Jogo");
             glutDisplayFunc(Desenha);
             glutReshapeFunc(AlteraTamanhoJanela);
             glutSpecialFunc(TeclasEspeciais);
             glutKeyboardFunc(GerenciaTeclado);
	         glutMouseFunc(GerenciaMouse); 
             Inicializa();
             glutTimerFunc(120, Timer, 1);
             glutMainLoop();
             return 0;
}
