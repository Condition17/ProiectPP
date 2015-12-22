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
int laps;
int pozitie;
int viteza;
int hp;
char nume[100]}player1,player2;

int restart,iesire=0,castigator=0;
void afisare_player(struct player *player){
    afisare_pista();

spacing(20);printf("--------- %s ----------\n\n",player -> nume);

spacing(20);printf("Lap: %d/3\n",player -> laps);
spacing(20);printf("Te afli pe pozitia %d la %d pozitii de urmatorul obstacol\n",player -> pozitie,distanta_obstacol(player -> pozitie));
spacing(20);printf("Pana la urmatoarea curba mai sunt %d pozitii",distanta_curba(player -> pozitie));
printf("\n");spacing(20);printf("Mai ai %d puncte de  viata",player -> hp);


}
void pozitionare(struct pista *pista,int initial,int final,char simbol){
    pista[initial].afisare = 0;
    pista[final].afisare = simbol;
    }

void turn_player(struct player *player,struct pista *pista, char simbol){

    int initial,miscare;
    initial = player -> pozitie;
    afisare_player( player );
    viteza_player( player );
 //   printf("\nviteza curenta:%d",player -> viteza);

    if(!restart && !iesire){
    miscare = deplasare(player -> viteza);
    player -> suma += miscare;

    player -> hp -= damage_obstacole(pista,miscare,player -> pozitie,player -> viteza);

    if(player -> hp<=0) {
            player ->hp = 100;
            printf("\n");spacing(20);printf("Masina s-a stricat. Drept urmare, aceasta a fost reparata si pozitionata cu %d pozitii inapoi\n",2*miscare);
            if(player -> suma - 2*miscare>=0) player -> suma -= 2*miscare;
            else player -> suma=0;
            player->viteza=0;

        }

    if ( player -> suma >= 100 ) { //cand trece prin start

        player -> laps++;
        player -> suma= player -> suma % 100;
        if(player -> hp + 20 >=100) player -> hp = 100;
        else player -> hp += 20;

        if(player -> laps == 3 && !castigator)
            if(simbol=='@') castigator=1;
            else castigator=2;

        }
    player -> pozitie = player -> suma % 100+1;

    //spacing(20);printf("miscare=%d | suma= %d | pozitie= %d\n",miscare,player->suma,player->pozitie);

    pozitionare(pista,initial,player->pozitie,simbol);
    }


}

void afisare_castigator(struct player *player){
    printf("\n");
    spacing(20);
      printf("%s a castigat aceasta cursa",player -> nume);
}

void spacing(int k){
    //functie de spatiere...mai e nevoie pe la afisare
    int o;
    for(o=1;o<=k;printf(" "),o++);
}

void intro(){
    //meniul de intrare in program

    char optiune;

    do{

    iesire=0;
    FILE *f;
    f=fopen("menu.in","r");
    char line[1000];
    while(1){
        fgets(line,1000,f);
        if(!feof(f)) printf("%s",line);
        else break;
    }
    fclose(f);
    spacing(20);
    printf("Optiunea ta: ");scanf("%hhi",&optiune);
    spacing(20);
        switch(optiune){
            case 1:{
                start_joc();
                break;

                }
            case 2:{
                printf("In curs de constructie");
                break;
            }
            default: if(optiune!=3) printf("\nOptiune invalida");
        }
    } while(optiune!=3 );
}

void pauza_joc(struct player *player){
    //meniul de pauza din joc
    //acesta poate fi accesat de jucator in timpul jocului

    char optiune;

    FILE *f;
    f=fopen("pauza.in","r");
    char line[1000];
    while(1){
        fgets(line,1000,f);
        if(!feof(f)) printf("%s",line);
        else break;
    }
    fclose(f);
    spacing(20);
    printf("Optiunea ta: ");scanf("%hhi",&optiune);
        switch(optiune){
            case 1:
                afisare_player( player );
                viteza_player(player);
                break;
            case 2:{
                restart=1;
                break;
            }
            case 3:{
                iesire=1;
                break;
            }
            default: printf("\nOptiune invalida");
        }
}



void start_joc(){
    char nume[100];

    printf("\nPlayer 1\n");
    do{
    printf("Nume:");scanf("%s",nume);}
    while(nume=="");
    strcpy(player1.nume,nume);

    printf("\nPlayer 2\n");
    do{
    printf("Nume:");scanf("%s",nume);}
    while(nume=="");
    strcpy(player2.nume,nume);

    castigator=0;
    begin();
}

void begin(){
    restart=0;
    if (restart==0) {
        initializare_playeri();
        initializare_obstacole();
        initializare_piste();
        }

while((player1.laps<=3 || player2.laps<=3) && restart==0 && iesire==0){
       if(player1.laps<=3) turn_player(&player1,&pista1,'@');
        if(player2.laps<=3) turn_player(&player2,&pista2,'#');

}

    if(restart) {
        printf("\n");
        spacing(20);
        printf("Jocul s-a restartat\n");
        begin();}

    else if(iesire) ;
    else {

        if(castigator == 1) afisare_castigator(&player1);
        else afisare_castigator(&player2);

         } //asta poate lipsi
}



void initializare_playeri(){

    //pozitiile de plecarea ale playerilor
    //+hp,+others
player1.viteza=0;
player1.laps=1;
player1.pozitie=1;
player1.suma=1;
player1.hp=100;
pista1[player1.pozitie].afisare='@';

player2.viteza=0;
player2.laps=1;
player2.pozitie=1;
player2.suma=1;
player2.hp=100;

pista2[player2.pozitie].afisare='#';


}


void afisare_pista(){
     int i,j;
//partea de sus
printf("\t\t ");

for(i=1;i<=42;i++)printf("-");
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



printf("\n\n\n");
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

void initializare_piste(){
int i;
 for(i=0;i<=100;i++) {
    pista1[i].afisare=0;
    pista2[i].afisare=0;

}
pista1[1].afisare='@';
pista2[1].afisare='#';
}

int distanta_obstacol(int pozitie){

    int ok=0, distanta=0;
    int initial=pozitie;

    while(!ok){pozitie=pozitie%101;
           if(pista1[pozitie].obstacol)ok=1;
            distanta++;
            pozitie++;
           }

        if(initial>pozitie)return distanta-2;
        return distanta-1;
        }


int distanta_curba(int pozitie){
    if(pozitie<39)return 39-pozitie;
    if(pozitie<49)return 49-pozitie;
    if(pozitie<88)return 88-pozitie;
    if(pozitie<100)return 100-pozitie;}

void viteza_player(struct player *player){

    int decizie;
    printf("\n");
    spacing(20);
    printf("Esti in viteza %d.\n\n",player->viteza);
    spacing(20);
    printf("Pentru a mari viteza cu o treapta apasa tasta 1.\n");
    spacing(20);printf("Pentru a scadea viteza cu o treapta, apasa tasta 2.\n");
    spacing(20);printf("Pentru a scadea viteza cu doua trepte, apasa tasta 3.\n");
    spacing(20);printf("Pentru a mentine viteza actuala, apasa tasta 4\n");
    spacing(20);printf("Pentru pauza apasa tasta 5.\n");
    spacing(20);printf("Optiunea ta:");scanf("%d",&decizie);
    if(decizie!=5) modificare_viteza(player,decizie);
    else pauza_joc(player);


}

void modificare_viteza(struct player *player,int decizie){

    int initial = player -> viteza;

    switch(decizie){
        case 1 :
            player -> viteza++;
            break;
        case 2 :
            player -> viteza--;
            break;
        case 3 :
            player -> viteza -= 2;
            break;
        case 4 :
            break;
        default :
            limite_viteza(player);
            break;
            }

    if(player -> viteza > 5 || player -> viteza < 1){
    //daca viteza este peste limita de 5 sau negativa se revine la viteza initiala
    //comanda nu se poate efectua
        player -> viteza = initial;
        limite_viteza(player);
}


}

void limite_viteza(struct player *player){

    int decizie;
    printf("\n");
    spacing(20);
    printf("Comanda nu se poate realiza, va rugam sa reintroduceti optiunea dorita\n");
    scanf("%d",&decizie);

modificare_viteza(player,decizie);
}

int deplasare(int viteza){

switch(viteza){
case 1 :
    return 1;
    break;
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

int damage_obstacole(struct pista *pista,int inaintare,int pozitie,int viteza){
int damage=0; int i;
for(i=pozitie+1;i<=pozitie+inaintare;i++)

if(i!=39&&i!=40&&i!=41&&i!=49&&i!=50&&i!=51&&i!=88&&i!=89&&i!=90&&i!=100&&i!=1&&i!=2)
    switch(viteza){
    case 1 :
        damage+=0;
        break;
    case 2 :
        damage+= pista[i%101].damage;
        break;
    case 3 :
        damage+=pista[i%101].damage*1,5;
        break;
    case 4 :
        damage+=pista[i%101].damage*2;
        break;
    case 5 :
        damage+=pista[i%101].damage*2,5;
        break;
                  }
  else
     if(i!=39&&i!=40&&i!=41&&i!=88&&i!=89&&i!=90)
           {if(viteza>3)damage+=10;}

         else if(viteza>4)damage+=10;

           return damage;}

int main(){


initializare_obstacole();
intro();
return 0;
}
