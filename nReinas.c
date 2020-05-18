#include <stdio.h>//printf()

#include <stdlib.h>//malloc()

#include <math.h>//abs()

#include <time.h>//clock()




/*
	vector solucion en donde se guardan las posiciones
	de las piezas del tablero en donde "no se atacan entre si".
*/
int* VECTOR_SOLUCION;
int NUMERO_PIEZAS;//numero de piezas del tablero




/*
parametros:

	filaActual: fila en la que se intenta colocar una nueva pieza

	funcion principal en donde se verifican y optienen las posiciones del tablero en donde las piezas
	no se ataquen entre si
*/
void colocaPiezas( int filaActual, int* columnas );

int* eliminaColumna( int* columnas, int j, int tam )// costo: 14 + 8n
{
	int* nuevoArreglo = (int*)malloc( (tam)*sizeof(int) );// costo: 6

	int k = 0;// costo: 1
	for(int i = 0; i <= tam; i++)// costo: 2 + n( 2 + 6 )
	{
		if( columnas[i] != j )// costo: 6
		{
			nuevoArreglo[k++] = columnas[i];//costo: 4
		}
	}
	return nuevoArreglo;// costo: 1
}





void mostrarVector( int* list, int tam );//muestra los valores del arreglo list
void guardaResultados( int* list, int tam );//guarda los valores del arreglo list en un archivo






/*
parametros:

	numeroPiezas: el numero de piezas(Reinas) con el que se realiza el problema

	tiempoEjecucion: tiempo total que realizo el algoritmo para encontrar las soluciones


	guarda en un archivo el tiempo total de ejecucion que realizo el algoritmo con un determinado numero de piezas 	
*/
void guardaTiempoEjecucion( int numeroPiezas, double tiempoEjecucion )
{
	char* cad = malloc(30);
	sprintf(cad,"../tiempos/Tiempos%d.txt",numeroPiezas);

	FILE* f = fopen(cad,"a");
	fprintf(f,"%f\n", tiempoEjecucion );
	fclose(f);

	//free(f);
	//f = NULL;
	free(cad);
	cad = NULL;
}






/*
	######  ######   ########   ###########   ######   #####
	#### #### ####  ####  ####    #######     #######  #####
	####  ##  #### ####    ####    #####      ##############
	####      #### ############   #######     #####  #######
	####      #### ####    #### ###########   #####    #####
*/
int numeroSoluciones = 0;
int main(int argc, char const *argv[])
{

	
	double runTime;
	clock_t _start,
			_end;

	NUMERO_PIEZAS = 0;
	int temp;
	int* columnas;

	while( NUMERO_PIEZAS != -1 )
	{
		printf("ingresa un valor mayor a cero para n: ");
		scanf("%d",&NUMERO_PIEZAS);
		
		if( NUMERO_PIEZAS != -1 )
		{
			numeroSoluciones=0;
			VECTOR_SOLUCION = (int*)malloc(NUMERO_PIEZAS*sizeof(int));

			columnas = (int*)malloc(NUMERO_PIEZAS*sizeof(int));
			for(int j = 0; j < NUMERO_PIEZAS; j++)
			{
				columnas[j] = j;
			}

			_start = clock();
			colocaPiezas( NUMERO_PIEZAS - 1, columnas );//costo:
			_end = clock();
			
			runTime = (double)(_end - _start)/CLOCKS_PER_SEC;	

			//guardaTiempoEjecucion( i, runTime);

			printf("\n\n#soluciones: %d\n",numeroSoluciones);
			printf("termino test%d: %f\n\n",NUMERO_PIEZAS,runTime);
			free(VECTOR_SOLUCION);
			VECTOR_SOLUCION = NULL;
		}
	}
	

	

	return 0;
}






/*
*/
void colocaPiezas( int PIEZAS_FALTANTES, int* columnas )
/*			 ____
			|					5			si n = 0
	costo: 	|
			|7 + 23n + n^2 + 7K*(n) + n*T(n-1)	si n > 0
			|____
*/
{
	if( PIEZAS_FALTANTES == -1 )// costo: 4 + n( 23 + n + 7K + T(n-1) )
	{
		/*
			se encontro una nueva solucion
		*/
		numeroSoluciones++;
		//mostrarVector( VECTOR_SOLUCION, NUMERO_PIEZAS );

		//guardaResultados( VECTOR_SOLUCION, NUMERO_PIEZAS );

	}
	else
	{
        /*
            recorre las columnas en donde aun no existe una pieza en el tablero
        */

        int j;// costo: 1
		
        for( j = 0; j <= PIEZAS_FALTANTES; j++)// costo: n( 23 + n + 7K + T(n-1) )
        {
            /*
                recorre el VECTOR_SOLUCION y obtiene las columnas
                de las piezas que ya estan situadas en el tablero
            */
			int i;// costo: 1
			int col = columnas[j];// costo: 3
            for( i = NUMERO_PIEZAS - 1; i > PIEZAS_FALTANTES; i--)// costo: 7( K-n )
            {
                /*
                    verifica si la pieza nueva esta situada en una misma
					diagonal que alguna pieza ya existente en el tablero
                */
                if( abs( i - PIEZAS_FALTANTES ) == abs( col - VECTOR_SOLUCION[ i ] ) )// costo: 7
                {
                    break;
                }
            }
            if( i == PIEZAS_FALTANTES )// costo: 19 + 8n + T(n-1)
            {
                VECTOR_SOLUCION[ PIEZAS_FALTANTES ] = col;// costo: 2
				if( PIEZAS_FALTANTES > 0 )// costo: 16 + 8n + T(n-1)
				{
                	colocaPiezas( PIEZAS_FALTANTES - 1, eliminaColumna( columnas, col, PIEZAS_FALTANTES ) );
				}
				else
				{
                	colocaPiezas( PIEZAS_FALTANTES - 1, NULL );
				}
            }
        }
		free(columnas);// costo: 1
		columnas = NULL;// costo: 1
	}
}





/*
*/
void mostrarVector( int* list, int tam )
{
	printf("-------------\n");
    int count = tam-1;
    for(int i = 0; i < count; i++)
    {
        printf("%d,%d :: ",i,list[i]);
    }
    printf("%d,%d",count,list[count]);
    
	printf("\n--------------");
	printf("\n\n");
}






/*
*/
void guardaResultados( int* list, int tam )
{
	char* nom = malloc(30);

	sprintf(nom,"../pruebas/test_%d.txt",NUMERO_PIEZAS);
	
	FILE* f = fopen(nom,"a");

	for(int i = 0; i < tam; i++)
	{
		fprintf(f,"%d : ",list[i]);
	}
	fprintf(f,"%d ::\n",list[ tam - 1 ]);
	
	fclose(f);
	free(f);
	f = NULL;

	free( nom );
	nom = NULL;
}
