#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

// Funcion para realizar las sustituciones de jugadores
int Cambios(int *a, int entra, int sale, int cancha[11][2], int afuera[5][2]){
    if(*a>=5){
        return 0;
    }
    if(cancha[sale-1][1]==-1){
        return 0;
    }
    else{
        int aux=cancha[sale][0];
        int auxfaltas=cancha[sale][1];
        cancha[sale][0] = afuera[entra][0];
        cancha[sale][1] = afuera[entra][1];
        afuera[entra][0]= aux;
        afuera[entra][1]= auxfaltas;
        (*a)++;
        return 1;
    }
}

// Funcion para manejar las tarjetas amarillas y rojas
void manejarTarjeta(int jugador, int equipo[][2], int *tarjetasAmarillas, int *tarjetasRojas, int *jugadoresEnCancha){
    if (equipo[jugador][1] == 1){
        (*tarjetasAmarillas)++;
        printf("\t\t\tEl jugador %d ha sido amonestado. Otra mas y no habra perdon\n", equipo[jugador][0]);
    }
    else if (equipo[jugador][1] == 2){
        (*tarjetasAmarillas)++;
        (*tarjetasRojas)++;
        (*jugadoresEnCancha)--;
        printf("\t\t\tEl jugador %d ha recibido su segunda amarilla. EXPULSION!\n", equipo[jugador][0]);
        int aux=equipo[jugador][0];
        for(int i=jugador; i<10; i++){
            equipo[i][0] = equipo[i + 1][0];
            equipo[i][1] = equipo[i + 1][1];
        }
        equipo[10][0] = aux;
        equipo[10][1] = 2;
    }
    else if(equipo[jugador][1]==-1){
        printf("\t\t\tEl jugador %d ha sido expulsado con roja directa.\n", equipo[jugador][0]);
        (*tarjetasRojas)++;
        (*jugadoresEnCancha)--;
        int aux=equipo[jugador][0];
        for(int i=jugador; i<10; i++){
            equipo[i][0] = equipo[i + 1][0];
            equipo[i][1] = equipo[i + 1][1];
        }
        equipo[10][0] = aux;
        equipo[10][1] = -1;
    }
}

// Funcion para mostrar las estadisticas del Partido
void estadisticas(int Amarilla, int Roja, int Cancha[11][2], int Banca[5][2]){
    if(Amarilla>0){
        printf("Tarjetas Amarillas: \n");
        for (int i = 0; i < 16; i++){
            if(i<11){
                if(Cancha[i][1] == 1){
                    printf("\tJugador Numero: %d\n", (Cancha[i][0]));
                }
            }
            else{
                if(Banca[i-11][1] == 1){
                    printf("\tJugador Numero: %d\n", (Banca[i-11][0]));
                }
            }
        }
    }

    else{
        printf("No hubo tarjeta Amarillas\n");
    }
    
    if(Roja>0){
        printf("Tarjetas Rojas: \n");
        for(int i=0; i<11; i++){
            if(Cancha[i][1]== -1){
                printf("\tJugador Numero: %d (Roja Directa)\n", (Cancha[i][0]));
            }
            else if(Cancha[i][1]==2){
                printf("\tJugador Numero: %d (Doble Amarilla)\n", (Cancha[i][0]));
            }
        }
    }
    else{
        printf("No hubo tarjeta Rojas\n");
    }

}

// La funcion principal que simula el partido
void partido(int Rival, int PdeO){
    int golesAlbirroja=0, golesRival=0;
    int CambiosAlbirroja=0, CambiosRival=0;
    int faltasAlbirroja=0, faltasRival=0;
    int TarjetasAmarillasAlbirroja=0, TarjetasAmarillasRival=0;
    int TarjetasRojasAlbirroja=0, TarjetasRojasRival=0;
    int NumeroDeJugadoresAlbirroja=11, NumeroDeJugadoresRival=11;
    int Rivalencancha[11][2]={{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0},{10,0},{11,0}};
    int Albirrojaencancha[11][2]={{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0},{10,0},{11,0}};
    int RivalSuplentes[5][2]={{12,0},{13,0},{14,0},{15,0},{16,0}};
    int AlbirrojaSuplente[5][2]={{12,0},{13,0},{14,0},{15,0},{16,0}};
    char rivales[4][15] = {"Uruguay", "Brasil", "Ecuador", "Peru"};

    for(int i = 0; i<=90; i++){
        if(i==45){
            printf("Termina el primer tiempo\n");
            printf("------------Descanso------------\n");
            printf("Comienza el segundo tiempo\n");
        }
        int evento = (rand()%100);
        printf("Minuto %d del partido:\t", i);
        if(evento < PdeO){
            int evento = rand()%5;
            switch(evento){
                case 0:{ //Cambio
                    int equipo = rand()%2;
                    if(CambiosAlbirroja==5 || CambiosRival==5){
                        if(equipo==0){
                            printf("El DT Albirrojo ya no puede hacer cambios y esta que se desespera\n");
                        }
                        else if(equipo==1){
                            printf("El DT de %s ya no puede hacer cambios y esta que se desespera\n", rivales[Rival]);
                        }
                        break;
                    }
                    else{
                        int EntraPy = rand()%(5-CambiosAlbirroja);
                        int SalePy = rand()%11;
                        int EntraRiv= rand()%(5-CambiosRival);
                        int SaleRiv = rand()%11;
                        printf("Parece que se producira un cambio\n");
                        int PYaux=Albirrojaencancha[SalePy][0];
                        int PYauxfaltas=Albirrojaencancha[SalePy][1];
                        int RIVaux=Rivalencancha[SaleRiv][0];
                        int RIVauxfaltas=Rivalencancha[SaleRiv][1];

                        if(equipo == 0){
                            if (Cambios(&CambiosAlbirroja, EntraPy, SalePy, Albirrojaencancha, AlbirrojaSuplente)){
                                printf("\t\t\tCambio en la albirroja\n");
                                printf("\t\t\tEl jugador %d sale y entra el suplente numero %d\n", AlbirrojaSuplente[EntraPy][0], Albirrojaencancha[SalePy][0]);
                            
                                for(int i=EntraPy; i<4; i++){
                                    AlbirrojaSuplente[i][0] = AlbirrojaSuplente[i + 1][0];
                                    AlbirrojaSuplente[i][1] = AlbirrojaSuplente[i + 1][1];
                                }
                                AlbirrojaSuplente[4][0]=PYaux;
                                AlbirrojaSuplente[4][1]=PYauxfaltas;
                            }
                        }
                        else{
                            if(Cambios(&CambiosRival, EntraRiv, SaleRiv, Rivalencancha, RivalSuplentes)){
                                printf("\t\t\tCambio en la seleccion de %s\n", rivales[Rival]);
                                printf("\t\t\tEl jugador %d sale y entra el suplente numero %d\n", RivalSuplentes[EntraRiv][0], Rivalencancha[SaleRiv][0]);
                            
                                for(int i=EntraRiv; i<4; i++){
                                    RivalSuplentes[i][0] = RivalSuplentes[i + 1][0];
                                    RivalSuplentes[i][1] = RivalSuplentes[i + 1][1];
                                }
                                RivalSuplentes[4][0]=RIVaux;
                                RivalSuplentes[4][1]=RIVauxfaltas;
                            }
                        };
                    break;}}
                case 1:{ //GOL PY
                    golesAlbirroja++;
                    printf("GOOOOOOOOOLAAAAAAZOOOOOOOOOOO DE LA ALBIRROJAAAAAAAA\n");
                    break;}
                case 2:{ //GOL RIVAL
                    golesRival++;
                    printf("gol de %s :| \n", rivales[Rival]);
                    break;}
                case 3:{ //FALTA PY
                    faltasAlbirroja++;
                    printf("Falta de la albirroja\n");
                    int nivel = rand() % 10;
                    int infractor = rand() %11;
                    do {
                        infractor = rand()%11;
                    } while (Albirrojaencancha[infractor][1]==-1 || Albirrojaencancha[infractor][1]==2);
                    
                    if (4<nivel && nivel<8) { //Amarilla
                        Albirrojaencancha[infractor][1]+= 1;
                        manejarTarjeta(infractor, Albirrojaencancha, &TarjetasAmarillasAlbirroja, &TarjetasRojasAlbirroja, &NumeroDeJugadoresAlbirroja);
                    }
                    else if (8<nivel){ //Roja Directa
                        Albirrojaencancha[infractor][1]=-1;
                        manejarTarjeta(infractor, Albirrojaencancha, &TarjetasAmarillasAlbirroja, &TarjetasRojasAlbirroja, &NumeroDeJugadoresAlbirroja);
                    }
                    else{ //No pasa nada
                        printf("\t\t\tEl jugador %d se ha salvado de la amonestacion\n", Albirrojaencancha[infractor][0]);
                    }
                    break;}
                case 4:{ //FALTA RIVAL
                    faltasRival++;
                    printf("Falta del rival\n");
                    int nivel = rand() % 10;
                    int infractor = rand() % 11;
                    do {
                        infractor= rand()%11;
                    } while (Rivalencancha[infractor][1]==-1 || Rivalencancha[infractor][1]==2);

                    if (4<nivel && nivel<9){ //Amarilla
                        Rivalencancha[infractor][1]+= 1;
                        manejarTarjeta(infractor, Rivalencancha, &TarjetasAmarillasRival, &TarjetasRojasRival, &NumeroDeJugadoresRival);
                        
                    } 
                    else if (8<nivel){//Roja Directa
                        Rivalencancha[infractor][1]=-1;
                        manejarTarjeta(infractor, Rivalencancha, &TarjetasAmarillasRival, &TarjetasRojasRival, &NumeroDeJugadoresRival);
                    } 
                    else{ //No pasa nada
                        printf("\t\t\tEl jugador %d se ha salvado de la amonestacion\n", Rivalencancha[infractor][0]);
                        }
                        break;}
                default:{
                    printf("Error en el evento\n");
                    break;}
            }}
        else{
            printf("Sin Eventos\n");
        }
        if(NumeroDeJugadoresAlbirroja<7 || NumeroDeJugadoresRival<7){
            printf("EL PARTIDO HA SIDO TERMINADO POR FALTA DE JUGADORES EN CANCHA\n");
            if(NumeroDeJugadoresAlbirroja<7){
                printf("La albirroja ha perdido el partido por las 5 expulsiones.\n");
                golesAlbirroja=0;
                golesRival=3;
            }
            else{
                printf("LA ALBIRROJA GANA POR WALKOVER\n");
                golesAlbirroja=3;
                golesRival=0;
            }
            break;
        }
    }


    printf("El partido ha terminado\n");
    printf("El resultado final es: %d - %d\n", golesAlbirroja, golesRival);
    if(golesAlbirroja > golesRival){
        printf("LA ALBIRROJA ESTA A UN PASO DEL MUNDIAL, SIEMPRE CAMPEONES ALBIRROJA VAMOS A POR MAS\n");
    }
    else if(golesAlbirroja < golesRival){
        printf("La albirroja ha perdido el partido\n");
    }
    else{
        printf("El partido ha terminado en empate\n");
    }
    printf("\n---------ESTADISTICAS---------\n");
    printf("La Albirroja ha tenido %d faltas\n", faltasAlbirroja);
    printf("De las cuales %d fueron tarjetas amarillas y %d fueron tarjetas rojas\n", TarjetasAmarillasAlbirroja, TarjetasRojasAlbirroja);
    printf("Jugadores de la albirroja amonestados:\n");
    estadisticas(TarjetasAmarillasAlbirroja, TarjetasRojasAlbirroja, Albirrojaencancha, AlbirrojaSuplente);

    printf("\nEl Rival ha tenido %d faltas\n", faltasRival);
    printf("De las cuales %d fueron tarjetas amarillas y %d fueron tarjetas rojas\n", TarjetasAmarillasRival, TarjetasRojasRival);
    printf("Jugadores del rival amonestados:\n");
    estadisticas(TarjetasAmarillasRival, TarjetasRojasRival, Rivalencancha, RivalSuplentes);
}

int main(){
    int opcion;
    do {
        printf("\n\n-----MENU DE OPCIONES-----\n");
        printf("1. Prediccion de partidos\n");
        printf("2. Canticos\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        opcion = getche() - '0'; 
        srand(time(NULL));
        printf("\n");
        switch (opcion) {
            case 1: {
                int contrincante;
                char rivales[4][15] = {"Uruguay", "Brasil", "Ecuador", "Peru"};
                printf("\n-----PREDICCION DE PARTIDOS-----\n");
                for(int i=0; i<4; i++){
                    printf("%d. %s\n", i+1, rivales[i]);
                }
                do{
                    int PdeO;
                    printf("Ingrese el numero del contrincante de la albirroja (1-4): ");
                    scanf("%d", &contrincante);
                    int rival = contrincante-1;
                    printf("Ingrese un numero entre 0-100\n (Sera el Porc. de ocurrencia en cada minuto de juego): ");
                    scanf("%d", &PdeO);
                    if(PdeO < 0 || PdeO > 100){
                        printf("Error. Ingrese un porcentaje entre 0 y 100.\n");
                        break;
                    }
                    PdeO/=2;
                    switch (contrincante){
                    case 1:{
                        printf("---------Partido contra Uruguay---------\n");
                        partido(rival, PdeO);}
                        
                        break;
                    case 2:{
                        printf("---------Partido contra Brasil---------\n");
                        partido(rival, PdeO);
                        break;}
                    case 3:{
                        printf("---------Partido contra Ecuador---------\n");
                        partido(rival, PdeO);
                        break;}
                    case 4:{ 
                        printf("---------Partido contra Peru---------\n");
                        partido(rival, PdeO);
                        break;}
                    default:{
                        printf("Error. Ingrese un numero entre 1 y 4.\n");
                        break;}
                    }                    
                } while(contrincante < 1 || contrincante > 4);
                break;} 
            case 2: {
                int vocales=0;
                printf("\n-----CANTICOS-----\n");
                printf("Ingrese su cantico: ");
                char cantico[500];
                fgets(cantico, sizeof(cantico), stdin);
                cantico[strcspn(cantico, "\n")] = 0;
                for (int i = 0; cantico[i] != '\0'; i++) {
                    if (cantico[i] >= 'a' && cantico[i] <= 'z') {
                        cantico[i] -= 32;
                    }
                }

                for (int i = 0; i < 500; i++){
                    for (int i = 0; cantico[i] != '\0'; i++) {
                        switch (cantico[i]) {
                            case 'A': cantico[i] = '4'; vocales++; break;
                            case 'E': cantico[i] = '3'; vocales++; break;
                            case 'I': cantico[i] = '1'; vocales++; break;
                            case 'O': cantico[i] = '0'; vocales++; break;
                            case 'U': cantico[i] = '7'; vocales++; break;
                        }
                    }}
                printf("Su cantico es: ");

                for (int i = 0; i < 500; i++){
                    if(cantico[i] == '\0'){
                        break;
                    }
                    printf("%c", cantico[i]);
                }
                printf("\n Se han cambiado %d vocales\n", vocales);
                break;}  
            case 3:{
                printf("\nSaliendo del programa...\n");
                break;}
            default:{
                printf("Opcion no valida. Por favor intente nuevamente.\n");
            }
        }     
    } while (opcion != 3);

    printf("Gracias por usarnos. Fin del programa :]\n");
    
    return 0xDEDA10;
}
