#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "menu.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/

int main()
{
	setbuf(stdout,NULL);
    int option;
    int listFlag=0;

    LinkedList* listaEmpleados = ll_newLinkedList();
    do{
    	if(utn_getMenu(&option, 2, 1, 10)==0)
    	{
			switch(option)
			{
				case 1:
					if(!controller_loadFromText("data.csv",listaEmpleados))
					{
						printf("\nEmpleados cargados correctamente\n");
						listFlag=1;
					}
				break;
				case 2:
					if(!controller_loadFromBinary("dataBin.csv", listaEmpleados))
					{
						printf("\nEmpleados cargados correctamente\n");
						listFlag=1;
					}
				break;
				case 3:
					if(listFlag && !controller_addEmployee(listaEmpleados))
					{
						printf("\nEmpleado dado de alta correctamente!\n");
					}
					else
					{
						printf("\nPrimero debe hacer la carga de los empleados\n");
					}
				break;
				case 4:
					if(listFlag && !controller_editEmployee(listaEmpleados))
					{
						printf("\nEmpleado modificado exitosamente!\n");
					}
					else
					{
						printf("\nPrimero debe hacer la carga de los empleados\n");
					}
				break;
				case 5:
					if(listFlag && !controller_removeEmployee(listaEmpleados))
					{
						printf("\nEmpleado dado de baja correctamente\n");
					}
					else
					{
						printf("\nPrimero debe hacer la carga de los empleados\n");
					}
				break;
				case 6:
					if(listFlag && !controller_ListEmployee(listaEmpleados))
					{
						printf("\nFin de la impresion\n");
					}
					else
					{
						printf("\nPrimero debe hacer la carga de los empleados\n");
					}
				break;
				case 7:
					if(listFlag && !controller_sortEmployee(listaEmpleados))
					{
						printf("\nFin del ordenamiento");
					}
					else
					{
						printf("\nPrimero debe hacer la carga de los empleados\n");
					}
				break;
				case 8:
					if(listFlag && !controller_saveAsText("data.csv", listaEmpleados))
					{
						printf("\nEmpleados guardados correctamente en el archivo\n");
					}
					else
					{
						printf("\nPrimero debe hacer la carga de los empleados\n");
					}
				break;
				case 9:
					if(listFlag && !controller_saveAsBinary("dataBin.csv", listaEmpleados))
					{
						printf("\nEmpleados guardados correctamente en el archivo (binario)\n");
					}
					else
					{
						printf("\nPrimero debe hacer la carga de los empleados\n");
					}
				break;
			}
    	}
    }while(option != 10);
    printf("Adios!");
    return 0;
}

