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
		crudOrdsShowAllIds(orders, length);
		printf("\nATENCION=>De todos los pedidos listados arriba elija el ID (del pedido Orden.Id) que desea procesar\n");
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
	int idx;
	int ordIdx;

	//ID:1 - ID_C:1 - k_tot: 1000 - k_p1:200 - k_p2:145 - k_p3: 230 - estado:Completado
	idx = _getFirstEmptyOrderIndex(orders, length);
	status = crudOrdsCreateMe(orders, idx, 1, 1000, length); //se crea orden id 1 para cliente id 1
	crudOrdsGetIndexById(orders, 1, length, &ordIdx);
	crudOrdsUpdateMePlasticsKgs(orders, ordIdx,200,145,230, length); //se procesa

	//ID:2 - ID_C:1 - k_tot: 800 - k_p1:210 - k_p2:45 - k_p3: 30 - estado:Completado
	idx = _getFirstEmptyOrderIndex(orders, length);
	status = crudOrdsCreateMe(orders, idx, 1, 800, length); //se crea orden id 2 para cliente id 1
	crudOrdsGetIndexById(orders, 2, length, &ordIdx);
	crudOrdsUpdateMePlasticsKgs(orders, ordIdx,210,45,30, length);

	//ID:3 - ID_C:2 - k_tot: 100 - estado:Pendiente
	idx = _getFirstEmptyOrderIndex(orders, length);
	status = crudOrdsCreateMe(orders, idx, 2, 100, length); //se crea orden id 3 para cliente id 2
	//ID:4 - ID_C:2 - k_tot: 300 - estado:Pendiente
	idx = _getFirstEmptyOrderIndex(orders, length);
	status = crudOrdsCreateMe(orders, idx, 2, 300, length); //se crea orden id 4 para cliente id 2

	//ID:5 - ID_C:3 - k_tot: 1500  - k_p1:500 - k_p2:150 - k_p3: 270 - estado:Completado
	idx = _getFirstEmptyOrderIndex(orders, length);
	status = crudOrdsCreateMe(orders, idx, 3, 1500, length); //se crea orden id 5 para cliente id 3
	crudOrdsGetIndexById(orders, 5, length, &ordIdx);
	crudOrdsUpdateMePlasticsKgs(orders, ordIdx,500,150,270, length);

	//ID:6 - ID_C:4 - k_tot: 750  - k_p1:100 - k_p2:50 - k_p3: 70 - estado:Completado
	idx = _getFirstEmptyOrderIndex(orders, length);
	status = crudOrdsCreateMe(orders, idx, 4, 750, length); //se crea orden id 6 para cliente id 4
	crudOrdsGetIndexById(orders, 6, length, &ordIdx);
	crudOrdsUpdateMePlasticsKgs(orders, ordIdx,100,50,70, length);

	//ID:7 - ID_C:1 - k_tot: 200 - estado:Pendiente
	idx = _getFirstEmptyOrderIndex(orders, length);
	status = crudOrdsCreateMe(orders, idx, 1, 200, length); //se crea orden id 7 para cliente id 1

	//ID:8 - ID_C:5 - k_tot: 30 - k_p1:10 - k_p2:5 - k_p3: 3 - estado:Completado
	idx = _getFirstEmptyOrderIndex(orders, length);
	status = crudOrdsCreateMe(orders, idx, 5, 30, length); //se crea orden id 8 para cliente id 5
	crudOrdsGetIndexById(orders, 8, length, &ordIdx);
	crudOrdsUpdateMePlasticsKgs(orders, ordIdx,10,5,3, length);

	//ID:9 - ID_C:6 - k_tot: 456 - estado:Pendiente
	idx = _getFirstEmptyOrderIndex(orders, length);
	status = crudOrdsCreateMe(orders, idx, 6, 456, length); //se crea orden id 9 para cliente id 6

	return status;
}

//===========Private functions============================
int _createTheOrder(Order orders[], int length, int cstmId) {
	int status = ERROR;
	float kgTotAux;
	int i = _getFirstEmptyOrderIndex(orders, length);
	if(i >= 0){
		do{
			printf("\n Ingrese los Kg Totales del pedido : \n");
			__fpurge(stdin);
			scanf("%f", &kgTotAux);
		}while(kgTotAux<=0.0);
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




