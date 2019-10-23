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
int  _getClientsAmountInStatusCompleted(Order orders[],int ordLength);
float _getKgTotalPPType(Order orders[],int ordLength);
void _calcKgPlasticTypeByCustomerId(int plsType, int indexCstm, Order orders[], int ordLength);
void _showPerct(Order order,float kgRecy, float kgTot, int ordId, char custCUit[]);

float _getKgTotalPPType(Order orders[],int ordLength) {
	float ppTot=0.0;
	for(int i=0;i<ordLength; i++){
		if((orders[i].isEmpty==FALSE)==TRUE && strcmp(orders[i].status, "Completado")==0){
			ppTot += orders[i].pp;
		}
	}
	return ppTot;
}

void ppAverageByClient(Customer customers[], Order orders[],int cstLength, int ordLength){
	int clientsCont = _getClientsAmountInStatusCompleted(orders,ordLength);
	float ppTotal = _getKgTotalPPType(orders,ordLength);
	printf("==>Cantiad de kilos de Polipropileno promedio por cliente: %f",(float)(ppTotal / clientsCont));
}
void printKgTOtByCuitAndPlasticType(Customer customers[], Order orders[],int cstLength, int ordLength){
	int plsType = utilsGetPlasticType();
	int indexCstm = utilGetCustomerIdByCuit(customers, cstLength);
	_calcKgPlasticTypeByCustomerId(plsType, indexCstm, orders, ordLength);
}

//***************Private functions***********************************
void _calcKgPlasticTypeByCustomerId(int plsType, int indexCstm, Order orders[], int ordLength){
	float kgTot=0.0;
	for(int i=0;i<ordLength;i++){
		if((indexCstm==orders[i].customerId)==TRUE){
			if((plsType==1)==TRUE)
				kgTot+=orders[i].hdpe;
			else if((plsType==2)==TRUE)
				kgTot+=orders[i].ldpe;
			else if((plsType==3)==TRUE)
				kgTot+=orders[i].pp;

		}
	}
	printf("\n Para cliente con Id %d y tipo de plastico %d [1=Hdpe 2=Ldpe 3=Pp] hay un total de %f\n", indexCstm,plsType, kgTot);
}

int _getClientsAmountInStatusCompleted(Order orders[],int ordLength) {
	int lastCsmId=-1;
	int clAmount=0;
	for(int i=0;i<ordLength; i++){
		if((orders[i].isEmpty==FALSE)==TRUE && strcmp(orders[i].status, "Completado")==0){
			if(lastCsmId != orders[i].customerId){
				lastCsmId = orders[i].customerId;
				clAmount++;
			}
		}
	}
	return clAmount;
}

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
	int j=0;
	int cont=TRUE;
	float result = 0.0;
	int kgTot=0;
	int kgRecy=0;

	for(int i=0;i<cstLength;i++){
		if((customers[i].isEmpty==FALSE)==TRUE){
			for(int e=0;e<ordLength;e++){

				if(( (customers[i].id == orders[e].customerId)==TRUE)
						&& (strcmp(orders[e].status,"Completado")==0) ){
					printf("\n-->id-->%d\n",orders[e].customerId);
					kgRecy += (int)orders[e].hdpe + orders[e].ldpe + orders[e].pp;
					kgTot +=(int)(orders[e].kgTot);
				}
				printf("-->que envio %d \n",kgRecy);
				printf("-->que envio %d \n",kgTot);
				//_showPerct(orders[e],kgRecy, kgTot, orders[e].id, customers[i].cuit);
				kgRecy = 0;
				kgTot = 0;
			}
			/*do {
				cont= (customers[i].id == orders[j].customerId) && ((strcmp(orders[j].status,"Completado")==0));
				if(cont==TRUE){
					kgTot+=(orders[j].kgTot);
					kgRecy+=orders[j].hdpe+orders[j].ldpe+orders[j].pp;
				}
				j++;
			} while (j<ordLength && cont==TRUE);
			if(cont==FALSE) {
				result = 100*(kgRecy/kgTot);
				printf("Id de Pedido = %d\n",orders[--j].id);
				printf("CUIT del cliente = %s\n",customers[--j].cuit);
				printf("porcentaje de plastico reciclado= %d%% \n",result);
				printf("\n********************************\n");
			}
			j=0;*/

		}

	}
}

void _showPerct(Order order,float kgRecy, float kgTot, int ordId, char custCUit[]){
	if(order.isEmpty == FALSE){
		printf("\n totales %f\n",kgTot);
		printf("\n recy %f\n",kgRecy);

		int result = (int)100*(kgRecy/kgTot);
		printf("Id de Pedido = %d\n",ordId);
		printf("CUIT del cliente = %s\n",custCUit);
		printf("porcentaje de plastico reciclado= %d%% \n",result);
		printf("\n********************************\n");
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


