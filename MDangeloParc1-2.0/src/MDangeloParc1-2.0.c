/*
 ============================================================================
 Name        : 0.c
 Author      : Mariano DAngelo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "commons-libs/MenuBuilder.h"
#include "commons-libs/PrintHelper.h"

#include "crud-libs/CrudCustomers.h"
#include "crud-libs/CrudOrders.h"

#include "manager-libs/MngCustomers.h"
#include "manager-libs/MngOrders.h"

#define SUCCESS 0
#define ERROR  -1
#define TRUE    1
#define FALSE   0

#define CUST_TOP 100
#define ORDERS_TOP 100

#define  CREATE_CUSTOMER 1
#define  UPDATE_CUSTOMER 2
#define  DELETE_CUSTOMER 3
#define  CREATE_ORDER 4
#define  PROCESS_ORDER 5
#define  SHOW_CLIENTS 6
#define  SHOW_ORDERS_PENDING 7
#define  SHOW_ORDERS_COMPLETED 8
#define  EXIT 9

#define HARCODE_ON 1

int main(void) {
	int status;
	Customer customers[CUST_TOP];
	Order orders[ORDERS_TOP];

	status = crudCstmInitializeAll(customers, CUST_TOP);
	status = crudOrdsInitializeAll(orders, ORDERS_TOP);
	int userSelect = -1;

	if(HARCODE_ON == TRUE){
		createHarcordCustomer(customers, CUST_TOP);
		createHarcodeTheOrders(orders,  ORDERS_TOP);
	}
	if(status==SUCCESS){
		do{
			mngbBuildMenuAndGetUserSelection(&userSelect);
			switch (userSelect) {
				case CREATE_CUSTOMER:
					printf("\nCreando cliente\n");
					mngCustomerCreation(customers, CUST_TOP);
					break;
				case UPDATE_CUSTOMER:
					printf("\nModificando cliente\n");
					mngCustomerModification(customers, CUST_TOP);
					break;
				case DELETE_CUSTOMER:
					printf("\nBorrando cliente\n");
					mngCustomerDelete(customers, CUST_TOP, orders, ORDERS_TOP);
					break;
				case CREATE_ORDER:
					printf("\nCreando pedido\n");
					mngOrdersCreation(orders, customers, ORDERS_TOP, CUST_TOP);
					break;
				case PROCESS_ORDER:
					printf("\nProcesando pedido\n");
					mngProcessOrders(orders,ORDERS_TOP);
					break;
				case SHOW_CLIENTS:
					printf("\nImprimir clientes y cant ordenes por estado Pendiente\n");
					checkAndShowCustomersOrdCantByOrderStatus(customers, orders, "Pendiente", CUST_TOP, ORDERS_TOP);
					break;
				case SHOW_ORDERS_PENDING:
					printf("\nImprimir pedidos en estado Pendiente\n");
					showOrdersCustomersByStatus(customers, orders, "Pendiente", CUST_TOP, ORDERS_TOP);
					break;
				case SHOW_ORDERS_COMPLETED:
					printf("\nImprimir pedidos en estado Completado\n");
					showOrdersCustomersByStatus(customers, orders, "Completado", CUST_TOP, ORDERS_TOP);
					break;
				default:
					printf("\nOPCION NO VALIDA = SALIENDO DEL PROGRAMA\n");
					break;
			}
		}while(userSelect==CREATE_CUSTOMER || userSelect==UPDATE_CUSTOMER || userSelect==DELETE_CUSTOMER || userSelect==CREATE_ORDER || userSelect==PROCESS_ORDER || userSelect==SHOW_CLIENTS || userSelect==SHOW_ORDERS_PENDING || userSelect==SHOW_ORDERS_COMPLETED);
	}else {
		printf("\nERROR=>Application error...!!\n");
	}
	return status;
}
