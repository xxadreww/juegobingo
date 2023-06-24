/* ||          JUEGO DE BINGO          ||
   ||      Francisco Isea :: UNEG      ||
*/

// || LIBRERIAS USADAS ||
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// || VARIABLES GLOBALES ||
#define FILAS 5
#define COLUMNAS 5

// || FUNCIONES Y PARAMETROS ||
int numerosRand(int min, int max);
void mostrar_tarjeta(int matriz[FILAS][COLUMNAS], int seleccionados[FILAS][COLUMNAS]);
int comprobar_bingo(int seleccionados[FILAS][COLUMNAS]);
int numExiste(int matriz[FILAS][COLUMNAS], int numero);

// || FUNCION PRINCIPAL ||
int main(){
    int matriz[FILAS][COLUMNAS], i, j, numero, limInferior=1, limSuperior=15, seleccionados[FILAS][COLUMNAS]={0}, bingo[FILAS][COLUMNAS];
    char continuar;

    // Aqui se genera la matriz del bingo
    for (i=0;i<FILAS;i++){
        for (j=0;j<COLUMNAS;j++){
            do {
                numero=numerosRand(limInferior, limSuperior); // Aqui se va a generar los numeros random del bingo
            } while (numExiste(matriz, numero)); // Aqui llama a la funcion de si un numero existe o no en la matriz
            matriz[i][j]=numero;
            limInferior+=15;
            limSuperior+=15;
        }
        limInferior=1; // limite inferior de la matriz
        limSuperior=15; // limite superior de la matriz
    }

    // Aqui se copia la matriz del bingo en la tarjeta de bingo
    for (i=0;i<FILAS;i++){
        for (j=0;j<COLUMNAS;j++){
            bingo[i][j]=matriz[i][j]; }
    }
    mostrar_tarjeta(bingo, seleccionados); // Va a la funcion que muestra la tarjeta del bingo
    system("pause");

    // Aqui permite jugar en bucle hasta marcar el Bingo o hasta que se quieran salir
    while (!comprobar_bingo(seleccionados)){
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Comando para cambiar color AMARILLO
    	printf("-----------------------------\n");
    	fflush(stdin); // Comando que limpia el buffer para evitar bug
        printf("%cDeseas seguir jugando? (s/n): ", 168);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Comando para cambiar color BLANCO (normal)
        scanf("%c", &continuar);
        if (continuar=='n'||continuar=='N'){
        	system("cls");
        	printf("----------------------------------\n");
        	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Color verde
            printf("\a Gracias por jugar. %cHasta luego!\n",173 );
            printf("  El juego se cerrar%c en breves\n", 160);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Color normal
            printf("----------------------------------\n");
            Sleep(3500);
            return 0;
        }

        system("cls");
        // Generar número aleatorio del 1 al 75
        int generado=numerosRand(1, 75);
        printf("El n%cmero generado es: %d\n", 163, generado);

        // Marcar número en la tarjeta si está en la matriz del Bingo
        if (numExiste(matriz, generado)){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Color verde
            printf("El n%cmero %d est%c en la matriz del Bingo.\n", 163, generado, 160);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Color normal
            // Marcar el número con una X en la tarjeta
            for (i=0;i<FILAS;i++){
                for (j=0;j<COLUMNAS;j++){
                    if (matriz[i][j]==generado){
                        seleccionados[i][j]=1;
                    }
                }
            }
            // Mostrar tarjeta actualizada
            mostrar_tarjeta(bingo, seleccionados);
            system("pause");
        } else { // Si no se encuentra en la tarjeta
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Color rojo
            printf("El n%cmero %d no est%c en la matriz del Bingo.\n", 163, generado, 160);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Color normal
        }
    }
	
	// Mensaje cuando sale del bucle porque se hizo bingo
    printf("-----------------------------\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    printf("\a%cFELICIDADES, HAZ HECHO BINGO!\n", 173);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    return 0;
}

// || FUNCION QUE GENERA LOS NUMEROS RANDOM DE LA MATRIZ ||
int numerosRand(int min, int max){
    return (rand()%(max-min+1))+min;
}

// || FUNCION QUE MUESTRA LOS DATOS DE LA TARJETA DEL BINGO ||
void mostrar_tarjeta(int matriz[FILAS][COLUMNAS], int seleccionados[FILAS][COLUMNAS]){
    printf("------------------------\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Color
    printf("  B");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Color
	printf("    I");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // Color
	printf("    N");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Color
	printf("    G");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); // Color
	printf("    O\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Color
    int i, j;
    for (i=0;i<FILAS;i++){
        for (j=0;j<COLUMNAS;j++){
            if (seleccionados[i][j]){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                printf("[XX] "); // Si hay bingo, marca con una X
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            } else {
                printf("[%2d] ", matriz[i][j]); // Si no, sigue su numero normal
            }
        }
        printf("\n");
    }
}

// || FUNCION PARA COMPROBAR SI SE HIZO BINGO O NO ||
int comprobar_bingo(int seleccionados[FILAS][COLUMNAS]){
    // For para comprobar si hay una línea horizontal completa
    for (int i=0;i<FILAS;i++){
        int cont=0;
        for (int j=0;j<COLUMNAS;j++){
            if (seleccionados[i][j]){
                cont++;
            }
        }
        if (cont==COLUMNAS){
            return 1; // Devuelve 1 porque se detecto un bingo
        }
    }
    // For para comprobar si hay una línea vertical completa
    for (int j=0;j<COLUMNAS;j++){
        int cont=0;
        for (int i=0;i<FILAS;i++){
            if (seleccionados[i][j]){
                cont++;
            }
        }
        if (cont==FILAS){
            return 1; // Devuelve 1 porque se detecto un bingo
        }
    }
    // For para comprobar si hay una línea diagonal completa
    int cont1=0;
    int cont2=0;
    for (int i=0;i<FILAS;i++){
        if (seleccionados[i][i]){
            cont1++;
        }
        if (seleccionados[i][FILAS-i-1]){
            cont2++;
        }
    }
    if (cont1==FILAS||cont2==FILAS){
        return 1; // Devuelve 1 porque se detecto un bingo
    }
    return 0; // Devuelve 0 porque no se detecto un bingo
}

// || FUNCION QUE DETECTA SI HAY NUMERO REPETIDO O NO EN LA TARJETA DE BINGO ||
int numExiste(int matriz[FILAS][COLUMNAS], int numero){
    int i, j;
    for (i=0;i<FILAS;i++){
        for (j=0;j<COLUMNAS;j++){
            if (matriz[i][j]==numero){
                return 1; // El número ya existe en la tarjeta de bingo
            }
        }
    }
    return 0; // El número no existe en la tarjeta de bingo
}
