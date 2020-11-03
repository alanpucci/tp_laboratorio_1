#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "menu.h"
#include "utn.h"

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
    int menuOption;
    int option;
    int listFlag=0;

    LinkedList* listaEmpleados = ll_newLinkedList();
    do{
    	if(utn_getMenu(&menuOption, 2, 1, 10)==0)
    	{
			switch(menuOption)
			{
				case 1:
					if(listFlag== 0 && !controller_loadFromText("data.csv",listaEmpleados))
					{
						printf("\nEmpleados cargados correctamente\n");
						listFlag=1;
					}
					else
					{
						if( !utn_getInt("\nYa hay una lista cargada, desea reemplazarla?: Presione 1 para aceptar o 2 para cancelar", "\nERROR!", &option, 2, 1, 2) &&
							option==1 && !controller_loadFromText("data.csv", listaEmpleados))
						{
							printf("\nEmpleados cargados correctamente\n");
						}
						else
						{
							printf("\nNo se cargaron los empleados\n");
						}
					}
				break;
				case 2:
					if(listFlag==0 && !controller_loadFromBinary("dataBin.csv", listaEmpleados))
					{
						printf("\nEmpleados cargados correctamente\n");
						listFlag=1;
					}
					else
					{
						if( !utn_getInt("\nYa hay una lista cargada, desea reemplazarla?: Presione 1 para aceptar o 2 para cancelar", "\nERROR!", &option, 2, 1, 2) &&
							option==1 && !controller_loadFromBinary("dataBin.csv", listaEmpleados))
						{
							printf("\nEmpleados cargados correctamente\n");
						}
						else
						{
							printf("\nNo se cargaron los empleados\n");
						}
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
					if(!controller_editEmployee(listaEmpleados))
					{
						printf("\nEmpleado modificado exitosamente!\n");
					}
					else
					{
						printf("\nPrimero debe hacer la carga de los empleados\n");
					}
				break;
				case 5:
					if(!controller_removeEmployee(listaEmpleados))
					{
						printf("\nEmpleado dado de baja correctamente\n");
					}
					else
					{
						printf("\nPrimero debe hacer la carga de los empleados\n");
					}
				break;
				case 6:
					if(!controller_ListEmployee(listaEmpleados))
					{
						printf("\nFin de la impresion\n");
					}
					else
					{
						printf("\nPrimero debe hacer la carga de los empleados\n");
					}
				break;
				case 7:
					if(!controller_sortEmployee(listaEmpleados))
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
    }while(menuOption != 10);
    printf("Adios!");
    return 0;
}

