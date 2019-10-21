/*
 * InfoMng.c
 *
 *  Created on: 17 oct. 2019
 *      Author: alumno
 */
#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>

#include "../crud-libs/CrudOrders.h"
#include "../crud-libs/CrudCustomers.h"
#include "./Utils.h"

#define ORD_STATUS_1 "Pendiente"
#define ORD_STATUS_2 "Completado"

#define SUCCESS 0
#define ERROR -1
#define TRUE  1
#define FALSE 0

int _getCantOrdersByCustmIdAndStatus(int customerId, Order orders[],int ordLength, char *statusN);
int _getCantOrdersByCustmId(int customerId, Order orders[],int ordLength);
int _getKgByCustmId(int customerId, Order orders[],int ordLength);
int _getKgRecicledByCustmId(int customerId, Order orders[],int ordLength);
int _getKgRecycled(int cstnId, Order order);

void printPendingOrdersByLocation(Customer customers[], Order orders[],int cstLength, int ordLength){
	int locCant=0;
	char locationOrigin[30];
	char locationDestiny[30];

	printf("\n Ingrese la localidad del cliente \n");
	__fpurge(stdin);
	fgets(locationOrigin, 30, stdin);
	utlsGetCleanString(locationOrigin,locationDestiny);

	for(int i=0;i<cstLength;i++){
		if((customers[i].isEmpty==FALSE)==TRUE && (strcmp(customers[i].location, locationDestiny)==0)){
			for(int e=0;e<ordLength;e++){
				if((customers[i].id==orders[e].customerId)==TRUE && (orders[e].isEmpty==FALSE)==TRUE && (strcmp(orders[e].status,"Pendiente")==0)){
					locCant++;
				}
			}

		}
	}
	printf("Para la localidad %s se encontraron %d Pedidos en estado Pendiente\n", locationDestiny, locCant);
}

void infoPrintCompletedOrds(Customer customers[], Order orders[],int cstLength, int ordLength){
	int result = 0;
	for(int i=0;i<cstLength;i++){
		if((customers[i].isEmpty==FALSE)==TRUE){
			for(int e=0;e<ordLength;e++){
				if(((customers[i].id == orders[e].customerId)==TRUE) && (strcmp(orders[e].status,"Completado")==0)){
					printf("Id de pedido = %d\n",orders[e].id);
					printf("CUIT del cliente = %s\n",customers[i].cuit);
					result = 100*((orders[e].hdpe+orders[e].ldpe+orders[e].pp)/(orders[e].kgTot));
					printf("porcentaje de plastico reciclado= %d%% \n",result);
					printf("\n********************************\n");
				}
			}
		}

	}
}


void customerWithLessThan100KgRecicled(Customer customers[], Order orders[],int cstLength, int ordLength){
	int less100Cant=0;
	float aux = 0.0;
	Order ordersByCustomer[ordLength];
	crudOrdsInitializeAll(ordersByCustomer, ordLength);

	for(int i =0; i<cstLength; i++){
		if(customers[i].isEmpty == FALSE) {
			utlsGetOrdersByCustomerId(customers[i],orders,ordLength,ordersByCustomer);
			for(int e=0; e<ordLength; e++){
				if((ordersByCustomer[e].isEmpty==FALSE)==TRUE){
					aux = _getKgRecycled(customers[i].id, ordersByCustomer[e]);
					if(aux<100 && aux>0){
						less100Cant++;
					}
				}
			}
		}
	}
	printf("\n Cantidad de Clientes que reciclaron menos de 100Kg=%d \n", less100Cant);
}

void customerWithMoreThan1000KgRecicled(Customer customers[], Order orders[],int cstLength, int ordLength){
	int more1000Cant=0;
	float aux = 0.0;
	Order ordersByCustomer[ordLength];
	crudOrdsInitializeAll(ordersByCustomer, ordLength);

	for(int i =0; i<cstLength; i++){
		if(customers[i].isEmpty == FALSE) {
			utlsGetOrdersByCustomerId(customers[i],orders,ordLength,ordersByCustomer);
			for(int e=0; e<ordLength; e++){
				if((ordersByCustomer[e].isEmpty==FALSE)==TRUE){
					aux = _getKgRecycled(customers[i].id, ordersByCustomer[e]);
					if(aux>1000){
						more1000Cant++;
					}
				}
			}
		}
	}
	printf("\n Cantidad de Clientes que reciclaron mas de 1000Kg=%d \n", more1000Cant);
}


void customerWithLessRecyblessKg(Customer customers[], Order orders[],int cstLength, int ordLength){
	float lessRecKg=0.0;
	float aux=0.0;
	int moreKgCstmId=-1;
	Order ordersByCustomer[ordLength];
	crudOrdsInitializeAll(ordersByCustomer, ordLength);

	for(int i=0; i<cstLength; i++){
		if(customers[i].isEmpty == FALSE) {
			utlsGetOrdersByCustomerId(customers[i],orders,ordLength,ordersByCustomer);
			for(int e=0; e<ordLength; e++){
				if((ordersByCustomer[e].isEmpty==FALSE)==TRUE) {
					aux = _getKgRecycled(customers[i].id, ordersByCustomer[e]);
					if(lessRecKg==0.0){
						lessRecKg = aux;
						moreKgCstmId = customers[i].id;
					}else if(aux<lessRecKg && aux>0){
						lessRecKg = aux;
						moreKgCstmId = customers[i].id;
					}
				}
			}
		}
	}
	if(lessRecKg>0){
		printf("\n Cliente id=%d con menos Kg de pedidos kg= %f", moreKgCstmId, lessRecKg);
	}else
		printf("\n No hay ningun pedido mierda ningun cliente para estado \n");
}
//D
void customerWithMoreRecycledKg(Customer customers[], Order orders[],int cstLength, int ordLength){
	float moreKgTot=0.0;
	int moreKgCstmId=-1;
	float aux = 0.0;
	Order ordersByCustomer[ordLength];
	crudOrdsInitializeAll(ordersByCustomer, ordLength);

	for(int i =0; i<cstLength; i++){
		if(customers[i].isEmpty == FALSE) {
			utlsGetOrdersByCustomerId(customers[i],orders,ordLength,ordersByCustomer);
			for(int e=0; e<ordLength; e++){
				if((ordersByCustomer[e].isEmpty==FALSE)==TRUE){
					aux = _getKgRecycled(customers[i].id, ordersByCustomer[e]);
					if(aux>moreKgTot){
						moreKgTot = aux;
						moreKgCstmId = customers[i].id;
					}
				}
			}
		}
	}
	if(moreKgTot>0.0){
		printf("\n Cliente id=%d con mas Kg de pedidos kg= %f", moreKgCstmId, moreKgTot);
	}else
		printf("\n No hay ningun pedido para ningun cliente para estado \n");
}

void customerWithMoreOrders(Customer customers[], Order orders[],int cstLength, int ordLength){
	int moreOrdsCant =-1;
	int moreCstmOrdsCantId=-1;
	char companyName[50];
	int aux = 0;

	for(int i =0; i<cstLength; i++){
		if(customers[i].isEmpty == FALSE){
			aux = _getCantOrdersByCustmId(customers[i].id, orders, ordLength);
			if(aux>moreOrdsCant){
				moreOrdsCant = aux;
				moreCstmOrdsCantId = customers[i].id;
				strcpy(companyName, customers[i].companyName);
			}
		}
	}
	if(moreOrdsCant>0){
		printf("\n Cliente %s con id=%d con mas cant de pedidos = %d",companyName, moreCstmOrdsCantId, moreOrdsCant);
	}else
		printf("\n No hay ningun pedido para ningun cliente para estado \n");
}

void customerWithMoreOrderStatus(Customer customers[], Order orders[],int cstLength, int ordLength, char *statusN){
	int moreOrdsCant =-1;
	int moreCstmOrdsCantId=-1;
	char companyName[50];
	int aux = 0;

	for(int i =0; i<cstLength; i++){
		if(customers[i].isEmpty == FALSE){
			aux = _getCantOrdersByCustmIdAndStatus(customers[i].id, orders, ordLength, statusN);
			if(aux>moreOrdsCant){
				moreOrdsCant = aux;
				moreCstmOrdsCantId = customers[i].id;
				strcpy(companyName,customers[i].companyName);
			}
		}
	}
	if(moreOrdsCant>0){
		printf("\n Cliente %s con id=%d tiene mas cant de pedidos en estado %s = %d",companyName, moreCstmOrdsCantId, statusN, moreOrdsCant);
	}else
		printf("\n No hay ningun pedido para ningun cliente para estado %s\n", statusN);
}


//****************Private functions*******************
int _getCantOrdersByCustmIdAndStatus(int customerId, Order orders[],int ordLength, char *statusN){
	int ordersCant=0;

	for(int e=0; e<ordLength; e++){
		if((customerId == orders[e].customerId) && (strcmp(orders[e].status, statusN)==0) && (orders[e].isEmpty == FALSE))
			ordersCant++;
	}
	return ordersCant;
}

int _getCantOrdersByCustmId(int customerId, Order orders[],int ordLength){
	int ordersCant=0;

	for(int e=0; e<ordLength; e++){
		if((customerId == orders[e].customerId) && (orders[e].isEmpty == FALSE))
			ordersCant++;
	}
	return ordersCant;
}

int _getKgRecycled(int cstnId, Order order){
	float kgTot=0.0;
	float kgRec=0.0;
	float result = 0.0;

	if((order.customerId==cstnId)==TRUE &&  (strcmp(order.status, "Completado")==0) ){
		kgTot=order.kgTot;
		kgRec=order.hdpe+order.ldpe+order.pp;
		result = (float)kgTot-kgRec;
	}
	return (result);
}

int _getKgByCustmId(int customerId, Order orders[],int ordLength){
	float kgTot=0.0;
	float kgRec=0.0;

	for(int e=0; e<ordLength; e++){
		if((customerId == orders[e].customerId) && (strcmp(orders[e].status, "Completado")==0)){
			printf("\n orden id %d\n", orders[e].id);
			kgTot+=orders[e].kgTot;
			kgRec+=orders[e].hdpe+orders[e].ldpe+orders[e].pp;
		}
	}
	return (kgTot-kgRec);
}

int _getKgRecicledByCustmId(int customerId, Order orders[],int ordLength){
	int kgTot=0.0;

	for(int e=0; e<ordLength; e++){
		if((strcmp(orders[e].status,"Completado")==0) &&(customerId == orders[e].customerId))
			kgTot+=(orders[e].hdpe + orders[e].ldpe + orders[e].pp);
	}
	return kgTot;
}


