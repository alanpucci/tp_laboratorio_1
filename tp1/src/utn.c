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

	if(msg!=NULL && pNumero!=NULL){
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
	}
	return retornar;
}

/**
 * \brief Pide un numero float al usuario
 * \param char *msg: Es el mensaje a ser mostrado
 * \param char *msgError: Es el mensaje de error en caso de que no se haya ingresado un numero
 * \param float *pNumero: Puntero que hace referencia al espacio en memoria del numero ingresado
 * \return -1 si algo salio mal, 0 si todo esta correcto
 */
int utn_getFloat(char *msg, char *msgError, float *pNumero)
{
	float bufferFloat;
	int respuestaScanf;
	int retornar = -1;

	if(msg!=NULL && msgError!=NULL && pNumero!=NULL)
	{
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
	}
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
	if(pResultado!=NULL)
	{
		*pResultado = numero1 + numero2;
		retornar = 0;
	}
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
	if(pResultado!=NULL)
	{
		*pResultado = numero1 - numero2;
		retornar = 0;
	}
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
	if(pResultado!=NULL)
	{
		*pResultado = numero1 * numero2;
		retornar = 0;
	}
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
	if(numero2 != 0 && pResultado!=NULL)
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
	if(numero >= 0 && pResultado!=NULL)
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

/**
 * \brief Imprime mensaje de las operaciones
 * \param float numero1: Recibe el primer numero y lo muestra en mensaje
 * \param float numero2: Recibe el segundo numero y lo muestra en mensaje
 */
void utn_imprimirOperaciones(float numero1, float numero2)
{
	printf("\nCalculo de la suma %.2f + %.2f", numero1, numero2);
	printf("\nCalculo de la resta %.2f - %.2f", numero1, numero2);
	printf("\nCalculo de la multiplicacion %.2f * %.2f", numero1, numero2);
	printf("\nCalculo de la division %.2f / %.2f", numero1, numero2);
	printf("\nCalculo del factorial de %.2f y %.2f\n", numero1, numero2);
}

/**
 * \brief Imprime el resultado de la suma, resta y multiplicacion
 * \param float numero1: Recibe el primer numero
 * \param float numero2: Recibe el segundo numero
 * \param float resultadoSuma: Recibe el resultado de la suma
 * \param float resultadoResta: Recibe el resultado de la resta
 * \param float resultadoMultiplicacion: Recibe el resultado de la multiplicacion
 * \param float resultadoDivision: Recibe el resultado de la division
 * \param float resultadoFactorial1: Recibe el resultado del factorial del ENTERO del primer numero
 * \param float resultadoFactorial2: Recibe el resultado del factorial del ENTERO del segundo numero
 */
void utn_imprimirResultados(float numero1, float numero2, float resultadoSuma, float resultadoResta, float resultadoMultiplicacion,
							float resultadoDivision, int resultadoFactorial1, int resultadoFactorial2)
{
	printf("\nEl resultado de %.2f + %.2f es: %.2f", numero1, numero2, resultadoSuma);
	printf("\nEl resultado de %.2f - %.2f es: %.2f", numero1, numero2, resultadoResta);
	printf("\nEl resultado de %.2f * %.2f es: %.2f", numero1, numero2, resultadoMultiplicacion);
	if(numero2 != 0)
	{
		printf("\nEl resultado de %.2f / %.2f es: %.2f", numero1, numero2, resultadoDivision);
	}
	else
	{
		printf("\nNo se puede dividir por 0");
	}
	if(numero1 >= 0)
	{
		printf("\nEl factorial del entero de %.2f es: %d", numero1, resultadoFactorial1);
	}
	else
	{
		printf("\nNo se puede hacer el factorial de un numero negativo");
	}
	if(numero2 >= 0)
	{
		printf("\nEl factorial del entero de %.2f es: %d", numero2, resultadoFactorial2);
	}
	else
	{
		printf("\nNo se puede hacer el factorial de un numero negativo");
	}
}

/**
 * \brief Calculo de todas las operaciones
 * \param float numero1: Recibe el primer numero ingresado
 * \param float numero2: Recibe el segundo numero ingresado
 * \param float *pResultadoSuma: Puntero al resultado de la suma
 * \param float *pResultadoResta: Puntero al resultado de la resta
 * \param float *pResultadoMultiplicacion: Puntero al resultado de la multiplicacion
 * \param float *pResultadoDivision: Puntero al resultado de la division
 * \param int *pResultadoFactorial1: Puntero al resultado del factorial del primer numero
 * \param int *pResultadoFactorial2: Puntero al resultado del factorial del segundo numero
 * \return retorna -1 si algo salio mal o 0 si todo esta bien
 */
int utn_operaciones(float numero1, float numero2, float *pResultadoSuma, float *pResultadoResta, float *pResultadoMultiplicacion, float *pResultadoDivision, int *pResultadoFactorial1, int *pResultadoFactorial2)
{
	int retornar =-1;
	float resultadoSuma;
	float resultadoResta;
	float resultadoMultiplicacion;
	float resultadoDivision;
	int resultadoFactorial1;
	int resultadoFactorial2;
	if(utn_suma(&resultadoSuma, numero1, numero2) == 0 &&
	   utn_resta(&resultadoResta, numero1, numero2) == 0 &&
	   utn_multiplicacion(&resultadoMultiplicacion, numero1, numero2) == 0 &&
	   pResultadoSuma!=NULL && pResultadoResta!=NULL && pResultadoMultiplicacion!=NULL)
	{
		*pResultadoSuma = resultadoSuma;
		*pResultadoResta = resultadoResta;
		*pResultadoMultiplicacion = resultadoMultiplicacion;
	}
	if(utn_division(&resultadoDivision, numero1, numero2) == 0 && pResultadoDivision!=NULL)
	{
		*pResultadoDivision = resultadoDivision;
	}
	if(utn_factorial(&resultadoFactorial1, numero1) == 0 && pResultadoFactorial1!=NULL)
	{
		*pResultadoFactorial1 = resultadoFactorial1;
	}
	if(utn_factorial(&resultadoFactorial2, numero2) == 0 && pResultadoFactorial2!=NULL)
	{
		*pResultadoFactorial2 = resultadoFactorial2;
	}
	retornar = 0;
	return retornar;
}
