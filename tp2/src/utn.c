#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARRAY_SIZE 4096
#define LONG_NOMBRE 50

static int myGets(char cadena[], int longitud);
static int isString(char cadena[]);
static int isInt(char cadena[]);
static int isFloat(char string[]);

/*
 * utn_getNumero : Pide al usuario un numero
 * pResultado: Direccion de memoria de la variable donde escribe el valor ingresado por el usuario
 * min: valor minimo valido (inclusive)
 * max: valor maximo valido (no inclusive)
 * msg: El mensaje que imprime para pedir un valor
 * msgError: mensaje que imprime si el rango no es valido
 * Retorno: 0: si esta todo OK. -1: Si hubo un error
 */

//NUEVO SCANF. SCANF NO SE USA MAS
static int myGets(char cadena[], int longitud)
{
	/*
	fflush(stdin);
	fgets (cadena, longitud, stdin);
	cadena[strlen (cadena) - 1] = '\0';
	return 0;
	*/
	int retorno=-1;
	if(cadena != NULL && longitud >0 && fgets(cadena,longitud,stdin)==cadena)
	{
		fflush(stdin);
		if(cadena[strlen(cadena)-1] == '\n' && cadena[0] != '\n')
		{
		cadena[strlen(cadena)-1] = '\0';
		}
		retorno=0;
	}
	return retorno;
}

static int isString(char string[])
{
	int retorno = 1;
	if(string != NULL && strlen(string) > 0)
	{
		for(int i = 0;string[i] != '\0'; i++)
		{
			if((string[i] < 'a' || string[i] > 'z') && (string[i] < 'A' || string[i] > 'Z') && string[i] != 32)
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

static int isFloat(char string[])
{
	int retorno = 1;
	int i = 0;

	if(string != NULL && strlen(string) > 0)
	{
		if(string[0] == '-')
		{
			i = 1;
		}

		for( ; string[i] != '\0' ; i++)
		{
			if((string[i] > '9' || string[i] < '0') && string[i] != '.')
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

static int isInt(char string[])
{
	int retorno = 1;
	int i = 0;

	if(string != NULL && strlen(string) > 0)
	{
		if(string[0] == '-')
		{
			i = 1;
		}

		for( ; string[i] != '\0' ; i++)
		{
			if(string[i] > '9' || string[i] < '0')
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

int utn_getString(char msg[], char msgError[], char pResult[], int attemps, int limit)
{
	int retorno = -1;
	char bufferString[ARRAY_SIZE];

	if(msg != NULL && msgError != NULL && pResult != NULL && attemps >= 0)
	{
		do
		{
			printf("\n%s", msg);
			if(myGets(bufferString, ARRAY_SIZE) == 0 && isString(bufferString) == 1 && strnlen(bufferString, sizeof(bufferString)) < limit)
			{
				retorno = 0;
				strncpy(pResult, bufferString, limit);
				break;
			}
			else
			{
				printf("%s", msgError);
				attemps--;
			}
		}while(attemps >= 0);
	}
	return retorno;
}

int utn_getInt(char msg[], char msgError[], int *pResult, int attemps, int min, int max)
{
	int retorno = -1;
	char bufferString[ARRAY_SIZE];
	int bufferInt;

	if(msg != NULL && msgError != NULL && pResult != NULL && attemps >= 0 && min <= max)
	{
		do
		{
			printf("%s", msg);
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
					printf("%s", msgError);
					attemps--;
				}

			}
			else
			{
				printf("%s", msgError);
				attemps--;
			}

		}while(attemps >= 0);
	}
	return retorno;
}

int utn_getFloat(char msg[], char msgError[], float *pResult, int attemps, int min, int max)
{
	int retorno = -1;
	char bufferString[ARRAY_SIZE];
	float bufferFloat;

	if(msg != NULL && msgError != NULL && pResult != NULL && attemps >= 0 && min <= max)
	{
		do
		{
			printf("%s", msg);
			if(myGets(bufferString, ARRAY_SIZE) == 0 && isFloat(bufferString) == 1)
			{
				bufferFloat = atof(bufferString);
				if(bufferFloat >= min && bufferFloat<= max)
				{
					*pResult = bufferFloat;
					retorno = 0;
					break;
				}
				else
				{
					printf("%s", msgError);
					attemps--;
				}

			}
			else
			{
				printf("%s", msgError);
				attemps--;
			}

		}while(attemps >= 0);
	}
	return retorno;
}

int utn_getMenu(int *pResult, int attemps, int min, int max)
{
	int retorno = -1;
	char bufferString[ARRAY_SIZE];
	int bufferInt;

	if(pResult != NULL && attemps >= 0 && min <= max)
	{
		do
		{
			printf("\nElija una opcion:\n1)Dar de alta un empleado\n2)Modificar un empleado\n3)Dar de baja un empleado\n4)INFORMAR\n5)Salir");
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
