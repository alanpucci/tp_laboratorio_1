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
 * \param path char*: Direccion del archivo
 * \param pArrayListEmployee LinkedList*: Puntero a la LinkedList
 * \return (-1) Si algo salio mal o (0) si todo esta bien
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
		fclose(pFile);
	}
    return retornar;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*: Direccion del archivo
 * \param pArrayListEmployee LinkedList*: Puntero a la LinkedList
 * \return (-1) Si algo salio mal o (0) si todo esta bien
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
		else
		{
			printf("\nEl archivo no existe");
		}
		fclose(pFile);
	}
	return retornar;
}

/** \brief Busca en la lista de empleados el maximo id y retorna ese valor + 1
 * \param pArrayListEmployee LinkedList*: Puntero a la LinkedList
 * \return el valor del maximo id encontrado + 1 o (-1) si algo salio mal
 */
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
 * \param pArrayListEmployee LinkedList*: Puntero a la LinkedList
 * \return (-1) Si algo salio mal o (0) si todo esta bien
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
		if(	!utn_getString("Ingrese el nombre del nuevo empleado: ", "\nERROR! No ingreso un nombre valido", bufferName, 2, BUFFER_SIZE) &&
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
		else
		{
			printf("\nHubo un error en la obtencion de datos\n");
		}
	}
    return retornar;;
}

/** \brief Buscar empleado por ID
 *
 * \param pArrayListEmployee LinkedList*: Puntero a la LinkedList
 * \param int id: Recibimos el ID a buscar
 * \param int* index: Devolvemos por referencia el indice del empleado encontrado
 * \return (-1) Si algo salio mal o (0) si todo esta bien
 *
 */
int controller_findById(LinkedList* pArrayListEmployee, int id, int* index)
{
	int retornar=-1;
	int len = ll_len(pArrayListEmployee);
	int bufferId;
	Employee* bufferEmp;
	if(pArrayListEmployee!=NULL && id>0 && index!=NULL)
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

/** \brief Modificar datos de empleado buscado por ID
 *
 * \param pArrayListEmployee LinkedList*: Puntero a la linked list
 * \return (-1) Si algo salio mal o (0) si todo esta bien
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
		if( !utn_getInt("\nIngrese el id del empleado a modificar: ", "\nERROR! Ingrese un ID valido", &id, 2, 1, 99999) &&
			!controller_findById(pArrayListEmployee, id, &index) && index>-1)
		{
			printf("\nEmpleado encontrado!");
			employee_printHeader();
			bufferEmp = ll_get(pArrayListEmployee, index);
			employee_print(bufferEmp);
			if(!utn_getInt( "\n\nQue campo desea cambiar?\n1)Nombre\n2)Horas trabajadas\n3)Sueldo\n4)Volver atras\n> >OPCION:",
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
		else
		{
			printf("\nID no encontrado, vuelva a intentar\n");
		}
	}
    return retornar;
}

/** \brief Baja de empleado por ID
 *
 * \param pArrayListEmployee LinkedList*: Puntero a la LinkedList
 * \return (-1) Si algo salio mal o (0) si todo esta bien
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
			employee_printHeader();
			bufferEmp = ll_get(pArrayListEmployee, index);
			employee_print(bufferEmp);
			if( !utn_getInt("\n\nDesea eliminarlo? Presione 1 para eliminar o 2 para cancelar: ", "\nERROR! eliga una opcion valida", &choosenOption, 2, 1, 2) &&
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

/** \brief Imprime todos los empleados
 *
 * \param pArrayListEmployee LinkedList*: Puntero a la LinkedList
 * \return (-1) Si algo salio mal o (0) si todo esta bien
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retornar=-1;
	int len = ll_len(pArrayListEmployee);
	Employee* bufferEmp;
	if(pArrayListEmployee!=NULL && !ll_isEmpty(pArrayListEmployee))
	{
		employee_printHeader();
		for(int i=0; i<len;i++)
		{
			bufferEmp = ll_get(pArrayListEmployee, i);
			employee_print(bufferEmp);
			retornar=0;
		}
		printf("\n-------------------------------------------------------------");
	}
	else
	{
		printf("\nNo hay empleados para listar");
	}
    return retornar;
}

/** \brief Ordenar empleados por nombre, 1 ascendente o 0 descendente
 *
 * \param pArrayListEmployee LinkedList*: Puntero a la LinkedList
 * \return (-1) Si algo salio mal o (0) si todo esta bien
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retornar=-1;
	int choosenOption;
	if(pArrayListEmployee!=NULL && !ll_isEmpty(pArrayListEmployee))
	{
		if(!utn_getInt("\nIngrese 1 para ascendente o 0 para descendente: ", "\nERROR! Ingrese 1 o 0" , &choosenOption, 2, 0, 1))
		{
			ll_sort(pArrayListEmployee, employee_compareByName, choosenOption);
			retornar=0;
		}
	}
	else
	{
		printf("\nNo hay empleados para ordenar\n");
	}
	return retornar;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*: Direccion del archivo
 * \param pArrayListEmployee LinkedList*: Puntero a la LinkedList
 * \return (-1) Si algo salio mal o (0) si todo esta bien
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
			ll_sort(pArrayListEmployee, employee_compareById, 1);
			fprintf(pFile, "id,nombre,horasTrabajadas,sueldo\n");
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
 * \param path char*: Direccion del archivo
 * \param pArrayListEmployee LinkedList*: Puntero a la LinkedList
 * \return (-1) Si algo salio mal o (0) si todo esta bien
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retornar=-1;
	int len = ll_len(pArrayListEmployee);
	FILE* pFile;
	Employee* bufferEmp;
	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		pFile = fopen(path, "wb");
		if(pFile!=NULL)
		{
			ll_sort(pArrayListEmployee, employee_compareById, 1);
			for(int i=0;i<len;i++)
			{
				bufferEmp = ll_get(pArrayListEmployee, i);
				fwrite(bufferEmp, sizeof(Employee),1, pFile);
				retornar=0;
			}
			fclose(pFile);
		}
	}
	return retornar;
}

/** \brief Pone letra Capital a un string que recibe, el resto de caracteres en minuscula
 *
 * \param char *string: Cadena de caracteres a capitalizar
 * \return (-1) Si algo salio mal o (0) si todo esta bien
 *
 */
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
