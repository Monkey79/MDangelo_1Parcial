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
		printf("=el char= %c\n",source[j]);
		printf("=el char= %d\n",source[j]);
		dest[j]=source[j];
		j++;
	}
	dest[j]='\0';
}
