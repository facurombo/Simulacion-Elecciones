/*/
/*                                                               */
/*   ELECCION                                                    */
/*                                                               */
/*   SE PIDE DETERMINAR AL REY DEL CONURBANO.                    */
/*   SE DISPONE DE UNA ESTRUCTURA TIPO GUIRNALDA                 */
/*   LOS NODOS PARTIDO DE LA LISTA PRINCIPAL (HORIZONTAL)        */
/*   TIENEN LOS NOMBRES DE LOS PARTIDOS DONDE SE REALIZARON      */
/*   LAS ELECCIONES Y UN PUNTERO A LOS CANDIDATOS.               */
/*   LOS NODOS CANDIDATO (QUE COMPONEN LA LISTA VERTICAL)        */
/*   TIENEN EL NOMBRE DEL CANDIDATO Y LOS VOTOS QUE OBTUVO       */
/*   EN ESE PARTIDO.                                             */
/*   		                                                     */
/*                                                               */

/*   SE PIDE :                                                   */
/*			1. DETERMINAR EL QUIEN ES EL REY DEL CONURBANO       */
/*             Y CUANTOS VOTOS TOTALES OBTUVO.                   */
/*          2. MOSTRAR EN QUE PARTIDOS EL REY DEL CONURBANO      */
/*             SALIO PRIMERO O SI NO LO LOGRO EN NINGUNO.        */
/*                                                               */



#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

class CANDIDATO { // Nodo tipo candidato
public:
    CANDIDATO(char *); // Constructor
    int VOTOS;
    char NOM[20];
    CANDIDATO *SIG;
};

CANDIDATO::CANDIDATO(char *S) // Constructor
{
    strcpy(NOM, S);
    VOTOS = rand() % 800;
    SIG = NULL;
}

class PARTIDO { // Nodo tipo partido
public:
    char NOM[20];
    CANDIDATO *PALUM;
    PARTIDO *SIG;
    PARTIDO(char *, CANDIDATO *);
};

PARTIDO::PARTIDO(char *S, CANDIDATO *PRIMERO) // Constructor
{
    strcpy(NOM, S);
    PALUM = PRIMERO;
    SIG = NULL;
}

class ELECCION { // Lista de partidos
private:
    PARTIDO *INICIO;
    PARTIDO *BUSCAR(char *);
public:
    ELECCION(); // Constructor
    void ARREGLATE(char *); // Carga la lista
    void MIRAR(); // Muestra la lista
    void GANADOR (); //FUNCION PARA DETERMINAR QUIEN GANA

};

ELECCION::ELECCION() // Constructor
{
    INICIO = NULL;
}

void ELECCION::ARREGLATE(char *S)
{

    char * GENERAPARTIDO();
    PARTIDO *PPAR = NULL;
    CANDIDATO *PAL = new CANDIDATO(S); // Crea el candidato

    char *BUF = GENERAPARTIDO(); // Genera el nombre del partido
    PPAR = BUSCAR(BUF);          // Busca si ya existe

    if (!PPAR) {
        // Si el partido no existe, lo crea y asocia al candidato
        PPAR = new PARTIDO(BUF, PAL);
        PPAR->SIG = INICIO;
        INICIO = PPAR;
    } else {
        // Si el partido ya existe, agrega al candidato al final de la lista
        CANDIDATO *P = PPAR->PALUM;
        while (P->SIG)
            P = P->SIG;

        P->SIG = PAL;
    }
}

PARTIDO *ELECCION::BUSCAR(char *S)
{
    PARTIDO *PPAR = INICIO;
    while (PPAR) {
        if (!strcmp(PPAR->NOM, S)) {
            return PPAR;
        }
        PPAR = PPAR->SIG;
    }
    return NULL;
}

void ELECCION::MIRAR()
{
    PARTIDO *PPAR = INICIO;
    CANDIDATO *PCAN = NULL;

    fflush(stdin);

    cout << "\n\n\t\t    ESCRUTINIO DE LA ELECCION\n\n";

    while (PPAR) {
        cout << "\n\n\tPARTIDO: " << PPAR->NOM << "\n";

        PCAN = PPAR->PALUM;
        while (PCAN) {
            printf("\t%-20s %10d votos\n", PCAN->NOM, PCAN->VOTOS);
            PCAN = PCAN->SIG;
        }

        PPAR = PPAR->SIG;

    }
}

void ELECCION::GANADOR (){

CANDIDATO * PCAND, *AUXCAND;
PARTIDO * PPART, *AUXPART;

int votos = 0, maxvotos = 0, flag = 1, maximovoto = 0, nosalioprimero = 1;
char ganador[20], primero [20];


// PUNTO 1

PPART = INICIO;

while (PPART){

    PCAND = PPART -> PALUM;


        while (PCAND){


            votos = 0;

            AUXPART = INICIO;

                while (AUXPART){

                    AUXCAND = AUXPART ->PALUM;

                        while (AUXCAND){

                            if (!strcmp(PCAND->NOM, AUXCAND->NOM)){
                                votos = votos + AUXCAND->VOTOS;}

                            AUXCAND = AUXCAND -> SIG;
                        }

                    AUXPART = AUXPART -> SIG;
                }





        if (flag  || votos > maxvotos){
            flag = 0;
            maxvotos = votos;
            strcpy (ganador, PCAND->NOM);}

        PCAND = PCAND -> SIG;

    }



    PPART= PPART ->SIG;
}


 cout << "\n\n EL REY O LA REYNA DEL CONURBANO ES " << ganador << " CON " << maxvotos;
 cout << "\n\n" ;


 //PUNTO 2

 cout << "\n\n  SALIO PRIMERO EN:  ";
 cout << "\n\n" ;

 flag = 1;
 PPART = INICIO;
    while (PPART){

        PCAND = PPART -> PALUM;
        strcpy (primero, PCAND->NOM);

            while (PCAND){

                if(flag || PCAND->VOTOS > maximovoto){
                    flag = 0;
                    maximovoto= PCAND -> VOTOS;
                    strcpy (primero, PCAND->NOM);
                }

            PCAND = PCAND -> SIG;
            }


        if (!strcmp(primero, ganador )){

            cout << "\n\n   " << PPART->NOM ;
            cout << "\n\n" ;
            nosalioprimero = 0;

        }


        PPART = PPART ->SIG;
    }

    if (nosalioprimero == 1){

        cout << "\n\n EL REY O LA REYNA DEL CONURBANO NO SALIO PRIMERO EN  NINGUN PARTIDO!!!";
        cout << "\n\n" ;

    }



}


char *GENERAPARTIDO();
char *GENERANOM();


int main()
{
    ELECCION E;
    char BUF[20];

    srand(65);

    strcpy(BUF, GENERANOM());
    while (strcmp(BUF, "FIN")) {
        E.ARREGLATE(BUF);
        strcpy(BUF, GENERANOM());
    }

    E.GANADOR(); // PUNTO 1 Y 2


    E.MIRAR();

    printf("\n\n");
    return 0;
}


char *GENERANOM()
{
    static int I = 0;
    static char NOM[][20] = {"DARIO", "CAROLINA", "LOLA", "LOLA",
                             "PACO", "LUIS", "MARIA", "ANSELMO",
                             "ANA", "LAURA", "PEDRO", "ANIBAL",
                             "PABLO", "ROMUALDO", "ALICIA", "MARTA",
                             "MARTIN", "TOBIAS", "ANA", "LORENA",
                             "ANDRES", "KEVIN", "LUCRECIA", "RAUL",
                             "ENZO", "BETO", "HERMINDO", "FELIPE",
                             "GUILLERMO", "LALO", "KARINA", "AQUILES",
                             "MINERVA", "OLGA", "LALO", "TATIANA",
                             "LILO", "STICH", "EMA", "THELMA",
                             "LOUISE", "BONNIE", "CLYDE", "ROMEO",
                             "LUJAN", "VERONICA", "JORGE", "ALEJANDRO",
                             "ROCIO", "LUJAN", "LIBORIO", "CONAN", "FIN"};
    return NOM[I++];
}

char *GENERAPARTIDO()
{
    static int I = 0;
    static char NOM[][20] = {"AVELLANEDA", "SAN MARTIN", "MORON", "MATANZA",
                             "LANUS", "SAN ISIDRO", "MORENO", "3 DE FEBRERO",
                             "QUILMES", "HURLINGHAM", "ITUZAINGO", "MERLO"};

    if (I >= 12) I = 0; // Reinicia si se excede el número de partidos
    return NOM[I++];
}

