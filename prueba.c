#include <stdio.h>
#include <stdlib.h>

void Cerebro(void);
void Jugar(int **);
void TerminarSiNo(int **, int, int, int);
void Esperar(void);
int RemplazarNumero(int **, int, int);
int BuscarNumero(int **, int);
void VerificarEntradaDatos(int *, int *, int *);
int **CrearMatriz(void);
int VerificarNumeroXFil(int **, int, int);
int VerificarNumeroXCol(int **, int, int);
void LimpiarMatriz(int **);
void MostrarMatriz(int **);
void SumaFilasColumnas(int **);
void GanoSiNo(int **, int);
void LiberarMemoria(int **);

int main()
{
    Cerebro();
    return 0;
}

void Cerebro(void)
{
    int **matriz;
    matriz = CrearMatriz();
    LimpiarMatriz(matriz);
    MostrarMatriz(matriz);
    Jugar(matriz);
    LiberarMemoria(matriz);
}

void Jugar(int **matriz)
{
    int numero;
    int fila;
    int columna;
    int infinito = 1;

    while (infinito == 1)
    {
        printf("Para salir/comprobar soduko coloca: 0,0,0 \n");
        printf("Introduce los datos de la siguiente manera: numero,fila,columna: ");
        scanf("%d,%d,%d", &numero, &fila, &columna);
        fflush(stdin);
        TerminarSiNo(matriz, numero, fila, columna);
        VerificarEntradaDatos(&numero, &fila, &columna);

        if (VerificarNumeroXFil(matriz, fila - 1, numero) == 1 && VerificarNumeroXCol(matriz, columna - 1, numero) == 1 &&
            BuscarNumero(matriz, numero) == 1 && RemplazarNumero(matriz, fila - 1, columna - 1) == 1)
        {
            matriz[fila - 1][columna - 1] = numero;
        }
        system("cls");
        MostrarMatriz(matriz);
    }
    SumaFilasColumnas(matriz);
    Esperar();
}

void TerminarSiNo(int **matriz, int a, int b, int c)
{
    int opcion = 0;
    if (a == 0 && b == 0 && c == 0)
    {
        printf("\n\n1. Salir del juego\n");
        printf("2. Editar Soduko\n");
        printf("3. Comprobar Soduko\n");
        printf("Escoge una opcion: ");
        scanf("%d", &opcion);
        fflush(stdin);
        system("cls");
        if (opcion == 2)
        {
            MostrarMatriz(matriz);
            Jugar(matriz);
        }
        else if (opcion == 3)
        {
            MostrarMatriz(matriz);
            SumaFilasColumnas(matriz);
        }
        else
            exit(-1);
    }
}

void Esperar(void)
{
    printf("escoge otro (pulsa cualquier tecla)...");
    getch();
    fflush(stdin);
}

int RemplazarNumero(int **matriz, int fila, int columna)
{

    char desicion;
    if (matriz[fila][columna] != 0)
    {

        printf("Ya existe un numero en esa posicion, deseas remplazarlo? S/N: ");
        scanf("%c", &desicion);
        fflush(stdin);

        if (desicion == 'S')
        {
            return 1;
        }
        return 0;
    }
    return 1;
}

int BuscarNumero(int **matriz, int numero)
{
    int x;
    int y = 0;
    char decision;

    for (x = 0; x < 3; x++)
    {
        for (y = 0; y < 3; y++)
        {
            if (matriz[x][y] == numero)
            {
                MostrarMatriz(matriz);
                printf("El numero ya fue colocado en %d,%d, deseas reemplazarlo? S/N: ", x + 1, y + 1);
                scanf("%c", &decision);
                fflush(stdin);
                if (decision == 'S')
                {
                    matriz[x][y] = 0;
                    return 1;
                }
                else
                {
                    Esperar();
                }
                return 0;
            }
        }
    }
    return 1;
}
// Si un número, fila o columna excede del rango estipulado entonces se vuelve a solicitar el dato
void VerificarEntradaDatos(int *numero, int *fila, int *columna)
{
    int datos[2];
    int decidir = 0;

    while (decidir == 0)
    {

        if (1 > *numero || *numero > 9)
        {
            printf("Coloca un numero valido entre 1 ~ 9: ");
            scanf("%d", &datos[0]);
            fflush(stdin);
            *numero = datos[0];
            decidir = 0;
        }
        else
        {
            decidir = 1;
        }
        if (1 > *fila || *fila > 3)
        {
            printf("Coloca una fila valida entre 1 ~ 3: ");
            scanf("%d", &datos[1]);
            fflush(stdin);
            *fila = datos[1];
            decidir = 0;
        }
        else
        {
            decidir = 1;
        }
        if (1 > *columna || *columna > 3)
        {
            printf("Coloca una columna valida entre 1 ~ 3: ");
            scanf("%d", &datos[2]);
            fflush(stdin);
            *columna = datos[2];
            decidir = 0;
        }
        else
        {
            decidir = 1;
        }
    }

    system("cls");
}

int **CrearMatriz(void)
{
    int i;
    int **matriz;
    matriz = (int **)malloc(3 * sizeof(int *));

    for (i = 0; i < 3; i++)
    {
        matriz[i] = (int *)malloc(3 * sizeof(int));
    }

    return matriz;
}

// Se verifica primero que no exista el numero en la matriz
int VerificarNumeroXFil(int **matriz, int fila, int numero)
{
    int y;
    char opcion;
    for (y = 0; y < 3; y++)
    {
        if (matriz[fila][y] == numero)
        {
            MostrarMatriz(matriz);
            printf("Epale este numero '%d' ya existe en la fila, deseas cambiarlo de lugar? S/N: ", numero);
            scanf("%c", &opcion);
            fflush(stdin);
            if (opcion == 'S')
            {
                matriz[fila][y] = 0;
                return 1;
            }
            Esperar();
            return 0;
        }
    }
    return 1;
}

int VerificarNumeroXCol(int **matriz, int columna, int numero)
{
    char opcion;
    int x;
    for (x = 0; x < 3; x++)
    {
        if (matriz[x][columna] == numero)
        {
            MostrarMatriz(matriz);
            printf("Epale este numero '%d' ya existe en la columna, deseas cambiarlo de lugar? S/N: ", numero);
            scanf("%c", &opcion);
            fflush(stdin);
            if (opcion == 'S')
            {
                matriz[x][columna] = 0;
                return 1;
            }
            Esperar();
            return 0;
        }
    }
    return 1;
}

void LimpiarMatriz(int **matriz)
{
    int x;
    int y;
    for (x = 0; x < 3; x++)
    {
        for (y = 0; y < 3; y++)
        {
            matriz[x][y] = 0;
        }
    }
}

void MostrarMatriz(int **matriz)
{
    int x;
    int y;
    int z = 0;
    int sumaFila = 0;
    int sumaColumna = 0;
    int sumas[2];

    for (x = 0; x < 3; x++)
    {
        sumaFila = 0;
        sumaColumna = 0;
        for (y = 0; y < 3; y++)
        {
            sumaFila = matriz[x][y] + sumaFila;
            sumaColumna = matriz[y][x] + sumaColumna;
            printf("%2d \t", matriz[x][y]);
        }
        printf(" = %2d \t\n", sumaFila);
        sumas[x] = sumaColumna;
    }

    printf("-- \t-- \t-- \t\n");
    printf("%2d \t%2d \t%2d \t\n", sumas[0], sumas[1], sumas[2]);
}

void SumaFilasColumnas(int **matriz)
{
    int x;
    int y;
    int sumaColumna = 0;
    int sumaFila = 0;
    int contador = 0;

    for (x = 0; x < 3; x++)
    {
        sumaFila = 0;
        sumaColumna = 0;
        for (y = 0; y < 3; y++)
        {
            sumaFila = (matriz[x][y]) + sumaFila;
            sumaColumna = matriz[y][x] + sumaColumna;
        }

        if (sumaFila == 15 && sumaColumna == 15)
        {
            contador++;
        }
    }

    GanoSiNo(matriz, contador);
}

void GanoSiNo(int **matriz, int contador)
{
    if (contador == 3)
    {

        printf("EUREKA!!! SODUKO RESUELTO!!!\n");
    }
    else
    {
        printf(" SODUKO NO RESUELTO!!!\n");
    }

    TerminarSiNo(matriz, 0, 0, 0);
}
void LiberarMemoria(int **matriz)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        free(matriz[i]);
    }

    free(matriz);
}