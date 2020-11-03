#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#define BUFFER_SIZE 4096

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*: Direccion del archivo
 * \param pArrayListEmployee LinkedList*: Puntero a la LinkedList
 * \return (-1) Si algo salio mal o (0) si todo esta bien
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retornar=-1;
	char bufferId[BUFFER_SIZE];
	char bufferName[BUFFER_SIZE];
	char bufferHours[BUFFER_SIZE];
	char bufferSalary[BUFFER_SIZE];
	Employee* bufferEmp;
	if(pFile!=NULL && pArrayListEmployee!=NULL)
	{
		ll_clear(pArrayListEmployee);
		do
		{
			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n",bufferId,bufferName,bufferHours,bufferSalary)==4)
			{
				bufferEmp = employee_newParametros(bufferId, bufferName, bufferHours, bufferSalary);
				ll_add(pArrayListEmployee, bufferEmp);
				retornar=0;
			}
		}while(feof(pFile)==0);
		fclose(pFile);
		//retornar = atoi(bufferId);
	}
    return retornar;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*: Direccion del archivo
 * \param pArrayListEmployee LinkedList*: Puntero a la LinkedList
 * \return (-1) Si algo salio mal o (0) si todo esta bien
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{

	int retornar=-1;
	char name[NAME_SIZE];
	int id;
	int hours;
	float salary;
	Employee* bufferEmp;
	if(pFile!=NULL && pArrayListEmployee!=NULL)
	{
		ll_clear(pArrayListEmployee);
		do
		{
			if( fread(&id, sizeof(int),1,pFile)==1 && fread(name, NAME_SIZE, 1, pFile)==1 &&
				fread(&hours, sizeof(int), 1, pFile)==1 && fread(&salary, sizeof(float),1,pFile))
			{
				bufferEmp = employee_newParameters(id, name, hours, salary);
				ll_add(pArrayListEmployee, bufferEmp);
				retornar=0;
			}
		}while(feof(pFile)==0);
		fclose(pFile);
	}
	return retornar;
}
