#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#define ARRAY_SIZE 4096

int utn_getMenu(int *pResult, int attemps, int min, int max)
{
	int retorno = -1;
	char bufferString[ARRAY_SIZE];
	int bufferInt;

	if(pResult != NULL && attemps >= 0 && min <= max)
	{
		do
		{
			printf("\nElija una opcion: \n"
					"1) Cargar los datos de los empleados desde 'data.csv' (modo texto)\n"
					"2) Cargar los datos de los empleados desde 'data.csv' (modo binario)\n"
					"3) Alta de empleado\n"
					"4) Modificar datos de empleado\n"
					"5) Baja de empleado\n"
					"6) Listar empleados\n"
					"7) Ordenar empleados\n"
					"8) Guardar los datos de los empleados en 'data.csv' (modo texto)\n"
					"9) Guarar los datos de los empleados en 'data.csv' (modo binario)\n"
					"10) Salir\n"
					"> > OPCION:");
			if(myGets(bufferString, ARRAY_SIZE) == 0 && isInt(bufferString) == 1)
			{
				bufferInt = atoi(bufferString);
				if(bufferInt >= min && bufferInt<= max)
				{
					*pResult = bufferInt;
					retorno = 0;
					break;
				}
				else
				{
					printf("\nError! elija una opcion valida");
					attemps--;
				}

			}
			else
			{
				printf("Error! elija una opcion valida");
				attemps--;
			}
		}while(attemps >= 0);
	}
	return retorno;
}
