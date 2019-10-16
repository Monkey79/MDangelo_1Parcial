/*
 * PrintHelper.c
 *
 *  Created on: 14 oct. 2019
 *      Author: monkey
 */

#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>

#include "../crud-libs/CrudOrders.h"
#include "../crud-libs/CrudCustomers.h"

#define ORD_STATUS_1 "Pendiente"
#define ORD_STATUS_2 "Completado"
#define TRUE  1
#define FALSE 0

void _showCustomerOrdersCantByStatus(Customer customers[], Order orders[],int cstLength, int ordLength, char *statusN);
void _showCustomerOrdersPendingStatus(Customer customers[], Order orders[],int cstLength, int ordLength);
void _showCustomerOrdersCompletedStatus(Customer customers[], Order orders[],int cstLength, int ordLength);

void checkAndShowCustomersOrdCantByOrderStatus(Customer customers[], Order orders[], char *status, int cstLength, int ordLength){
	if(crudCstmCanUpdateDelete(customers, cstLength) == TRUE){
		if(strcmp(status, ORD_STATUS_1)==0)
			_showCustomerOrdersCantByStatus(customers, orders, cstLength, ordLength, ORD_STATUS_1);
		else if(strcmp(status, ORD_STATUS_2)==0){
			_showCustomerOrdersCantByStatus(customers, orders, cstLength, ordLength, ORD_STATUS_2);
		}
	}else
		printf("\nERROR=>NO hay Clientes cargados\n");


}
void showOrdersCustomersByStatus(Customer customers[], Order orders[],char *status, int cstLength, int ordLength){
	if(crudCstmCanUpdateDelete(customers, cstLength) == TRUE && crudOrdsCanUpdateDelete(orders, ordLength) == TRUE){
		if(strcmp(status, ORD_STATUS_1)==0)
			_showCustomerOrdersPendingStatus(customers, orders, cstLength, ordLength);
		else if(strcmp(status, ORD_STATUS_2)==0){
			_showCustomerOrdersCompletedStatus(customers, orders, cstLength, ordLength);
		}
	}else
		printf("\nERROR=>NO hay Clientes ni Pedidos cargados\n");

}

//============Private functions===============
void _showCustomerOrdersCantByStatus(Customer customers[], Order orders[],int cstLength, int ordLength, char *statusN){
	int ordersCant=0;
	for(int i=0; i<cstLength; i++){
		if(customers[i].isEmpty == FALSE){
			for(int e=0; e<ordLength; e++){
				if( (customers[i].id == orders[e].customerId) && (strcmp(orders[e].status, statusN)==0))
						ordersCant++;
			}
			printf("\n==Cliente.ID: %d===", customers[i].id);
			printf("\n==Cliente.Empresa: %s===", customers[i].companyName);
			printf("\n==Cliente.Direccion: %s===", customers[i].adress);
			printf("\n==Cliente.Localidad: %s===", customers[i].location);
			printf("\n==Cliente.Cuit: %s===", customers[i].cuit);
			printf("\n==Cliente.Ordenes en estado %s:%d===", statusN, ordersCant);
			printf("\n===============================\n");
			ordersCant = 0;
		}//end if
	}
}

void _showCustomerOrdersPendingStatus(Customer customers[], Order orders[],int cstLength, int ordLength){
	printf("\n==Cliente.Ordenes en estado Pendiente==\n");
	for(int i=0; i<cstLength; i++){
		if(customers[i].isEmpty == FALSE){
			printf("\n==Cliente.ID: %d===", customers[i].id);
				printf("\n==Cliente.Empresa: %s===", customers[i].companyName);
				printf("\n==Cliente.Direccion: %s===", customers[i].adress);
				printf("\n==Cliente.Localidad: %s===", customers[i].location);
				printf("\n==Cliente.Cuit: %s===", customers[i].cuit);
				for(int e=0; e<ordLength; e++){
					if( (customers[i].id == orders[e].customerId) && (strcmp(orders[e].status, ORD_STATUS_1)==0)){
						printf("\n\t==Orden.ID: %d===", orders[e].id);
						printf("\n\t==Orden.Customer_ID: %d===", orders[e].customerId);
						printf("\n\t==Orden.Customer_ID: %d===", orders[e].customerId);
						printf("\n\t==Orden.Kg_Totales: %f===", orders[e].kgTot);
						printf("\n\t==Orden.Estado: %s===", orders[e].status);
					}
				}
				printf("\n=====================================\n");
		}
	}
}
void _showCustomerOrdersCompletedStatus(Customer customers[], Order orders[],int cstLength, int ordLength){
	printf("\n==Cliente.Ordenes en estado Completado==\n");
	for(int i=0; i<cstLength; i++){
		if(customers[i].isEmpty == FALSE){
			printf("\n==Cliente.ID: %d===", customers[i].id);
			printf("\n==Cliente.Empresa: %s===", customers[i].companyName);
			printf("\n==Cliente.Direccion: %s===", customers[i].adress);
			printf("\n==Cliente.Localidad: %s===", customers[i].location);
			printf("\n==Cliente.Cuit: %s===", customers[i].cuit);
			for(int e=0; e<ordLength; e++){
				if( (customers[i].id == orders[e].customerId) && (strcmp(orders[e].status, ORD_STATUS_2)==0)){
					printf("\n\t==Orden.ID: %d===", orders[e].id);
					printf("\n\t==Orden.Customer_ID: %d===", orders[e].customerId);
					printf("\n\t==Orden.Customer_ID: %d===", orders[e].customerId);
					printf("\n\t==Orden.Kg_Totales: %f===", orders[e].kgTot);
					printf("\n\t==Orden.Estado: %s===", orders[e].status);
					printf("\n\t==Orden.Kg_HDPE: %f===", orders[e].hdpe);
					printf("\n\t==Orden.Kg_LDPE: %f===", orders[e].ldpe);
					printf("\n\t==Orden.Kg_PP: %f===", orders[e].pp);
				}
			}
			printf("\n=====================================\n");
		}
	}
}
