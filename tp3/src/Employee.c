#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#define BUFFER_SIZE 4096

static int isValidInt(char string[]);
static int isValidString(char* string);
static int isValidFloat(char string[]);

/** \brief Uso de malloc para obtener una nueva direccion de memoria
 * 	\return la nueva direccion de memoria
 */
Employee* employee_new()
{
	return (Employee*)malloc(sizeof(Employee));
}

/** \brief Dar de alta un empleado recibiendo los parametros como texto
 * \param char* idStr: Recibo el id en forma de texto
 * \param char* nombreStr: Recibo el nombre
 * \param char* horasTrabajadasStr: Recibo las horas trabajadas en forma de texto
 * \param char* sueldo: Recibo el sueldo en forma de texto
 * \return la direccion de memoria del empleado con todos sus datos cargados o NULL en caso de que algo haya salido mal
 */
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldo)
{
	Employee* this = employee_new();
	if(this!=NULL)
	{
		if(  employee_setIdTxt(this, idStr)!=-1 &&
		     employee_setNombre(this, nombreStr)!=-1 &&
			 employee_setHorasTrabajadasTxt(this, horasTrabajadasStr)!=-1 &&
			 employee_setSueldoTxt(this, sueldo)!=-1)
		{
			return this;
		}
	}
	employee_delete(this);
	return NULL;
}

/** \brief Dar de alta un empleado recibiendo los parametros tal y como son
 * \param char* idStr: Recibo el id en forma de entero
 * \param char* nombreStr: Recibo el nombre
 * \param char* horasTrabajadasStr: Recibo las horas trabajadas en forma de entero
 * \param char* sueldo: Recibo el sueldo en forma de flotante
 * \return la direccion de memoria del empleado con todos sus datos cargados o NULL en caso de que algo haya salido mal
 */
Employee* employee_newParameters(int id,char* name,int hours, float salary)
{
	Employee* this = employee_new();
	if(this!=NULL)
	{
		if(  employee_setId(this, id)!=-1 &&
		     employee_setNombre(this, name)!=-1 &&
			 employee_setHorasTrabajadas(this, hours)!=-1 &&
			 employee_setSueldo(this, salary)!=-1)
		{
			return this;
		}
	}
	employee_delete(this);
	return NULL;
}

/** \brief Borra la direccion de memoria reservada de un empleado
 *  \param Employee* this: Puntero del empleado
 *
 */
void employee_delete(Employee* this)
{
	free(this);
}

/** \brief Obtengo el id de un empleado
 * \param Employee* this: Puntero del empleado
 * \param int* id: Pasaje por referencia del id del empleado
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int employee_getId(Employee* this, int* id)
{
	int retornar=-1;
	if(this!=NULL && id!=NULL)
	{
		*id = this->id;
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno el id de un empleado
 * \param Employee* this: Puntero del empleado
 * \param int id: Recibo el id a ser asignado a ese empleado
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int employee_setId(Employee* this, int id)
{
	int retornar=-1;
	if(this!=NULL && id>0)
	{
		this->id = id;
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno el id de un empleado recibiendo el id como texto
 * \param Employee* this: Puntero del empleado
 * \param char* id: Recibo el id, en forma de texto, a ser asignado a ese empleado
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int employee_setIdTxt(Employee* this, char* id)
{
	int retornar=-1;
	char bufferId[BUFFER_SIZE];
	if(this!=NULL && id!=NULL && isValidInt(id)==1)
	{
		strncpy(bufferId, id, BUFFER_SIZE);
		this->id = atoi(bufferId);
		retornar=0;
	}
	return retornar;
}

/** \brief Obtengo el nombre de un empleado
 * \param Employee* this: Puntero del empleado
 * \param char* name: Recibo el puntero a donde se va a guardar el nombre de ese empleado
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int employee_getNombre(Employee* this, char* nombre)
{
	int retornar=-1;
	if(this!=NULL && nombre!=NULL)
	{
		strncpy(nombre, this->nombre, NAME_SIZE);
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno el nombre de un empleado
 * \param Employee* this: Puntero del empleado
 * \param char* name: Recibo el puntero del nombre a ser colocado al empleado
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int employee_setNombre(Employee* this, char* nombre)
{
	int retornar=-1;
	if(this!=NULL && nombre!=NULL && isValidString(nombre)==1)
	{
		strncpy(this->nombre, nombre, NAME_SIZE);
		retornar=0;
	}
	return retornar;
}

/** \brief Obtengo las horas trabajadas de un empleado
 * \param Employee* this: Puntero del empleado
 * \param int* horasTrabajadas: Pasaje por referencia de las horas trabajadas de ese empleado
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int employee_getHorasTrabajadas(Employee* this, int* horasTrabajadas)
{
	int retornar=-1;
	if(this!=NULL && horasTrabajadas!=NULL)
	{
		*horasTrabajadas = this->horasTrabajadas;
		retornar=0;;
	}
	return retornar;;
}

/** \brief Asigno las horas trabajadas de un empleado
 * \param Employee* this: Puntero del empleado
 * \param int horasTrabajadas: Recibo las horas trabajadas a asignar al empleado
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int employee_setHorasTrabajadas(Employee* this, int horasTrabajadas)
{
	int retornar=-1;
	if(this!=NULL && horasTrabajadas>0)
	{
		this->horasTrabajadas = horasTrabajadas;
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno las horas trabajadas de un empleado en forma de texto
 * \param Employee* this: Puntero del empleado
 * \param char* horasTrabajadas: Recibo las horas trabajadas, en forma de texto, a asignar al empleado
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int employee_setHorasTrabajadasTxt(Employee* this, char* horasTrabajadas)
{
	int retornar=-1;
	char bufferHoras[BUFFER_SIZE];
	if(this!=NULL && horasTrabajadas>0 && isValidInt(horasTrabajadas)==1)
	{
		strncpy(bufferHoras, horasTrabajadas, BUFFER_SIZE);
		this->horasTrabajadas = atoi(bufferHoras);
		retornar=0;
	}
	return retornar;
}

/** \brief Obtengo el sueldo de un empleado
 * \param Employee* this: Puntero del empleado
 * \param float* sueldo: Pasaje por referencia del sueldo de un empleado
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int employee_getSueldo(Employee* this, float* sueldo)
{
	int retornar=-1;
	if(this!=NULL && sueldo!=NULL)
	{
		*sueldo = this->sueldo;
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno el sueldo de un empleado
 * \param Employee* this: Puntero del empleado
 * \param float sueldo: Recibo el sueldo a asignar al empleado
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int employee_setSueldo(Employee* this, float sueldo)
{
	int retornar=-1;
	if(this!=NULL && sueldo>0)
	{
		this->sueldo = sueldo;
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno el sueldo de un empleado en forma de texto
 * \param Employee* this: Puntero del empleado
 * \param char* sueldo: Recibo el sueldo, en forma de texto, a asignar al empleado
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int employee_setSueldoTxt(Employee* this, char* sueldo)
{
	int retornar=-1;
	char bufferSueldo[BUFFER_SIZE];
	if(this!=NULL && isValidFloat(sueldo)==1)
	{
		strncpy(bufferSueldo, sueldo, BUFFER_SIZE);
		this->sueldo = atof(bufferSueldo);
		retornar=0;
	}
	return retornar;
}

/** \brief Imprime los datos de un empleado
 *  \param Employee* this: Puntero del empleado
 *  \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int employee_print(Employee* this)
{
	int retornar=-1;
	char bufferName[BUFFER_SIZE];
	int bufferId;
	int bufferHours;
	float bufferSalary;
	if(this!=NULL)
	{
		if( !employee_getId(this, &bufferId) &&
			!employee_getNombre(this, bufferName) &&
			!employee_getHorasTrabajadas(this, &bufferHours) &&
			!employee_getSueldo(this, &bufferSalary))
		{
			printf("\n%-10d%-20s%-20d%.2f", bufferId, bufferName, bufferHours, bufferSalary);
			retornar = 0;
		}
	}
	return retornar;
}

/** \brief Imprime el header de los empleados
 */
void employee_printHeader(void)
{
	printf("\n-------------------------------------------------------------");
	printf("\nID        Nombre              Horas trabajadas    Salario    ");
	printf("\n-------------------------------------------------------------");
}

/**
 * \brief Funcion para validar si el array de caracteres que recibe es una cadena de texto y no otra cosa
 * \param char string[]: Es el string que vamos a validar
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
static int isValidString(char* string)
{
	int retornar=1;
	if(string!=NULL && strlen(string)>0)
	{
		for(int i=0;i<strlen(string);i++)
		{
			if((string[i]<'a' || string[i]>'z') && (string[i]<'A' || string[i]>'Z') && string[i]!=32 && string[i]!=45)
			{
				retornar=0;
				break;
			}
		}
	}
	return retornar;
}

/**
 * \brief Funcion para validar si la cadena de caracteres que recibimos corresponde a un float
 * \char string[]: Es la cadena de caracteres que vamos a validar
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
static int isValidFloat(char string[])
{
	int retornar = 1;
	int i = 0;
	int commaCounter=0;

	if(string!=NULL && strlen(string)>0)
	{
		if(string[0]=='-')
		{
			i=1;
		}
		for(;i<strlen(string);i++)
		{
			if(string[i]=='.')
			{
				commaCounter++;
			}
			if(commaCounter>1 || ((string[i]>'9' || string[i]<'0') && string[i]!='.'))
			{
				retornar=0;
				break;
			}
		}
	}
	return retornar;
}

/**
 * \brief Funcion para validar si la cadena de caracteres que recibimos corresponde a un entero
 * \char string[]: Es la cadena de caracteres que vamos a validar
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
static int isValidInt(char string[])
{
	int retornar = 1;
	int i = 0;

	if(string!=NULL && strlen(string)>0)
	{
		if(string[0]=='-')
		{
			i=1;
		}
		for(;i<strlen(string);i++)
		{
			if(string[i]>'9' || string[i]<'0')
			{
				retornar=0;
				break;
			}
		}
	}
	return retornar;
}

/** \brief Funcion criterio que compara nombres entre dos empleados
 *  \param void* employee1: Puntero void que castearemos al primer empleado
 *  \param void* employee2: Puntero void que castearemos al segundo empleado
 *  \return (1) Si el primer empleado tiene un nombre "mayor" al segundo, (-1) Si el segundo empleado tiene un nombre "mayor" al primero o (0) si son iguales
 */
int employee_compareByName(void* employee1, void* employee2)
{
	int retornar;
	Employee* bufferFirstEmp = (Employee*) employee1;
	Employee* bufferSecondEmp = (Employee*) employee2;
	char bufferName1[BUFFER_SIZE];
	char bufferName2[BUFFER_SIZE];
	employee_getNombre(bufferFirstEmp, bufferName1);
	employee_getNombre(bufferSecondEmp, bufferName2);
	if(employee1!=NULL && employee2!=NULL)
	{
		if(strncmp(bufferName1,bufferName2,NAME_SIZE)>0)
		{
			retornar=1;
		}
		else
		{
			if(strncmp(bufferName1,bufferName2,NAME_SIZE)<0)
			{
				retornar=-1;
			}
			else
			{
				retornar=0;
			}
		}
	}
	return retornar;
}

/** \brief Funcion criterio que compara ids entre dos empleados
 *  \param void* employee1: Puntero void que castearemos al primer empleado
 *  \param void* employee2: Puntero void que castearemos al segundo empleado
 *  \return (1) Si el primer empleado tiene un id mayor al segundo, (-1) Si el segundo empleado tiene un id mayor al primero o (0) si son iguales
 */
int employee_compareById(void* employee1, void* employee2)
{
	int retornar;
	Employee* bufferFirstEmp = employee1;
	Employee* bufferSecondEmp = employee2;
	int bufferId1;
	int bufferId2;
	if(employee1!=NULL && employee2!=NULL)
	{
		employee_getId(bufferFirstEmp, &bufferId1);
		employee_getId(bufferSecondEmp, &bufferId2);
		if(bufferId1>bufferId2)
		{
			retornar=1;
		}
		else
		{
			if(bufferId1<bufferId2)
			{
				retornar=-1;
			}
			else
			{
				retornar=0;
			}
		}
	}
	return retornar;
}
