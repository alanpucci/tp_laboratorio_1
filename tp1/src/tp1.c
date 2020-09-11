#include <stdio.h>
#include <stdlib.h>
#include "utn_TP1.h"

int main(void) {
	setbuf(stdout, NULL);
	int opcionElegida;
	float numero1;
	float numero2;
	float resultadoSuma;
	float resultadoResta;
	float resultadoMultiplicacion;
	float resultadoDivision;
	int resultadoFactorialNumero1;
	int resultadoFactorialNumero2;
	int banderaPrimerNumero=0;
	int banderaSegundoNumero=0;
	int banderaCalculo=0;

	if(utn_getOption("Bienvenido a la calculadora basica, por favor ingrese una opcion: ", &opcionElegida) == 0)
	{
		while(opcionElegida != 5)
		{
			switch(opcionElegida)
			{
				case 1:
					if(utn_getNumber("\nIngrese el primer numero: ", "\nERROR! Ingrese un numero valido: ", &numero1) == 0)
					{
						printf("\nTu primer numero es: %.2f\n", numero1);
						utn_getOption("\nQue opcion desea ingresar? ", &opcionElegida);
						banderaPrimerNumero=1;
					}
				break;
				case 2:
					if(utn_getNumber("\nIngrese el segundo numero: ", "\nERROR! Ingrese un numero valido: ", &numero2) == 0)
					{
						printf("\nTu segundo numero es: %.2f\n", numero2);
						utn_getOption("\nQue opcion desea ingresar? ", &opcionElegida);
						banderaSegundoNumero=1;
					}
				break;
				case 3:
					if(banderaPrimerNumero == 1 && banderaSegundoNumero == 1 &&
						   (utn_suma(&resultadoSuma, numero1, numero2) == 0 &&
							utn_resta(&resultadoResta, numero1, numero2) == 0 &&
							utn_multiplicacion(&resultadoMultiplicacion, numero1, numero2) == 0))
					{
						printf("\nCalculo de la suma %.2f + %.2f", numero1, numero2);
						printf("\nCalculo de la resta %.2f - %.2f", numero1, numero2);
						printf("\nCalculo de la multiplicacion %.2f * %.2f", numero1, numero2);
						printf("\nCalculo de la division %.2f / %.2f", numero1, numero2);
						printf("\nCalculo del factorial de %.2f y %.2f\n", numero1, numero2);
						banderaCalculo=1;
					}
					else
					{
						printf("\nPor favor, ingrese los dos numeros.");
					}
					utn_getOption("\nQue opcion desea ingresar?", &opcionElegida);
				break;
				case 4:
					if(banderaPrimerNumero == 1 && banderaSegundoNumero == 1 && banderaCalculo == 1)
					{
						printf("\nEl resultado de %.2f + %.2f es: %.2f", numero1, numero2, resultadoSuma);
						printf("\nEl resultado de %.2f - %.2f es: %.2f", numero1, numero2, resultadoResta);
						printf("\nEl resultado de %.2f * %.2f es: %.2f", numero1, numero2, resultadoMultiplicacion);
						if(utn_division(&resultadoDivision, numero1, numero2) == 0)
						{
							printf("\nEl resultado de %.2f / %.2f es: %.2f", numero1, numero2, resultadoDivision);
						}
						else
						{
							printf("\nNo se puede dividir por 0");
						}
						if(utn_factorial(&resultadoFactorialNumero1, numero1) == 0)
						{
							printf("\nEl factorial de %.2f es: %d", numero1, resultadoFactorialNumero1);
						}
						else
						{
							printf("\nNo se puede hacer el factorial de un numero negativo");
						}
						if(utn_factorial(&resultadoFactorialNumero2, numero2) == 0)
						{
							printf("\nEl factorial de %.2f es: %d\n", numero2, resultadoFactorialNumero2);
						}
						else
						{
							printf("\nNo se puede hacer el factorial de un numero negativo\n");
						}
					}
					else
					{
						printf("\nPor favor, realice los pasos anteriores");
					}
					utn_getOption("\nQue opcion desea ingresar?", &opcionElegida);
				break;
				default:
					utn_getOption("\nERROR! por favor, elija una opcion valida", &opcionElegida);
				break;
			}
		}
		printf("\n\nAdios!!");
	}
}
