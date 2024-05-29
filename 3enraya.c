#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char jugador1[39], jugador2[39], jugador[39];
char tablero[3][3];
int n;//se borra después
void inicializarTablero(char  tableroVacio[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            tableroVacio[i][j]= ' ';

    }
}
void imprimir(char tableroImprimir[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("|%c|", tableroImprimir[i][j]);
        }
        printf("\n");
        printf("---------\n");
    }
}
int turno(){
    static int turnoJugador=0;
    turnoJugador++;
    if (turnoJugador%2!=0)
        return 1;
    else
        return 0;
}
int comprobar(int *filaComprobar, char *columnaComprobar) {
    int aux;
    if (*columnaComprobar>'c') {
        aux = *columnaComprobar - 'A';
    }
    else {
        aux = *columnaComprobar - 'a';
    }
    if(tablero[*filaComprobar][aux]!= ' ') {
        printf("Posici\xA2n ya ocupada, elige otros par\xA0metros\n");

        return 0;
    }
    else
        return 1;
}
void vaciarEntrada(){
    char c;
    while((c=getchar())!='\n');

}
void colocarFicha(char *col, int *fila, char jugador[]){
    int valido;
    int aux;
    char entrada[256];
    do {
        printf("Es el turno de %s\n", jugador);

        printf("\xA8 En qu\x82 columna quieres poner tu ficha?\n");
        do {
            vaciarEntrada();
            scanf("%s", entrada);
            if (strlen(entrada) == 1) {
                *col = entrada[0];
                if (*col == 'a' || *col == 'b' || *col == 'c' || *col == 'A' || *col == 'B' || *col == 'C') {
                    valido = 1;
                }
                else {
                    valido=0;
                    printf("La columna que has introducido no existe, elige otra\n");
                }}
            else {
                valido = 0;
                printf("La columna que has introducido tiene más de un car\xA0\x67ter, introduce una columna v\xA0lida\n");
            }
        } while (valido != 1);
        printf("\xA8Y en qu\x82 fila quieres colocar tu ficha?\n");
        do {
            vaciarEntrada();
            if((n=scanf("%d", fila))>0){
                *fila = *fila - 1;
                if (*fila == 0 || *fila == 1 || *fila == 2) {

                    valido = 1;
                } else {
                    valido = 0;
                    printf("La fila que has introducido no existe, introduce una fila v\xA0lida\n");
                }
            }
            else{
                valido=0;
                printf("Valor de fila introducido incorrecto, elige otro\n");
            }
        } while (valido != 1);

    }while (comprobar(fila, col)!=1);
    if (*col>'c') {
        aux = *col - 'A';
    }
    else {
        aux = *col - 'a';
    }
    if(strcmp(jugador, jugador1)==0)
        tablero[*fila][aux]='X';

    else

        tablero[*fila][aux]='O';

}
int ganado(int *fila , char *col) {
    int aux;
    int auxfila, auxcol;
    int gana;
    int i;
    char pos;
    if (*col>'c') {
        aux = *col - 'A';
    }
    else {
        aux = *col - 'a';
    }
    auxcol=aux;
    pos=tablero[*fila][aux];
    aux++;
    aux=aux%3;
    //se comprueba por filas y luego por columnas
    for(i=0; i<2;i++){
        if(pos==tablero[*fila][aux]){
            aux++;
            aux=aux%3;
            if (pos==tablero[*fila][aux]){
                gana=1;

                return gana;
            }
        }
    }
    auxfila=*fila;
    pos=tablero[auxfila][auxcol];
    auxfila++;
    auxfila=auxfila%3;

    //aqui es donde se ve por columnas si gana
    for(i=0; i<2;i++){
        if(pos==tablero[auxfila][auxcol]){
            auxfila++;
            auxfila=auxfila%3;
            if (pos==tablero[auxfila][auxcol]){
                gana=1;

                return gana;
            }
        }
    }
    // aquí se ve la diagonal de arriba a abajo
    // se comprueba que los dos indices sean iguales
    auxfila=*fila;
    aux = auxcol;
    if(auxfila == aux){
        pos=tablero[auxfila][aux];
        aux++;
        aux=aux%3;
        auxfila++;
        auxfila=auxfila%3;

        for(i=0; i<2;i++){
            if(pos==tablero[auxfila][aux]){
                auxfila++;
                auxfila=auxfila%3;
                aux++;
                aux=aux%3;
                if (pos==tablero[auxfila][aux]){
                    gana=1;

                    return gana;
                }
            }
        }
    }


    // aquí se ve la diagonal de abajo a arriba
    // la diagonal tiene la particularidad de que los índices suman 2
    // Por tanto hay que ver que todas las posicionmes son iguales

    auxfila=*fila;
    aux = auxcol;
    if ((auxfila+aux) ==2)
    {
        if(tablero[2][0] == tablero[1][1])
            if(tablero[1][1] == tablero[0][2])
            {
                gana=1;
                return gana;
            }
    }


    gana=0;
    return gana;


}
int comprobarTuyo(int *filaComprobar, char *columnaComprobar, char jugador[]) {
    int aux;
    char caracter;
    if (*columnaComprobar>'c') {
        aux = *columnaComprobar - 'A';
    }
    else {
        aux = *columnaComprobar - 'a';
    }
    if(strcmp(jugador,jugador1)==0)
        caracter='X';
    else
        caracter='O';
    if(tablero[*filaComprobar][aux]== caracter)
        return 1;
    else
        return 0;
}
int moverFicha(char *col, int *fila, char jugador[]){
    //Comprueba que en la posición que se le ha indicado hay una ficha del jugador correspondiente y la vacía
    int valido;
    int aux;
    char entrada[256];
    do {
        printf("Es el turno de %s\n", jugador);

        printf("\xA8 En qu\x82 columna está la ficha que quieres cambiar?\n");
        do {
            vaciarEntrada();
            scanf("%s", entrada);
            if (strlen(entrada) == 1) {
                *col = entrada[0];
                if (*col == 'a' || *col == 'b' || *col == 'c' || *col == 'A' || *col == 'B' || *col == 'C') {
                    valido = 1;
                }
                else {
                    valido=0;
                    printf("La columna que has introducido no existe, elige otra\n");
                }}
            else {
                valido = 0;
                printf("La columna que has introducido tiene más de un car\xA0\x67ter, introduce una columna v\xA0lida\n");
            }
        } while (valido != 1);
        printf("\xA8Y en qu\x82 fila está?\n");
        do {
            vaciarEntrada();
            if((n=scanf("%d", fila))>0){
                *fila = *fila - 1;
                if (*fila == 0 || *fila == 1 || *fila == 2) {

                    valido = 1;
                } else {
                    valido = 0;
                    printf("La fila que has introducido no existe, introduce una fila v\xA0lida\n");
                }
            }
            else{
                valido=0;
                printf("Valor de fila introducido incorrecto, elige otro\n");
            }
        } while (valido != 1);

    }while (comprobarTuyo(fila, col, jugador)!=1);
    if (*col>'c') {
        aux = *col - 'A';
    }
    else {
        aux = *col - 'a';
    }

    tablero[*fila][aux]=' ';
    imprimir(tablero);
    colocarFicha(col, fila, jugador);
    imprimir(tablero);
    return 1;
}
int main(int argc, char *argv[]) {
    int i, j, k;
    int fila;
    char col;
    system("clear");
    system("cls");
    printf("\n");
    printf("##################\n");
    printf("    3 EN RAYA\n");
    printf("##################\n");
    printf("\n");
    //inicializa el tablero a ' '
    inicializarTablero(tablero);
    printf("Introduce el nombre del primer jugador:\n");
    scanf("%[a-z A-Z á-ú é Á-Ú]", jugador1);
    vaciarEntrada();
    printf("Ahora introduce el nombre del segundo jugador:\n");
    scanf("%[a-z A-Z á-ú é Á-Ú]", jugador2);
    //Más adelante, pedir confirmación de si los nombres son correctos y si los quiere cambiar
    //imprime el tablero
    printf("El primer jugador se representar\xA0 con 'X' y el segundo con 'O'\n");
    if(turno()==1){
        strcpy(jugador, jugador1);
    } else
        strcpy(jugador, jugador2);

    for(i=0; i<6; i++){
        imprimir(tablero);
        colocarFicha(&col, &fila, jugador);
        /*if(turno()==1){
            strcpy(jugador, jugador1);
        } else
            strcpy(jugador, jugador2);*/
        if(i==4 || i==5){
            if(ganado(&fila, &col))
            {
                imprimir(tablero);
                printf("HA GANADO EL JUGADOR = %s\n",jugador);
                return EXIT_SUCCESS;//ha ganado el primer jugador al colocar las 3 primeroas fichas
            }
        }

        // cambio de turno
        if(turno()==1){
            strcpy(jugador, jugador1);
        } else
            strcpy(jugador, jugador2);


    }
    //
    // a partir de aquí se pueden cambiar las fichas de posición porque ya se han puesto las 6 en el tablero y la lógica cambia
    //

    printf("AHORA PUEDE CAMBIAR LA POSICIÓN DE LA FICHA el jugador = %s\n", jugador);
    imprimir(tablero);

    do{
        moverFicha(&col,&fila, jugador);
        if(turno()==1){
            strcpy(jugador, jugador1);
        } else
            strcpy(jugador, jugador2);
    }while(ganado(&fila, &col)!=1);
    
    printf("¡Has ganado!\n");
    return EXIT_SUCCESS;
}
