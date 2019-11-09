#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	FILE* pFile;
	int retorno = -1;
	if(pArrayListEmployee != NULL)
	{
		pFile = fopen(path,"r");
		if(pFile != NULL)
		{
			retorno = parser_EmployeeFromText(pFile,pArrayListEmployee);
			fclose(pFile);
		}
	}
	return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	FILE* pFile;
	int retorno = -1;

	if(pArrayListEmployee != NULL)
	{
		pFile = fopen(path,"rb");
		if(pFile != NULL)
		{
			retorno = parser_EmployeeFromBinary(pFile,pArrayListEmployee);
			fclose(pFile);
			retorno = 0;
		}
	}
	return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	Employee* pEmployee;

	int ret = -1;
	int auxId;
	int len;
	char auxNombre[128];
	char auxHorasTrabajoStr[128];
	char auxSueldoStr[128];


	if(pArrayListEmployee != NULL)
	{
		pEmployee = employee_new();

		len = ll_len(pArrayListEmployee);
		auxId = len++;

		utn_getTexto("Ingrese nombre : ","Error",0,127,3,auxNombre);
		utn_getTexto("\nIngrese sueldo : ","\nError",1,50,3,auxSueldoStr);
		utn_getTexto("\nIngrese horas : ","\nError",1,50,3,auxHorasTrabajoStr);

		if(pEmployee != NULL && !employee_setId(pEmployee,auxId) &&
				!employee_setNombre(pEmployee,auxNombre) &&
				!employee_setSueldoStr(pEmployee,auxSueldoStr) &&
				!employee_setHorasTrabajadasStr(pEmployee,auxHorasTrabajoStr))
		{
			if(!ll_add(pArrayListEmployee,pEmployee))
			{
				printf("\nEmpleado cargado");
				ret = 0;
			}
			else
			{
				printf("Error al agregar empleado");
			}
		}
	}

	return ret;

}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{

	int ret = -1;
	Employee* employee;

	int auxId;
	char auxNombre[128];
	char auxHorasTrabajo[128];
	char auxSueldo[128];
	char opcion;
	int posicion;

	if(pArrayListEmployee != NULL)
	{
		utn_getUnsignedInt("\nID de empleado a modificar: ","\nError",1,sizeof(int),1,20,3,&auxId);
		posicion = employee_findEmployeeById(pArrayListEmployee, auxId);
		if(posicion == -1)
		{
			printf("\nNo existe este ID");
		}
		else
		{
			do
			{
				employee = ll_get(pArrayListEmployee, posicion);

				utn_getChar("\nQue desea modificar?: \nA: Nombre \nB: Horas trabajadas \nC: Sueldo \nS: salir\nElija una opcion(A/B/C/D/S):","\nError",'A','Z',1,&opcion);

				switch(opcion)
				{
				case 'A':
					utn_getTexto("\nIngrese nuevo nombre de empleado: ","\nError",1,128,3, auxNombre);                      //mensaje + cambiar campo nombre
					employee_setNombre(employee, auxNombre);
					break;
				case 'B':
					utn_getTexto("\nIngrese nueva cantidad de horas trabajadas: ","\nError",1,128,3,auxHorasTrabajo);
					employee_setHorasTrabajadasStr(employee, auxHorasTrabajo);
					break;
				case 'C':
					utn_getTexto("\nIngrese nuevo salario de empleado: ","\nError",1,128,3,auxSueldo);           //mensaje + cambiar campo varInt
					employee_setSueldoStr(employee, auxSueldo);
					break;
				case 'S':
					break;
				default:
					printf("\nOpcion no valida");
				}
			}while(opcion!='S');

			ret = 0;
		}
	}

	return ret;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int auxId;
	int ret = -1;
	int posicion;

	if(pArrayListEmployee != NULL)
	{
		utn_getUnsignedInt("\nID de empleado a remover: ","\nError",1,sizeof(int),1,20,3,&auxId);

		posicion = employee_findEmployeeById(pArrayListEmployee, auxId);
		if(posicion == -1)
		{
			printf("\nNo existe este ID");
		}
		else
		{
			ll_remove(pArrayListEmployee, posicion);
			ret = 0;
		}
	}

	return ret;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i;
	Employee* employee;

	int auxId;
	char auxNombre[128];
	int auxHorasTrabajo;
	int auxSueldo;
	int len;

	if(pArrayListEmployee != NULL)
	{
		len = ll_len(pArrayListEmployee);

		for(i = 0; i <= len; i++)
		{
			employee = ll_get(pArrayListEmployee, i);
			employee_getId(employee, &auxId);
			employee_getNombre(employee, auxNombre);
			employee_getHorasTrabajadas(employee, &auxHorasTrabajo);
			employee_getSueldo(employee, &auxSueldo);

			if(employee != NULL)
			{
				printf("%d,%s,%d,%d\n",auxId,auxNombre,auxHorasTrabajo,auxSueldo);
				retorno = 0;
		}
	        }
	    }

	    return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int ret = -1;
	if(pArrayListEmployee != NULL)
	{
				ll_sort(pArrayListEmployee,employee_comparaPorNombre,1);
		ret = 0;
	}

	return ret;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	 int ret = -1;
	 int i;
	 int len;
	 int auxId;
	 char auxNombre[128];
	 int auxHorasTrabajo;
	 int auxSueldo;

	 Employee* pEmpl;
	 FILE* fp = fopen(path, "w+");
	 if(fp != NULL)
	 {
		 fprintf(fp, "id,nombre,horasTrabajadas,sueldo\n");

		 len = ll_len(pArrayListEmployee);

		 for(i = 0;i < len;i++)
		 {
			 pEmpl = ll_get(pArrayListEmployee, i);
			 employee_getId(pEmpl, &auxId);
			 employee_getNombre(pEmpl, auxNombre);
			 employee_getHorasTrabajadas(pEmpl, &auxHorasTrabajo);
			 employee_getSueldo(pEmpl, &auxSueldo);
			 fprintf(fp, "%d,%s,%d,%d\n", auxId, auxNombre, auxHorasTrabajo, auxSueldo);

			 ret++;
		 }

		 fclose(fp);
	 }
	 return ret;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int ret = -1;
	int i;
	Employee* pEmpl;
	int len;
	FILE* fp = fopen(path, "w+b");
	if(fp != NULL)
	{
		len = ll_len(pArrayListEmployee);
		for(i = 0;i < len;i++)
		{
			pEmpl = ll_get(pArrayListEmployee, i);
			fwrite(pEmpl,sizeof(Employee), 1, fp);
			ret++;
		}
		fclose(fp);
	}
	return ret;
}
