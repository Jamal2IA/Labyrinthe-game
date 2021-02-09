#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include<time.h>
#include<math.h>
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//                          A STAR


typedef struct _node{
int indice[2];
int valeur;
int start_cost;
int end_cost;
int f_cost;
struct _node* parent;
}node;
//------------------------------------------------------
int** A_STAR;// TABLEAU DU CHEMIN QU ON CHERCHE
int A_COUNT=0;// LE NOMBRE DE CASES DU CHEMIN
int** A_STAR2;// TABLEAU DU CHEMIN QU ON CHERCHE
int A_COUNT2=0;// LE NOMBRE DE CASES DU CHEMIN pour la sortie 2
node* OPEN[32*32]={NULL};
node* CLOSED[32*32]={NULL};
node* current ;// EQUIVALENT A UN PIVOT
int P[32][32];// TABLEAU DU LABYRINTHE
int Now;// DIMENSION DU MODE CHOISIE
int start[2];// POSTION DE LA CASE DE DEPART
int goal[2];
int start2[2];
//------------------------------------------------------

int** carre(int indice[2]){

int C[4][2]={
            {indice[0]-1,indice[1]},
            {indice[0],indice[1]-1},
            {indice[0],indice[1]+1},
            {indice[0]+1,indice[1]} } ;
int **L;
int i,j;
L=(int**)malloc(sizeof(int*)*4);
    if(L==NULL)
        printf("ERREUR LORS DE L ALLOCATION");
    for(i=0;i<4;i++)
        L[i]=(int*)malloc(sizeof(int)*2);
        if(L==NULL)
            printf("ERREUR LORS DE L ALLOCATION");
for(i=0;i<4;i++){
    for(j=0;j<2;j++)
        L[i][j]=C[i][j];
}// JUSTE POUR LA PRATIQUE CAR ON DOIT RETOURNER UN TABLEAU DYNAMIQUE MAIS ON PEUT L IMPLENTER COMME UN TABLEAU STATIQUE

return L;
}


void ajouter_open(node* mynode){
    int i=0;
    while (1){
        if(OPEN[i]==NULL){
        OPEN[i]=mynode;
        return;}
        else
        i=i+1;
    }
}


void ajouter_closed(node* mynode){
    int i=0;
    while (1){
        if(CLOSED[i]==NULL){
        CLOSED[i]=mynode;
        return;}
        else
        i=i+1;
    }
}



int into(int indice[2],int N,int M){
    if (indice[0]<0 || indice [1]<0 || indice[0]>=N || indice[1]>=M)
        return 0;
    return 1;
}



int findinOPEN(int c[2]){
    int i=0;
    while(OPEN[i]!=NULL){
        if(OPEN[i]->indice[0]==c[0] && OPEN[i]->indice[0]==c[0])
            return i;

        i=i+1;
    }
    return -1;
}
//------------------------------------------------------

int lower(){
    int k=0;
    int i=0;
    while(OPEN[i]!=NULL){
        if(OPEN[i]->f_cost<OPEN[k]->f_cost)
            k=i;
        if(OPEN[i]->f_cost==OPEN[k]->f_cost){
            if (OPEN[i]->end_cost<=OPEN[k]->end_cost)
                k=i;
        }
        i=i+1;
    }
    return k;
}


void removefromOPEN(int k){
    int i=0;
    while (OPEN[i]!=NULL){
        if(OPEN[i+1]==NULL )
        {
            OPEN[k]=OPEN[i];
            OPEN[i]=NULL;
            return;
        }
        i=i+1;
    }
    return;
}
int notinclosed(int c[2]){
    int i=0;
    while(CLOSED[i]!=NULL){
        if (CLOSED[i]->indice[0]==c[0] && CLOSED[i]->indice[1]==c[1])
            return 0;
        i=i+1;
    }
    return 1;

}

int update_(int start[2],int goal[2],int* indice,node* parent){
    if (P[indice[0]][indice[1]]==1)
        return 0;
    node* mynode;
    mynode=(node*)malloc(sizeof(node));
    if(mynode==NULL){
        printf("ERREUR LORS DE L ALLOCATION .");
    }
    mynode->indice[0]=indice[0];
    mynode->indice[1]=indice[1];

    mynode->end_cost=abs(indice[0]-goal[0])+abs(indice[1]-goal[1]);
    if(parent==NULL)
        mynode->start_cost=0;
    else
        mynode->start_cost=parent->start_cost+1;
        mynode->f_cost=mynode->start_cost+mynode->end_cost;
    if(findinOPEN(mynode->indice)==-1 ){
        mynode->parent=parent;
        ajouter_open(mynode);
        }
    else{
        if(mynode->f_cost<OPEN[findinOPEN(mynode->indice)]->f_cost){
            mynode->parent=parent;
            removefromOPEN(findinOPEN(mynode->indice));
            ajouter_open(mynode);
            }
    return 1;}


}
void update_voisin(node* current,int start[2], int goal[2]){
    int i,j;
    int** L;
    L=(int**)malloc(sizeof(int*)*4);
    if(L==NULL)
        printf("ERREUR LORS DE L ALLOCATION");
    for(i=0;i<4;i++)
        L[i]=(int*)malloc(sizeof(int)*2);
        if(L==NULL)
            printf("ERREUR LORS DE L ALLOCATION");
    for(i=0;i<4;i++){
        for(j=0;j<2;j++)
            L[i][j]=carre(current->indice)[i][j];}

    for(i=0;i<4;i++){
        if(into(L[i],Now,Now) && notinclosed(L[i]) ){
            update_(start,goal,L[i],current);
        }
    }
}

void initialise_OPEN(){
    int i=0;
    while(OPEN[i]!=NULL){
        OPEN[i]=NULL;
        i=i+1;
}
}
void initialise_CLOSED(){
    int i=0;
    while(CLOSED[i]!=NULL){
        CLOSED[i]=NULL;
        i=i+1;
}
}

int A_STAR_SOLUTION(int start[2],int goal[2]){
    int j;
    initialise_CLOSED();
    initialise_OPEN();
    update_(start,goal,start,NULL);
    current=OPEN[0];
    int b[2]={14,14};
    while(current->end_cost!=0 && OPEN[0]!=NULL){
        current=OPEN[lower()];
        if(OPEN[lower()]!=NULL)
        printf("(fcost=%d)",OPEN[lower()]->f_cost);
        removefromOPEN(lower());
        ajouter_closed(current);
        update_voisin(current,start,goal);
        }
    if(current->end_cost!=0)
        {
        printf("pas de solution") ;return 0;
        }
    A_COUNT=0;
    while(current->parent!=NULL){
        A_STAR[A_COUNT][0]=current->indice[0];
        A_STAR[A_COUNT][1]=current->indice[1];
        current=current->parent;
        A_COUNT++;
        }
   // for(j=0;j<A_COUNT;j++){
     //   printf("(%d,%d)/",A_STAR[j][0],A_STAR[j][1]);
       // }

	return 0;
}








//--------------------------------------------------------------------------------

//-------------------------------------------------------------------------------



int hauteur_case;
int largeur_case;
int mode_;
int Hauteur_laby=560;
int Largeur_laby=540;
int w=0;





//-------------------------------------------
               //MISE EN PAGE
    SDL_Rect un_rect={30,80,40,40};
    SDL_Rect deux_rect={130,80,40,40};
    SDL_Rect trois_rect={220,80,40,40};// LES MODES

    SDL_Rect resoudre_rect={80,170,140,50};
    SDL_Rect modifier_rect={80,310,140,50};

    SDL_Rect sortie_rect={20,540,90,40};
    SDL_Rect entre_rect={180,540,90,40};

    SDL_Rect arriere_plan={0,0,880,600};


//-------------------------------------------

typedef struct _mode{
int nombre_case;
int hauteur ;
int largeur;
}mode;
mode M[3];
void remplirmode(int a , int b , int c){
    int H[3]={a,b,c};
    int i;
    for(i=0;i<3;i++){
    M[i].nombre_case=H[i];
    M[i].hauteur=Hauteur_laby/H[i];
    M[i].largeur=Largeur_laby/H[i];

    }


}
int in(int x,int y,int a1,int a2,int b1 , int b2){
    if(x<a2 && x>=a1 && y>=b1 && y<b2)
        return 1;
    return 0;
}

int into_case(SDL_Rect rect ,SDL_Event event){

return(in(int(event.button.x),int(event.button.y),rect.x,rect.x+rect.w,rect.y,rect.y+rect.h));
}
			// retourne si le clic est dans une case

//------------------------------------------------------------------

//-------------------------------------------------------------------------------------
void SDL_AFFICHAGE(SDL_Window * pWindow){
    int i,j;
    SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED); // CEARTION DE SDL RENDERER
    if ( pRenderer )
    {
        SDL_Surface* Sprite1 = SDL_LoadBMP("CIEL.bmp");
        SDL_Surface* Sprite2 = SDL_LoadBMP("SABLE.bmp");
        SDL_Surface* Sprite3 = SDL_LoadBMP("lumi.bmp");
        SDL_Surface* Sprite4 = SDL_LoadBMP("generer.bmp");
        SDL_Surface* Sprite5 = SDL_LoadBMP("resoudre.bmp");
        SDL_Surface* Sprite6;
        switch (mode_){
            case 0 :
                Sprite6 = SDL_LoadBMP("ARRIEREPLAN.bmp");break;
            case 1 :
                Sprite6 = SDL_LoadBMP("mode 2.bmp");break;
            case 2 :
                Sprite6 = SDL_LoadBMP("mode 3.bmp");break;

                    }
        SDL_Surface* Sprite7 = SDL_LoadBMP("entre.bmp");
        SDL_Surface* Sprite8 = SDL_LoadBMP("solution.bmp");
        if ( Sprite1 )
            {
            SDL_Texture* Texture1 = SDL_CreateTextureFromSurface(pRenderer,Sprite1);
            SDL_Texture* Texture3 = SDL_CreateTextureFromSurface(pRenderer,Sprite3);
            SDL_Texture* Texture2 = SDL_CreateTextureFromSurface(pRenderer,Sprite2);
            SDL_Texture* Texture4 = SDL_CreateTextureFromSurface(pRenderer,Sprite4);
            SDL_Texture* Texture5 = SDL_CreateTextureFromSurface(pRenderer,Sprite5);
            SDL_Texture* Texture6= SDL_CreateTextureFromSurface(pRenderer,Sprite6);
            SDL_Texture* Texture7= SDL_CreateTextureFromSurface(pRenderer,Sprite7);
            SDL_Texture* Texture8= SDL_CreateTextureFromSurface(pRenderer,Sprite8);    // PREPARATION DES TEXTURES
            if ( Texture1 )
            {
                if (w==1){
                    A_STAR_SOLUTION(start,goal);
                    for (i=0;i<A_COUNT;i++){
                        for(j=0;j<2;j++){
                               A_STAR2[i][j]=A_STAR[i][j];}}
                    A_COUNT2=A_COUNT;
                    A_STAR_SOLUTION(start2,goal);
                    w=0;}

                SDL_RenderCopy(pRenderer,Texture6,NULL,&arriere_plan);
                Now=M[mode_].nombre_case;
                largeur_case=M[mode_].largeur;
                hauteur_case=M[mode_].hauteur;
                SDL_Rect L[Now][Now];
                for (i=0;i<Now;i++){
                    for(j=0;j<Now;j++){
                        L[i][j]={320+largeur_case*j,20+hauteur_case*i,largeur_case,hauteur_case};
                    }
                }

//-------------------------------------------------------------------
                  //COPIE DES SPIRITES
                for (i=0;i<Now;i++){
                    for(j=0;j<Now;j++){
                        if(P[i][j]==0)
                            SDL_RenderCopy(pRenderer,Texture1,NULL,&(L[i][j]));
                        if(P[i][j]==1)
                            SDL_RenderCopy(pRenderer,Texture2,NULL,&(L[i][j]));
                        if(P[i][j]==5)
                            SDL_RenderCopy(pRenderer,Texture3,NULL,&(L[i][j]));
                        if(P[i][j]==10)
                            SDL_RenderCopy(pRenderer,Texture7,NULL,&(L[i][j]));
                        if(P[i][j]==20){ SDL_RenderCopy(pRenderer,Texture1,NULL,&(L[i][j]));
                            }
                                    }
                                    }
            printf("%d",A_STAR[0][0]);
            SDL_RenderPresent(pRenderer);

            if (A_COUNT!=0){
            for (i=0;i<A_COUNT || i<A_COUNT2;i++){
                    if(i<A_COUNT)
                        SDL_RenderCopy(pRenderer,Texture8,NULL,&(L[A_STAR[i][0]][A_STAR[i][1]]));
                    if(i<A_COUNT2)
                        SDL_RenderCopy(pRenderer,Texture8,NULL,&(L[A_STAR2[i][0]][A_STAR2[i][1]]));
                    SDL_RenderPresent(pRenderer);
                    SDL_Delay(200);}
                    }
                    A_COUNT=0;
 //----------------------------------------------------------------------
            char cont = 1; // Affichage
            SDL_Event event;
            SDL_WaitEvent(&event);
            while ( cont != 0 )
            {
                while ( SDL_PollEvent(&event) )
                {
                    /* TRAITEMENT DE L EVENEMENT*/
                    switch (event.type)  // SUIVANT LE TYPE
                    {
                        case SDL_MOUSEBUTTONDOWN:
                            switch(event.button.button){
                                case SDL_BUTTON_LEFT:{

                                    if (int((event.button.x-320)/largeur_case)<Now && int((event.button.x-320)/largeur_case)>=0 && int((event.button.y-20)/hauteur_case)>=0 && int((event.button.y-20)/hauteur_case)<Now){
                                        int a=int ((event.button.x-320)/largeur_case);
                                        printf("%d",a);
                                        int b=int ((event.button.y-20)/hauteur_case);
                                        printf("%d",b);
                                        P[b][a]=1;
                                        cont=0;
                                        }
                                    if (into_case(un_rect,event)){

                                        mode_=0;
                                        cont=0;

                                        }
                                    if (into_case(deux_rect,event)){

                                        mode_=1;
                                        cont=0;

                                        }
                                    if (into_case(trois_rect,event)){

                                        mode_=2;
                                        cont=0;

                                        }
                                    if (into_case(resoudre_rect,event)){
                                        w=1;
                                        cont=0;
                                        }
                                    if(into_case(modifier_rect,event)){


                                        }

                                    if(into_case(sortie_rect,event)){
                                        srand(time(NULL));
                                        P[start[0]][start[1]]=0;
                                        start[1]=rand()%(Now-2)+1;
                                        P[Now-2][start[1]]=5;
                                        start[0]=Now-2;
                                        cont=0;
                                        }
                                    if(into_case(entre_rect,event)){
                                        srand(time(NULL));
                                        P[goal[0]][goal[1]]=0;
                                        goal[1]=rand()%(Now-2)+1;
                                        P[1][goal[1]]=10;
                                        goal[0]=1;
                                        cont=0;
                                    }
                                   break;}
                            case SDL_BUTTON_RIGHT:{
                                if (int((event.button.x-320)/largeur_case)<Now && int((event.button.x-320)/largeur_case)>=0 && int((event.button.y-20)/hauteur_case)>=0 && int((event.button.y-20)/hauteur_case)<Now){
                                    int a=int ((event.button.x-320)/largeur_case);
                                    printf("%d",a);
                                    int b=int ((event.button.y-20)/hauteur_case);
                                    printf("%d",b);
                                    P[b][a]=0;
                                    cont=0;

                                    }
                                break;
                            }
                            break;


                            }
                    }
            }


            SDL_DestroyTexture(Texture1);
            SDL_DestroyTexture(Texture2);
            SDL_DestroyTexture(Texture3);
            SDL_DestroyTexture(Texture4);
            SDL_DestroyTexture(Texture5);
            SDL_DestroyTexture(Texture6);
            SDL_DestroyTexture(Texture7);
            SDL_DestroyTexture(Texture8);  // LIBERATION DE LA MEMOIRE ASSOCIE AUX TEXTURES
        }}
        else
        {
            fprintf(stdout,"Echec de creation de la texture (%s)\n",SDL_GetError());
        }

        SDL_FreeSurface(Sprite1);
        SDL_FreeSurface(Sprite2);
        SDL_FreeSurface(Sprite3);
        SDL_FreeSurface(Sprite4);
        SDL_FreeSurface(Sprite5);
        SDL_FreeSurface(Sprite6);
        SDL_FreeSurface(Sprite7);
        SDL_FreeSurface(Sprite8);// LIBERATION DES RESSOURCES UTILISE PAR LES SPIRITES
    }
    else
    {
        fprintf(stdout,"Echec de chargement du sprite (%s)\n",SDL_GetError());
    }

    SDL_DestroyRenderer(pRenderer); // LIBERATION DE LA MEMOIRE DE SDL RENDERER
}
else
{
    fprintf(stdout,"Echec de creation du renderer (%s)\n",SDL_GetError());
}
}






int main(int argc, char *argv[])
{
    remplirmode(8,16,32);
    mode_=1;
    Now=M[mode_].nombre_case;
    int i,j,contt=1;
    for(i=0;i<Now;i++){
        for(j=0;j<Now;j++){
            if(i%3==0)
                P[i][j]=0;
            if(i%3==1)
                P[i][j]=0;
            if(i%3==2)
                P[i][j]=0;
        }
    }
    for(i=0;i<Now;i++){
        P[i][0]=1;
        P[0][i]=1;
        P[Now-1][i]=1;
        P[i][Now-1]=1;}
    P[5][5]=1;
    P[2][2]=10;
    P[14][14]=5;
    start[0]=14;
    start[1]=14;
    start2[0]=14;
    start2[1]=1;
    P[14][1]=5;
    goal[0]=2;
    goal[1]=2;
    A_STAR=(int**)malloc(sizeof(int*)*32*32);
    for(i=0;i<32*32;i++)
        A_STAR[i]=(int*)malloc(sizeof(int)*2);
    A_STAR2=(int**)malloc(sizeof(int*)*32*32);
    for(i=0;i<32*32;i++)
        A_STAR2[i]=(int*)malloc(sizeof(int)*2);

        // INTIALISTAION DE LA SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Echec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }
        // Création de la fenêtre //
        SDL_Window* pWindow=NULL;
        pWindow = SDL_CreateWindow("Labyrinthe",SDL_WINDOWPOS_UNDEFINED,
                                                                  SDL_WINDOWPOS_UNDEFINED,
                                                                  880,
                                                                  600,
                                                                  SDL_WINDOW_SHOWN);


if( pWindow )
        {   while(contt!=0)
                {

                    SDL_AFFICHAGE(pWindow);

                }

            SDL_Delay(1000); // 1 SEC D ATTENTE


            SDL_DestroyWindow(pWindow);
        }
        else
        {
            fprintf(stderr,"Erreur de creation de la fenetre: %s\n",SDL_GetError());
        }
SDL_Quit();
return 0;
}









//---------------------------------------------------------------------
