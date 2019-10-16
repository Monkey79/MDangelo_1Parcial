/**
 * @purpose: Take care all about create,read, delete, update Customers (Clientes).
 * @autor: mdangelo
 */
#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>
#include "CrudCustomers.h"

#define SUCCESS 0
#define ERROR -1
#define TRUE  1
#define FALSE 0

int MY_CUSTOMER_ID = 0;

//Inicializa el array de clientes
int crudCstmInitializeAll(Customer customers[], int length){
	int status = ERROR;
	if(customers!= NULL && length>0){
		status = SUCCESS;
		for (int i = 0; i < length;i++) {
			customers[i].isEmpty = TRUE;
		}
	}
	return status;
}

int crudCstmCreateMe(Customer customers[], int i, char coName[],char cuit[], char address[], char location[], int length){
	int status = ERROR;
	if(customers!= NULL && length>0){
		status = SUCCESS;
	    strcpy(customers[i].companyName, coName);
	    strcpy(customers[i].cuit, cuit);
	    strcpy(customers[i].adress, address);
	    strcpy(customers[i].location, location);
	    customers[i].isEmpty = FALSE;
	    customers[i].id = ++MY_CUSTOMER_ID;
	    printf("\n Customer with ID %d created OK!!\n",customers[i].id);
	}
	return status;
}

int crudCstmUpdateMe(Customer customers[], int i, char address[], char location[], int length){
	int status = ERROR;
	if(customers!= NULL && length>0){
		status = SUCCESS;
	    strcpy(customers[i].adress, address);
	    strcpy(customers[i].location, location);
	    printf("\n Customer with ID %d updated OK!!\n",customers[i].id);
	}
	return status;
}

int crudCstmDeleteMe(Customer customers[], int i, int length){
	int status = ERROR;
	if(customers!= NULL && length>0){
		status = SUCCESS;
		customers[i].isEmpty = TRUE;
		printf("\n Customer with ID %d deleted OK!!\n",customers[i].id);
	}
	return status;
}
//devuelve, de existir, la posicion de un cliente segun su ID si no la encuentra devuelve -1
int crudCstmGetIndexById(Customer customers[], int id, int length, int *index){
	int status = ERROR;
	int found = FALSE;
	int i = 0;

	if(customers!= NULL && length>0){
		status = SUCCESS;
		while((i < length) && found==FALSE){
			found = (customers[i].id == id);
			i++;
		}
		if(found == FALSE){
			i = ERROR;
			printf("\n No se encontro cliente con el id %d\n", id);
		}else
			i = i-1;

		*index = i;
	}
	return status;
}

int crudCstmShowAll(Customer customers[], int length){
	int status = ERROR;
	if(customers!= NULL && length>0){
		status = SUCCESS;
		for (int i = 0; i < length; i++) {
			if(customers[i].isEmpty == FALSE){
				printf("\n***CLiente.Id: %d",customers[i].id);
				printf("\n***CLiente.NombreEmpresa: %s",customers[i].companyName);
				printf("\n***CLiente.Direccion: %s",customers[i].adress);
				printf("\n***CLiente.CUIT: %s", customers[i].cuit);
				printf("\n***CLiente.Localidad: %s", customers[i].location);
			}
		}
	}
	return status;
}

int crudCstmShowAllIds(Customer customers[], int length){
	int status = ERROR;
	if(customers!= NULL && length>0){
		status = SUCCESS;
		for (int i = 0; i < length; i++) {
			if(customers[i].isEmpty == FALSE){
				printf("\n***CLiente.Id: %d",customers[i].id);
			}
		}
	}
	return status;
}
//chequea si al menos hay un cliente cargado para poder o bien hacer una actualizacion o borrado
int crudCstmCanUpdateDelete(Customer customers[], int length){
	int isEmpty = TRUE;
	int i = 0;
	int can;
	while((i < length) && isEmpty==TRUE){
		isEmpty = (customers[i].isEmpty == TRUE);
		i++;
	}
	can =(isEmpty==TRUE)? FALSE:TRUE;
	return can;
}

