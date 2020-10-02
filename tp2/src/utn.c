#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARRAY_SIZE 4096
#define LONG_NOMBRE 50

static int myGets(char cadena[], int longitud);
static int isString(char cadena[]);
static int isInt(char cadena[]);
static int isFloat(char string[]);

/**
 * \brief Funcion para obtener un string
 * \param char cadena[]: Donde se va a guardar el string
 * \param int longitud: El tama�o del array de caracteres para no sobrepasarlo
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
static int myGets(char cadena[], int longitud)
{
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

/**
 * \brief Funcion para validar si el array de caracteres que recibe es una cadena de texto y no otra cosa
 * \param char string[]: Es el string que vamos a validar
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
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

/**
 * \brief Funcion para validar si la cadena de caracteres que recibimos corresponde a un float
 * \char string[]: Es la cadena de caracteres que vamos a validar
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
static int isFloat(char string[])
{
	int retorno = 1;
	int i = 0;
	int commaCounter=0;

	if(string != NULL && strlen(string) > 0)
	{
		if(string[0] == '-')
		{
			i = 1;
		}

		for(;string[i] != '\0' ; i++)
		{
			if(string[i] == '.')
			{
				commaCounter++;
			}
			if(commaCounter>1 || ((string[i] > '9' || string[i] < '0') && string[i] != '.'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Funcion para validar si la cadena de caracteres que recibimos corresponde a un entero
 * \char string[]: Es la cadena de caracteres que vamos a validar
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
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
		for(;string[i] != '\0' ; i++)
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

/**
 * \brief Funcion para pedirle al usuario un string
 * \param char msg[]: Puntero a una cadena de texto
 * \param char msgError[]: Puntero a una cadena de texto en caso de error
 * \param char pResult[]: El string que vamos a devolver
 * \param int attemps: Reintentos que va a tener la funcion en caso de error
 * \param int limit: Es el tama�o para no sobrepasar la cadena de texto
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
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

/**
 * \brief Funcion para pedirle al usuario un numero entero
 * \param char msg[]: Puntero a una cadena de texto
 * \param char msgError[]: Puntero a una cadena de texto en caso de error
 * \param int *pResult: Puntero del entero que vamos a devolver
 * \param int attemps: Reintentos que va a tener la funcion en caso de error
 * \param int min: Es el minimo permitido para el numero
 * \param int max: Es el maximo permitido para el numero
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
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

/**
 * \brief Funcion para pedirle al usuario un numero flotante
 * \param char msg[]: Puntero a una cadena de texto
 * \param char msgError[]: Puntero a una cadena de texto en caso de error
 * \param float *pResult: Puntero del flotante que vamos a devolver
 * \param int attemps: Reintentos que va a tener la funcion en caso de error
 * \param int min: Es el minimo permitido para el numero
 * \param int max: Es el maximo permitido para el numero
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
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

/**
 * \brief Funcion que me imprime el menu en el main.c
 * \param int *pResult: Puntero que hace referencia a la opcion del menu elegida
 * \param int attemps: Cantidad de reintentos
 * \param int min: Es el minimo permitido para el numero
 * \param int max: Es el maximo permitido para el numero
 * \return (-1) si algo salio mal (0) si todo esta OK

 */
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
