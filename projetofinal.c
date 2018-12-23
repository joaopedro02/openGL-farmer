//Joao Pedro Miranda Miguel
//103227


#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include "SOIL.h"
#define tambase 0.1
#define pi 3.141592
void mostrapersonagem();
void crianimacaoauto();
void criaambiente();
void desenha();
void criaanimacaoanda(double x,double z);
void criaanimacaoplanta();
void controlaandar(int a);

//fila de animacao------------------------------------
typedef struct{
    double x;
    double y;
    double z;
    double tempo;
    float largura;
    float altura;
    float largura2;
    float altura2;
    float raio;
}tponto;

typedef struct {
    float superior;
    float inferior;
    float superiorlado;
    float superiorgiro;
}braco;

typedef struct{
    float superior;
    float inferior;
    float superiorlado;
} perna;

typedef float mao;
typedef float pe;


typedef struct {
    braco bracodireito;
    braco bracoesquerdo;
    perna pernadireita;
    perna pernaesquerda;
    float cabeca;
    mao maodireitalado;
    mao maoesquerdalado;
    mao maodireitacimabaixo;
    mao maoesquedacimabaixo;
    pe pedireito;
    pe peesquerdo;
    float cabecalado;
    float cabecacimabaxo;
    float angtronco;
    int fim;
    tponto posicao;

}humanoide;

typedef humanoide titemm;

typedef struct tcelulaa{
    titemm item;
    struct tcelulaa *prox;
}tcelulaa;

typedef struct {
    tcelulaa *primeiro;
    tcelulaa *ultimo;
    tcelulaa *atual;
}tfilaanima;

void iniciaaanima(tfilaanima* fila){
    fila->primeiro=NULL;
    fila->ultimo=NULL;
    fila->atual=NULL;
}
int insereanima(tfilaanima *fila,titemm p){
    if(fila->primeiro==NULL){
        fila->primeiro=(tcelulaa *) malloc(sizeof(tcelulaa));
        if(fila->primeiro==NULL)
            return 0;
        fila->primeiro->item=p;
        fila->primeiro->prox=NULL;
        fila->ultimo=fila->primeiro;
        fila->atual=fila->primeiro;
        return 1;
    }else{
        fila->ultimo->prox=(tcelulaa*) malloc(sizeof(tcelulaa));
        if(fila->ultimo->prox==NULL)
            return 0;
        fila->ultimo=fila->ultimo->prox;
        fila->ultimo->prox=NULL;
        fila->ultimo->item=p;
        return 1;
    }
}

titemm removeeanima(tfilaanima* fila){
    if(fila->primeiro!=NULL){
    titemm aux;
        if(fila->primeiro==fila->ultimo){
            aux=fila->primeiro->item;
            free(fila->primeiro);
            fila->primeiro=NULL;
            fila->ultimo=NULL;
            fila->atual=NULL;
            return aux;
        }else{
            aux=fila->primeiro->item;
            tcelulaa*aux2;
            aux2=fila->primeiro;
            fila->primeiro=fila->primeiro->prox;
            free(aux2);
            fila->atual=fila->primeiro;
            return aux;
        }

    }

}

void apagafilaanima(tfilaanima *fila){
    tcelulaa* aux;
    if(fila->primeiro!=NULL){
    while(fila->primeiro->prox!=NULL){
        aux=fila->primeiro;
        fila->primeiro=fila->primeiro->prox;
        free(aux);
    }
    free(fila->primeiro);
    fila->primeiro=NULL;
    fila->ultimo=NULL;
    fila->atual=NULL;
    }
}

titemm proximodafilaanima(tfilaanima *fila){
   titemm p;p.fim=1;
   p.bracodireito.superior=0;
    p.bracodireito.inferior=0;
    p.cabecacimabaxo=0;
    p.cabecalado=0;
    p.maodireitalado=0;
    p.angtronco=0;
    p.pedireito=0;
    p.pernadireita.inferior=0;
    p.pernaesquerda.superior=0;
    p.pernaesquerda.inferior=0;
    p.maoesquerdalado=0;
    p.maodireitacimabaixo=0;
    p.maoesquedacimabaixo=0;
    p.pernadireita.superiorlado=0;
    p.pernaesquerda.superiorlado=0;
    p.bracodireito.superiorgiro=0;
    p.bracodireito.superiorlado=0;
    p.bracoesquerdo.superiorgiro=0;
    p.bracoesquerdo.superiorlado=0;
    p.pernadireita.superior=0;
    p.bracoesquerdo.inferior=0;
    p.bracodireito.inferior=0;
    p.bracodireito.superior=0;
    p.bracoesquerdo.superior=0;
    p.peesquerdo=0;
    p.posicao.x=0;
    p.posicao.y=0;
    p.posicao.z=0;
    p.posicao.tempo=0;
   if(fila->atual!=NULL){
    tcelulaa* aux;
    aux=fila->atual;
    fila->atual=fila->atual->prox;
    return aux->item;
   }else{
    return p;
   }
}
void voltaproprimeirofilaanima(tfilaanima * fila){
    fila->atual=fila->primeiro;
}
//----------------------------------------


//fila para os clicks do mause------------------------------------


typedef tponto titem;

typedef struct tcelula{
    titem item;
    struct tcelula *prox;
}tcelula;

typedef struct {
    tcelula *primeiro;
    tcelula *ultimo;
    tcelula *atual;
    tcelula *atual2;
}tfila;

void iniciaa(tfila* fila){
    fila->primeiro=NULL;
    fila->ultimo=NULL;
    fila->atual=NULL;
    fila->atual2=NULL;
}
int insere(tfila *fila,titem p){
    if(fila->primeiro==NULL){
        fila->primeiro=(tcelula *) malloc(sizeof(tcelula));
        if(fila->primeiro==NULL)
            return 0;
        fila->primeiro->item=p;
        fila->primeiro->prox=NULL;
        fila->ultimo=fila->primeiro;
        fila->atual=fila->primeiro;
        fila->atual2=fila->primeiro;
        return 1;
    }else{
        fila->ultimo->prox=(tcelula*) malloc(sizeof(tcelula));
        if(fila->ultimo->prox==NULL)
            return 0;
        fila->ultimo=fila->ultimo->prox;
        fila->ultimo->prox=NULL;
        fila->ultimo->item=p;
        return 1;
    }
}

titem removee(tfila* fila){
    if(fila->primeiro!=NULL){
    titem aux;
        if(fila->primeiro==fila->ultimo){
            aux=fila->primeiro->item;
            free(fila->primeiro);
            fila->primeiro=NULL;
            fila->ultimo=NULL;
            fila->atual=NULL;
            fila->atual2=NULL;
            return aux;
        }else{
            aux=fila->primeiro->item;
            tcelula*aux2;
            aux2=fila->primeiro;
            fila->primeiro=fila->primeiro->prox;
            free(aux2);
            fila->atual=fila->primeiro;
            fila->atual2=fila->primeiro;
            return aux;
        }

    }

}

void apagafila(tfila *fila){
    tcelula* aux;
    if(fila->primeiro!=NULL){
    while(fila->primeiro->prox!=NULL){
        aux=fila->primeiro;
        fila->primeiro=fila->primeiro->prox;
        free(aux);
    }
    free(fila->primeiro);
    fila->primeiro=NULL;
    fila->ultimo=NULL;
    fila->atual=NULL;
    fila->atual2=NULL;
    }
}

titem proximodafila(tfila *fila){
    titem p;p.tempo=-1;
    if(fila->atual!=NULL){
    tcelula* aux;
    aux=fila->atual;
    fila->atual=fila->atual->prox;
    return aux->item;
    }else{
    return p;
    }
}

titem* proximodafilaatual2(tfila *fila){
    if(fila->atual2!=NULL){
    tcelula* aux;
    aux=fila->atual2;
    fila->atual2=fila->atual2->prox;
    return &aux->item;
    }else{
    return NULL;
    }
}

titem atualdafila(tfila *fila){
    if(fila->atual!=NULL){
        return fila->atual->item;
    }else{
    titem p;p.tempo=-1;
    return p;
    }
}

titem* atual2dafila(tfila *fila){
    if(fila->atual2!=NULL){
        return &fila->atual2->item;
    }else{
      return NULL;
    }

}

void voltaproprimeirofila(tfila * fila){
    fila->atual=fila->primeiro;
}

void voltaproprimeirofilaatual2(tfila*fila){
    fila->atual2=fila->primeiro;
}

//----------------------------------------

// humanoide

humanoide ser;

// camera
    double za,xa,ya,cxa,cza,theta;

    float angy,angx;

// menu
int oqueassetasfazem;

//janelas

int janelaprincipal,subjanela;
//posicao luz
GLfloat position[] = {10, 50 ,20, 0.0 } ;
    GLfloat position1[] = {0, 50 ,10 , 0.0 } ;

//desenha enxada ?
int mostraenxada;

//estadodojogo
int estadoanimacaoautomatica;
int estadodojogo;
// animacaoautomatica

tfilaanima animacaoauto;
tfilaanima anda;
tfilaanima planta;

//itens do jogo

tfila arvores,arvores2,solos,posicoesdomause;

//------------------------------------------------
void inicia3(){
glClearColor(0.0,0.0,0.0,0.0);
    ser.bracodireito.superior=0;
    ser.bracodireito.inferior=0;
    ser.cabecacimabaxo=0;
    ser.cabecalado=0;
    ser.maodireitalado=0;
    ser.angtronco=0;
    ser.pedireito=0;
    ser.peesquerdo=0;
    ser.pernadireita.inferior=0;
    ser.pernaesquerda.superior=0;
    ser.pernaesquerda.inferior=0;
    ser.maoesquerdalado=0;
    ser.maodireitacimabaixo=0;
    ser.maoesquedacimabaixo=0;
    ser.pernadireita.superiorlado=0;
    ser.pernaesquerda.superiorlado=0;
    ser.bracodireito.superiorgiro=0;
    ser.bracodireito.superiorlado=0;
    ser.bracoesquerdo.superiorgiro=0;
    ser.bracoesquerdo.superiorlado=0;
    ser.pernadireita.superior=0;
    ser.bracoesquerdo.inferior=0;
    ser.bracodireito.inferior=0;
    ser.fim=0;
    ser.bracodireito.superior=0;
    ser.bracoesquerdo.superior=0;

    ser.posicao.y=0;

    position[0] = 10;
    position[1] =50;
    position[2] = 20;
    position1[0] =0;
    position1[1] =50;
    position1[2] = 10;
    glLightfv( GL_LIGHT0, GL_POSITION, position );
    glLightfv( GL_LIGHT1, GL_POSITION, position1 );
    //ser.posicao.z=0;
    ser.posicao.tempo=0;
    mostraenxada=0;
    estadodojogo=0;
    angy=0;
    angx=0;
    oqueassetasfazem=0;

}
void inicia2(){
glClearColor(0.0,0.0,0.0,0.0);
    ser.bracodireito.superior=0;
    ser.bracodireito.inferior=0;
    ser.cabecacimabaxo=0;
    ser.cabecalado=0;
    ser.maodireitalado=0;
    ser.angtronco=0;
    ser.pedireito=0;
    ser.peesquerdo=0;
    ser.pernadireita.inferior=0;
    ser.pernaesquerda.superior=0;
    ser.pernaesquerda.inferior=0;
    ser.maoesquerdalado=0;
    ser.maodireitacimabaixo=0;
    ser.maoesquedacimabaixo=0;
    ser.pernadireita.superiorlado=0;
    ser.pernaesquerda.superiorlado=0;
    ser.bracodireito.superiorgiro=0;
    ser.bracodireito.superiorlado=0;
    ser.bracoesquerdo.superiorgiro=0;
    ser.bracoesquerdo.superiorlado=0;
    ser.pernadireita.superior=0;
    ser.bracoesquerdo.inferior=0;
    ser.bracodireito.inferior=0;
    ser.fim=0;
    ser.bracodireito.superior=0;
    ser.bracoesquerdo.superior=0;
    ser.posicao.raio=0;
    ser.posicao.x=0;
    ser.posicao.y=0;
    ser.posicao.z=0;
    ser.posicao.tempo=0;
    ser.posicao.largura2=0;
    mostraenxada=0;
    estadodojogo=0;
    angy=0;
    angx=0;
    position[0] = 10;
    position[1] =50;
    position[2] = -20;
    position1[0] =0;
    position1[1] =50;
    position1[2] = -10;
    glLightfv( GL_LIGHT0, GL_POSITION, position );
    glLightfv( GL_LIGHT1, GL_POSITION, position1 );
    oqueassetasfazem=0;
  za=-2;
    oqueassetasfazem=0;
    xa=1;ya=0;cxa=0;cza=0,theta=-26.565051*pi/180.0;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(xa,0,za,cxa,0,cza,0,1,0);
}

int carrega6Texturas(char* nome,GLuint *texture);
int carregaTexturaUnica(char* nome,GLuint *texture);
//declaracao das variaveis que vao guardar os identificadores das texturas;
GLuint textfazendero[6];
GLuint textChao[1];
GLuint textfazenderotronco[6];
GLuint textfazenderobraco[1];
GLuint textfazenderoperna[1];
GLuint textfazenderope[1];
GLuint textfazenderopesco[1];
GLuint textsolo[1];
GLuint textparedecasa[1];
GLuint texttelhadocasa[1];

void inicia(){
    iniciaa(&arvores);
    iniciaa(&arvores2);
    iniciaa(&solos);
    iniciaa(&posicoesdomause);

    iniciaaanima(&animacaoauto);
    iniciaaanima(&anda);
    iniciaaanima(&planta);

    glClearColor(0.0,0.0,0.0,0.0);
   carrega6Texturas("fazenderocabe",textfazendero);
   carrega6Texturas("fazenderotronco",textfazenderotronco);
   carregaTexturaUnica("textchao",textChao);
   carregaTexturaUnica("telhadocasa",texttelhadocasa);
   carregaTexturaUnica("paredecasa",textparedecasa);
   carregaTexturaUnica("fazenderocalca",textfazenderoperna);
   carregaTexturaUnica("fazenderobraco",textfazenderobraco);
   carregaTexturaUnica("fazenderope",textfazenderope);
   carregaTexturaUnica("fazenderocabe3",textfazenderopesco);
   carregaTexturaUnica("cantero",textsolo);
    estadoanimacaoautomatica=0;
    ser.bracodireito.superior=0;
    ser.bracodireito.inferior=0;
    ser.cabecacimabaxo=0;
    ser.cabecalado=0;
    ser.maodireitalado=0;
    ser.angtronco=0;
    ser.pedireito=0;
    ser.pernadireita.inferior=0;
    ser.pernaesquerda.superior=0;
    ser.pernaesquerda.inferior=0;
    ser.maoesquerdalado=0;
    ser.maodireitacimabaixo=0;
    ser.maoesquedacimabaixo=0;
    ser.pernadireita.superiorlado=0;
    ser.pernaesquerda.superiorlado=0;
    ser.bracodireito.superiorgiro=0;
    ser.bracodireito.superiorlado=0;
    ser.bracoesquerdo.superiorgiro=0;
    ser.bracoesquerdo.superiorlado=0;
    ser.pernadireita.superior=0;
    ser.bracoesquerdo.inferior=0;
    ser.bracodireito.inferior=0;
    ser.fim=0;
    ser.bracodireito.superior=0;
    ser.bracoesquerdo.superior=0;

    ser.posicao.x=0;
    ser.posicao.y=0;
    ser.posicao.z=0;
    ser.posicao.tempo=0;
    mostraenxada=0;
    estadodojogo=0;
    angy=0;
    angx=0;
    za=-2;
    oqueassetasfazem=0;
    xa=1;ya=0;cxa=0;cza=0,theta=-26.565051*pi/180.0;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(xa,0,za,cxa,0,cza,0,1,0);
    criaambiente();
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_LIGHTING);
     glEnable(GL_COLOR_MATERIAL);
     glEnable (GL_NORMALIZE);
     glEnable (GL_TEXTURE_2D);

}
void Cubocom6texturas(float size,GLint textura[]){
  static GLfloat normais[6][3] =
    {
      {-1.0, 0.0, 0.0},
      {0.0, 1.0, 0.0},
      {1.0, 0.0, 0.0},
      {0.0, -1.0, 0.0},
      {0.0, 0.0, 1.0},
      {0.0, 0.0, -1.0}
    };
    static GLint faces[6][4] =
    {
      {1, 2, 3, 0},
      {6, 7, 3, 2},
      {5, 6, 7, 4},
      {5, 4, 0, 1},
      {5, 6, 2, 1},
      {4, 7, 3, 0}
    };
    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

    for (i = 5; i >= 0; i--) {
      glBindTexture(GL_TEXTURE_2D, textura[i]);
      glBegin(GL_QUADS);
      glNormal3fv(&normais[i][0]);
      glTexCoord2f(1.0,0.0);glVertex3fv(&v[faces[i][0]][0]);
      glTexCoord2f(1.0,1.0);glVertex3fv(&v[faces[i][1]][0]);
      glTexCoord2f(0.0,1.0);glVertex3fv(&v[faces[i][2]][0]);
      glTexCoord2f(0.0,0.0);glVertex3fv(&v[faces[i][3]][0]);
      glEnd();
    }
    glBindTexture(GL_TEXTURE_2D,0);

}
void ChaocomTextura(float size,GLint textura[]){
  static GLfloat normais[6][3] =
    {
      {-1.0, 0.0, 0.0},
      {0.0, 1.0, 0.0},
      {1.0, 0.0, 0.0},
      {0.0, -1.0, 0.0},
      {0.0, 0.0, 1.0},
      {0.0, 0.0, -1.0}
    };
    static GLint faces[6][4] =
    {
      {1, 2, 3, 0},
      {6, 7, 3, 2},
      {5, 6, 7, 4},
      {5, 4, 0, 1},
      {5, 6, 2, 1},
      {4, 7, 3, 0}
    };
    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

    for (i = 5; i >= 0; i--) {
      glBindTexture(GL_TEXTURE_2D, textura[0]);
      glBegin(GL_QUADS);
      glNormal3fv(&normais[i][0]);
      glTexCoord2f(50.0,0.0);glVertex3fv(&v[faces[i][0]][0]);
      glTexCoord2f(50.0,50.0);glVertex3fv(&v[faces[i][1]][0]);
      glTexCoord2f(0.0,50.0);glVertex3fv(&v[faces[i][2]][0]);
      glTexCoord2f(0.0,0.0);glVertex3fv(&v[faces[i][3]][0]);
      glEnd();
    }
    glBindTexture(GL_TEXTURE_2D,0);

}

void CubocomUnicatextura(float size,GLint textura[]){
  static GLfloat normais[6][3] =
    {
      {-1.0, 0.0, 0.0},
      {0.0, 1.0, 0.0},
      {1.0, 0.0, 0.0},
      {0.0, -1.0, 0.0},
      {0.0, 0.0, 1.0},
      {0.0, 0.0, -1.0}
    };
    static GLint faces[6][4] =
    {
      {1, 2, 3, 0},
      {6, 7, 3, 2},
      {5, 6, 7, 4},
      {5, 4, 0, 1},
      {5, 6, 2, 1},
      {4, 7, 3, 0}
    };
    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

    for (i = 5; i >= 0; i--) {
      glBindTexture(GL_TEXTURE_2D, textura[0]);
      glBegin(GL_QUADS);
      glNormal3fv(&normais[i][0]);
      glTexCoord2f(1.0,0.0);glVertex3fv(&v[faces[i][0]][0]);
      glTexCoord2f(1.0,1.0);glVertex3fv(&v[faces[i][1]][0]);
      glTexCoord2f(0.0,1.0);glVertex3fv(&v[faces[i][2]][0]);
      glTexCoord2f(0.0,0.0);glVertex3fv(&v[faces[i][3]][0]);
      glEnd();
    }
    glBindTexture(GL_TEXTURE_2D,0);

}

int carrega6Texturas(char* nome,GLuint *texture){
 int i=0;
  char* ext=".png";
  char num[]="0";
  char result[200];

  for(i=0;i<6;i++){
    strcpy(result,"texturas\\");
    strcat(result,nome);
    num[0]=i+48;
    strcat(result,num);
    strcat(result,ext);
    texture[i] = SOIL_load_OGL_texture(result,SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y); //carrega textura com uma funcao da biblioteca SOIL

    if(texture[i] == 0)
    return 0;

  }

  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  return 1;
}

int carregaTexturaUnica(char* nome,GLuint *texture){

  char* ext=".png";
  char num[]="0";
  char result[200];

    strcpy(result,"texturas\\");
    strcat(result,nome);
    strcat(result,ext);
    texture[0] = SOIL_load_OGL_texture(result,SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y); //carrega textura com uma funcao da biblioteca SOIL

    if(texture[0] == 0)
    return 0;



  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  return 1;
}

void desenhahumanoide(){
glColor3f(1,1,1);
glPushMatrix();
    glColor3f(1,1,1);
    mostraenxada=ser.posicao.largura2;
    glTranslatef(ser.posicao.x*tambase,ser.posicao.y*tambase,ser.posicao.z*tambase);
    glRotatef(ser.posicao.raio,0,1,0);
    glPushMatrix();
        glTranslatef(0,-3*tambase,0);
        glRotatef(-ser.angtronco,1,0,0);
        glTranslatef(0,3*tambase,0);
        glPushMatrix();
            //tronco

            glScalef(3,6,1);
            Cubocom6texturas(tambase,textfazenderotronco);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,-0.375*tambase,0);
            glTranslatef(1.5*tambase,3*tambase,0);
            glColor3f(0.3607,0.2,0.0902);
            glutSolidSphere(0.375*tambase,20,20);

        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,-0.375*tambase,0);
            glTranslatef(-1.5*tambase,3*tambase,0);

            glutSolidSphere(0.375*tambase,20,20);
        glPopMatrix();
        glColor3f(1,1,1);
        //bracoDireito
        glPushMatrix();
            glTranslatef(0,-0.375*tambase,0);
            glTranslatef(1.75*tambase,3*tambase,0);
            glRotatef(ser.bracodireito.superiorgiro,0,1,0);
            glRotatef(ser.bracodireito.superiorlado,0,0,1);
            glRotatef(ser.bracodireito.superior,1,0,0);
            glTranslatef(0,0.375*tambase,0);

            glPushMatrix();
                glTranslatef(0.375*tambase,-1.5*tambase,0);
                glScalef(0.75,3,0.75);
                CubocomUnicatextura(tambase,textfazenderobraco);
            glPopMatrix();
        //esfera
            glPushMatrix();
            glColor3f(0.3607,0.2,0.0902);
                glTranslatef(0.375*tambase,-3*tambase,0);
                glutSolidSphere(0.375*tambase,20,20);
            glPopMatrix();
            glColor3f(1,1,1);

            glPushMatrix();
                glTranslatef(0,-3*tambase,0);
                //rotate em z colocar aqui
                glRotatef(ser.bracodireito.inferior,1,0,0);
                glPushMatrix();
                    glTranslatef(0.375*tambase,-1.5*tambase,0);
                    glScalef(0.75,3,0.75);
                    CubocomUnicatextura(tambase,textfazenderobraco);
                glPopMatrix();

                        glTranslatef(0.1875*tambase,-3*tambase,0);
                        glRotatef(ser.maodireitalado,0,0,1);
                        glRotatef(ser.maodireitacimabaixo,1,0,0);
                    glPushMatrix();

                        glTranslatef(0.125*tambase,-0.5*tambase,0);
                        glScalef(0.25,1,1);
                        CubocomUnicatextura(tambase,textfazenderopesco);
                    glPopMatrix();

                    //desenha enchada
                    if(mostraenxada==1){
                        glTranslatef(0,-0.7*tambase,0);
                        glTranslatef(-0.1*tambase,0.3*tambase,-1.2*tambase);
                        glPushMatrix();
                            glColor3f(0.5882,0.2941,0);
                            glRotatef(90,1,0,0);
                            glScalef(0.35,4,0.5);
                            glutSolidCube(tambase);
                        glPopMatrix();

                        glPushMatrix();
                            glColor3f(0.1254,0.1098,0.12156);
                            glTranslatef(0,-0.25*tambase,-2*tambase);
                            glTranslatef(0,0,-0.05*tambase);
                            glScalef(1.5,1,0.1);
                            glutSolidCube(tambase);

                        glPopMatrix();
                    }
                    glColor3f(1,1,1);

            glPopMatrix();


        glPopMatrix();


        //Braco esquerdo
        glPushMatrix();
            glTranslatef(0,-0.375*tambase,0);
            glTranslatef(-1.75*tambase,3*tambase,0);
            glRotatef(ser.bracoesquerdo.superiorgiro,0,1,0);
            glRotatef(ser.bracoesquerdo.superiorlado,0,0,1);
            glRotatef(ser.bracoesquerdo.superior,1,0,0);
            glTranslatef(0,0.375*tambase,0);

            glPushMatrix();
                glTranslatef(-0.375*tambase,-1.5*tambase,0);
                glScalef(0.75,3,0.75);
                CubocomUnicatextura(tambase,textfazenderobraco);
            glPopMatrix();
                //esfera
             glPushMatrix();
             glColor3f(0.3607,0.2,0.0902);
                glTranslatef(-0.375*tambase,-3*tambase,0);
                glutSolidSphere(0.375*tambase,20,20);
            glPopMatrix();
            glColor3f(1,1,1);
            glPushMatrix();
                glTranslatef(0,-3*tambase,0);
                //rotate em z colocar aqui
                glRotatef(ser.bracoesquerdo.inferior,1,0,0);
                glPushMatrix();
                    glTranslatef(-0.375*tambase,-1.5*tambase,0);
                    glScalef(0.75,3,0.75);
                    CubocomUnicatextura(tambase,textfazenderobraco);
                glPopMatrix();

                    glTranslatef(-0.1875*tambase,-3*tambase,0);
                    glRotatef(ser.maoesquerdalado,0,0,1);
                    glRotatef(ser.maoesquedacimabaixo,1,0,0);
                    glPushMatrix();

                        glTranslatef(-0.125*tambase,-0.5*tambase,0);
                        glScalef(0.25,1,1);
                        CubocomUnicatextura(tambase,textfazenderopesco);
                    glPopMatrix();
                    if(mostraenxada==2){
                        glTranslatef(0,-0.7*tambase,0);
                        glTranslatef(+0.1*tambase,0.3*tambase,-1.2*tambase);
                        glPushMatrix();
                            glColor3f(0.5882,0.2941,0);
                            glRotatef(90,1,0,0);
                            glScalef(0.35,4,0.5);
                            glutSolidCube(tambase);
                        glPopMatrix();

                        glPushMatrix();
                            glColor3f(0.1254,0.1098,0.12156);
                            glTranslatef(0,-0.25*tambase,-2*tambase);
                            glTranslatef(0,0,-0.05*tambase);
                            glScalef(1.5,1,0.1);
                            glutSolidCube(tambase);

                        glPopMatrix();
                    }
                    glColor3f(1,1,1);

            glPopMatrix();


        glPopMatrix();
         //cabeca

        glPushMatrix();
            glTranslatef(0,3.6*tambase,0);
            glRotatef(ser.cabecalado,0,1,0);
            glRotatef(ser.cabecacimabaxo,1,0,0);
            glTranslatef(0,1*tambase,-0.2*tambase);

            Cubocom6texturas(0.2,textfazendero);

        glPopMatrix();

        //pescoco

        glPushMatrix();
            glTranslatef(0,3*tambase,0);
            glTranslatef(0,0.35*tambase,0);
            glScalef(0.5,0.7,0.5);
            CubocomUnicatextura(tambase,textfazenderopesco);
        glPopMatrix();

    glPopMatrix();


    glPushMatrix();
    glColor3f(0.3607,0.2,0.0902);
            glTranslatef(-tambase,-3*tambase,0);
            glutSolidSphere(0.5*tambase,20,20);
        glPopMatrix();
        glColor3f(1,1,1);
    //perna direita
    glPushMatrix();
        glTranslatef(1.5*tambase,-3*tambase,0);
        glRotatef(ser.pernadireita.superiorlado,0,0,1);
        glRotatef(ser.pernadireita.superior,1,0,0);
        glPushMatrix();
            glTranslatef(-0.5*tambase,-2*tambase,0);
            glScalef(1,4,1);
            CubocomUnicatextura(tambase,textfazenderoperna);
        glPopMatrix();
        //esfera
         glPushMatrix();
         glColor3f(0.3607,0.2,0.0902);
            glTranslatef(-0.5*tambase,-4*tambase,0);
            glutSolidSphere(0.5*tambase,20,20);
        glPopMatrix();
        glColor3f(1,1,1);

        glPushMatrix();
            glTranslatef(0,-4*tambase,0);

            glRotatef(ser.pernadireita.inferior,1,0,0);
            glPushMatrix();
                glTranslatef(-0.5*tambase,-2*tambase,0);
                glScalef(1,4,1);
                CubocomUnicatextura(tambase,textfazenderoperna);
            glPopMatrix();

                glPushMatrix();
                    glTranslatef(0,-4*tambase,0);
                    glRotatef(ser.pedireito,1,0,0);
                    glTranslatef(-0.5*tambase,-0.25*tambase,-0.5*tambase);
                    glScalef(1,0.5,2);
                    CubocomUnicatextura(tambase,textfazenderope);
                glPopMatrix();

        glPopMatrix();


    glPopMatrix();





    //perna esquerda
    glPushMatrix();
    glColor3f(0.3607,0.2,0.0902);
            glTranslatef(tambase,-3*tambase,0);
            glutSolidSphere(0.5*tambase,20,20);
        glPopMatrix();
        glColor3f(1,1,1);
 glPushMatrix();
        glTranslatef(-1.5*tambase,-3*tambase,0);
        glRotatef(ser.pernaesquerda.superiorlado,0,0,1);
        glRotatef(ser.pernaesquerda.superior,1,0,0);
        glPushMatrix();
            glTranslatef(+0.5*tambase,-2*tambase,0);
            glScalef(1,4,1);
            CubocomUnicatextura(tambase,textfazenderoperna);
        glPopMatrix();
        //esfera
        glPushMatrix();
        glColor3f(0.3607,0.2,0.0902);
            glTranslatef(+0.5*tambase,-4*tambase,0);
            glutSolidSphere(0.5*tambase,20,20);
        glPopMatrix();
        glColor3f(1,1,1);

        glPushMatrix();
            glTranslatef(0,-4*tambase,0);

            glRotatef(ser.pernaesquerda.inferior,1,0,0);
            glPushMatrix();
                glTranslatef(+0.5*tambase,-2*tambase,0);
                glScalef(1,4,1);
                CubocomUnicatextura(tambase,textfazenderoperna);
            glPopMatrix();

                glPushMatrix();
                    glTranslatef(0,-4*tambase,0);
                    glRotatef(ser.peesquerdo,1,0,0);
                    glTranslatef(+0.5*tambase,-0.25*tambase,-0.5*tambase);
                    glScalef(1,0.5,2);
                    CubocomUnicatextura(tambase,textfazenderope);
                glPopMatrix();

        glPopMatrix();


    glPopMatrix();





glPopMatrix();
}

void desenhaarvore(titem parametros){

glPushMatrix();
    glTranslatef(parametros.x,parametros.y,parametros.z);
    glTranslatef(0,-1.15,0);
    glTranslatef(0,parametros.altura*tambase/2,0);
    glPushMatrix();
        //adicionar cor
        glColor3f(0.545,0.2705,0);
        glScalef(parametros.largura,parametros.altura,parametros.largura);
        glutSolidCube(tambase);
    glPopMatrix();


    glColor3f(0,1,0);
    glTranslatef(0,tambase*parametros.altura/2,0);
    glPushMatrix();

    glScalef(parametros.largura2,parametros.altura2/4,parametros.largura2);
    glRotatef(-90,1,0,0);
    glutSolidCone(tambase,tambase,20,20);
    glPopMatrix();

    glTranslatef(0,parametros.altura2*tambase/8,0);
    glPushMatrix();
    glScalef(parametros.largura2,parametros.altura2/2,parametros.largura2);
    glRotatef(-90,1,0,0);
    glutSolidCone(tambase,tambase,20,20);
    glPopMatrix();

    glTranslatef(0,-parametros.altura2*tambase/3,0);
    glPushMatrix();
    glScalef(parametros.largura2,parametros.altura2,parametros.largura2);
    glRotatef(-90,1,0,0);
    glutSolidCone(tambase,tambase,20,20);
    glPopMatrix();

glPopMatrix();

}

void desenhaarvore2(titem parametros){

glPushMatrix();
    glTranslatef(parametros.x,parametros.y,parametros.z);
    glTranslatef(0,-1.15,0);
    glTranslatef(0,parametros.altura*tambase/2,0);
    glPushMatrix();
        //adicionar cor
        glColor3f(0.545,0.2705,0);
        glScalef(parametros.largura,parametros.altura,parametros.largura);
        glutSolidCube(tambase);
    glPopMatrix();


    glColor3f(0,1,0);
    glTranslatef(0,tambase*parametros.altura,0);
    glPushMatrix();

    glScalef(parametros.raio,parametros.raio,parametros.raio);

    glutSolidSphere(tambase,20,20);
    glPopMatrix();

    glTranslatef(0,parametros.raio*tambase/4,0);
    glPushMatrix();
    glScalef(parametros.raio,parametros.raio,parametros.raio);

    glutSolidSphere(tambase,20,20);

    glPopMatrix();

    glTranslatef(0,parametros.raio*tambase/3,0);
    glPushMatrix();
    glScalef(parametros.raio,parametros.raio,parametros.raio);

    glutSolidSphere(tambase,20,20);
    glPopMatrix();

glPopMatrix();

}

void desenhachao(){

    glColor3f(0.7,1,0.7);
    glPushMatrix();
        glTranslatef(0,-1.16,0);
        glTranslatef(0,0.005,0);
        glScalef(1500,0.1,1500);
        ChaocomTextura(0.1,textChao);

    glPopMatrix();
}
void desenhaceu(){
glColor3f(0,0.7490,1);
    glPushMatrix();
        glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 60 );

        glScalef(700,700,700);
        glutSolidSphere(tambase,10,10);

    glPopMatrix();


}

void desenhaplanta(){
glColor3f(0.2,1,0.2);
    glPushMatrix();

        glRotatef(rand()%90,0,1,0);
        glTranslatef(0,-0.95,0);
        glPushMatrix();

            glScalef(0.35,4,0.35);
            glutSolidCube(tambase);
        glPopMatrix();

        glPushMatrix();
            glColor3f((rand()%10)/10.0,0,(rand()%10)/10.0);
            glTranslatef(0,0.2,0);
            glutSolidSphere(0.0175,5,5);
        glPopMatrix();
        glColor3f(0.2,1,0.2);

        glTranslatef(0.0525,-0.04,0);
         glPushMatrix();
            glScalef(1,0.1,1);
            glutSolidCube(tambase);
         glPopMatrix();


         glPushMatrix();
            glTranslatef(-0.095,0.015,0);
            glScalef(1,0.1,1);
            glutSolidCube(tambase);
         glPopMatrix();

        glTranslatef(0,0.2,0);
         glPushMatrix();
            glScalef(1,0.1,1);
            glutSolidCube(tambase);
         glPopMatrix();
         glTranslatef(-0.095,0.015,0);
         glPushMatrix();
            glScalef(1,0.1,1);
            glutSolidCube(tambase);
         glPopMatrix();



    glPopMatrix();

}

void desenhasolo(titem parametro){

  glColor3f(0.3,0.2,0.03);
    glPushMatrix();
        glTranslatef(parametro.x,parametro.y,parametro.z);
        glPushMatrix();
        glTranslatef(0,-1.15,0);

        glPushMatrix();
            glScalef(parametro.largura,0.5,parametro.largura);
            CubocomUnicatextura(tambase,textsolo);
        glPopMatrix();
        glPopMatrix();
        if(parametro.tempo==2)
            desenhaplanta();

    glPopMatrix();

}



void desenhacasa(titem parametross){

glColor3f(0.93334,0.81176,0.63137);//cordacasa
    glPushMatrix();
    glTranslatef(parametross.x,parametross.y,parametross.z);
    glPushMatrix();
        glTranslatef(0,-0.05,0);
        glPushMatrix();
            glTranslatef(0,0,-0.5);
            glPushMatrix();
                glTranslatef(0,0,0.5);
                glScalef(22,22,10);
                  CubocomUnicatextura(tambase,textparedecasa);
            glPopMatrix();

            glTranslatef(-0.55,0.275,-0.01);
            glPushMatrix();
                glColor3f(0.54118,0.16863,0.88627);
                glScalef(6,6,0.1);
                glutSolidCube(tambase);
            glPopMatrix();

            glColor3f(0.96078,0.96078,0.86275);//colocar cinza
            glTranslatef(0,0,-0.01);
            glPushMatrix();

                glScalef(0.5,6,0.1);
                glutSolidCube(tambase);
            glPopMatrix();

            glPushMatrix();
                glRotatef(90,1,0,0);
                glScalef(6,0.5,0.1);
                glutSolidCube(tambase);
            glPopMatrix();


        glPopMatrix();

        glColor3f(0.93334,0.81176,0.63137);//cordacasa


        glPushMatrix();
            glTranslatef(1.1,0,0);
            glPushMatrix();
                glTranslatef(0.01,-0.15,0);
                glColor3f(0.54509,0.27843,0.14902);//porta
                glScalef(0.1,19,5);
                glutSolidCube(tambase);
            glPopMatrix();
            glColor3f(0.96078,0.96078,0.86275);//um prata;
            glTranslatef(0,0,-0.2);
            glutSolidSphere(0.05,5,5);
        glPopMatrix();


        glTranslatef(0,1.1,0);
        glColor3f(0.6,0.3,0.11765);//cor do telhado
        glPushMatrix();
            glTranslatef(0,0.5,0);
            glTranslatef(0,0,-0.2668);
            glRotatef(27,1,0,0);
            glTranslatef(0,-0.15,0);
            glScalef(22,15,0.1);
          CubocomUnicatextura(tambase,texttelhadocasa);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,0.5,0);
            glTranslatef(0,0,+0.2668);
            glRotatef(-27,1,0,0);
            glTranslatef(0,-0.15,0);
            glScalef(22,15,0.1);
          CubocomUnicatextura(tambase,texttelhadocasa);
        glPopMatrix();

        glColor3f(0.93334,0.81176,0.63137);
        glBindTexture(GL_TEXTURE_2D, textparedecasa[0]);
        glPushMatrix();
            glTranslatef(-1.1,0,0);
            glBegin(GL_TRIANGLES);
                glNormal3f(-1,0,0);
              glTexCoord2f(1.0,0.0);  glVertex3f(0,0,0.5);
                glNormal3f(-1,0,0);
              glTexCoord2f(0.0,0.0);  glVertex3f(0,0,-0.5);
                glNormal3f(-1,0,0);
              glTexCoord2f(0.5,1.0);  glVertex3f(0,1,0);
            glEnd();


        glPopMatrix();
        glPushMatrix();
            glTranslatef(1.1,0,0);
            glBegin(GL_TRIANGLES);
                glNormal3f(1,0,0);
                glTexCoord2f(1.0,0.0);glVertex3f(0,0,0.5);
                glNormal3f(1,0,0);
                glTexCoord2f(0.0,0.0);glVertex3f(0,0,-0.5);
                glNormal3f(1,0,0);
                glTexCoord2f(0.5,1.0);glVertex3f(0,1,0);
            glEnd();

glBindTexture(GL_TEXTURE_2D,0);
        glPopMatrix();

    glPopMatrix();
    glPopMatrix();
}


void  rodaplanta(int a){
    if(estadodojogo==0){
    titemm aux;
     aux= proximodafilaanima(&planta);

        if(aux.fim!=1){
                ser= aux;
        glutTimerFunc(10,rodaplanta,0);

        desenha();
        }else{
            titem* aux=atual2dafila(&posicoesdomause);
            if(aux!=NULL)
            aux->tempo=2;
            apagafilaanima(&planta);
            glutPostRedisplay();
        }

    }
}

void criaanimacaoanda(double x,double z){


     int i;
    humanoide aux;
    aux.bracodireito.superior=0;
    aux.bracodireito.inferior=0;
    aux.cabecacimabaxo=0;
    aux.cabecalado=0;
    aux.maodireitalado=0;
    aux.angtronco=0;
    aux.pedireito=0;
    aux.pernadireita.inferior=0;
    aux.pernaesquerda.superior=0;
    aux.pernaesquerda.inferior=0;
    aux.maoesquerdalado=0;
    aux.maodireitacimabaixo=0;
    aux.maoesquedacimabaixo=0;
    aux.pernadireita.superiorlado=0;
    aux.pernaesquerda.superiorlado=0;
    aux.bracodireito.superiorgiro=0;
    aux.bracodireito.superiorlado=0;
    aux.bracoesquerdo.superiorgiro=0;
    aux.bracoesquerdo.superiorlado=0;
    aux.pernadireita.superior=0;
    aux.bracoesquerdo.inferior=0;
    aux.bracodireito.inferior=0;
    aux.peesquerdo=0;
    aux.bracodireito.superior=0;
    aux.bracoesquerdo.superior=0;
    aux.fim=0;
    aux.posicao.raio=0;
    aux.posicao.x=ser.posicao.x;
    aux.posicao.y=0;
    aux.posicao.z=ser.posicao.z;
    aux.posicao.tempo=0;

    float frames;

    frames=12.0;
    int j;


    double deltax=x-ser.posicao.x*0.1;
    double deltaxpos=deltax;
    double deltaz=+z-ser.posicao.z*0.1;
    double deltazpos=deltaz;
    double iniciax=ser.posicao.x;
    double iniciaz=ser.posicao.z;

    if(deltax<0)
        deltaxpos=-1*deltax;


    if(deltaz<0)
       deltazpos=-1*deltaz;

int foiantes=0;
aux.posicao.z=iniciaz;
    //deslocamento em x
    if(x>ser.posicao.x*0.1)
        aux.posicao.raio=-90;
    else if(x<ser.posicao.x*0.1)
        aux.posicao.raio=90;
if(0.364<deltaxpos){
    aux.pernadireita.inferior=aux.pernadireita.inferior-35.0;
    aux.bracodireito.superior=-5.0;

for(j=0;j*0.7044+(0.364)<deltaxpos;j++){
    for(i=0;i<frames;i++){

        aux.pernadireita.superior=aux.pernadireita.superior+30.0/frames;

        aux.bracodireito.superior=aux.bracodireito.superior-5.0/frames;
        aux.pernaesquerda.superior=aux.pernaesquerda.superior-15/frames;
        aux.peesquerdo=aux.peesquerdo+15/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+15/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior+15/frames;

        //deslocamento em y
        aux.posicao.y=-8+8*cos(((i+1)*(15.0/frames))*pi/180.0);

        //deslocamento em x
        if(deltax>0)
        aux.posicao.x=iniciax+8*sin(((i+1)*(15.0/frames))*pi/180.0);
        else
            aux.posicao.x=iniciax-8*sin(((i+1)*(15.0/frames))*pi/180.0);

        insereanima(&anda,aux);
    }
    iniciax=aux.posicao.x;
    for(i=0;i<frames/2;i++){
        aux.pernadireita.superior=aux.pernadireita.superior-8.725/(frames/2);
        aux.pernadireita.inferior=aux.pernadireita.inferior+13.725/(frames/2);
        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior-7.5/(frames/2);
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior-7.5/(frames/2);
        aux.bracodireito.superior=aux.bracodireito.superior+5.0/(frames/2);

                        insereanima(&anda,aux);

    }

    for(i=0;i<frames;i++){
        aux.pernadireita.superior=aux.pernadireita.superior-21.275/frames;
        aux.pernadireita.inferior=aux.pernadireita.inferior+21.274/frames;
        aux.bracodireito.superior=aux.bracodireito.superior+5.0/frames;
         if(deltax>0)
        aux.posicao.x=iniciax+4*sin(((i+1)*(21.275/frames))*pi/180.0);
        else
            aux.posicao.x=iniciax-4*sin(((i+1)*(21.275/frames))*pi/180.0);

        //deslocamento em y
        aux.posicao.y=-8+8*cos((15.0-((i+1)*(15.0/frames)))*pi/180.0);

        aux.pernaesquerda.superior=aux.pernaesquerda.superior+15/frames;
        aux.pernaesquerda.inferior=aux.pernaesquerda.inferior-35/frames;
        aux.peesquerdo=aux.peesquerdo-15/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior-12.5/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior-7.5/frames;

                        insereanima(&anda,aux);

    }
    if((j+1)*0.7044<deltaxpos){
    iniciax=aux.posicao.x;
    for(i=0;i<frames;i++){
        aux.pernaesquerda.superior=aux.pernaesquerda.superior+30.0/frames;


        aux.pernadireita.superior=aux.pernadireita.superior-15/frames;
        aux.pedireito=aux.pedireito+15/frames;

        aux.bracodireito.superior=aux.bracodireito.superior+15/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior+15/frames;
        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior-5.0/frames;
        //deslocamento em y
        aux.posicao.y=-8+8*cos(((i+1)*(15.0/frames))*pi/180.0);

        //deslocamento em x
        if(deltax>0)
        aux.posicao.x=iniciax+8*sin(((i+1)*(15.0/frames))*pi/180.0);
        else
            aux.posicao.x=iniciax-8*sin(((i+1)*(15.0/frames))*pi/180.0);

        insereanima(&anda,aux);
    }
    iniciax=aux.posicao.x;
    for(i=0;i<frames/2;i++){
        aux.pernaesquerda.superior=aux.pernaesquerda.superior-8.725/(frames/2);
        aux.pernaesquerda.inferior=aux.pernaesquerda.inferior+13.725/(frames/2);
        aux.bracodireito.superior=aux.bracodireito.superior-7.5/(frames/2);
        aux.bracodireito.inferior=aux.bracodireito.inferior-7.5/(frames/2);
        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+5.0/(frames/2);
                        insereanima(&anda,aux);

    }
    for(i=0;i<frames;i++){
        aux.pernaesquerda.superior=aux.pernaesquerda.superior-21.275/frames;
        aux.pernaesquerda.inferior=aux.pernaesquerda.inferior+21.274/frames;
        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+5.0/frames;
         if(deltax>0)
        aux.posicao.x=iniciax+4*sin(((i+1)*(21.275/frames))*pi/180.0);
        else
            aux.posicao.x=iniciax-4*sin(((i+1)*(21.275/frames))*pi/180.0);

        //deslocamento em y
        aux.posicao.y=-8+8*cos((15.0-((i+1)*(15.0/frames)))*pi/180.0);

        aux.pernadireita.superior=aux.pernadireita.superior+15/frames;
        aux.pernadireita.inferior=aux.pernadireita.inferior-35/frames;
        aux.pedireito=aux.pedireito-15/frames;

        aux.bracodireito.superior=aux.bracodireito.superior-12.5/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior-7.5/frames;

                        insereanima(&anda,aux);

    }
    iniciax=aux.posicao.x;
}else{
  for(i=0;i<frames;i++){
    aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+10/frames;
    aux.bracodireito.superior=aux.bracodireito.superior-5/frames;
    aux.pernaesquerda.inferior=aux.pernaesquerda.inferior + 35/frames;
    insereanima(&anda,aux);
  }
  foiantes=1;
  break;}
}
if(foiantes==0){
for(i=0;i<frames;i++){

       aux.pernadireita.inferior=aux.pernadireita.inferior+35/frames;
                               insereanima(&anda,aux);

   }
 }
}

   //-------------------------------------agora pra z
foiantes=0;
       if(z>ser.posicao.z*0.1)
        aux.posicao.raio=-180;
    else if(z<ser.posicao.z*0.1)
        aux.posicao.raio=0;
    if(0.364<deltazpos){
    aux.pernadireita.inferior=aux.pernadireita.inferior-35.0;
    aux.bracodireito.superior=-5.0;
iniciaz=ser.posicao.z;
for(j=0;j*0.7044+(0.364)<deltazpos;j++){
    for(i=0;i<frames;i++){

        aux.pernadireita.superior=aux.pernadireita.superior+30.0/frames;

        aux.bracodireito.superior=aux.bracodireito.superior-5.0/frames;
        aux.pernaesquerda.superior=aux.pernaesquerda.superior-15/frames;
        aux.peesquerdo=aux.peesquerdo+15/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+15/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior+15/frames;

        //deslocamento em y
        aux.posicao.y=-8+8*cos(((i+1)*(15.0/frames))*pi/180.0);

        //deslocamento em x
        if(deltaz>0)
        aux.posicao.z=iniciaz+8*sin(((i+1)*(15.0/frames))*pi/180.0);
        else
            aux.posicao.z=iniciaz-8*sin(((i+1)*(15.0/frames))*pi/180.0);

        insereanima(&anda,aux);
    }
    iniciaz=aux.posicao.z;
    for(i=0;i<frames/2;i++){
        aux.pernadireita.superior=aux.pernadireita.superior-8.725/(frames/2);
        aux.pernadireita.inferior=aux.pernadireita.inferior+13.725/(frames/2);
        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior-7.5/(frames/2);
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior-7.5/(frames/2);
        aux.bracodireito.superior=aux.bracodireito.superior+5.0/(frames/2);

                        insereanima(&anda,aux);

    }

    for(i=0;i<frames;i++){
        aux.pernadireita.superior=aux.pernadireita.superior-21.275/frames;
        aux.pernadireita.inferior=aux.pernadireita.inferior+21.274/frames;
        aux.bracodireito.superior=aux.bracodireito.superior+5.0/frames;
         if(deltaz>0)
        aux.posicao.z=iniciaz+4*sin(((i+1)*(21.275/frames))*pi/180.0);
        else
            aux.posicao.z=iniciaz-4*sin(((i+1)*(21.275/frames))*pi/180.0);

        //deslocamento em y
        aux.posicao.y=-8+8*cos((15.0-((i+1)*(15.0/frames)))*pi/180.0);

        aux.pernaesquerda.superior=aux.pernaesquerda.superior+15/frames;
        aux.pernaesquerda.inferior=aux.pernaesquerda.inferior-35/frames;
        aux.peesquerdo=aux.peesquerdo-15/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior-12.5/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior-7.5/frames;

                        insereanima(&anda,aux);

    }
    if((j+1)*0.7044<deltazpos){
    iniciaz=aux.posicao.z;
    for(i=0;i<frames;i++){
        aux.pernaesquerda.superior=aux.pernaesquerda.superior+30.0/frames;


        aux.pernadireita.superior=aux.pernadireita.superior-15/frames;
        aux.pedireito=aux.pedireito+15/frames;

        aux.bracodireito.superior=aux.bracodireito.superior+15/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior+15/frames;
        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior-5.0/frames;
        //deslocamento em y
        aux.posicao.y=-8+8*cos(((i+1)*(15.0/frames))*pi/180.0);

        //deslocamento em x
        if(deltaz>0)
        aux.posicao.z=iniciaz+8*sin(((i+1)*(15.0/frames))*pi/180.0);
        else
            aux.posicao.z=iniciaz-8*sin(((i+1)*(15.0/frames))*pi/180.0);

        insereanima(&anda,aux);
    }
    iniciaz=aux.posicao.z;
    for(i=0;i<frames/2;i++){
        aux.pernaesquerda.superior=aux.pernaesquerda.superior-8.725/(frames/2);
        aux.pernaesquerda.inferior=aux.pernaesquerda.inferior+13.725/(frames/2);
        aux.bracodireito.superior=aux.bracodireito.superior-7.5/(frames/2);
        aux.bracodireito.inferior=aux.bracodireito.inferior-7.5/(frames/2);
        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+5.0/(frames/2);
                        insereanima(&anda,aux);

    }
    for(i=0;i<frames;i++){
        aux.pernaesquerda.superior=aux.pernaesquerda.superior-21.275/frames;
        aux.pernaesquerda.inferior=aux.pernaesquerda.inferior+21.274/frames;
        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+5.0/frames;
         if(deltaz>0)
        aux.posicao.z=iniciaz+4*sin(((i+1)*(21.275/frames))*pi/180.0);
        else
            aux.posicao.z=iniciaz-4*sin(((i+1)*(21.275/frames))*pi/180.0);

        //deslocamento em y
        aux.posicao.y=-8+8*cos((15.0-((i+1)*(15.0/frames)))*pi/180.0);

        aux.pernadireita.superior=aux.pernadireita.superior+15/frames;
        aux.pernadireita.inferior=aux.pernadireita.inferior-35/frames;
        aux.pedireito=aux.pedireito-15/frames;

        aux.bracodireito.superior=aux.bracodireito.superior-12.5/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior-7.5/frames;

                        insereanima(&anda,aux);

    }
    iniciaz=aux.posicao.z;
}else{
  for(i=0;i<frames;i++){
    aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+10/frames;
    aux.bracodireito.superior=aux.bracodireito.superior-5/frames;
    aux.pernaesquerda.inferior=aux.pernaesquerda.inferior + 35/frames;
    insereanima(&anda,aux);
  }
  foiantes=1;
  break;}
}
if(foiantes==0){
for(i=0;i<frames;i++){

       aux.pernadireita.inferior=aux.pernadireita.inferior+35/frames;
                               insereanima(&anda,aux);

   }

}
    }

}
void criaanimacaoplanta(){
    int i;
    humanoide aux;
    aux.bracodireito.superior=0;
    aux.bracodireito.inferior=0;
    aux.cabecacimabaxo=0;
    aux.cabecalado=0;
    aux.maodireitalado=0;
    aux.angtronco=0;
    aux.pedireito=0;
    aux.pernadireita.inferior=0;
    aux.pernaesquerda.superior=0;
    aux.pernaesquerda.inferior=0;
    aux.maoesquerdalado=0;
    aux.maodireitacimabaixo=0;
    aux.maoesquedacimabaixo=0;
    aux.pernadireita.superiorlado=0;
    aux.pernaesquerda.superiorlado=0;
    aux.bracodireito.superiorgiro=0;
    aux.bracodireito.superiorlado=0;
    aux.bracoesquerdo.superiorgiro=0;
    aux.bracoesquerdo.superiorlado=0;
    aux.pernadireita.superior=0;
    aux.bracoesquerdo.inferior=0;
    aux.bracodireito.inferior=0;
    aux.peesquerdo=0;
    aux.bracodireito.superior=0;
    aux.bracoesquerdo.superior=0;
    aux.fim=0;
    aux.posicao.raio=ser.posicao.raio;
    aux.posicao.x=ser.posicao.x;
    aux.posicao.y=0;
    aux.posicao.z=ser.posicao.z;
    aux.posicao.tempo=0;

    float frames=10.0;
    int j;

    for(i=0;i<frames;i++){
        //agacha
        aux.pernadireita.superior=aux.pernadireita.superior+75.0/frames;
        aux.pernadireita.inferior=aux.pernadireita.inferior-150.0/frames;
        aux.pedireito=aux.pedireito+75.0/frames;
        aux.angtronco=aux.angtronco+15.0/frames;
        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+10/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior+10/frames;
        //faiz a translacao
        aux.posicao.y=-8+8*cos((i+1)*(75.0/frames)*pi/180.0);

        aux.pernaesquerda.superior=aux.pernaesquerda.superior+75.0/frames;
        aux.pernaesquerda.inferior=aux.pernaesquerda.inferior-150.0/frames;
        aux.peesquerdo=aux.peesquerdo+75.0/frames;

    //-----------------------------
        aux.bracodireito.superior=aux.bracodireito.superior+10/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior+90/frames;


        insereanima(&planta,aux);
    }
    insereanima(&planta,aux);
    aux.posicao.largura2=1;
    insereanima(&planta,aux);

    for(j=0;j<4;j++){
    for(i=0;i<frames;i++){
        aux.bracodireito.inferior=aux.bracodireito.inferior-70/frames;
        insereanima(&planta,aux);
    }
    for(i=0;i<frames;i++){
        aux.bracodireito.inferior=aux.bracodireito.inferior+70/frames;
        insereanima(&planta,aux);
    }
    }

    for(i=0;i<frames;i++){
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior+80/frames;
        insereanima(&planta,aux);
    }
    for(i=0;i<frames;i++){
        aux.maoesquerdalado=aux.maoesquerdalado+70/frames;
        insereanima(&planta,aux);
    }
    for(j=0;j<3;j++){
            for(i=0;i<frames;i++){
                 aux.maoesquerdalado=aux.maoesquerdalado-110/frames;
                insereanima(&planta,aux);
            }
            for(i=0;i<frames;i++){
                 aux.maoesquerdalado=aux.maoesquerdalado+110/frames;
                insereanima(&planta,aux);
            }
    }
    for(i=0;i<frames;i++){
        aux.maoesquerdalado=aux.maoesquerdalado-70/frames;
        insereanima(&planta,aux);
    }

   for(i=0;i<frames;i++){
        //agacha
        aux.pernadireita.superior=aux.pernadireita.superior-75.0/frames;
        aux.pernadireita.inferior=aux.pernadireita.inferior+150.0/frames;
        aux.pedireito=aux.pedireito-75.0/frames;
        //faiz a translacao
        aux.posicao.y=-8+8*cos((75-(i+1)*(75.0/frames))*pi/180.0);

        aux.pernaesquerda.superior=aux.pernaesquerda.superior-75.0/frames;
        aux.pernaesquerda.inferior=aux.pernaesquerda.inferior+150.0/frames;
        aux.peesquerdo=aux.peesquerdo-75.0/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior-10/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior-90/frames;
        aux.bracodireito.superior=aux.bracodireito.superior-10/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior-90/frames;

                aux.angtronco=aux.angtronco-15.0/frames;


        insereanima(&planta,aux);

    }
    aux.posicao.largura2=0;
    insereanima(&planta,aux);
}


void criaambiente(){
    int i,numdearvores1=5,numdearvores2=5;
    titem aux;
    aux.largura=4; aux.altura=24;aux.largura2=24;aux.altura2=48;
    aux.y=0;aux.tempo=0;aux.raio=20;
    srand(10007);

    for(i=0;i<numdearvores1;i++){
            aux.x=(rand()%50)-50;
            aux.z=(rand()%45)+5;
            insere(&arvores,aux);
    }
    for(i=0;i<numdearvores2;i++){
            aux.x=(rand()%50)-50;
            aux.z=(rand()%45)+5;
            insere(&arvores2,aux);
    }

    for(i=0;i<numdearvores1;i++){
            aux.x=(rand()%50)-50;
            aux.z=(rand()%45)-50;
            insere(&arvores,aux);
    }
    for(i=0;i<numdearvores2;i++){
            aux.x=(rand()%50)-50;
            aux.z=(rand()%45)-50;
            insere(&arvores2,aux);
    }
    //-----------

    for(i=0;i<numdearvores1;i++){
            aux.x=(rand()%50)+30;
            aux.z=(rand()%45)-3;
            insere(&arvores,aux);
    }
    for(i=0;i<numdearvores2;i++){
            aux.x=(rand()%50)+30;
            aux.z=(rand()%45)-3;
            insere(&arvores2,aux);
    }

    for(i=0;i<numdearvores1;i++){
            aux.x=(rand()%50)+30;
            aux.z=(rand()%45)+30;
            insere(&arvores,aux);
    }
    for(i=0;i<numdearvores2;i++){
            aux.x=(rand()%50)+30;
            aux.z=(rand()%45)+30;
            insere(&arvores2,aux);
    }

    for(i=0;i<numdearvores1;i++){
            aux.x=(rand()%50)+20;
            aux.z=(rand()%45)-30;
            insere(&arvores,aux);
    }
    for(i=0;i<numdearvores2;i++){
            aux.x=(rand()%50)+20;
            aux.z=(rand()%45)-30;
            insere(&arvores2,aux);
    }

    aux.x=0.4;
    aux.y=0;
    aux.z=0.4;
    aux.tempo=2;
    aux.largura=8;
    for(i=0;i<10;i++){
        aux.x=aux.x+0.5;
        insere(&solos,aux);
        aux.z=aux.z+0.5;
        insere(&solos,aux);
        aux.z=aux.z+0.5;
        insere(&solos,aux);
        aux.z=aux.z+0.5;
        insere(&solos,aux);
        aux.z=aux.z+0.5;
        insere(&solos,aux);
        aux.z=aux.z-2.0;
    }

    aux.x=0.4;
    aux.y=0;
    aux.z=3.8;
    aux.tempo=2;
    aux.largura=8;
    for(i=0;i<10;i++){
        aux.x=aux.x+0.5;
        insere(&solos,aux);
        aux.z=aux.z+0.5;
        insere(&solos,aux);
        aux.z=aux.z+0.5;
        insere(&solos,aux);
        aux.z=aux.z+0.5;
        insere(&solos,aux);
        aux.z=aux.z+0.5;
        insere(&solos,aux);
        aux.z=aux.z-2.0;
    }
    aux.x=0.4;
    aux.y=0;
    aux.z=7.5;
    aux.tempo=2;
    aux.largura=8;
    for(i=0;i<10;i++){
        aux.x=aux.x+0.5;
        insere(&solos,aux);
        aux.z=aux.z+0.5;
        insere(&solos,aux);
        aux.z=aux.z+0.5;
        insere(&solos,aux);
        aux.z=aux.z+0.5;
        insere(&solos,aux);
        aux.z=aux.z+0.5;
        insere(&solos,aux);
        aux.z=aux.z-2.0;
    }
    aux.x=-0.981687;
    aux.z=3.221200;
    insere(&solos,aux);

    aux.x=-1.317674;
    aux.z=3.058875;
    insere(&solos,aux);

    aux.x=-1.619865;
    aux.z=3.445374;
    insere(&solos,aux);

    aux.x=-1.854489;
    aux.z=3.225374;
    insere(&solos,aux);

    aux.x=-2.161338;
    aux.z=3.097190;
    insere(&solos,aux);

    aux.x=-2.554346;
    aux.z=3.254736;
    insere(&solos,aux);

    aux.x=-3.042595;
    aux.z=3.377130;
    insere(&solos,aux);

    aux.x=-1.719773;
    aux.z=2.976987;
    insere(&solos,aux);

    aux.x=-2.863410;
    aux.z=3.208781;
    insere(&solos,aux);

    aux.x=-3.336220;
    aux.z=3.647461;
    insere(&solos,aux);

    aux.x=-3.271369;
    aux.z=4.167013;
    insere(&solos,aux);

    aux.x=-3.295493;
    aux.z=4.422232;
    insere(&solos,aux);

    aux.x=-1.146440;
    aux.z=4.659145;
    insere(&solos,aux);

    aux.x=-1.545807;
    aux.z=4.679392;
    insere(&solos,aux);

    aux.x=-1.945241;
    aux.z=4.704529;
    insere(&solos,aux);

    aux.x=-2.319798;
    aux.z=4.689934;
    insere(&solos,aux);

    aux.x=-2.625922;
    aux.z=4.685446;
    insere(&solos,aux);

    aux.x=-2.908730;
    aux.z=4.704473;
    insere(&solos,aux);

    aux.x=-3.238203;
    aux.z=4.698647;
    insere(&solos,aux);

    aux.x=-3.361828;
    aux.z=3.917706;
    insere(&solos,aux);

    aux.x=-1.229808;
    aux.z=4.892498;
    insere(&solos,aux);

    aux.x=-1.739836;
    aux.z=4.853353;
    insere(&solos,aux);

    aux.x=-2.162704;
    aux.z=4.905857;
    insere(&solos,aux);

    aux.x=-2.491581;
    aux.z=4.804374;
    insere(&solos,aux);

    aux.x=-3.387214;
    aux.z=4.574269;
    insere(&solos,aux);

    aux.x=-3.306363;
    aux.z=3.417534;
    insere(&solos,aux);

}


void crianimacaoauto(){
    int i;
    humanoide aux;
    aux.bracodireito.superior=0;
    aux.bracodireito.inferior=0;
    aux.cabecacimabaxo=0;
    aux.cabecalado=0;
    aux.maodireitalado=0;
    aux.angtronco=0;
    aux.pedireito=0;
    aux.pernadireita.inferior=0;
    aux.pernaesquerda.superior=0;
    aux.pernaesquerda.inferior=0;
    aux.maoesquerdalado=0;
    aux.maodireitacimabaixo=0;
    aux.maoesquedacimabaixo=0;
    aux.pernadireita.superiorlado=0;
    aux.pernaesquerda.superiorlado=0;
    aux.bracodireito.superiorgiro=0;
    aux.bracodireito.superiorlado=0;
    aux.bracoesquerdo.superiorgiro=0;
    aux.bracoesquerdo.superiorlado=0;
    aux.pernadireita.superior=0;
    aux.bracoesquerdo.inferior=0;
    aux.bracodireito.inferior=0;
    aux.peesquerdo=0;
    aux.bracodireito.superior=0;
    aux.bracoesquerdo.superior=0;
    aux.fim=0;
    aux.posicao.x=ser.posicao.x;
    aux.posicao.y=0;
    aux.posicao.raio=ser.posicao.raio;
    aux.posicao.z=ser.posicao.z;
    aux.posicao.tempo=0;

    float frames=10.0;
    //abaixa o tronco
    for(i=0;i<frames;i++){
        aux.angtronco=aux.angtronco+40.0/frames;
        insereanima(&animacaoauto,aux);
    }
    //levanta o tronco
    for(i=0;i<frames;i++){
        aux.angtronco=aux.angtronco-40/frames;
        insereanima(&animacaoauto,aux);
    }
    // mexe bracos


    for(i=0;i<frames;i++){
        aux.bracodireito.superior=aux.bracodireito.superior+90.0/frames;

        aux.bracodireito.superiorlado=aux.bracodireito.superiorlado+90.0/frames;
        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro-90.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior+90.0/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+90.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro +60.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior+90.0/frames;
        insereanima(&animacaoauto,aux);
    }

    for(i=0;i<frames;i++){
        aux.bracodireito.superior=aux.bracodireito.superior-90.0/frames;

        aux.bracodireito.superiorlado=aux.bracodireito.superiorlado-90.0/frames;
        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro+90.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior-90.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior-90.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro -60.0/frames;
        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior-90.0/frames;
        insereanima(&animacaoauto,aux);
    }


    for(i=0;i<frames;i++){
        aux.bracodireito.superior=aux.bracodireito.superior+90.0/frames;
        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro -60.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior+90.0/frames;

        aux.cabecalado=aux.cabecalado+60.0/frames;
        aux.cabecacimabaxo=aux.cabecacimabaxo+10.0/frames;
        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+90.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro -60.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior+90.0/frames;
        insereanima(&animacaoauto,aux);

    }

    for(i=0;i<frames;i++){

        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro +120.0/frames;
        aux.cabecalado=aux.cabecalado-120.0/frames;
        if(i<30)
        aux.cabecacimabaxo=aux.cabecacimabaxo-10.0/frames;
        else
            aux.cabecacimabaxo=aux.cabecacimabaxo+10.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro +120.0/frames;

        insereanima(&animacaoauto,aux);

    }

    for(i=0;i<frames;i++){
        aux.bracodireito.superior=aux.bracodireito.superior-90.0/frames;
        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro -60.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior-90.0/frames;

        aux.cabecalado=aux.cabecalado+60.0/frames;
        aux.cabecacimabaxo=aux.cabecacimabaxo-10.0/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior-90.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro -60.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior-90.0/frames;
        insereanima(&animacaoauto,aux);

    }

    // o avatar agacha
    for(i=0;i<frames;i++){
        //agacha
        aux.pernadireita.superior=aux.pernadireita.superior+50.0/frames;
        aux.pernadireita.inferior=aux.pernadireita.inferior-100.0/frames;
        aux.pedireito=aux.pedireito+50.0/frames;
        //faiz a translacao
        aux.posicao.y=-8+8*cos((i+1)*(50.0/frames)*pi/180.0);

        aux.pernaesquerda.superior=aux.pernaesquerda.superior+50.0/frames;
        aux.pernaesquerda.inferior=aux.pernaesquerda.inferior-100.0/frames;
        aux.peesquerdo=aux.peesquerdo+50.0/frames;

    //-----------------------------

        aux.bracodireito.superior=aux.bracodireito.superior+90.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior+90.0/frames;
        aux.bracodireito.superiorlado=aux.bracodireito.superiorlado+75.0/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+90.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior+90.0/frames;
        aux.bracoesquerdo.superiorlado=aux.bracoesquerdo.superiorlado-75.0/frames;
        insereanima(&animacaoauto,aux);
    }

   for(i=0;i<frames;i++){
        //agacha
        aux.pernadireita.superior=aux.pernadireita.superior-50.0/frames;
        aux.pernadireita.inferior=aux.pernadireita.inferior+100.0/frames;
        aux.pedireito=aux.pedireito-50.0/frames;
        //faiz a translacao
        aux.posicao.y=-8+8*cos((50.0-(i+1)*(50.0/frames))*pi/180.0);

        aux.pernaesquerda.superior=aux.pernaesquerda.superior-50.0/frames;
        aux.pernaesquerda.inferior=aux.pernaesquerda.inferior+100.0/frames;
        aux.peesquerdo=aux.peesquerdo-50.0/frames;

    //-----------------------------

        aux.bracodireito.superior=aux.bracodireito.superior-90.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior-90.0/frames;
        aux.bracodireito.superiorlado=aux.bracodireito.superiorlado-75.0/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior-90.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior-90.0/frames;
        aux.bracoesquerdo.superiorlado=aux.bracoesquerdo.superiorlado+75.0/frames;
        insereanima(&animacaoauto,aux);
    }
    //-------------------------------------------------------------------------------------------------

    for(i=0;i<frames;i++){
        aux.bracodireito.superior=aux.bracodireito.superior+90.0/frames;

        aux.bracodireito.superiorlado=aux.bracodireito.superiorlado+90.0/frames;
        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro-90.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior+90.0/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+90.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro +60.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior+90.0/frames;
        insereanima(&animacaoauto,aux);
    }

    for(i=0;i<frames;i++){
        aux.bracodireito.superior=aux.bracodireito.superior-90.0/frames;

        aux.bracodireito.superiorlado=aux.bracodireito.superiorlado-90.0/frames;
        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro+90.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior-90.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior-90.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro -60.0/frames;
        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior-90.0/frames;
        insereanima(&animacaoauto,aux);
    }


    for(i=0;i<frames;i++){
        aux.bracodireito.superior=aux.bracodireito.superior+90.0/frames;
        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro -60.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior+90.0/frames;

        aux.cabecalado=aux.cabecalado+60.0/frames;
        aux.cabecacimabaxo=aux.cabecacimabaxo+10.0/frames;
        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+90.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro -60.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior+90.0/frames;
        insereanima(&animacaoauto,aux);

    }

    for(i=0;i<frames;i++){

        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro +120.0/frames;
        aux.cabecalado=aux.cabecalado-120.0/frames;
        if(i<frames/2)
        aux.cabecacimabaxo=aux.cabecacimabaxo-10.0/frames;
        else
            aux.cabecacimabaxo=aux.cabecacimabaxo+10.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro +120.0/frames;

        insereanima(&animacaoauto,aux);

    }

    for(i=0;i<frames;i++){
        aux.bracodireito.superior=aux.bracodireito.superior-90.0/frames;
        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro -60.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior-90.0/frames;

        aux.cabecalado=aux.cabecalado+60.0/frames;
        aux.cabecacimabaxo=aux.cabecacimabaxo-10.0/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior-90.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro -60.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior-90.0/frames;
        insereanima(&animacaoauto,aux);

    }

    // o avatar agacha
    for(i=0;i<frames;i++){
        //agacha
        aux.pernadireita.superior=aux.pernadireita.superior+50.0/frames;
        aux.pernadireita.inferior=aux.pernadireita.inferior-100.0/frames;
        aux.pedireito=aux.pedireito+50.0/frames;
        aux.pernadireita.superiorlado=aux.pernadireita.superiorlado+30.0/frames;
        //faiz a translacao
        aux.posicao.y=-8+8*cos((i+1)*(50.0/frames)*pi/180.0);

        aux.pernaesquerda.superior=aux.pernaesquerda.superior+50.0/frames;
        aux.pernaesquerda.inferior=aux.pernaesquerda.inferior-100.0/frames;
        aux.peesquerdo=aux.peesquerdo+50.0/frames;

    //-----------------------------

        aux.bracodireito.superior=aux.bracodireito.superior+90.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior+90.0/frames;
        aux.bracodireito.superiorlado=aux.bracodireito.superiorlado+75.0/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+90.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior+90.0/frames;
        aux.bracoesquerdo.superiorlado=aux.bracoesquerdo.superiorlado-75.0/frames;
        insereanima(&animacaoauto,aux);
    }

   for(i=0;i<frames;i++){
        //agacha
        aux.pernadireita.superior=aux.pernadireita.superior-50.0/frames;
        aux.pernadireita.inferior=aux.pernadireita.inferior+100.0/frames;
        aux.pedireito=aux.pedireito-50.0/frames;
        aux.pernadireita.superiorlado=aux.pernadireita.superiorlado-30.0/frames;
        //faiz a translacao
        aux.posicao.y=-8+8*cos((50-(i+1)*(50.0/frames))*pi/180.0);

        aux.pernaesquerda.superior=aux.pernaesquerda.superior-50.0/frames;
        aux.pernaesquerda.inferior=aux.pernaesquerda.inferior+100.0/frames;
        aux.peesquerdo=aux.peesquerdo-50.0/frames;

    //-----------------------------

        aux.bracodireito.superior=aux.bracodireito.superior-90.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior-90.0/frames;
        aux.bracodireito.superiorlado=aux.bracodireito.superiorlado-75.0/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior-90.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior-90.0/frames;
        aux.bracoesquerdo.superiorlado=aux.bracoesquerdo.superiorlado+75.0/frames;
        insereanima(&animacaoauto,aux);
    }

    //----------------------------------------------------------------------------------------------------------------aaaaaa
     for(i=0;i<frames;i++){
        aux.bracodireito.superior=aux.bracodireito.superior+90.0/frames;

        aux.bracodireito.superiorlado=aux.bracodireito.superiorlado+90.0/frames;
        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro-90.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior+90.0/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+90.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro +60.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior+90.0/frames;
        insereanima(&animacaoauto,aux);
    }

    for(i=0;i<frames;i++){
        aux.bracodireito.superior=aux.bracodireito.superior-90.0/frames;

        aux.bracodireito.superiorlado=aux.bracodireito.superiorlado-90.0/frames;
        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro+90.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior-90.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior-90.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro -60.0/frames;
        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior-90.0/frames;
        insereanima(&animacaoauto,aux);
    }


    for(i=0;i<frames;i++){
        aux.bracodireito.superior=aux.bracodireito.superior+90.0/frames;
        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro -60.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior+90.0/frames;

        aux.cabecalado=aux.cabecalado+60.0/frames;
        aux.cabecacimabaxo=aux.cabecacimabaxo+10.0/frames;
        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+90.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro -60.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior+90.0/frames;
        insereanima(&animacaoauto,aux);

    }

    for(i=0;i<frames;i++){

        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro +120.0/frames;
        aux.cabecalado=aux.cabecalado-120.0/frames;
        if(i<frames/2)
        aux.cabecacimabaxo=aux.cabecacimabaxo-10.0/frames;
        else
            aux.cabecacimabaxo=aux.cabecacimabaxo+10.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro +120.0/frames;

        insereanima(&animacaoauto,aux);

    }

    for(i=0;i<frames;i++){
        aux.bracodireito.superior=aux.bracodireito.superior-90.0/frames;
        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro -60.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior-90.0/frames;

        aux.cabecalado=aux.cabecalado+60.0/frames;
        aux.cabecacimabaxo=aux.cabecacimabaxo-10.0/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior-90.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro -60.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior-90.0/frames;
        insereanima(&animacaoauto,aux);

    }

    // o avatar agacha
    for(i=0;i<frames;i++){
        //agacha
        aux.pernadireita.superior=aux.pernadireita.superior+50.0/frames;
        aux.pernadireita.inferior=aux.pernadireita.inferior-100.0/frames;
        aux.pedireito=aux.pedireito+50.0/frames;
        //faiz a translacao
        aux.posicao.y=-8+8*cos((i+1)*(50.0/frames)*pi/180.0);

        aux.pernaesquerda.superior=aux.pernaesquerda.superior+50.0/frames;
        aux.pernaesquerda.inferior=aux.pernaesquerda.inferior-100.0/frames;
        aux.peesquerdo=aux.peesquerdo+50.0/frames;

    //-----------------------------

        aux.bracodireito.superior=aux.bracodireito.superior+90.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior+90.0/frames;
        aux.bracodireito.superiorlado=aux.bracodireito.superiorlado+75.0/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+90.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior+90.0/frames;
        aux.bracoesquerdo.superiorlado=aux.bracoesquerdo.superiorlado-75.0/frames;
        insereanima(&animacaoauto,aux);
    }

   for(i=0;i<frames;i++){
        //agacha
        aux.pernadireita.superior=aux.pernadireita.superior-50.0/frames;
        aux.pernadireita.inferior=aux.pernadireita.inferior+100.0/frames;
        aux.pedireito=aux.pedireito-50.0/frames;
        //faiz a translacao
        aux.posicao.y=-8+8*cos((50-(i+1)*(50.0/frames))*pi/180.0);

        aux.pernaesquerda.superior=aux.pernaesquerda.superior-50.0/frames;
        aux.pernaesquerda.inferior=aux.pernaesquerda.inferior+100.0/frames;
        aux.peesquerdo=aux.peesquerdo-50.0/frames;

    //-----------------------------

        aux.bracodireito.superior=aux.bracodireito.superior-90.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior-90.0/frames;
        aux.bracodireito.superiorlado=aux.bracodireito.superiorlado-75.0/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior-90.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior-90.0/frames;
        aux.bracoesquerdo.superiorlado=aux.bracoesquerdo.superiorlado+75.0/frames;
        insereanima(&animacaoauto,aux);
    }
    //-------------------------------------------------------------------------------------------------

    for(i=0;i<frames;i++){
        aux.bracodireito.superior=aux.bracodireito.superior+90.0/frames;

        aux.bracodireito.superiorlado=aux.bracodireito.superiorlado+90.0/frames;
        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro-90.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior+90.0/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+90.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro +60.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior+90.0/frames;
        insereanima(&animacaoauto,aux);
    }

    for(i=0;i<frames;i++){
        aux.bracodireito.superior=aux.bracodireito.superior-90.0/frames;

        aux.bracodireito.superiorlado=aux.bracodireito.superiorlado-90.0/frames;
        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro+90.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior-90.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior-90.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro -60.0/frames;
        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior-90.0/frames;
        insereanima(&animacaoauto,aux);
    }


    for(i=0;i<frames;i++){
        aux.bracodireito.superior=aux.bracodireito.superior+90.0/frames;
        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro -60.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior+90.0/frames;

        aux.cabecalado=aux.cabecalado+60.0/frames;
        aux.cabecacimabaxo=aux.cabecacimabaxo+10.0/frames;
        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+90.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro -60.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior+90.0/frames;
        insereanima(&animacaoauto,aux);

    }

    for(i=0;i<frames;i++){

        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro +120.0/frames;
        aux.cabecalado=aux.cabecalado-120.0/frames;
        if(i<frames/2)
        aux.cabecacimabaxo=aux.cabecacimabaxo-10.0/frames;
        else
            aux.cabecacimabaxo=aux.cabecacimabaxo+10.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro +120.0/frames;

        insereanima(&animacaoauto,aux);

    }

    for(i=0;i<frames;i++){
        aux.bracodireito.superior=aux.bracodireito.superior-90.0/frames;
        aux.bracodireito.superiorgiro=aux.bracodireito.superiorgiro -60.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior-90.0/frames;

        aux.cabecalado=aux.cabecalado+60.0/frames;
        aux.cabecacimabaxo=aux.cabecacimabaxo-10.0/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior-90.0/frames;
        aux.bracoesquerdo.superiorgiro=aux.bracoesquerdo.superiorgiro -60.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior-90.0/frames;
        insereanima(&animacaoauto,aux);

    }

    // o avatar agacha
    for(i=0;i<frames;i++){
        //agacha
        aux.pernadireita.superior=aux.pernadireita.superior+50.0/frames;
        aux.pernadireita.inferior=aux.pernadireita.inferior-100.0/frames;
        aux.pedireito=aux.pedireito+50.0/frames;
        aux.pernaesquerda.superiorlado=aux.pernaesquerda.superiorlado-30.0/frames;
        //faiz a translacao
        aux.posicao.y=-8+8*cos((i+1)*(50.0/frames)*pi/180.0);

        aux.pernaesquerda.superior=aux.pernaesquerda.superior+50.0/frames;
        aux.pernaesquerda.inferior=aux.pernaesquerda.inferior-100.0/frames;
        aux.peesquerdo=aux.peesquerdo+50.0/frames;

    //-----------------------------

        aux.bracodireito.superior=aux.bracodireito.superior+90.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior+90.0/frames;
        aux.bracodireito.superiorlado=aux.bracodireito.superiorlado+75.0/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior+90.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior+90.0/frames;
        aux.bracoesquerdo.superiorlado=aux.bracoesquerdo.superiorlado-75.0/frames;
        insereanima(&animacaoauto,aux);
    }

   for(i=0;i<frames;i++){
        //agacha
        aux.pernadireita.superior=aux.pernadireita.superior-50.0/frames;
        aux.pernadireita.inferior=aux.pernadireita.inferior+100.0/frames;
        aux.pedireito=aux.pedireito-50.0/frames;
        aux.pernaesquerda.superiorlado=aux.pernaesquerda.superiorlado+30.0/frames;
        //faiz a translacao
        aux.posicao.y=-8+8*cos((50-(i+1)*(50.0/frames))*pi/180.0);

        aux.pernaesquerda.superior=aux.pernaesquerda.superior-50.0/frames;
        aux.pernaesquerda.inferior=aux.pernaesquerda.inferior+100.0/frames;
        aux.peesquerdo=aux.peesquerdo-50.0/frames;

    //-----------------------------

        aux.bracodireito.superior=aux.bracodireito.superior-90.0/frames;
        aux.bracodireito.inferior=aux.bracodireito.inferior-90.0/frames;
        aux.bracodireito.superiorlado=aux.bracodireito.superiorlado-75.0/frames;

        aux.bracoesquerdo.superior=aux.bracoesquerdo.superior-90.0/frames;
        aux.bracoesquerdo.inferior=aux.bracoesquerdo.inferior-90.0/frames;
        aux.bracoesquerdo.superiorlado=aux.bracoesquerdo.superiorlado+75.0/frames;
        insereanima(&animacaoauto,aux);
    }
}


void animacaoautomatica(int a){

    ser= proximodafilaanima(&animacaoauto);

        if(ser.fim!=1){
        glutTimerFunc(50,animacaoautomatica,0);

        desenha();
        }else{
            voltaproprimeirofilaanima(&animacaoauto);
            glutPostRedisplay();
        }


}


void desenha(){

 if(oqueassetasfazem==0||oqueassetasfazem==15){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glRotatef(angx,1,0,0);
        glRotatef(angy,0,1,0);
        desenhachao();
        desenhaceu();

        desenhahumanoide();


        titem aux,aux2;


        aux=proximodafila(&arvores);
        while(aux.tempo!=-1){
            desenhaarvore(aux);
            aux=proximodafila(&arvores);

        }

        aux=proximodafila(&arvores2);
        while(aux.tempo!=-1){
                desenhaarvore2(aux);
                aux=proximodafila(&arvores2);

        }
        srand(10);

        aux=proximodafila(&solos);
        while(aux.tempo!=-1){
            desenhasolo(aux);
            aux=proximodafila(&solos);

        }

        aux=proximodafila(&posicoesdomause);
        while(aux.tempo!=-1){
                aux.largura=8;

            desenhasolo(aux);
            aux=proximodafila(&posicoesdomause);

        }

        aux2.x=-2;aux2.y=0;aux2.z=4;
        desenhacasa(aux2);
       //--------------------------------------------------------------------------------

        voltaproprimeirofila(&arvores);
        voltaproprimeirofila(&arvores2);
        voltaproprimeirofila(&solos);
        voltaproprimeirofila(&posicoesdomause);


    glutSwapBuffers();
 }else if (oqueassetasfazem<15){
    mostrapersonagem();
 }
}


void comanda(unsigned char letra,int x,int y){

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        switch(letra){
        case 27:
            apagafila(&solos);
            apagafila(&arvores);
            apagafila(&arvores2);
            apagafila(&posicoesdomause);

            apagafilaanima(&animacaoauto);
            apagafilaanima(&anda);
            apagafilaanima(&planta);
            exit(0);
            break;
        case 'a':
            xa=xa-0.2*sin(theta-pi/2);
            za=za-0.2*cos(theta-pi/2);
            cza=cza-0.2*cos(theta-pi/2);
            cxa=cxa-0.2*sin(theta-pi/2);
            break;
        case 'd':
            xa=xa+0.2*sin(theta-pi/2);
            za=za+0.2*cos(theta-pi/2);
            cza=cza+0.2*cos(theta-pi/2);
            cxa=cxa+0.2*sin(theta-pi/2);
            break;
        case 's':
            xa=xa-0.2*sin(theta);
            za=za-0.2*cos(theta);
            cza=cza-0.2*cos(theta);
            cxa=cxa-0.2*sin(theta);
            break;
        case 'w':
            xa=xa+0.2*sin(theta);
            za=za+0.2*cos(theta);
            cza=cza+0.2*cos(theta);
            cxa=cxa+0.2*sin(theta);
            break;
        case 'q':
            theta=theta+pi/100;
            cza=za+cos(theta);
            cxa=xa+sin(theta);
            break;
        case 'e':
            theta=theta-pi/100;
            cza=za+cos(theta);
            cxa=xa+sin(theta);
        }

        gluLookAt(xa,0,za,cxa,0,cza,0,1,0);
        glutPostRedisplay();
         glLightfv( GL_LIGHT0, GL_POSITION, position );
        glLightfv( GL_LIGHT1, GL_POSITION, position1 );

}

void comanda2(int tecla,int x,int y){
    if(oqueassetasfazem==1){
        switch (tecla){
        case GLUT_KEY_LEFT:

            break;
        case GLUT_KEY_RIGHT:

            break;
        case GLUT_KEY_DOWN:
            if(ser.pedireito-5>=-15)
            ser.pedireito=ser.pedireito-5;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            if(ser.pedireito+5<=30)
            ser.pedireito=ser.pedireito+5;
            glutPostRedisplay();
            break;
        }
    }else if(oqueassetasfazem==2){
        switch (tecla){
        case GLUT_KEY_LEFT:

            break;
        case GLUT_KEY_RIGHT:

            break;
        case GLUT_KEY_DOWN:
            if(ser.peesquerdo-5>=-15)
                ser.peesquerdo=ser.peesquerdo-5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            if(ser.peesquerdo+5<=30)
                ser.peesquerdo=ser.peesquerdo+5;
                glutPostRedisplay();
            break;
        }


    }else if(oqueassetasfazem==3){
        switch (tecla){
        case GLUT_KEY_LEFT:
            if(ser.pernadireita.superiorlado-5 >=-15)
                ser.pernadireita.superiorlado=ser.pernadireita.superiorlado-5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:

            if(ser.pernadireita.superiorlado+5<=20)
            ser.pernadireita.superiorlado=ser.pernadireita.superiorlado+5;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            if(ser.pernadireita.superior-5>=-40)
            ser.pernadireita.superior=ser.pernadireita.superior-5;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:

            if(ser.pernadireita.superior+5<=50)
            ser.pernadireita.superior=ser.pernadireita.superior+5;
            glutPostRedisplay();
            break;
        }

    }else if(oqueassetasfazem==4){
         switch (tecla){
        case GLUT_KEY_LEFT:
            if(ser.pernaesquerda.superiorlado-5 >=-15)
                ser.pernaesquerda.superiorlado=ser.pernaesquerda.superiorlado-5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:

            if(ser.pernaesquerda.superiorlado+5<=20)
            ser.pernaesquerda.superiorlado=ser.pernaesquerda.superiorlado+5;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            if(ser.pernaesquerda.superior-5>=-40)
            ser.pernaesquerda.superior=ser.pernaesquerda.superior-5;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:

            if(ser.pernaesquerda.superior+5<=50)
            ser.pernaesquerda.superior=ser.pernaesquerda.superior+5;
            glutPostRedisplay();
            break;
        }

    }else if(oqueassetasfazem==5){
        switch (tecla){
        case GLUT_KEY_LEFT:
            if(ser.bracodireito.superiorlado+5<=90)
                ser.bracodireito.superiorlado= ser.bracodireito.superiorlado+5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            if(ser.bracodireito.superiorlado-5>=-15)
                ser.bracodireito.superiorlado= ser.bracodireito.superiorlado-5;
                glutPostRedisplay();

            break;
        case GLUT_KEY_DOWN:
            if(ser.bracodireito.superior-5>=-40)
                ser.bracodireito.superior=ser.bracodireito.superior-5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_UP:

            if(ser.bracodireito.superior+5<=90)
                ser.bracodireito.superior=ser.bracodireito.superior+5;
                glutPostRedisplay();
            break;
        }

    }else if(oqueassetasfazem==6){
        switch (tecla){
        case GLUT_KEY_LEFT:
            if(ser.bracoesquerdo.superiorlado+5<=20)
                ser.bracoesquerdo.superiorlado= ser.bracoesquerdo.superiorlado+5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            if(ser.bracoesquerdo.superiorlado-5>=-90)
                ser.bracoesquerdo.superiorlado= ser.bracoesquerdo.superiorlado-5;
                glutPostRedisplay();

            break;
        case GLUT_KEY_DOWN:
            if(ser.bracoesquerdo.superior-5>=-40)
                ser.bracoesquerdo.superior=ser.bracoesquerdo.superior-5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_UP:

            if(ser.bracoesquerdo.superior+5<=90)
                ser.bracoesquerdo.superior=ser.bracoesquerdo.superior+5;
                glutPostRedisplay();
            break;
        }

    }else if(oqueassetasfazem==-1||oqueassetasfazem==-2){
        switch (tecla){
        case GLUT_KEY_LEFT:
            if(ser.maodireitalado+5<=20)
                ser.maodireitalado=ser.maodireitalado+5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            if(ser.maodireitalado-5>=-30)
                ser.maodireitalado=ser.maodireitalado-5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            if(ser.maodireitacimabaixo+5<=10)
                ser.maodireitacimabaixo=ser.maodireitacimabaixo+5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            if(ser.maodireitacimabaixo-5>=-10)
                ser.maodireitacimabaixo=ser.maodireitacimabaixo-5;
                glutPostRedisplay();
            break;
        }

    }else if(oqueassetasfazem==-3||oqueassetasfazem==-4){
       switch (tecla){
        case GLUT_KEY_LEFT:
            if(ser.maoesquerdalado+5<=20)
                ser.maoesquerdalado=ser.maoesquerdalado+5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            if(ser.maoesquerdalado-5>=-30)
                ser.maoesquerdalado=ser.maoesquerdalado-5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            if(ser.maoesquedacimabaixo+5<=10)
                ser.maoesquedacimabaixo=ser.maoesquedacimabaixo+5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            if(ser.maoesquedacimabaixo-5>=-10)
                ser.maoesquedacimabaixo=ser.maoesquedacimabaixo-5;
                glutPostRedisplay();
            break;
        }


    }else if(oqueassetasfazem==9){
        switch (tecla){
        case GLUT_KEY_LEFT:
            if(ser.cabecalado-5>=-75)
                ser.cabecalado=ser.cabecalado-5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:

            if(ser.cabecalado+5<=75)
                ser.cabecalado=ser.cabecalado+5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            if(ser.cabecacimabaxo-5>=-30)
                ser.cabecacimabaxo=ser.cabecacimabaxo-5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_UP:

            if(ser.cabecacimabaxo+5<=35)
                ser.cabecacimabaxo=ser.cabecacimabaxo+5;
                glutPostRedisplay();
            break;
        }

    }else if(oqueassetasfazem==11){
        switch (tecla){
        case GLUT_KEY_LEFT:

            break;
        case GLUT_KEY_RIGHT:

            break;
        case GLUT_KEY_DOWN:
            if(ser.pernadireita.inferior-5>=-100)
                ser.pernadireita.inferior=ser.pernadireita.inferior-5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_UP:

            if(ser.pernadireita.inferior+5<=0)
                ser.pernadireita.inferior=ser.pernadireita.inferior+5;
                glutPostRedisplay();
            break;
        }

    }else if(oqueassetasfazem==12){
        switch (tecla){
        case GLUT_KEY_LEFT:

            break;
        case GLUT_KEY_RIGHT:

            break;
        case GLUT_KEY_DOWN:
            if(ser.pernaesquerda.inferior-5>=-100)
                ser.pernaesquerda.inferior=ser.pernaesquerda.inferior-5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            if(ser.pernaesquerda.inferior+5<=0)
                ser.pernaesquerda.inferior=ser.pernaesquerda.inferior+5;
                glutPostRedisplay();
            break;
        }

    }else if(oqueassetasfazem==13){
        switch (tecla){
        case GLUT_KEY_LEFT:

            break;
        case GLUT_KEY_RIGHT:

            break;
        case GLUT_KEY_DOWN:
            if(ser.bracodireito.inferior-5>=0)
                ser.bracodireito.inferior=ser.bracodireito.inferior-5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_UP:

            if(ser.bracodireito.inferior+5<=100)
                ser.bracodireito.inferior=ser.bracodireito.inferior+5;
                glutPostRedisplay();
            break;
        }

    }else if(oqueassetasfazem==14){
        switch (tecla){
        case GLUT_KEY_LEFT:

            break;
        case GLUT_KEY_RIGHT:

            break;
        case GLUT_KEY_DOWN:

            if(ser.bracoesquerdo.inferior-5>=0)
                ser.bracoesquerdo.inferior=ser.bracoesquerdo.inferior-5;
                glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            if(ser.bracoesquerdo.inferior+5<=100)
                ser.bracoesquerdo.inferior=ser.bracoesquerdo.inferior+5;
                glutPostRedisplay();
            break;
        }

    }else if(oqueassetasfazem==-10){
        switch (tecla){
        case GLUT_KEY_LEFT:
            break;
        case GLUT_KEY_RIGHT:

            break;
        case GLUT_KEY_DOWN:

            if(ser.angtronco-5>=0)
                ser.angtronco=ser.angtronco-5;
                    glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            if(ser.angtronco+5<=90)
                ser.angtronco=ser.angtronco+5;
                glutPostRedisplay();
            break;
        }

    }
    glutPostRedisplay();
}
void definejanela(int x, int y){
    glViewport(0,0,x,y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60,1.777777778,0.1,200);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(xa,0,za,0,0,0,0,1,0);

}

void mostrapersonagem(){
    glClearColor(0,0.5,0.5,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

        glRotatef(angy,0,1,0);
        glRotatef(angx,1,0,0);

        desenhahumanoide();

    glPopMatrix();
    glutSwapBuffers();

}

void controlaanimacaoauto(int num){
    titemm aux;int tempod=15;
    int tempoan=10;
   if(estadodojogo==1){
     if(estadoanimacaoautomatica==0){
       aux =proximodafilaanima(&animacaoauto);
        if(aux.fim!=1){
            ser=aux;
            desenha();
            glutTimerFunc(tempod,controlaanimacaoauto,0);
        }else{
            estadoanimacaoautomatica=1;
            apagafilaanima(&animacaoauto);
            criaanimacaoanda(-6,0);
            glutTimerFunc(0,controlaanimacaoauto,0);
        }
    }else if(estadoanimacaoautomatica==1){
        aux= proximodafilaanima(&anda);
        if(aux.fim!=1){
            ser=aux;
            desenha();
            glutTimerFunc(tempoan,controlaanimacaoauto,0);
        }else{
            estadoanimacaoautomatica=2;
            apagafilaanima(&anda);
            crianimacaoauto();
            glutTimerFunc(0,controlaanimacaoauto,0);
        }
    }else if(estadoanimacaoautomatica==2){
       aux =proximodafilaanima(&animacaoauto);
        if(aux.fim!=1){
            ser=aux;
            desenha();
            glutTimerFunc(tempod,controlaanimacaoauto,0);
        }else{
            estadoanimacaoautomatica=3;
            apagafilaanima(&animacaoauto);
            criaanimacaoanda(-6,-6);
            glutTimerFunc(0,controlaanimacaoauto,0);
        }
    }else if(estadoanimacaoautomatica==3){
        aux= proximodafilaanima(&anda);
        if(aux.fim!=1){
            ser=aux;
            desenha();
            glutTimerFunc(tempoan,controlaanimacaoauto,0);
        }else{
            estadoanimacaoautomatica=4;
            apagafilaanima(&anda);
            crianimacaoauto();
            glutTimerFunc(0,controlaanimacaoauto,0);
        }
    }else if(estadoanimacaoautomatica==4){
       aux =proximodafilaanima(&animacaoauto);
        if(aux.fim!=1){
            ser=aux;
            desenha();
            glutTimerFunc(tempod,controlaanimacaoauto,0);
        }else{
            estadoanimacaoautomatica=5;
            apagafilaanima(&animacaoauto);
            criaanimacaoanda(0,-6);
            glutTimerFunc(0,controlaanimacaoauto,0);
        }
    }else if(estadoanimacaoautomatica==5){
        aux= proximodafilaanima(&anda);
        if(aux.fim!=1){
            ser=aux;
            desenha();
            glutTimerFunc(tempoan,controlaanimacaoauto,0);
        }else{
            estadoanimacaoautomatica=6;
            apagafilaanima(&anda);
            crianimacaoauto();
            glutTimerFunc(0,controlaanimacaoauto,0);
        }
    }else if(estadoanimacaoautomatica==6){
       aux =proximodafilaanima(&animacaoauto);
        if(aux.fim!=1){
            ser=aux;
            desenha();
            glutTimerFunc(tempod,controlaanimacaoauto,0);
        }else{
            estadoanimacaoautomatica=7;
            apagafilaanima(&animacaoauto);
            criaanimacaoanda(0,0);
            glutTimerFunc(0,controlaanimacaoauto,0);
        }
    }else if(estadoanimacaoautomatica==7){
        aux= proximodafilaanima(&anda);
        if(aux.fim!=1){
            ser=aux;
            desenha();
            glutTimerFunc(tempoan,controlaanimacaoauto,0);
        }else{
            estadoanimacaoautomatica=0;
            apagafilaanima(&anda);
            crianimacaoauto();
            glutTimerFunc(0,controlaanimacaoauto,0);
        }
    }

   }
}
void movePersonagem(int item){
    if(estadodojogo!=2){
    inicia2();
    apagafilaanima(&planta);
    }
    estadodojogo=2;
    oqueassetasfazem=item;
    if(item==-1)
        ser.posicao.largura2=1;
        else if(item==-3)
            ser.posicao.largura2=2;
        else if(item==-2||item==-4)
            ser.posicao.largura2=0;
    mostrapersonagem();
}
void voltapromodojogo(int a){
  apagafila(&posicoesdomause);
  apagafilaanima(&planta);
  apagafilaanima(&animacaoauto);
  apagafilaanima(&anda);


  ser.posicao.raio=0;
  ser.posicao.x=0;
  ser.posicao.y=0;
  ser.posicao.z=0;
  ser.posicao.tempo=0;
  ser.posicao.largura2=0;
  oqueassetasfazem=0;
  za=-2;
  oqueassetasfazem=0;
  xa=1;ya=0;cxa=0;cza=0,theta=-26.565051*pi/180.0;
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(xa,0,za,cxa,0,cza,0,1,0);
  inicia3();
  glutPostRedisplay();
}
void jogo(int item){
    if(item==2){
        if(estadodojogo!=0){
                    apagafilaanima(&planta);

                titem* aux=atual2dafila(&posicoesdomause);
        if(aux!=NULL && aux->tempo!=2){
            aux->tempo=0;
        }
            glutTimerFunc(0,controlaandar,0);

            apagafilaanima(&animacaoauto);
            apagafilaanima(&anda);
            apagafilaanima(&planta);
            inicia3();
        }

        estadodojogo=0;
        oqueassetasfazem==0;
        glutPostRedisplay();

    }else if(item==1){
        if(estadodojogo!=1){
        apagafilaanima(&anda);
        inicia3();
         estadodojogo=1;
         estadoanimacaoautomatica=0;
        crianimacaoauto();
        controlaanimacaoauto(0);
        }
        oqueassetasfazem=15;
        glutPostRedisplay();
    }else if(item==3){
        estadodojogo=3;
        glutTimerFunc(0,voltapromodojogo,0);
    }
}

void criamenu(){
    int configuraenxadaesquerdo=glutCreateMenu(movePersonagem);
    glutAddMenuEntry("com a enxada",-3);
    glutAddMenuEntry("sem a enxada",-4);
int configuraenxadadireito=glutCreateMenu(movePersonagem);
    glutAddMenuEntry("com a enxada",-1);
    glutAddMenuEntry("sem a enxada",-2);

int moverpersonagem = glutCreateMenu(movePersonagem);
    glutAddMenuEntry("pe direito",1);
    glutAddMenuEntry("pe esquerdo",2);
    glutAddMenuEntry("perna direita superior",3);
    glutAddMenuEntry("perna direita inferior",11);
    glutAddMenuEntry("perna esquerda superior",4);
    glutAddMenuEntry("perna esquerda inferior",12);
    glutAddMenuEntry("braco direito superior",5);
    glutAddMenuEntry("braco direito inferior",13);
    glutAddMenuEntry("braco esquerdo superior",6);
    glutAddMenuEntry("braco esquerdo inferior",14);
    glutAddSubMenu("mao direita",configuraenxadadireito);
    glutAddSubMenu("mao esquerda",configuraenxadaesquerdo);
    glutAddMenuEntry("cabeca",9);
    glutAddMenuEntry("tronco",-10);



    glutCreateMenu(jogo);
    glutAddSubMenu("move personagem", moverpersonagem);
    glutAddMenuEntry("animacao automatica",1);
    glutAddMenuEntry("modo jogo",2);
    glutAddMenuEntry("reseta o jogo",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);


}


void luz(){
    GLfloat luz_ambiente[] = { 0.1, 0.1,0.1, 1.0 } ;
     GLfloat luz_ambiente2[] = { 0.25, 0.25,0.25, 1.0 } ;
    GLfloat objeto_ambiente[] = { 0.4,0.4, 0.4, 1.0};
    GLfloat luz_difusa[] = {0.7,0.7,0.7,1.0} ;
    GLfloat luz_difusa2[] = {0.5,0.5,0.7,1.0} ;
    GLfloat objeto_difusa[] = { 0.4,0.4, 0.4, 1.0};
    GLfloat luz_especular[] = { 1.0,1.0, 1.0, 1.0 } ;
    GLfloat objeto_especular[] = { 0.5,0.5, 0.5, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente );
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa );
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz_especular );
    glLightfv(GL_LIGHT1, GL_AMBIENT, luz_ambiente2 );
    glLightfv(GL_LIGHT1, GL_DIFFUSE, luz_difusa2 );
    glLightfv(GL_LIGHT1, GL_SPECULAR, luz_especular );

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambiente);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glLightfv( GL_LIGHT0, GL_POSITION, position );

    glLightfv( GL_LIGHT1, GL_POSITION, position1 );
    glEnable (GL_COLOR_MATERIAL);
glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}
void controlaandar(int a){
    titem* aux=atual2dafila(&posicoesdomause);
    titemm aux2;
if(estadodojogo==0){
   if(aux!=NULL){
    if(aux->tempo==0){
        criaanimacaoanda(aux->x,aux->z);
        aux->tempo=1;
        glutTimerFunc(0,controlaandar,0);
    }else if(aux->tempo==1){
        aux2=proximodafilaanima(&anda);
        if(aux2.fim!=1){
            ser=aux2;
            desenha();
            glutTimerFunc(7,controlaandar,0);
        }else{
            criaanimacaoplanta();
            rodaplanta(0);
            aux->tempo=3;
            desenha();
            apagafilaanima(&anda);
            glutTimerFunc(0,controlaandar,0);
        }
    }else if(aux->tempo==2){
        aux=proximodafilaatual2(&posicoesdomause);
        glutTimerFunc(0,controlaandar,0);
    }else if(aux->tempo==3){
        glutTimerFunc(0,controlaandar,0);
    }
   }else{

   }
   }
}
void pegaclick(int botao,int estado,int x, int y){
    switch(botao){
    case GLUT_LEFT_BUTTON:
        if(estado==GLUT_DOWN&&estadodojogo==0){
                GLdouble projecao[16];
                glGetDoublev(GL_PROJECTION_MATRIX, projecao);


                GLdouble modelvieww[16];
                glGetDoublev(GL_MODELVIEW_MATRIX, modelvieww);

                GLint view[4];
                glGetIntegerv(GL_VIEWPORT,view);

                GLdouble objx1,objx2,objy1,objy2,objz1,objz2,z;
                titem aux;
                GLfloat winx, winy, winz;

                        winx =x;
                        winy =view[3]- y;
                        glReadPixels(winx, winy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winz);

                gluUnProject(winx,winy,winz,modelvieww,projecao,view,&objx1,&objy1,&objz1);

            aux.x=objx1;
            aux.y=0;
            aux.z=objz1;
            titem* aux2;
            aux.tempo=0;

            aux2=atual2dafila(&posicoesdomause);
            if(aux2==NULL){
              glutTimerFunc(0,controlaandar,5);
              voltaproprimeirofilaatual2(&posicoesdomause);
            }
            if(aux.x<50&&aux.x>-50&&aux.z<50&&aux.z>-50){
            insere(&posicoesdomause,aux);
            }
            glutPostRedisplay();
        }

        break;


    }

}
int main(int num,char**arg){

    glutInit(&num,arg);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(400,500);
    janelaprincipal=glutCreateWindow("humanoide");
    inicia();
    luz();
    criamenu();

    glutFullScreen();

    glutDisplayFunc(desenha);
    glutMouseFunc(pegaclick);
    glutKeyboardFunc(comanda);
    glutSpecialFunc(comanda2);
    glutReshapeFunc(definejanela);
    glutMainLoop();
return 0;
}
