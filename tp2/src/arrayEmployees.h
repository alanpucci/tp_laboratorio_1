#ifndef ARRAYEMPLOYEES_H_
#define ARRAYEMPLOYEES_H_

#define TRUE 1
#define FALSE 0
#define NAME_SIZE 51
#define SALARY_MIN 0.00
#define SALARY_MAX 99999999.00
#define EMPLOYEES_LEN 999

typedef struct
{
	int id;
	char name[NAME_SIZE];
	char lastName[NAME_SIZE];
	float salary;
	int sector;
	int isEmpty;
}Employee;

int employee_initEmployees(Employee* list, int len);
int employee_addEmployee(Employee *pArrayEmployee, int len);
int employee_modifyEmployee(Employee *pArrayEmployees, int len);
int employee_removeEmployee(Employee *list, int len);
int employee_report(Employee *pArrayEmployees, int len);

#endif
