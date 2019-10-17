/*
 * MngOrders.c
 *
 *  Created on: 13 oct. 2019
 *      Author: monkey
 */
#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>

#include "../crud-libs/CrudOrders.h"
#include "MngOrders.h"

#define SUCCESS 0
#define ERROR -1
#define TRUE  1
#define FALSE 0
#define HARCODE_ON 1

int _createTheOrder(Order orders[], int length, int cstmId);
int _getFirstEmptyOrderIndex(Order orders[], int length);
int _processTheOrder(Order orders[], int ordIndx,int length);
int _showAllCustomers();

int mngOrdersCreation(Order orders[], Customer customers[], int length, int custLength) {
	int status = ERROR;
	char usrOpt = 's';
	int custId;
	int custIndex;
	do{
		printf("\n==>Desea crear un Pedido? (s|n)\n");
		__fpurge(stdin);
		scanf("%c", &usrOpt);
	}while(usrOpt!='s' && usrOpt!='n');
	if(usrOpt == 's') {
		//1-listo clientes existentes para pedir ID al usuario
		status = crudCstmShowAllIds(customers,custLength);
		printf("\nDe los clientes listados mas arriba, elija el id para asociar el nuevo pedido al cliente correspondiente;\n");
		__fpurge(stdin);
		scanf("%d",&custId);
		//2-Con ese Id veo si realmente existe en el vector (indice>=0)
		crudCstmGetIndexById(customers, custId, custLength, &custIndex);
		if(custIndex>=0){
			printf("\nOk=> se va a crear el Pedido y asociarlo con el Cliente.ID %d\n", custId);
			//3-FInalmente creo el pedido y lo asicio con el respectivo id de cliente
			status = _createTheOrder(orders, length, custId);
		}
	}
	return status;
}

int mngProcessOrders(Order orders[], int length){
	int status = ERROR;
	int ordId;
	int ordIdx;
	if(crudOrdsCanUpdateDelete(orders, length) == TRUE){
		crudOrdsShowAll(orders, length);
		printf("\n ATENCION=>De todos los pedidos listados arriba elija el ID de aquel que desea procesar\n");
		scanf("%d",&ordId);
		crudOrdsGetIndexById(orders, ordId, length, &ordIdx);
		if(ordIdx>=0){
			_processTheOrder(orders, ordIdx, length);
		}else
			printf("\nERROR=>NO existe Pedido con ese ID\n");
	}else{
		printf("\nERROR=>NO se puede procesar ningun pedido porque aun NO hay ninguno cargado\n");
	}
	return status;
}

int mngShowAllOrders(Order orders[], int length) {
	return crudOrdsShowAll(orders, length);
}
int createHarcodeTheOrders(Order orders[], int length) {
	int status = ERROR;
	float kgTotAux;
	int idx;
	for(int i=0;i<3;i++){
		idx = _getFirstEmptyOrderIndex(orders, length);
		kgTotAux = 2.56+i;
		status = crudOrdsCreateMe(orders, idx, (i+1), kgTotAux, length);
	}
	idx = _getFirstEmptyOrderIndex(orders, length);
	status = crudOrdsCreateMe(orders, idx, 3, 589.99, length);
	return status;
}

//===========Private functions============================
int _createTheOrder(Order orders[], int length, int cstmId) {
	int status = ERROR;
	float kgTotAux;
	int i = _getFirstEmptyOrderIndex(orders, length);
	if(i >= 0){
		printf("\n Ingrese los Kg Totales del pedido : \n");
		__fpurge(stdin);
		scanf("%f", &kgTotAux);
		status = crudOrdsCreateMe(orders, i, cstmId, kgTotAux, length);
	}else
		printf("\nError=>No hay mas espacio libre disponible\n");
	return status;
}

int _getFirstEmptyOrderIndex(Order orders[], int length) {
	int notEmpty = TRUE;
	int i = 0;
	do{
		notEmpty = (orders[i].isEmpty  == FALSE);
		i++;
	}while((i < length) && notEmpty==TRUE);
	i = (notEmpty == TRUE)?-1:(i-1);
	return i;
}

int _showAllCustomers(Customer customers[], int length){
 return crudCstmShowAll(customers, length);
}

int _processTheOrder(Order orders[], int ordIndx,int length) {
	int status = ERROR;
	float hdpeAux = 0.00;
	float ldpeAux = 0.00;
	float ppAux = 0.00;
	do{
		printf("\nIngrese cant kg para HDPE:\n");
		__fpurge(stdin);
		scanf("%f", &hdpeAux);
	}while(hdpeAux<=0.00);
	do{
		printf("\nIngrese cant kg para LDPE:\n");
		__fpurge(stdin);
		scanf("%f", &ldpeAux);
	}while(ldpeAux<=0.00);
	do{
		printf("\nIngrese cant kg para PP:\n");
		__fpurge(stdin);
		scanf("%f", &ppAux);
	}while(ppAux<=0.00);
	status = crudOrdsUpdateMePlasticsKgs(orders, ordIndx,hdpeAux,ldpeAux,ppAux, length);
	return status;
}




