/*
 * Utils.c
 *
 *  Created on: 19 oct. 2019
 *      Author: monkey
 */
#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>

#include "Utils.h"

#define SUCCESS 0
#define ERROR  -1
#define TRUE  	1
#define FALSE 	0


void utlsGetOrdersByCustomerId(Customer custm,Order ordersVc[],int ordLength, Order ordersByCstmVc[]) {
	int cstmId = custm.id;
	for(int i = 0; i<ordLength; i++){
		//printf("%d \n",  (*(ordersVc+i)).id);
		if((ordersVc[i].isEmpty == FALSE)==TRUE && (ordersVc[i].customerId == cstmId)==TRUE) {
			ordersByCstmVc[i] = ordersVc[i];
		}
	}
}

void utlsGetCleanString(char source[], char dest[]){
	int j=0;
	while(source[j]!='\0' && source[j]!=10){
		dest[j]=source[j];
		j++;
	}
	dest[j]='\0';
}

int utilsGetPlasticType(){
	int plTypeAux = 0;
	do {
		printf("\n Ingrese el tipo de plastico [1=HDPE | 2=LDPE | 3=PP]");
		__fpurge(stdin);
		scanf("%d", &plTypeAux);
	} while (plTypeAux!=1 && plTypeAux!=2 && plTypeAux!=3);
	return plTypeAux;
}

int utilGetCustomerIdByCuit(Customer customers[], int cstmLength){
	char cuitAux[15];
	char cuitFinal[15];
	int id;
	printf("\n Ingrese el CUIT del cliente \n");
	__fpurge(stdin);
	fgets(cuitAux, 15, stdin);

	utlsGetCleanString(cuitAux, cuitFinal);

	int i=0;
	int found = FALSE;
	do {
		if((customers[i].isEmpty==FALSE) == TRUE){
			found = strcmp(customers[i].cuit, cuitFinal)==0;
			i++;
		}

	} while ((found==FALSE)==TRUE && i<cstmLength);
	if((found==FALSE)==TRUE){
		id = -1;
	}else
		id = customers[--i].id;

	return id;
}
