#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
#define NAME_SIZE 128
typedef struct
{
    int id;
    char nombre[NAME_SIZE];
    int horasTrabajadas;
    float sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldo);
Employee* employee_newParameters(int id,char* name,int hours, float salary);
void employee_delete();

int employee_setId(Employee* this,int id);
int employee_setIdTxt(Employee* this,char* id);
int employee_getId(Employee* this,int* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_setHorasTrabajadasTxt(Employee* this, char* horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this, int* horasTrabajadas);

int employee_setSueldo(Employee* this,float sueldo);
int employee_setSueldoTxt(Employee* this, char* sueldo);
int employee_getSueldo(Employee* this,float* sueldo);

int employee_print(Employee* this);
int employee_sortByName(void* employee1, void* employee2);
int employee_sortById(void* employee1, void* employee2);
#endif // employee_H_INCLUDED
