#include <stdio.h>
#include <stdlib.h>


/**
 * \brief Menu de la calculadora, solicita un entero al usuario que representa la opcion elegida
 * \param char *msg: Es el mensaje a ser mostrado
 * \param int *pNumero: Puntero que hace referencia al espacio en memoria de la opcion elegida
 * \return -1 si algo salio mal, 0 si todo esta correcto
 */
int utn_getOption(char *msg, int *pNumero)
{
	setbuf(stdout, NULL);

	int respuestaScanf;
	int bufferInt;
	int retornar = -1;
	printf("%s", msg);
	printf("\n 1) Ingresar el primer operando."
			"\n 2) Ingresar el segundo operando."
			"\n 3) Calcular todas las operaciones."
			"\n 4) Informar los resultados."
			"\n 5) Salir.\n");
	fflush(stdin);
	respuestaScanf = scanf("%d", &bufferInt);
	while(respuestaScanf == 0)
	{
		printf("ERROR, por favor ingrese una opcion valida:"
					"\n 1) Ingresar el primer operando."
					"\n 2) Ingresar el segundo operando."
					"\n 3) Calcular todas las operaciones."
					"\n 4) Informar los resultados."
					"\n 5) Salir.\n");
		fflush(stdin);
		respuestaScanf = scanf("%d", &bufferInt);
	}
	*pNumero = bufferInt;
	retornar = 0;
	return retornar;
}

/**
 * \brief Pide un numero float al usuario
 * \param char *msg: Es el mensaje a ser mostrado
 * \param char *msgError: Es el mensaje de error en caso de que no se haya ingresado un numero
 * \param float *pNumero: Puntero que hace referencia al espacio en memoria del numero ingresado
 * \return -1 si algo salio mal, 0 si todo esta correcto
 */
int utn_getNumber(char *msg, char *msgError, float *pNumero)
{
	float bufferFloat;
	int respuestaScanf;
	int retornar = -1;

	printf("%s", msg);
	fflush(stdin);
	respuestaScanf = scanf("%f", &bufferFloat);
	while(respuestaScanf == 0)
	{
		printf("%s", msgError);
		fflush(stdin);
		respuestaScanf = scanf("%f", &bufferFloat);
	}
	*pNumero = bufferFloat;
	retornar = 0;
	return retornar;
}

/**
 * \brief Realiza la suma entre dos numeros
 * \param float *pResultado: puntero que hace referencia al resultado de la suma
 * \param float numero1: parametro del primer numero ingresado
 * \param float numero2: parametro del segundo numero ingresado
 * \return -1 si algo salio mal, 0 si todo esta correcto
 */
int utn_suma(float *pResultado, float numero1, float numero2)
{
	int retornar = -1;
	*pResultado = numero1 + numero2;
	retornar = 0;
	return retornar;
}

/**
 * \brief Realiza la resta entre dos numeros
 * \param float *pResultado: puntero que hace referencia al resultado de la suma
 * \param float numero1: parametro del primer numero ingresado
 * \param float numero2: parametro del segundo numero ingresado
 * \return -1 si algo salio mal, 0 si todo esta correcto
 */
int utn_resta(float *pResultado, float numero1, float numero2)
{
	int retornar = -1;
	*pResultado = numero1 - numero2;
	retornar = 0;
	return retornar;
}

/**
 * \brief Realiza la multiplicacion entre dos numeros
 * \param float *pResultado: puntero que hace referencia al resultado de la suma
 * \param float numero1: parametro del primer numero ingresado
 * \param float numero2: parametro del segundo numero ingresado
 * \return -1 si algo salio mal, 0 si todo esta correcto
 */
int utn_multiplicacion(float *pResultado, float numero1, float numero2)
{
	int retornar = -1;
	*pResultado = numero1 * numero2;
	retornar = 0;
	return retornar;
}

/**
 * \brief Realiza la division entre dos numeros
 * \param float *pResultado: puntero que hace referencia al resultado de la suma
 * \param float numero1: parametro del primer numero ingresado
 * \param float numero2: parametro del segundo numero ingresado
 * \return -1 si algo salio mal, 0 si todo esta correcto
 */
int utn_division(float *pResultado, float numero1, float numero2)
{
	int retornar = -1;
	if(numero2 != 0)
	{
		*pResultado = numero1 / numero2;
		retornar = 0;
	}
	return retornar;
}

/**
 * \brief Realiza la operacion del factorial de un numero
 * \param int *pResultado
 * \param float numero1: parametro del primer numero ingresado
 * \param float numero2: parametro del segundo numero ingresado
 * \return -1 si algo salio mal, 0 si todo esta correcto
 */
int utn_factorial(int *pResultado, float numero)
{
	int retornar = -1;
	int bufferInt = 1;
	if(numero >= 0)
	{
		for(int i = 1; i <= numero; i++)
		{
			bufferInt *= i;
		}
		*pResultado = bufferInt;
		retornar = 0;
	}
	return retornar;
}
