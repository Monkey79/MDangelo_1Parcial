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
#include "commons-libs/InfoMng.h"

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

#define  PRINT_MORE_PENDING 9
#define  PRINT_MORE_COMPLETED 10
#define  PRINT_MORE_CUSTOMERS 11
#define  PRINT_MORE_CUSTOMERS_KG 12
#define  PRINT_LESS_CUSTOMERS_KG 13
#define  PRINT_MORE_1000_KG 14
#define  PRINT_LESS_100_KG 15


#define  EXIT 29

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
				case PRINT_MORE_PENDING:
					printf("\nImprimir Cliente con mas pedidos Pendiente\n");
					customerWithMoreOrderStatus(customers, orders,CUST_TOP, ORDERS_TOP, "Pendiente");
					break;
				case PRINT_MORE_COMPLETED:
					printf("\nImprimir Cliente con mas pedidos Completado\n");
					customerWithMoreOrderStatus(customers, orders,CUST_TOP, ORDERS_TOP, "Completado");
					break;
				case PRINT_MORE_CUSTOMERS:
					printf("\nImprimir Cliente con mas pedidos\n");
					customerWithMoreOrders(customers, orders,CUST_TOP, ORDERS_TOP);
					break;
				case PRINT_MORE_CUSTOMERS_KG:
					printf("\nImprimir Cliente con mas KG por pedidos\n");
					customerWithMoreKg(customers, orders,CUST_TOP, ORDERS_TOP);
					break;
				case PRINT_LESS_CUSTOMERS_KG:
					printf("\nImprimir Cliente con menos KG por pedidos\n");
					customerWithMLessKg(customers, orders,CUST_TOP, ORDERS_TOP);
					break;
				case PRINT_MORE_1000_KG:
					printf("\nImprimir cant Cliente que reciclaron mas de 1000KG\n");
					customerWithMoreThan1000KgRecicled(customers, orders,CUST_TOP, ORDERS_TOP);
					break;
				case PRINT_LESS_100_KG:
					printf("\nImprimir cant Cliente que reciclaron menos de 100KG\n");
					customerWithLessThan100KgRecicled(customers, orders,CUST_TOP, ORDERS_TOP);
					break;
				default:
					printf("\nOPCION NO VALIDA = SALIENDO DEL PROGRAMA\n");
					break;
			}
		}while(userSelect==CREATE_CUSTOMER || userSelect==UPDATE_CUSTOMER
				|| userSelect==DELETE_CUSTOMER || userSelect==CREATE_ORDER
				|| userSelect==PROCESS_ORDER || userSelect==SHOW_CLIENTS
				|| userSelect==SHOW_ORDERS_PENDING || userSelect==SHOW_ORDERS_COMPLETED
				|| userSelect==PRINT_MORE_PENDING || userSelect==PRINT_MORE_COMPLETED
				|| userSelect==PRINT_MORE_CUSTOMERS || userSelect==PRINT_MORE_CUSTOMERS_KG
				|| userSelect==PRINT_LESS_CUSTOMERS_KG || userSelect==PRINT_MORE_1000_KG
				|| userSelect==PRINT_LESS_100_KG);
	}else {
		printf("\nERROR=>Application error...!!\n");
	}
	return status;
}
