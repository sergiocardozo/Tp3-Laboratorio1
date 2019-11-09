#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;

int employee_generaId(void);
void employee_setIdInicial(int value);

Employee* employee_new();
Employee* employee_newParametrosInt(int id,char* nombreStr,int horasTrabajadas,int sueldo);
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr);
int employee_delete(Employee* this);

int employee_setId(Employee* this,int id);
int employee_setIdStr(Employee* this,char* id);
int employee_getId(Employee* this,int* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_setHorasTrabajadasStr(Employee* this,char* horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_setSueldoStr(Employee* this,char* sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

int employee_findEmployeeById(LinkedList* pArrayListEmployee, int id);
int employee_comparaPorNombre(void *this,void *that);

int controller_PrintEmployee(LinkedList* pArrayListEmployee, int index);

#endif // employee_H_INCLUDED
