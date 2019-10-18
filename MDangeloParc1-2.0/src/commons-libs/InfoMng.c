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


void customerWithLessThan100KgRecicled(Customer customers[], Order orders[],int cstLength, int ordLength){
	int less100KgCant =0;
	float aux = 0.0;

	for(int i =0; i<cstLength; i++){
		if(customers[i].isEmpty == FALSE){
			aux = _getKgRecicledByCustmId(customers[i].id, orders, ordLength);
			if(aux<100){
				less100KgCant++;
			}
		}
	}
	if(less100KgCant>0){
		printf("\n Cantidad de clientes que reciclaron menos de 100kg %d", less100KgCant);
	}else
		printf("\n No hubo clientes que hayan reciclado menos de 100kg \n");
}

void customerWithMoreThan1000KgRecicled(Customer customers[], Order orders[],int cstLength, int ordLength){
	int more1000KgCant =0;
	float aux = 0.0;

	for(int i =0; i<cstLength; i++){
		if(customers[i].isEmpty == FALSE){
			aux = _getKgRecicledByCustmId(customers[i].id, orders, ordLength);
			if(aux>1000){
				more1000KgCant++;
			}
		}
	}
	if(more1000KgCant>0){
		printf("\n Cantidad de clientes que reciclaron mas de 1000kg %d", more1000KgCant);
	}else
		printf("\n No hubo clientes que hayan reciclado mas de 1000kg \n");
}


void customerWithMLessKg(Customer customers[], Order orders[],int cstLength, int ordLength){
	float lessKgTot = 0.0;
	int lessKgCstmId=-1;
	float aux;

	lessKgTot = _getKgByCustmId(customers[0].id, orders, ordLength);

	for(int i =1; i<cstLength; i++){
		if(customers[i].isEmpty == FALSE){
			aux = _getKgByCustmId(customers[i].id, orders, ordLength);
			printf("\n que pasa %f \n", aux);
			if(aux<=lessKgTot){
				lessKgTot = aux;
				lessKgCstmId = customers[i].id;
			}
		}
	}
	if(lessKgTot>0.0){
		printf("\n Cliente id=%d con menos Kg de pedidos kg= %f", lessKgCstmId, lessKgTot);
	}else
		printf("\n No hay ningun pedido para ningun cliente para estado \n");
}
//D
void customerWithMoreKg(Customer customers[], Order orders[],int cstLength, int ordLength){
	float moreKgTot =-1.0;
	int moreKgCstmId=-1;
	float aux = 0.0;

	for(int i =0; i<cstLength; i++){
		if(customers[i].isEmpty == FALSE){
			aux = _getKgByCustmId(customers[i].id, orders, ordLength);
			printf("\n que pasa cliente %d --kg-- %f \n",customers[i].id,aux);
			if(aux>moreKgTot){
				moreKgTot = aux;
				moreKgCstmId = customers[i].id;
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


