#include "arrayEmployees.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

static int idGenerate(void);
static int employee_searchEmpty(Employee pArrayEmployees[], int limit, int *pIndex);
static int addEmployee(Employee* list, int len, int id, char name[],char lastName[],float salary,int sector, int index);
static int findEmployeeById(Employee *list, int len, int id, int *pIndex);
static int employee_print(Employee* pArrayEmployees, int len);
static int sortEmployees(Employee *list, int len, int order);
static int salaryTotal(Employee *list, int len, float *pSalaryTotal, float *pAverage);
static int surpassAverage(Employee *list, int len, int averageSalary, int *pResult);

/**
 * \brief Funcion para dar de alta un empleado pidiendo su nombre, apellido, salario y sector. El id se genera automaticamente autoincrementandose
 * \param Employee *pArrayEmployee: Puntero al array de empleados
 * \param int len: Tamaño del array de empleados
 * \return (-1) Si algo salio mal, (0) si todo salio bien.
 */
int employee_addEmployee(Employee *pArrayEmployee, int len)
{
	int retornar = -1;
	Employee bufferEmployee;
	int index;

	if(pArrayEmployee != NULL && len > 0)
	{
		if(utn_getString("Ingrese el nombre del empleado: ", "\nERROR! Ingrese un nombre valido: ", bufferEmployee.name, 2, NAME_SIZE) == 0 &&
		   utn_getString("Ingrese el apellido del empleado: ", "\nERROR! Ingrese un apellido valido: ", bufferEmployee.lastName, 2, NAME_SIZE) == 0 &&
		   utn_getFloat("\nIngrese el salario: ", "\nERROR! Ingrese un numero valido: ", &bufferEmployee.salary, 2, SALARY_MIN, SALARY_MAX) == 0 &&
		   utn_getInt("\nIngrese el sector: ", "\nERROR! Ingrese un sector valido: ", &bufferEmployee.sector, 2, 0, 500) == 0)

		{
			employee_searchEmpty(pArrayEmployee, len, &index);
			bufferEmployee.id = idGenerate();
			addEmployee(pArrayEmployee, len, bufferEmployee.id, bufferEmployee.name, bufferEmployee.lastName, bufferEmployee.salary, bufferEmployee.sector, index);
			retornar = 0;
		}
	}
	return retornar;
}

/**
 * \brief Funcion estatica para cargar todos los datos pedidos previamente a una posicion de nuestro array de empleados.
 * \param Employee* list: Puntero al array de empleados
 * \param int len: tamaño del array de empleados
 * \param int id: recibimos el id ya generado previamente
 * \param char name[]: recibimos el nombre del empleado
 */
static int addEmployee(Employee* list, int len, int id, char name[],char lastName[],float salary,int sector, int index)
{
	int retornar = -1;
	strcpy(list[index].name, name);
	strcpy(list[index].lastName, lastName);
	list[index].id = id;
	list[index].salary = salary;
	list[index].sector = sector;
	list[index].isEmpty = FALSE;
	retornar = 0;
	return retornar;
}

int modifyEmployee(Employee *pArrayEmployee, int len)
{
	int retornar = -1;
	int index;
	int id;
	int choosedOption;
	Employee bufferEmployee;
	if(pArrayEmployee != NULL && len > 0)
	{
		if(utn_getInt("\nIngrese el id del empleado a modificar: ", "\nError! Ingrese un ID valido: ", &id, 2, 0, 999) == 0 &&
		   findEmployeeById(pArrayEmployee, len, id, &index) == 0 && pArrayEmployee[index].isEmpty == FALSE)
		{
			printf("\nEmpleado encontrado!\nNombre: %s, Apellido: %s, Salario: %.2f, Sector: %d",
					pArrayEmployee[index].name, pArrayEmployee[index].lastName, pArrayEmployee[index].salary, pArrayEmployee[index].sector);
			bufferEmployee = pArrayEmployee[index];
			do
			{
				if(utn_getInt("\nQue campo desea modificar?\n1)Nombre\n2)Apellido\n3)Salario\n4)Sector\n5)Volver atras ",
						"\nERROR! Elija una opcion valida",	&choosedOption, 2, 1, 5) == 0)
				{
					switch(choosedOption)
					{
						case 1:
							if(utn_getString("Ingrese el nuevo nombre del empleado: ", "\nERROR! Ingrese un nombre valido: ",
												pArrayEmployee[index].name, 2, NAME_SIZE) == 0)
							{
								//strncpy(pArrayEmployee[index].name, bufferEmployee.name, NAME_SIZE);
								//printf("Nombre modificado exitosamente! Nuevo nombre: %s", pArrayEmployee[index].name);
								//addEmployee(pArrayEmployee, len, id, pArrayEmployee[index].name,
								//			bufferEmployee.lastName, bufferEmployee.salary, bufferEmployee.sector, index);
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
								printf("\nApellido modificado exitosamente! Nuevo apellido: %s", pArrayEmployee[index].lastName);
								addEmployee(pArrayEmployee, len, id, bufferEmployee.name,
											pArrayEmployee[index].lastName, bufferEmployee.salary, bufferEmployee.sector, index);
								retornar = 0;
							}
							else
							{
								printf("\nHubo un error en el cambio del apellido, por favor vuelva a intentarlo");
							}
						break;
						case 3:
							if(utn_getFloat("Ingrese el nuevo salario del empleado: ", "\nERROR! Ingrese un salario valido: ",
												&pArrayEmployee[index].salary, 2, SALARY_MIN, SALARY_MAX) == 0)
							{
								printf("\nSalario modificado exitosamente! Nuevo salario: %.2f", pArrayEmployee[index].salary);
								addEmployee(pArrayEmployee, len, id, bufferEmployee.name,
											bufferEmployee.lastName, pArrayEmployee[index].salary, bufferEmployee.sector, index);
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
								printf("\nSector modificado exitosamente! Nuevo sector: %d", pArrayEmployee[index].sector);
								addEmployee(pArrayEmployee, len, id, bufferEmployee.name,
											bufferEmployee.lastName, bufferEmployee.salary, pArrayEmployee[index].sector, index);
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
			}while(choosedOption != 5);
		}
		else
		{
			printf("\nID no encontrado! Vuelva a intentar");
		}
	}
	return retornar;
}

int removeEmployee(Employee *list, int len)
{
	int retornar = -1;
	int id;
	int index;
	if(list != NULL && len > 0)
	{
		if(utn_getInt("\nIngrese el id del empleado a eliminar: ", "\nError! Ingrese un ID valido: ", &id, 2, 1, 999) == 0 &&
			findEmployeeById(list, len, id, &index) == 0 && list[index].isEmpty == FALSE)
		{
			printf("Empleado encontrado! Procesando eliminacion...");
			list[index].isEmpty = TRUE;
			return 0;
		}
	}
	return retornar;
}

/**
 * \brief Imprime los alumnos cargados
 * \param Alumno arrayAlumnos[], Es el puntero al array de alumnos
 * \param int limite, es el limite de array
 * \return (-1) Error / (0) Ok
 *
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
				printf("\nID: %d - Nombre: %s - Apellido: %s - Salario: %.2f - Sector: %d", pArrayEmployees[i].id,
						pArrayEmployees[i].name, pArrayEmployees[i].lastName, pArrayEmployees[i].salary, pArrayEmployees[i].sector);
				retorno = 0;
			}
		}
	}
	return retorno;
}

int employee_report(Employee *pArrayEmployees, int len)
{
	int retornar = -1;
	int order;
	float totalSalary;
	float averageSalary;
	int surpassAverageCounter;
	if(pArrayEmployees != NULL && len > 0)
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

static int sortEmployees(Employee *list, int len, int order)
{
	int retornar = -1;
	Employee auxSwap;
	int flagSectorSwap = 1;
	int flagLastNameSwap = 1;
	if(list != NULL && len > 0 && (order == 1 || order == 0))
	{
		if(order == 1)
		{
			while(flagSectorSwap == 1)
			{
				flagSectorSwap = 0;
				for(int i=0; i<len-1;i++)
				{
					if(list[i].sector > list[i+1].sector)
					{
						auxSwap = list[i];
						list[i] = list[i+1];
						list[i+1] = auxSwap;
						flagSectorSwap = 1;
						while(flagLastNameSwap == 1)
						{
							flagLastNameSwap = 0;
							for(int i=0; i<len-1;i++)
							{
								if(strcmp(list[i].lastName, list[i+1].lastName) > 0)
								{
									auxSwap = list[i];
									list[i] = list[i+1];
									list[i+1] = auxSwap;
									flagLastNameSwap = 1;
								}
							}
						}
					}
				}
			}
			retornar = 0;
		}
		else
		{
			while(flagSectorSwap == 1)
			{
				flagSectorSwap = 0;
				for(int i=0; i<len-1;i++)
				{
					if(list[i].sector < list[i+1].sector)
					{
						auxSwap = list[i];
						list[i] = list[i+1];
						list[i+1] = auxSwap;
						flagSectorSwap = 1;
						while(flagLastNameSwap == 1)
						{
							flagLastNameSwap = 0;
							for(int i=0; i<len-1;i++)
							{
								if(strcmp(list[i].lastName, list[i+1].lastName) < 0)
								{
									auxSwap = list[i];
									list[i] = list[i+1];
									list[i+1] = auxSwap;
									flagLastNameSwap = 1;
								}
							}
						}
					}
				}
			}
			retornar = 0;
		}
	}
	return retornar;
}

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
 * \brief Inicializa el array de empleados
 * \param Employee* list, Es el puntero al array de empleados
 * \param int len, es el limite de array
 * \return (-1) Error / (0) Ok
 *
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

static int employee_searchEmpty(Employee pArrayEmployees[], int limit, int *pIndex)
{
	int retornar = -1;
	if(pArrayEmployees != NULL && pIndex != NULL)
	{
		for(int i = 0; i < limit; i++)
		{
			if(pArrayEmployees[i].isEmpty == TRUE && pArrayEmployees[i].id == -1)
			{
				*pIndex = i;
				retornar = 0;
				break;
			}
		}
	}
	return retornar;
}

static int idGenerate(void)
{
	static int id=0;
	id = id+1;
	return id;
}

static int findEmployeeById(Employee *list, int len, int id, int *pIndex)
{
	int retornar = -1;
	if(list != NULL && len > 0 && id > 0)
	{
		for(int i=0; i < len; i++)
		{
			if(list[i].id == id && list[i].isEmpty == FALSE)
			{
				*pIndex = i;
				retornar = 0;
				break;
			}
		}
	}
	return retornar;
}
