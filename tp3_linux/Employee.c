#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"

static int idGen = 0;

int employee_generaId(void)
{
    return idGen++;
}

 void employee_setIdInicial(int value)
{
    idGen = value;
}

Employee* employee_new()
{
	return (Employee*)malloc(sizeof(Employee));

}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
	Employee* emp = employee_new();
	if(emp != NULL)
	{
		employee_setIdStr(emp, idStr);
		employee_setNombre(emp, nombreStr);
		employee_setHorasTrabajadasStr( emp, horasTrabajadasStr);
		employee_setSueldoStr( emp, sueldoStr);
	}
	return emp;
}

int employee_delete(Employee* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}
	return retorno;
}

int employee_setIdStr(Employee* this,char* id)
{
    int retorno = -1;
    int idAux;
    if(this != NULL)
    {
        if(isValidNumber(id))
        {
            idAux = atoi(id);
            this->id = idAux;
            retorno = 0;
        }
    }
    return retorno;
}

int employee_setId(Employee* this,int id)
{
    int ret=-1;
    if(this!=NULL && id>=0)
    {
        this->id=id;
        ret=0;
    }
    return ret;
}

int employee_getId(Employee* this,int* id)
{
	int ret = -1;

	if(this != NULL && id > 0)
	{
		*id = this->id;
		ret = 0;
	}
	return ret;
}

int employee_setNombre(Employee* this,char* nombre)
{
    int retorno = -1;
    if(this != NULL)
    {
        if(isValidName(nombre))
        {
            strncpy(this->nombre,nombre,sizeof(this->nombre));
            retorno = 0;
        }

    }
    return retorno;
}


int employee_getNombre(Employee* this,char* nombre)
{
    int retorno = -1;
    if(this != NULL)
    {
        strncpy(nombre,this->nombre,sizeof(this->nombre));
        retorno = 0;
    }
    return retorno;
}

int employee_setHorasTrabajadasStr(Employee* this,char* horasTrabajadas)
{
    int retorno = -1;
    int horasAux;
    if(this != NULL)
    {
        if(isValidNumber(horasTrabajadas))
        {
            horasAux = atoi(horasTrabajadas);
            this->horasTrabajadas = horasAux;
            retorno = 0;
        }
    }
    return retorno;
}

int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
	int ret = 0;

	if(this != NULL && horasTrabajadas > 0)
	{
		*horasTrabajadas = this->horasTrabajadas;
		ret = 1;
	}
	return ret;
}

int employee_setSueldoStr(Employee* this,char* sueldo)
{
    int retorno = -1;
    int sueldoAux;
    if(this != NULL)
    {
        if(isValidNumber(sueldo))
        {
            sueldoAux = atoi(sueldo);
            this->sueldo = sueldoAux;
            retorno = 0;
        }
    }
    return retorno;
}

int employee_getSueldo(Employee* this,int* sueldo)
{
	int ret = 0;

	if(this != NULL && sueldo > 0)
	{
		*sueldo = this->sueldo;
		ret = 1;
	}
	return ret;
}

int employee_findEmployeeById(LinkedList* pArrayListEmployee, int id)
{
    int ret = -1;
    int i;
    Employee* pEmployee;
    int auxId;
    int len;

    if (pArrayListEmployee != NULL && id >= 0)
    {
        len = ll_len(pArrayListEmployee);

        for (i = 0;i < len;i++)
        {
            pEmployee = ll_get(pArrayListEmployee,i);
            employee_getId(pEmployee,&auxId);

            if (id==auxId)
            {
                ret = i;
                break;
            }
        }
    }
    else
    {
        printf("\nLa lista esta vacia");
    }
    return ret;
}

int employee_comparaPorNombre(void *pPersonaA,void *pPersonaB)
{
    int retorno = 0;

    if(strcmp(((Employee*)pPersonaA)->nombre,((Employee*)pPersonaB)->nombre) > 0)
    {
    	retorno = 1;
    }
    if(strcmp(((Employee*)pPersonaA)->nombre,((Employee*)pPersonaB)->nombre) < 0)
    {
    	retorno = -1;
    }

    return retorno;
}


