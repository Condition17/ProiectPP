#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct pista{
int ocupat;
int damage;
char obstacol;
char afisare;
}pista1[101],pista2[101];

struct player{
int nr_pasi;
int suma;
int laps;
int pozitie;
int viteza;
int hp;
int vieti_pierdute;
int scazut_obstacole;
int obstacole_succes;
int suma_spatii_parcurse;
char nume[100];
int trepte[5];

}player1,player2;

int restart=0,iesire=0,castigator=0;
int obstacole_curent(struct player *player){
    int i,rest=0;
    for(i=1;i<=player -> pozitie && player->laps<4;i++)
        if(i==10 || i==60 || i==80 || i==30 || i==39 || i==40 || i==41 || i==49
           || i== 50 || i == 51 || i == 88 || i == 89 || i == 91 || i == 100 || (i == 1 && player -> laps >1) || (i == 2 && player -> laps >1)) rest++;
    return (player -> laps-1)*15+rest;
}
void initializare_trepte(struct player *player){
    int i;
    for(i=1;i<=5;i++)
        player -> trepte[i]=0;
}

void utilizare_trepte(struct player *player,int viteza){
    int i=1;
    if(viteza==0) printf(".");
    else{
        for(;i<=player -> trepte[viteza];i++)
            printf("%c",223);
    }

    printf(" %d\n",player -> trepte[viteza]);
}
void statistica_jucator(struct player *player){
    char optiune[100];
    int i;
    spacing(20);printf("--------- %s ----------\n\n",player -> nume);
    spacing(20);printf("Mutari: %d\n",player -> nr_pasi);
    spacing(20);if(player -> vieti_pierdute == 0) printf("Nu ti-ai distrus masina niciodata\n");
        else if (player -> vieti_pierdute == 1)printf("Ti-ai distrus masina o singura data\n");
        else printf ("Ai distrus masina de %d ori\n",player -> vieti_pierdute);
    spacing(20);printf("Obstacole trecute fara damage: %d/%d\n",player->obstacole_succes,obstacole_curent(player));
    if( obstacole_curent(player)) {spacing(20);printf("Rata de trecere cu succes a obstacolelor: %.2f%% \n",(player -> obstacole_succes * 100.0)/obstacole_curent(player));}
    spacing(20);printf("Damage total:%d\n",player->scazut_obstacole);
    if (player -> nr_pasi) {spacing(20);printf("Viteza medie de deplasare: %d",player->suma_spatii_parcurse/player->nr_pasi);
    if(player->suma_spatii_parcurse/player->nr_pasi>1) printf(" spatii\n\n");
    else printf(" spatiu\n\n");
    spacing(20);printf("Utilizarea treptelor de viteza:\n");}

    for(i=1;i<=5;i++){
    spacing(20);printf("Viteza %d:%d",i,player -> trepte[i]); printf("\n"); //);utilizare_trepte(&player,i);
    }
    printf("\n");
do{

spacing(20);printf("Pentru a te intoarce in meniul de statistici apasa 1:");
scanf("%s",optiune);

} while(strlen(optiune)>1 || optiune[0]!='1');

}

void afisare_meniu_statistici(){

    //meniul de statistici

    FILE *f;
    f = fopen("statistici_head.in","r");
     char line[1000];
     printf("\n");
    while(1){
        fgets(line,1000,f);
        if(!feof(f)) printf("%s",line);
        else break;
    }
    fclose(f);

    printf("                    |  1 |              %s\n",player1.nume);
    printf("                    |____|________________________________________|\n");
    printf("                    |    |                                        |\n");
    printf("                    |  2 |              %s\n",player2.nume);
    printf("                    |____|________________________________________|\n");


     f = fopen("statistici_bottom.in","r");
      while(1){
        fgets(line,1000,f);
        if(!feof(f)) printf("%s",line);
        else break;
    }
    fclose(f);
}

void statistici(){

    char optiune[100];
    do{
    afisare_meniu_statistici();

    printf("\n");
    spacing(20);

    printf("Optiunea ta: ");scanf("%s",optiune);

    if(strlen(optiune)==1){

        switch(optiune[0]){
            case '1':
                statistica_jucator(&player1);
                break;
            case '2':
                statistica_jucator(&player2);
                break;

            case '3':
                break;

            default:{
                printf("\n");
            spacing(20);
             printf("Optiune invalida\n");
            }
        }
    }else {
        spacing(20);
        printf("Optiune invalida\n");}

    } while(optiune[0]!='3' || strlen(optiune)>1);
}

void sfarsit_joc(){
    //meniul de la sfrasitul cursei

   char optiune[100];
    do{
    FILE *f;
    f=fopen("sfarsit.in","r");
    char line[1000];
    while(1){
        fgets(line,1000,f);
        if(!feof(f)) printf("%s",line);
        else break;
    }
    fclose(f);
    printf("\n");
    spacing(20);
    printf("Optiunea ta: ");scanf("%s",optiune);
    if(strlen(optiune)==1){
        switch(optiune[0]){
            case '1':
                restart=1;
                printf("\n");
                spacing(20);
                printf("Jocul s-a restartat\n");
                begin();
                break;
            case '2':
                statistici();
                break;

            case '3':
                break;

            default:{
                printf("\n");
            spacing(20);
             printf("Optiune invalida\n");
            }
        }
    }else {
        printf("\n");
        spacing(20);
        printf("Optiune invalida\n");}

    } while(optiune[0]!='1' && optiune[0]!='3');

}
void hall_of_fame(){
    //Afiseaza cei mai buni 5 jucatori care au jucat jocul in functie de numarul de miscari pe care l-au avut

    struct player jucator[5];
    struct player temp,test;
    int i,j,final=0,ocupat=0; //cate elemente sunt in vectorul de jucatori la un anumit pas

    FILE *f;
    f=fopen("jucatori.in","r");
    while(1){

        fscanf(f,"%s %d",test.nume,&test.nr_pasi);
        if(feof(f)) break;
        else{
            if(ocupat==4) final=1;
            //printf("\n");spacing(20);printf("%s %d",test.nume,test.nr_pasi);
            j=ocupat;

            while(j >= 1 && test.nr_pasi < jucator[j-1].nr_pasi){
                jucator[j] = jucator[j-1];
                j--;
            }

        if(ocupat<4){
            jucator[j] = test;
            ocupat++;}
        else
            if (jucator[ocupat].nr_pasi > test.nr_pasi ) jucator[j] = test;

        }

}

        printf("\n");

         if(final==0) ocupat--; //daca nu s-a completat ultima pozitie din vector
    for(i=0;i<=ocupat;i++){
       spacing(20);printf("%d. %s %d\n",i+1,jucator[i].nume,jucator[i].nr_pasi);

        }


    fclose(f);
    }


void afisare_player(struct player *player){
    afisare_pista();

spacing(20);printf("--------- %s ----------\n\n",player -> nume);

spacing(20);printf("Lap: %d/2\n",player -> laps);
spacing(20);printf("Te afli pe pozitia %d la %d pozitii de urmatorul obstacol\n",player -> pozitie,distanta_obstacol(player -> pozitie));
spacing(20);
if(distanta_curba(player->pozitie)>0)
        printf("Pana la urmatoarea curba mai sunt %d pozitii",distanta_curba(player -> pozitie));
    else printf("Esti in curba");
printf("\n");spacing(20);printf("Mai ai %d puncte de  viata",player -> hp);


}
void pozitionare(struct pista *pista,int initial,int final,char simbol){
    pista[initial].afisare = 0;
    pista[final].afisare = simbol;
    }

void turn_player(struct player *player,struct pista *pista, char simbol){

    int initial,miscare,dmg=0;
    initial = player -> pozitie;
    afisare_player( player );
    viteza_player( player );
 //   printf("\nviteza curenta:%d",player -> viteza);

    if(!restart && !iesire){
    player -> nr_pasi++;
    miscare = deplasare(player -> viteza);

    player -> trepte[ player -> viteza]++;

    player -> suma_spatii_parcurse += miscare; //verifica daca nu cumva se poate si fara!!!

    //e posibil ca player -> suma_spatii_parcurse == player -> suma

    player -> suma += miscare;
    dmg = damage_obstacole(pista,miscare,player);
    player -> hp -= dmg;
    player -> scazut_obstacole += dmg;
    if(player -> hp<=0) {
            player ->hp = 100;
            printf("\n");spacing(20);printf("Masina s-a stricat. Drept urmare, aceasta a fost reparata si pozitionata cu %d pozitii inapoi\n",2*miscare);
            player -> vieti_pierdute++;
            if(player -> suma - miscare>=0) player -> suma -= miscare;
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
     afisare_pista();
    printf("\n");
    spacing(20);
      printf("%s a castigat aceasta cursa",player -> nume);

    FILE *f;

    f = fopen("jucatori.in","a");
    fprintf(f,"%s %d\n",player->nume,player->nr_pasi);
    fclose(f);
}

void spacing(int k){
    //functie de spatiere...mai e nevoie pe la afisare
    int o;
    for(o=1;o<=k;printf(" "),o++);
}

void intro(){
    //meniul de intrare in program

    char optiune[100];

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
    printf("Optiunea ta: ");scanf("%s",optiune);
    spacing(20);
    if(strlen(optiune)==1){

        switch(optiune[0]){
            case '1':{
                start_joc();
                break;

                }
            case '2':{
                hall_of_fame();
                break;
            }

            default: if(optiune[0]!='3') printf("Optiune invalida\n");
        }

        } else
            printf("Optiune invalida\n");

        } while(optiune[0]!='3' || strlen(optiune)>1 );



}

void pauza_joc(struct player *player){
    //meniul de pauza din joc
    //acesta poate fi accesat de jucator in timpul jocului

    char optiune[100];
    do{
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
    printf("Optiunea ta: ");scanf("%s",optiune);
    printf("\n");
    spacing(20);
        if(strlen(optiune)==1){
        switch(optiune[0]){
            case '1':
                afisare_player( player );
                viteza_player(player);
                break;
            case '2':{
                statistici();
                break;
            }

            case '3':{
                restart=1;
                break;
            }
            case '4':{
                iesire=1;
                break;
            }
            default:{
                 spacing(20);
                 printf("Optiune invalida\n");
            }
        }
        } else printf("Optiune invalida\n");
        } while ((optiune[0]!='1'  && optiune[0]!='3' && optiune[0]!='4') || strlen(optiune)>1);
}



void start_joc(){
    char nume1[100];
    char nume2[100];
    printf("\n");
    spacing(20);printf("Player 1\n");
    do{
    spacing(20);printf("Nume:");scanf("%s",nume1);}
    while(nume1=="");
    strcpy(player1.nume,nume1);


    do{
    spacing(20);printf("Player 2\n");
    spacing(20);printf("Nume:");scanf("%s",nume2);}
    while(nume2=="" || strcmp(nume1,nume2)==0);
    strcpy(player2.nume,nume2);

    castigator=0;
    begin();
}

void begin(){

    restart=0;
    if (restart==0) {
        initializare_playeri();
        initializare_obstacole();
        initializare_piste();
        castigator=0;
        }

while((player1.laps<=2 || player2.laps<=1) && restart==0 && iesire==0){
       if(player1.laps<=2) turn_player(&player1,&pista1,'@');
       //daca intri in joc si dai iesire/restart fara conditiile restart==0 si iesire==0 o sa treaca la player2 si mai apoi o sa iasa
       if(player2.laps<=2 && restart==0 && iesire==0) turn_player(&player2,&pista2,'#');

}

    if(restart) { //daca se da restart in timpul desfasurarii jocului
        printf("\n");
        spacing(20);
        printf("Jocul s-a restartat\n");
        begin();}

    else if(iesire) ; //iesire in timpul desfasurarii jocului
    else {

        if(castigator == 1)
            afisare_castigator(&player1);
        else afisare_castigator(&player2);
        sfarsit_joc(); //meniul de la finalul fiecarei partide
         } //asta poate lipsi
}



void initializare_playeri(){

    //pozitiile de plecarea ale playerilor
    //+hp,+others
player2.nr_pasi=player1.nr_pasi=0;
player1.viteza=0;
player1.laps=1;
player1.pozitie=1;
player1.suma=1;
player1.hp=100;
player1.vieti_pierdute=0;
player1.scazut_obstacole=0;
pista1[player1.pozitie].afisare='@';
player1.obstacole_succes=0;
player1.suma_spatii_parcurse=0;
initializare_trepte(&player1);

player2.viteza=0;
player2.laps=1;
player2.pozitie=1;
player2.suma=1;
player2.hp=100;
player2.vieti_pierdute;
pista2[player2.pozitie].afisare='#';
player2.obstacole_succes=0;
player2.suma_spatii_parcurse=0;
player2.scazut_obstacole=0;
initializare_trepte(&player2);
}


void afisare_pista(){
     int i,j;
//partea de sus
printf("\n");
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
pista1[10].damage=20;
pista2[10].damage=20;
pista1[60].damage=20;
pista2[60].damage=20;
pista1[30].damage=20;
pista2[30].damage=10;
pista1[80].damage=10;
pista2[80].damage=10;

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


int distanta_curba(int pozitie){int i=pozitie;
    if(i==39||i==40||i==41||i==49||i==50||i==51||i==88||i==89||i==90||i==100||i==1||i==2)return -1;
    if(pozitie<39)return 39-pozitie;
    if(pozitie<49)return 49-pozitie;
    if(pozitie<88)return 88-pozitie;
    if(pozitie<100)return 100-pozitie;}

void viteza_player(struct player *player){

    char decizie[100];
    printf("\n");
    spacing(20);
    printf("Esti in viteza %d.\n\n",player->viteza);
    spacing(20);
    printf("Pentru a mari viteza cu o treapta apasa tasta 1.\n");
    spacing(20);printf("Pentru a scadea viteza cu o treapta, apasa tasta 2.\n");
    spacing(20);printf("Pentru a scadea viteza cu doua trepte, apasa tasta 3.\n");
    spacing(20);printf("Pentru a mentine viteza actuala, apasa tasta 4\n");
    spacing(20);printf("Pentru pauza apasa tasta 5.\n");
    spacing(20);printf("Optiunea ta:");scanf("%s",decizie);
    modificare_viteza(player,&decizie);



}

void modificare_viteza(struct player *player,char decizie[100]){

    int initial = player -> viteza;
    if(strlen(decizie)==1){
    switch(decizie[0]){
        case '1' :
            player -> viteza++;
            break;
        case '2' :
            player -> viteza--;
            break;
        case '3' :
            player -> viteza -= 2;
            break;
        case '4' :
            break;
        case '5':
            pauza_joc(player);
            break;
        default: if(!(player -> viteza > 5 || player -> viteza < 1)) limite_viteza(player);
            }

    } else if(!(player -> viteza > 5 || player -> viteza < 1)) limite_viteza(player);

    if((player -> viteza > 5 || player -> viteza < 1)&& !iesire && !restart){
    //daca viteza este peste limita de 5 sau negativa se revine la viteza initiala
    //comanda nu se poate efectua
        player -> viteza = initial;
        limite_viteza(player);
}



}

void limite_viteza(struct player *player){

    char decizie[100];
    printf("\n");
    spacing(20);
    printf("Comanda nu se poate realiza, va rugam sa reintroduceti optiunea dorita\n");
    spacing(20);
    scanf("%s",decizie);
    modificare_viteza(player,&decizie);
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
return 0;
}

int damage_obstacole(struct pista *pista,int inaintare,struct player *player){
int damage=0; int i;
for(i=player -> pozitie+1;i<=player -> pozitie+inaintare;i++)

if(i!=39&&i!=40&&i!=41&&i!=49&&i!=50&&i!=51&&i!=88&&i!=89&&i!=90&&i!=100&&i!=1&&i!=2)
    switch(player -> viteza){
    case 1 :
        damage+=0;
        if(i==10 || i==30 || i == 60 || i == 80) player -> obstacole_succes++;
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

}  else
     if(i!=39&&i!=40&&i!=41&&i!=88&&i!=89&&i!=90)
           {if(player -> viteza>3)damage+=10;
                else if (player -> laps > 1) player -> obstacole_succes++;

           }

         else if (player -> viteza>4)damage+=10;
                else
                    player -> obstacole_succes++;

           return damage;

           }

int main(){


initializare_obstacole();
intro();
return 0;
}
