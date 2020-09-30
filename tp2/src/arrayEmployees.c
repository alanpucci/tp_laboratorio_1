#include "arrayEmployees.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "utn.h"

static int idGenerate(void);
static int employee_searchEmpty(Employee pArrayEmployees[], int limit);
static int addEmployee(Employee* list, int len, int id, char name[],char lastName[],float salary,int sector);
static int findEmployeeById(Employee *list, int len, int id);
static int employee_print(Employee* pArrayEmployees, int len);
static int sortEmployees(Employee *list, int len, int order);
static int salaryTotal(Employee *list, int len, float *pSalaryTotal, float *pAverage);
static int surpassAverage(Employee *list, int len, int averageSalary, int *pResult);
static int capitalizeStrings(char *string);
static int searchForEmpty(Employee *list, int len);
static int removeEmployee(Employee* list, int len, int id);

/**
 * \brief Function to add an employee asking for name, last name, salary and sector. ID is generated automatically
 * \param Employee *pArrayEmployee: Pointer to an employee array
 * \param int len: employee array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int employee_addEmployee(Employee *pArrayEmployee, int len)
{
	int retornar = -1;
	Employee bufferEmployee;
	if(pArrayEmployee != NULL && len > 0)
	{
		if(employee_searchEmpty(pArrayEmployee, len) >= 0 && utn_getString("Ingrese el nombre del empleado: ", "\nERROR! Ingrese un nombre valido: ", bufferEmployee.name, 2, NAME_SIZE) == 0 &&
		   utn_getString("Ingrese el apellido del empleado: ", "\nERROR! Ingrese un apellido valido: ", bufferEmployee.lastName, 2, NAME_SIZE) == 0 &&
		   utn_getFloat("\nIngrese el salario: ", "\nERROR! Ingrese un numero valido: ", &bufferEmployee.salary, 2, SALARY_MIN, LONG_MAX) == 0 &&
		   utn_getInt("\nIngrese el sector: ", "\nERROR! Ingrese un sector valido: ", &bufferEmployee.sector, 2, 0, 999) == 0)

		{
			bufferEmployee.id = idGenerate();
			addEmployee(pArrayEmployee, len, bufferEmployee.id, bufferEmployee.name, bufferEmployee.lastName, bufferEmployee.salary, bufferEmployee.sector);
			retornar = 0;
		}
	}
	return retornar;
}

/** \brief add in a existing list of employees the values received as parameters
 * in the first empty position
 * \param Employee *list: Pointer to an Employee array
 * \param int len: Length of the array
 * \param int id: receive the id
 * \param char name[]: receive the name to give to a new employee
 * \param char lastName[]: receive the last name to give to a new employee
 * \param float salary: receive the salary to give to a new employee
 * \param int sector: receive the sector to give to a new employee
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without free space] - (0) if Ok
 */
static int addEmployee(Employee* list, int len, int id, char name[],char lastName[],float salary,int sector)
{
	int retornar = -1;
	int index = employee_searchEmpty(list, len);
	strncpy(list[index].name, name, NAME_SIZE);
	strncpy(list[index].lastName, lastName, NAME_SIZE);
	capitalizeStrings(list[index].name);
	capitalizeStrings(list[index].lastName);
	list[index].id = id;
	list[index].salary = salary;
	list[index].sector = sector;
	list[index].isEmpty = FALSE;
	retornar = 0;
	return retornar;
}

/**
 * \brief Function to modify an employee searched by ID
 * \param Employee *pArrayEmployee: Pointer to an Employee array
 * \param int len: Length of the array
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int employee_modifyEmployee(Employee *pArrayEmployee, int len)
{
	int retornar = -1;
	int index;
	int id;
	int choosenOption;
	if(pArrayEmployee != NULL && len > 0 && searchForEmpty(pArrayEmployee, len) == 0)
	{
		if(utn_getInt("\nIngrese el id del empleado a modificar: ", "\nError! Ingrese un ID valido: ", &id, 2, 0, 999) == 0)
		{
			index = findEmployeeById(pArrayEmployee, len, id);
			printf("\nEmpleado encontrado!\nNombre: %s, Apellido: %s, Salario: %.2f, Sector: %d",
					pArrayEmployee[index].name, pArrayEmployee[index].lastName, pArrayEmployee[index].salary, pArrayEmployee[index].sector);
			do
			{
				if(pArrayEmployee[index].isEmpty == FALSE && utn_getInt("\nQue campo desea modificar?\n1)Nombre\n2)Apellido\n3)Salario\n4)Sector\n5)Volver atras ",
						"\nERROR! Elija una opcion valida",	&choosenOption, 2, 1, 5) == 0)
				{
					switch(choosenOption)
					{
						case 1:
							if(utn_getString("Ingrese el nuevo nombre del empleado: ", "\nERROR! Ingrese un nombre valido: ",
												pArrayEmployee[index].name, 2, NAME_SIZE) == 0)
							{
								printf("\nNombre del empleado modificado con exito! Nuevo nombre: %s", pArrayEmployee[index].name);
								retornar = 0;
							}
							else
							{
								printf("\nHubo un error en el cambio del nombre, por favor vuelva a intentarlo");
							}
						break;
						case 2:
							if(utn_getString("Ingrese el nuevo apellido del empleado: ", "\nERROR! Ingrese un apellido valido: ",
												pArrayEmployee[index].lastName, 2, len) == 0)
							{
								printf("\nApellido del empleado modificado con exito! Nuevo apellido: %s", pArrayEmployee[index].lastName);
								retornar = 0;
							}
							else
							{
								printf("\nHubo un error en el cambio del apellido, por favor vuelva a intentarlo");
							}
						break;
						case 3:
							if(utn_getFloat("Ingrese el nuevo salario del empleado: ", "\nERROR! Ingrese un salario valido: ",
												&pArrayEmployee[index].salary, 2, SALARY_MIN, LONG_MAX) == 0)
							{
								printf("\nSalario del empleado modificado con exito! Nuevo salario: %.2f", pArrayEmployee[index].salary);
								retornar = 0;
							}
							else
							{
								printf("\nHubo un error en el cambio del salario, por favor vuelva a intentarlo");
							}
						break;
						case 4:
						if(utn_getInt("Ingrese el nuevo sector del empleado: ", "\nERROR! Ingrese un sector valido: ",
												&pArrayEmployee[index].sector, 2, 0, 500) == 0)
							{
								printf("\nSector del empleado modificado con exito! Nuevo sextor: %d", pArrayEmployee[index].sector);
								retornar = 0;
							}
							else
							{
								printf("\nHubo un error en el cambio del sector, por favor vuelva a intentarlo");
							}
						break;
					}
				}
				break;
			}while(choosenOption != 5);
		}
		else
		{
			printf("\nID no encontrado! Vuelva a intentar");
		}
	}
	return retornar;
}

/**
 * \brief Function to modify an employee searched by ID
 * \param Employee *pArrayEmployee: Pointer to an Employee array
 * \param int len: Length of the array
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int employee_removeEmployee(Employee *list, int len)
{
	int retornar = -1;
	int id;
	if(list != NULL && len > 0 && searchForEmpty(list, len) == 0)
	{
		if(utn_getInt("\nIngrese el id del empleado a eliminar: ", "\nError! Ingrese un ID valido: ", &id, 2, 1, 999) == 0)
		{
			if(removeEmployee(list, len, id) == 0)
			{
				retornar = 0;
				printf("\nEmpleado encontrado, Procesando eliminacion...");
			}
		}
	}
	return retornar;
}
/**
 * \brief Remove a Employee by Id (put isEmpty Flag in 1)
 * \param Employee *pArrayEmployee: Pointer to an Employee array
 * \param int len: Length of the array
 * \param int id: receive an id
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't find a employee] - (0) if Ok
 *
 */
static int removeEmployee(Employee* list, int len, int id)
{
	int retornar = -1;
	int index;
	if(list != NULL && len > 0)
	{
		index = findEmployeeById(list, len, id);
		if(list[index].isEmpty == FALSE)
		{
			list[index].isEmpty = TRUE;
			retornar = 0;
		}
	}
	return retornar;
}

/**
 * \brief Function to print all the employees in the array
 * \param Employee *pArrayEmployee: Pointer to an Employee array
 * \param int len: Length of the array
 * \return (-1) if something went wrong, (0) if everything is OK
 */
static int employee_print(Employee* pArrayEmployees, int len)
{
	int retorno = -1;
	if(pArrayEmployees != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(pArrayEmployees[i].isEmpty == FALSE)
			{
				printf("\nID: %d - Nombre: %s - Apellido: %s - Salario: %.2f - Sector: %d",pArrayEmployees[i].id,
						pArrayEmployees[i].name, pArrayEmployees[i].lastName, pArrayEmployees[i].salary, pArrayEmployees[i].sector);
				retorno = 0;
			}
		}
	}
	return retorno;
}

/**
 * \brief Function to report by printing: list of employees (ascendent or descendent), salary accumulated of all employees, the average of salary
 *        and how many emplooyes surpass the average
 * \param Employee *pArrayEmployee: Pointer to an Employee array
 * \param int len: Length of the array
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int employee_report(Employee *pArrayEmployees, int len)
{
	int retornar = -1;
	int order;
	float totalSalary;
	float averageSalary;
	int surpassAverageCounter;
	if(pArrayEmployees != NULL && len > 0 && searchForEmpty(pArrayEmployees, len) == 0)
	{
		if(utn_getInt("\nIngrese un numero para ordenar:\n0)De forma descendente\n1)De forma ascendente ",
					  "\nERROR! Ingrese una opcion valida", &order, 2, 0, 1) == 0)
		{
			sortEmployees(pArrayEmployees, len, order);
			salaryTotal(pArrayEmployees, len, &totalSalary, &averageSalary);
			surpassAverage(pArrayEmployees, len, averageSalary, &surpassAverageCounter);
			retornar = 0;
		}
		employee_print(pArrayEmployees, len);
		printf("\nEl salario total es: %.2f", totalSalary);
		printf("\nEl promedio del salario es: %.2f", averageSalary);
		printf("\nEl promedio lo superan %d empleados", surpassAverageCounter);
	}
	return retornar;
}

/**
 * \brief Function to search in the Employee array for an empty field
 * \param Employee *pArrayEmployee: Pointer to an Employee array
 * \param int len: Length of the array
 * \return (-1) if something went wrong, (0) if everything is OK
 */

static int searchForEmpty(Employee *list, int len)
{
	int retornar = -1;
	if(list != NULL && len > 0)
	{
		for(int i=0; i<len; i++)
		{
			if(list[i].isEmpty == FALSE)
			{
				retornar = 0;
				break;
			}
		}
	}

	return retornar;
}

/**
 * \brief Function to sort the list of employees by ascendent (0) or descendent(1)
 * \param Employee *list: Pointer the an Employee array
 * \param int len: Length of the array
 * \param int order: Number we receive to determine if the list is going to sort ascendent or descendent
 * \return (-1) if something went wrong, (0) if everything is OK
 */
static int sortEmployees(Employee *list, int len, int order)
{
	int retornar = -1;
	Employee auxSwap;
	int flagSwap;
	if(list != NULL && len > 0 && (order == 1 || order == 0))
	{
		do
		{
			flagSwap = 0;
			for(int i=0; i<len-1; i++)
			{
				if( (order == 1 && ( (strncmp(list[i].lastName, list[i+1].lastName, NAME_SIZE) > 0) ||
					(strncmp(list[i].lastName, list[i+1].lastName, NAME_SIZE) == 0 && list[i].sector > list[i+1].sector)))
						||
					(order == 0 && ( (strncmp(list[i].lastName, list[i+1].lastName, NAME_SIZE) < 0) ||
					(strncmp(list[i].lastName, list[i+1].lastName, NAME_SIZE) == 0 && list[i].sector < list[i+1].sector))))
				{
					auxSwap = list[i];
					list[i] = list[i+1];
					list[i+1] = auxSwap;
					flagSwap = 1;
					retornar = 0;
				}
			}
		}while(flagSwap);
	}
	return retornar;
}

/**
 * \brief Function to calculate the salary's accumulated of all employees and the average
 * \param Employee *list: Pointer to an Employee array
 * \param int len: Length of the array
 * \param float *pSalaryTotal: Pointer of the salary's total accumulated of all employees
 * \param float *pAverage: Pointer of the salary average
 * \return (-1) if something went wrong, (0) if everything is OK
 */
static int salaryTotal(Employee *list, int len, float *pSalaryTotal, float *pAverage)
{
	int retornar = -1;
	float accSalary=0;
	int salaryCounter=0;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE)
			{
				accSalary += list[i].salary;
				salaryCounter++;
			}
		}
		*pSalaryTotal = accSalary;
		*pAverage = accSalary / salaryCounter;
		retornar = 0;
	}
	return retornar;
}


/**
 * \brief Function to calculate how many employees surpass the salary average
 * \param Employee *list: Pointer to an Employee array
 * \param int len: Length of the array
 * \param int averageSalary: receive the salary average
 * \param int *pResult: Pointer of the result of how many employees surpass the average
 *\return (-1) if something went wrong, (0) if everything is OK
 */
static int surpassAverage(Employee *list, int len, int averageSalary, int *pResult)
{
	int retornar = -1;
	int surpassAverageCounter=0;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE && list[i].salary > averageSalary)
			{
				surpassAverageCounter++;
				retornar = 0;
			}
		}
		*pResult = surpassAverageCounter;
	}
	return retornar;
}

/**
 * \brief Function to init isEmpty to TRUE of an Employee array
 * \param Employee *list: Pointer to an Employee array
 * \param int len: Length of the array
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int initEmployees(Employee* list, int len)
{
	int retornar = -1;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			list[i].isEmpty = TRUE;
			list[i].id = -1;
		}
		retornar = 0;
	}
	return retornar;
}

/**
 * \brief Function that returns the first index found on an Employee array that is empty
 * \param Employee *list: Pointer to an Employee array
 * \param int len: Length of the array
 * \return the index of an empty employee or (-1) if something went wrong
 */
static int employee_searchEmpty(Employee *pArrayEmployees, int len)
{
	int retornar = -1;
	if(pArrayEmployees != NULL)
	{
		for(int i = 0; i < len; i++)
		{
			if(pArrayEmployees[i].isEmpty == TRUE && pArrayEmployees[i].id == -1)
			{
				retornar = i;
				break;
			}
		}
	}
	return retornar;
}

/**
 * \brief Function to auto-generate an ID
 * \return the id
 */
static int idGenerate(void)
{
	static int id=0;
	id = id+1;
	return id;
}

/**
 * \brief Function to find an employee index receiving an id
 * \param Employee *list: Pointer to an Employee array
 * \param int len: Length of the array
 * \param int id: receive the id to be searched
 * \return the index or (-1) if something went wrong
 */
static int findEmployeeById(Employee *list, int len, int id)
{
	int retornar = -1;
	if(list != NULL && len > 0 && id > 0)
	{
		for(int i=0; i < len; i++)
		{
			if(list[i].id == id && list[i].isEmpty == FALSE)
			{
				retornar = i;
				break;
			}
		}
	}
	return retornar;
}

/**
 * \brief Function to converts an string to lowercase and it first letter to uppercase
 * \param char *string: receive an string, preferents a name
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
