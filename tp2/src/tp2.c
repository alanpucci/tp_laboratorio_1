#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrayEmployees.h"
#include "utn.h"

int main(void) {
	setbuf(stdout,NULL);
	int menuOption;
	Employee arrayEmployees[EMPLOYEES_LEN];
	/*
	employee_initEmployees(arrayEmployees, EMPLOYEES_LEN);
	arrayEmployees[0].id = 1;
	strcpy(arrayEmployees[0].name, "Alan");
	strcpy(arrayEmployees[0].lastName, "Pucci");
	arrayEmployees[0].salary = 1341;
	arrayEmployees[0].sector = 134;
	arrayEmployees[0].isEmpty = FALSE;

	arrayEmployees[1].id = 2;
	strcpy(arrayEmployees[1].name, "Jorge");
	strcpy(arrayEmployees[1].lastName, "Pucci");
	arrayEmployees[1].salary = 141;
	arrayEmployees[1].sector = 12;
	arrayEmployees[1].isEmpty = FALSE;

	arrayEmployees[2].id = 3;
	strcpy(arrayEmployees[2].name, "Albert");
	strcpy(arrayEmployees[2].lastName, "Pucci");
	arrayEmployees[2].salary = 656;
	arrayEmployees[2].sector = 54;
	arrayEmployees[2].isEmpty = FALSE;

	arrayEmployees[3].id = 4;
	strcpy(arrayEmployees[3].name, "Robert");
	strcpy(arrayEmployees[3].lastName, "Pucci");
	arrayEmployees[3].salary = 111;
	arrayEmployees[3].sector = 2;
	arrayEmployees[3].isEmpty = FALSE;

	arrayEmployees[4].id = 5;
	strcpy(arrayEmployees[4].name, "Alejandro");
	strcpy(arrayEmployees[4].lastName, "Pucci");
	arrayEmployees[4].salary = 111;
	arrayEmployees[4].sector = 205;
	arrayEmployees[4].isEmpty = FALSE;
	*/
	if(initEmployees(arrayEmployees, EMPLOYEES_LEN)==0)
	{
		do
		{
			utn_getMenu(&menuOption, 2, 1, 5);
			switch(menuOption)
			{
				case 1:
					if(employee_addEmployee(arrayEmployees, EMPLOYEES_LEN) == 0)
					{
						printf("\nEmpleado ingresado exitosamente!\n");
					}
					else
					{
						printf("Hubo un error!");
					}
				break;
				case 2:
					if(employee_modifyEmployee(arrayEmployees, EMPLOYEES_LEN) == 0)
					{
						printf("\nModificacion exitosa");
					}
					else
					{
						printf("\nEmpleado inexistente");
					}
				break;
				case 3:
					if(employee_removeEmployee(arrayEmployees, EMPLOYEES_LEN) == 0 )
					{
						printf("Empleado eliminado exitosamente!");
					}
					else
					{
						printf("\nEmpleado inexistente");
					}
				break;
				case 4:
					if(employee_report(arrayEmployees, EMPLOYEES_LEN) == 0)
					{
						printf("\nFin del reporte");
					}
					else
					{
						printf("\nLista inexistente");
					}
				break;
			}
		}while(menuOption != 5);
	}
	printf("Adios!!");
	return EXIT_SUCCESS;
}
