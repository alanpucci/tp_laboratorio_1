#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#define BUFFER_SIZE 4096

static int isValidInt(char string[]);
static int isValidString(char* string);
static int isValidFloat(char string[]);

Employee* employee_new()
{
	return (Employee*)malloc(sizeof(Employee));
}

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

void employee_delete(Employee* this)
{
	free(this);
}

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
			printf("\nID: %d - Nombre: %s - Horas trabajadas: %d - Sueldo: %.2f", bufferId, bufferName, bufferHours, bufferSalary);
			retornar = 0;
		}
	}
	return retornar;
}

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

int employee_sortByName(void* employee1, void* employee2)
{
	Employee* bufferFirstEmp = employee1;
	Employee* bufferSecondEmp = employee2;
	char bufferName1[BUFFER_SIZE];
	char bufferName2[BUFFER_SIZE];
	employee_getNombre(bufferFirstEmp, bufferName1);
	employee_getNombre(bufferSecondEmp, bufferName2);
	if(strncmp(bufferName1,bufferName2,NAME_SIZE)>0)
	{
		return 1;
	}
	else
	{
		if(strncmp(bufferName1,bufferName2,NAME_SIZE)<0)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
}

int employee_sortById(void* employee1, void* employee2)
{
	Employee* bufferFirstEmp = employee1;
	Employee* bufferSecondEmp = employee2;
	int bufferId1;
	int bufferId2;
	employee_getId(bufferFirstEmp, &bufferId1);
	employee_getId(bufferSecondEmp, &bufferId2);
	if(bufferId1>bufferId2)
	{
		return 1;
	}
	else
	{
		if(bufferId1<bufferId2)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
}
