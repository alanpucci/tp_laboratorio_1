#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"
#define BUFFER_SIZE 4096

static int capitalizeStrings(char *string);

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int retornar=-1;
	FILE* pFile;
	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		pFile = fopen(path, "r");
		if(pFile!=NULL && !parser_EmployeeFromText(pFile, pArrayListEmployee))
		{
			retornar=0;
		}
		else
		{
			printf("\nEl archivo no existe");
		}
	}
    return retornar;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retornar=-1;
	FILE* pFile;
	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		pFile = fopen(path, "rb");
		if(pFile!=NULL && !parser_EmployeeFromBinary(pFile, pArrayListEmployee))
		{
			retornar=0;
		}
	}
	return retornar;
}

int controller_searchMaxId(LinkedList* pArrayListEmployee)
{
	int retornar=-1;
	int len = ll_len(pArrayListEmployee);
	Employee* bufferEmp;
	int id;
	int maxId;
	if(pArrayListEmployee!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			bufferEmp = ll_get(pArrayListEmployee, i);
			employee_getId(bufferEmp, &id);
			if(i==0 || id>maxId)
			{
				maxId = id;
				retornar = maxId+1;
			}
		}
	}
	return retornar;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int retornar=-1;
	char bufferName[BUFFER_SIZE];
	int bufferHours;
	float bufferSalary;
	int bufferId;
	Employee* bufferEmp;
	if(pArrayListEmployee!=NULL)
	{
		if(	!utn_getString("\nIngrese el nombre del nuevo empleado: ", "\nERROR! No ingreso un nombre valido", bufferName, 2, BUFFER_SIZE) &&
			!utn_getInt("\nIngrese las horas trabajadas del empleado: ", "\nERROR! No ingreso un numero valido", &bufferHours, 2, 1, 9999) &&
			!utn_getFloat("\nIngrese el sueldo del nuevo empleado: ", "\nEROR! No ingreso un numero valido", &bufferSalary, 2, 1, 999999))
		{
			bufferId = controller_searchMaxId(pArrayListEmployee);
			capitalizeStrings(bufferName);
			bufferEmp = employee_newParameters(bufferId, bufferName, bufferHours, bufferSalary);
			ll_add(pArrayListEmployee, bufferEmp);
			printf("\nID para el nuevo empleado: %d", bufferId);
			retornar=0;
		}
	}
    return retornar;;
}

int controller_findById(LinkedList* pArrayListEmployee, int id, int* index)
{
	int retornar=-1;
	int len = ll_len(pArrayListEmployee);
	int bufferId;
	Employee* bufferEmp;
	if(pArrayListEmployee!=NULL && id>0)
	{
		for(int i=0;i<len;i++)
		{
			bufferEmp = ll_get(pArrayListEmployee, i);
			if(!employee_getId(bufferEmp, &bufferId) && bufferId == id)
			{
				retornar = 0;
				*index = i;
				break;
			}
		}
	}
	return retornar;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retornar=-1;
	int id;
	int index;
	int choosenOption;
	char bufferName[BUFFER_SIZE];
	int bufferHours;
	float bufferSalary;
	Employee* bufferEmp;
	if(pArrayListEmployee!=NULL)
	{
		if( !utn_getInt("\nIngrese el id del empleado a dar de baja: ", "\nERROR! Ingrese un numero valido", &id, 2, 1, 99999) &&
			!controller_findById(pArrayListEmployee, id, &index) && index>-1)
		{
			printf("\nEmpleado encontrado!");
			bufferEmp = ll_get(pArrayListEmployee, index);
			employee_print(bufferEmp);
			if(!utn_getInt( "\nQue campo desea cambiar?\n1)Nombre\n2)Horas trabajadas\n3)Sueldo\n4)Volver atras\n> >OPCION:",
							"ERROR! No ingreso una opcion valida" , &choosenOption, 2, 1, 4))
			{
				switch(choosenOption)
				{
					case 1:
						if( !utn_getString("Ingrese el nuevo nombre: ", "\nERROR! No ingreso un nombre valido", bufferName, 2, BUFFER_SIZE) &&
							!capitalizeStrings(bufferName) && !employee_setNombre(bufferEmp, bufferName))
						{
							ll_set(pArrayListEmployee, index, bufferEmp);
							retornar=0;
						}
					break;
					case 2:
						if( !utn_getInt("\nIngrese las horas trabajadas: ", "\nERROR! No ingreso un numero valido", &bufferHours, 2, 1, 9999) &&
							!employee_setHorasTrabajadas(bufferEmp, bufferHours))
						{
							ll_set(pArrayListEmployee, index, bufferEmp);
							retornar=0;
						}
					break;
					case 3:
						if( !utn_getFloat("\nIngrese el nuevo salario: ", "\nERROR! No ingreso un numero valido", &bufferSalary, 2, 1, 999999) &&
							!employee_setSueldo(bufferEmp, bufferSalary))
						{
							ll_set(pArrayListEmployee, index, bufferEmp);
							retornar=0;
						}
					break;
				}
			}
		}
	}
    return retornar;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int retornar=-1;
	int id;
	int index;
	int choosenOption;
	Employee* bufferEmp;
	if(pArrayListEmployee!=NULL)
	{
		if( !utn_getInt("\nIngrese el id del empleado a dar de baja: ", "\nERROR! Ingrese un numero valido", &id, 2, 1, 99999) &&
			!controller_findById(pArrayListEmployee, id, &index) && index>-1)
		{
			printf("\nEmpleado encontrado!\n");
			bufferEmp = ll_get(pArrayListEmployee, index);
			employee_print(bufferEmp);
			if( !utn_getInt("\nDesea eliminarlo? Presione 1 para eliminar o 2 para cancelar: ", "\nERROR! eliga una opcion valida", &choosenOption, 2, 1, 2) &&
				choosenOption==1)
			{
				ll_remove(pArrayListEmployee, index);
				retornar=0;
			}
			else
			{
				printf("\nEmpleado NO eliminado\n");
			}
		}
		else
		{
			printf("\nNo se encontro un empleado con ese ID, vuelva a intentar");
		}
	}
    return retornar;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retornar=-1;
	int len = ll_len(pArrayListEmployee);
	Employee* bufferEmp;
	char bufferName[BUFFER_SIZE];
	int bufferId;
	int bufferHours;
	float bufferSalary;
	if(pArrayListEmployee!=NULL)
	{
		for(int i=0; i<len;i++)
		{
			bufferEmp = ll_get(pArrayListEmployee, i);
			if(	!employee_getNombre(bufferEmp, bufferName) &&
				!employee_getId(bufferEmp, &bufferId) &&
				!employee_getHorasTrabajadas(bufferEmp, &bufferHours) &&
				!employee_getSueldo(bufferEmp, &bufferSalary))
			{
				printf("ID: %d - Nombre: %s - Horas trabajadas: %d - Sueldo: %.2f\n", bufferId, bufferName, bufferHours, bufferSalary);
				retornar=0;
			}
		}
	}
    return retornar;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retornar=-1;
	int len = ll_len(pArrayListEmployee);
	Employee* bufferFirstEmp;
	Employee* bufferSecondEmp;
	int r;
	if(pArrayListEmployee!=NULL)
	{
		for(int i=0;i<len-1;i++)
		{
			bufferFirstEmp = ll_get(pArrayListEmployee, i);
			bufferSecondEmp = ll_get(pArrayListEmployee, i+1);
			r =	ll_sort(pArrayListEmployee, employee_sort, 1);
			printf("%d",r);
		}
		retornar=0;
	}
	return retornar;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int retornar=-1;
	int len = ll_len(pArrayListEmployee);
	char bufferName[BUFFER_SIZE];
	int bufferId;
	int bufferHours;
	float bufferSalary;
	FILE* pFile;
	Employee* bufferEmp;
	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		pFile = fopen(path, "w");
		if(pFile!=NULL)
		{
			for(int i=0;i<len;i++)
			{
				bufferEmp = ll_get(pArrayListEmployee, i);
				if( !employee_getId(bufferEmp, &bufferId) &&
					!employee_getNombre(bufferEmp, bufferName) &&
					!employee_getHorasTrabajadas(bufferEmp, &bufferHours) &&
					!employee_getSueldo(bufferEmp, &bufferSalary))
				{
					fprintf(pFile, "%d,%s,%d,%f\n",bufferId, bufferName, bufferHours, bufferSalary);
					retornar=0;
				}
			}
			fclose(pFile);
		}
	}
    return retornar;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retornar=-1;
	int len = ll_len(pArrayListEmployee);
	char bufferName[BUFFER_SIZE];
	int bufferId;
	int bufferHours;
	float bufferSalary;
	FILE* pFile;
	Employee* bufferEmp;
	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		pFile = fopen(path, "wb");
		if(pFile!=NULL)
		{
			for(int i=0;i<len;i++)
			{
				bufferEmp = ll_get(pArrayListEmployee, i);
				if( !employee_getId(bufferEmp, &bufferId) &&
					!employee_getNombre(bufferEmp, bufferName) &&
					!employee_getHorasTrabajadas(bufferEmp, &bufferHours) &&
					!employee_getSueldo(bufferEmp, &bufferSalary))
				{
					fwrite(&bufferId,sizeof(int),1,pFile);
					fwrite(bufferName, NAME_SIZE,1,pFile);
					fwrite(&bufferHours, sizeof(int),1,pFile);
					fwrite(&bufferSalary, sizeof(float),1,pFile);
					retornar=0;
				}
				retornar=0;
			}
			fclose(pFile);
		}
	}
	return retornar;
}

static int capitalizeStrings(char *string)
{
	int retornar = -1;
	char bufferName[NAME_SIZE];
	strncpy(bufferName, string, NAME_SIZE);
	bufferName[0] = toupper(bufferName[0]);
	for(int i=1;i<NAME_SIZE;i++)
	{
		bufferName[i] = tolower(bufferName[i]);
	}
	strncpy(string, bufferName, NAME_SIZE);
	retornar = 0;
	return retornar;
}
