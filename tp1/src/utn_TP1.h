/*
 * utn_TP1.h
 *
 *  Created on: Sep 6, 2020
 *      Author: alane
 */

#ifndef UTN_TP1_H_
#define UTN_TP1_H_

int utn_getNumber(char *msg, char *msgError, float *pNumero);
int utn_suma(float *pResultado, float numero1, float numero2);
int utn_resta(float *pResultado, float numero1, float numero2);
int utn_multiplicacion(float *pResultado, float numero1, float numero2);
int utn_division(float *pResultado, float numero1, float numero2);
int utn_getOption(char *msg, int *pNumero);
int utn_factorial(int *pResultado, float numero);
void utn_imprimirOperaciones(float numero1, float numero2);
void utn_imprimirResultados(float numero1, float numero2, float resultadoSuma, float resultadoResta, float resultadoMultiplicacion, float resultadoDivision, int resultadoFactorial1, int resultadoFactorial2);
int utn_operaciones(float numero1, float numero2, float *pResultadoSuma, float *pResultadoResta, float *pResultadoMultiplicacion, float *pResultadoDivision, int *pResultadoFactorial1, int *pResultadoFactorial2);

#endif /* UTN_TP1_H_ */
