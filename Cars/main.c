#include <stdio.h>
#include <stdlib.h>
struct pista{
int ocupat;
int damage;
char obstacol;
char afisare;
}pista1[101],pista2[101];
struct player{
int suma;
int pozitie;
int viteza;
int hp;
char nume[100]}player1,player2;
void afisare_pista(){
     int i,j;
//partea de sus
printf("\t\t ");
for(i=1;i<=42;i++)printf("_");
printf("\n");
printf("\t       /  ");
for(i=1;i<=40;i++)if(pista1[i].afisare!=0)printf("%c",pista1[i].afisare);
                     else printf("%c",pista1[i].obstacol);
printf(" \\\t\t  \n\t       |  ");
for(i=1;i<=40;i++)if(pista2[i].afisare!=0)printf("%c",pista2[i].afisare);
                       else printf("%c",pista2[i].obstacol);
printf("  |\n\t       |   ");
for(i=1;i<=38;i++)printf("_");
printf("   |");
//partea din mijloc
for(j=1;j<=10;j++){printf("\n\t       |%c%c|",pista1[101-j].afisare,pista2[101-j].afisare);
for(i=1;i<=38;i++)printf(" ");
printf("|%c%c|",pista2[40+j].afisare,pista1[40+j].afisare);}
//partea de jos


printf("\n\t       |   ");
for(i=1;i<=38;i++)printf("_");
printf("   | ");
printf("\n\t       |  ");
for(i=1;i<=40;i++)if(pista2[91-i].afisare)printf("%c",pista2[91-i].afisare);
                    else printf("%c",pista2[91-i].obstacol);
printf("  |\n");
printf("\t       |  ");
for(i=1;i<=40;i++)if(pista1[91-i].afisare)printf("%c",pista1[91-i].afisare);
                     else printf("%c",pista1[91-i].obstacol);
printf("  |\n");

printf("   \t        \\ ");
for(i=1;i<=40;i++)printf("_");
printf(" /");



printf("\n\n\n\n\n\n\n\n\n");
}
void initializare_obstacole(){
pista1[10].obstacol='o';
pista2[10].obstacol='o';
pista1[60].obstacol='o';
pista2[60].obstacol='o';
pista1[30].obstacol=254;
pista2[30].obstacol=254;
pista1[80].obstacol=254;
pista2[80].obstacol=254;
pista1[10].damage=30;
pista2[10].damage=30;
pista1[60].damage=30;
pista2[60].damage=30;
pista1[30].damage=20;
pista2[30].damage=20;
pista1[80].damage=20;
pista2[80].damage=20;
}
void afisare_player1(){
    afisare_pista();
printf("%s se afla pe pozitia %d la %d pozitii de urmatorul obstacol\n",player1.nume,player1.pozitie,distanta_obstacol(player1.pozitie));
printf("Pana la urmatoarea curba mai sunt %d pozitii",distanta_curba(player1.pozitie));
printf("\nMai aveti %d puncte de  viata",player1.hp);

}
void afisare_player2(){
    afisare_pista();
printf("%s se afla pe pozitia %d la %d pozitii de urmatorul obstacol\n",player2.nume,player2.pozitie,distanta_obstacol(player2.pozitie));
printf("Pana la urmatoarea curba mai sunt %d pozitii",distanta_curba(player2.pozitie));
printf("\nMai aveti %d puncte de  viata",player2.hp);

}
int distanta_obstacol(int pozitie){
int ok=0, distanta=0; int initial=pozitie;
while(!ok){pozitie=pozitie%101;
           if(pista1[pozitie].obstacol)ok=1;
           distanta++;
           pozitie++;
           }
        if(initial>pozitie)return distanta-2;
        return distanta-1;}
int distanta_curba(int pozitie){
if(pozitie<39)return 39-pozitie;
if(pozitie<49)return 49-pozitie;
if(pozitie<88)return 88-pozitie;
if(pozitie<100)return 100-pozitie;}
void viteza_player1(){int decizie;
printf("\nSunteti in viteza %d.\nPentru a mari viteza cu o treapta apasati tasta 1.\nPentru a scadea viteza cu o treapta, apasati tasta 2.\nPebtru a scadea viteza cu doua trepte, apasati tasta 3.\nPentru a mentine viteza actuala, apasati tasta 4\n",player1.viteza);
scanf("%d",&decizie);
modificare_viteza(decizie);}
void modificare_viteza(int decizie){
int initial=player1.viteza;
switch(decizie){
case 1 :
    player1.viteza++;
    break;
case 2 :
    player1.viteza--;
    break;
case 3 :
    player1.viteza-=2;
    break;
case 4 :
    break;
default :
    limite_viteza();
    break;}
if(player1.viteza>5||player1.viteza<1){
    player1.viteza=initial;
    limite_viteza();
}
}
void limite_viteza(){int decizie;
printf("\nComanda nu se poate realiza, va rugam sa reintroduceti optiunea dorita\n");
scanf("%d",&decizie);
modificare_viteza(decizie);}
int deplasare(int viteza){
switch(viteza){
case 1 :
    return 1;
case 2 :
    return rand()%3+1;
case 3 :
    return rand()%4+2;
case 4 :
    return rand()%5+3;
case 5 :
    return rand()%7 +4;
    }
}
int damage_obstacole(int inaintare,int pozitie,int viteza){
int damage=0; int i;
for(i=pozitie+1;i<=pozitie+inaintare;i++)
if(i!=39&&i!=40&&i!=41&&i!=49&&i!=50&&i!=51&&i!=88&&i!=89&&i!=90&&i!=100&&i!=1&&i!=2)
    switch(viteza){
    case 1 :
        damage+= 0;
        break;
    case 2 :
        damage+= pista1[i%101].damage;
        break;
    case 3 :
        damage+=pista1[i%101].damage*1,5;
        break;
    case 4 :
        damage+=pista1[i%101].damage*2;
        break;
    case 5 :
        damage+=pista1[i%101].damage*2,5;
        break;
                  }
  else
     if(i!=39&&i!=40&&i!=41&&i!=88&&i!=89&&i!=90)
           {if(viteza>3)damage+=10;}

         else if(viteza>4)damage+=10;

           return damage;}
void pozitionare(int initial){pista1[initial].afisare=0;
                   pista1[player1.pozitie].afisare='@';}

int main(){int miscare,initial;
initializare_obstacole();
player1.suma=1;
player1.hp=100;
strcpy(player1.nume,"Stefan");
player1.pozitie=1;
while(1){initial=player1.pozitie;
pista1[player1.pozitie].afisare='@';
afisare_player1();
viteza_player1();
miscare=deplasare(player1.viteza);
player1.suma+=miscare;
player1.hp-=damage_obstacole(miscare,player1.pozitie,player1.viteza);
player1.pozitie=player1.suma%100+1;
pozitionare(initial);
}
    return 0;
}
