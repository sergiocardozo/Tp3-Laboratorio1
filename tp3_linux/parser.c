#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int ret= 0;
	char bufferId[4096];
	char bufferNombre[4096];
	char bufferHorasTrabajadas[4096];
	char bufferSueldo[4096];
	Employee *pEmpleado;

	if(pFile!=NULL && pArrayListEmployee!=NULL)
	{
		fscanf(pFile,"[^\n]\n");
		while(!feof(pFile))
		{
			fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",  bufferId,
					bufferNombre,
					bufferHorasTrabajadas,
					bufferSueldo);

			pEmpleado = employee_newParametros(bufferId,bufferNombre,bufferHorasTrabajadas,bufferSueldo);

			if(pEmpleado != NULL)
			{
				if(!ll_add(pArrayListEmployee,pEmpleado))
				{
					ret++;
				}
			}
		}
	}
	return ret;
}



/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int ret = 0;
    Employee* pEmployee;

    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        do{
            //generar espacio en memoria
            pEmployee = employee_new();
            // guardarlo en el archivo
            if(fread(pEmployee, sizeof(Employee), 1, pFile))
            {
                // agregarlo a la linkedlist
                if(!ll_add(pArrayListEmployee, pEmployee))
                {
                	ret++;
                }
            }
            else
            {
                employee_delete(pEmployee);
            }
        }while(!feof(pFile));
    }
    return ret;
}
