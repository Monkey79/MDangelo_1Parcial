/**
 * @purpose: Take care all about create,read, delete, update Orders (Pedidos)
 * @autor: mdangelo
 */
#ifndef MY_LIBS_CRUDORRDERS_C_
#define MY_LIBS_CRUDORRDERS_C_

#include "../crud-libs/CrudOrders.h"

#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>

#define SUCCESS 0
#define ERROR -1
#define TRUE  1
#define FALSE 0

#define STATUS_1 "Pendiente"
#define STATUS_2 "Completado"

int MY_ORDER_ID = 0;


int crudOrdsInitializeAll(Order orders[], int length) {
	int status = ERROR;
	if(orders != NULL && length>0){
		status = SUCCESS;
		for (int i = 0; i < length; i++) {
			orders[i].id = 0;
			orders[i].customerId = 0;
			orders[i].isEmpty = TRUE;
		}
	}
	return status;
}

int crudOrdsCreateMe(Order orders[], int i, int cstmId,float kgTot, int length){
	int status = ERROR;
	if(orders!= NULL && length>0){
		status = SUCCESS;
		orders[i].id = ++MY_ORDER_ID;
		orders[i].customerId = cstmId;
		orders[i].kgTot = kgTot;
	    strcpy(orders[i].status, STATUS_1);
	    orders[i].isEmpty = FALSE;
	    printf("\n Order with ID %d created OK!!\n",orders[i].id);
	}
	return status;
}
int crudOrdsUpdateMe(Order orders[], int i,float kgTot, int length){
	int status = ERROR;
	if(orders!= NULL && length>0){
		status = SUCCESS;
		orders[i].kgTot = kgTot;
	    printf("\n Order with ID %d updated OK!!\n",orders[i].id);
	}
	return status;
}
int crudOrdsUpdateMePlasticsKgs(Order orders[], int i,float hdpe,float ldpe,float pp, int length){
	int status = ERROR;
	if(orders!= NULL && length>0){
		status = SUCCESS;
		orders[i].hdpe = hdpe;
		orders[i].ldpe = ldpe;
		orders[i].pp = pp;
		orders[i].isEmpty = FALSE;
	    strcpy(orders[i].status, STATUS_2);
	    printf("\n Order with ID %d updated OK!!\n",orders[i].id);
	}
	return status;
}
int crudOrdsDeleteMe(Order orders[],int length, int cstmId) {
	int status = ERROR;
	if(orders!= NULL && length>0){
		status = SUCCESS;
		for(int e=0; e<length; e++){
			if(orders[e].customerId == cstmId){
				orders[e].isEmpty = TRUE;
			}
		}
	}
	return status;
}
//devuelve, de existir, la posicion de una Orden segun su ID si no la encuentra devuelve -1
int crudOrdsGetIndexById(Order orders[], int id, int length, int *index) {
	int status = ERROR;
	int found = FALSE;
	int i = 0;
	if(orders!= NULL && length>0){
		status = SUCCESS;
		while((i < length) && found==FALSE){
			found = (orders[i].id == id);
			i++;
		}
		if(found == FALSE){
			i = ERROR;
			printf("\n No se encontro la orden con el id %d\n", id);
		}else
			i = i-1;

		*index = i;
	}
	return status;
}

int crudOrdsShowAll(Order orders[], int length) {
	int status = ERROR;
	if(orders!= NULL && length>0){
		status = SUCCESS;
		for (int i = 0; i < length; i++) {
			if(orders[i].isEmpty == FALSE){
				printf("\n***Orden.Id: %d",orders[i].id);
				printf("\n***Oorder.CustomerId: %d",orders[i].customerId);
				printf("\n***Oorder.kgTotal: %f",orders[i].kgTot);
				printf("\n***CLiente.HDPE: %f",orders[i].hdpe);
				printf("\n***CLiente.LDPE: %f", orders[i].ldpe);
				printf("\n***CLiente.PP: %f", orders[i].pp);
			}
		}
	}
	return status;
}
int crudOrdsShowAllIds(Order orders[], int length){
	int status = ERROR;
	if(orders!= NULL && length>0){
		status = SUCCESS;
		for (int i = 0; i < length; i++) {
			if(orders[i].isEmpty == FALSE){
				printf("\n***Pedido.Id: %d",orders[i].id);
			}
		}
	}
	return status;
}

//chequea si al menos hay una ORDEN cargado para poder o bien hacer una actualizacion o borrado
int crudOrdsCanUpdateDelete(Order orders[], int length){
	int isEmpty = TRUE;
	int i = 0;
	int can;
	while((i < length) && isEmpty==TRUE){
		isEmpty = (orders[i].isEmpty == TRUE);
		i++;
	}
	can =(isEmpty==TRUE)? FALSE:TRUE;
	return can;
}
#endif /* MY_LIBS_CRUDORRDERS_C_ */
