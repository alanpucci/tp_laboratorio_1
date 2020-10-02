#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrayEmployees.h"
#include "utn.h"

int main(void) {
	setbuf(stdout,NULL);
	int menuOption;
	Employee arrayEmployees[EMPLOYEES_LEN];

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
