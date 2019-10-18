/*
 * mngCustomers.c
 *
 *  Created on: 12 oct. 2019
 *      Author: monkey
 */

#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>

#define SUCCESS 0
#define ERROR -1
#define TRUE  1
#define FALSE 0

#include "../crud-libs/CrudCustomers.h"
#include "../manager-libs/MngCustomers.h"

#define SUCCESS 0
#define ERROR -1
#define TRUE  1
#define FALSE 0

int _createTheCustomer(Customer customers[], int length);
int _updateTheCustomer(Customer customers[], int length);
int _getFirstEmptyCustomerIndex(Customer customers[], int length);
int _deleteTheCustomerAndHisOrders(Customer customers[], int length, Order orders[], int ordLength);
void  _listAllCustomersIds(Customer customers[], int length);
int _getIdToUpdateOrDelete();

int mngCustomerGetKgTotRecyByCuitAndPlasticType(Customer customers[], int cstLength, Order orders[], int ordLength){
	int status = ERROR;
	char cuit[14];
	int plastType=1;

	printf("\n Ingrese el CUIT\n");
	__fpurge(stdin);
	fgets(cuit, 14, stdin);


	do{
		printf("\n Ingrese tipo de plastico [1=hdpe 2=ldpe 3=pp] \n");
		__fpurge(stdin);
		//scanf("%d");

	}while(plastType!=1 && plastType!=2 && plastType!=3);


	return status;
}

int mngCustomerCreation(Customer customers[], int length){
	int status = ERROR;
	char usrOpt = 's';
	do{
		printf("\n==>Desea crear un Cliente? (s|n)\n");
		__fpurge(stdin);
		scanf("%c", &usrOpt);
	}while(usrOpt!='s' && usrOpt!='n');
	if(usrOpt == 's'){
		status =_createTheCustomer(customers, length);
	}
	return status;
}

int mngCustomerModification(Customer customers[], int length){
	int status = ERROR;
	char usrOpt = 's';
	if(crudCstmCanUpdateDelete(customers, length) == TRUE){
		do{
			printf("\n==>Desea modificar un Cliente? (s|n)\n");
			__fpurge(stdin);
			scanf("%c", &usrOpt);
		}while(usrOpt!='s' && usrOpt!='n');
		if(usrOpt == 's') status = _updateTheCustomer(customers, length);
	}else{
		printf("\nERROR=>No puede modificar ningun cliente porque NO tiene nada aun cargado\n");
	}

	return status;
}

int mngCustomerDelete(Customer customers[], int length, Order orders[], int ordLength){
	int status = ERROR;
	char usrOpt = 's';
	if(crudCstmCanUpdateDelete(customers, length) == TRUE) {
		do{
			printf("\n==>Desea borrar un Cliente y sus Pedidos? (s|n)\n");
			__fpurge(stdin);
			scanf("%c", &usrOpt);
		}while(usrOpt!='s' && usrOpt!='n');
		if(usrOpt == 's') status = _deleteTheCustomerAndHisOrders(customers, length, orders, ordLength);
	}else{
		printf("\nERROR=>No puede eliminar ningun cliente porque NO tiene nada aun cargado\n");
	}
	return status;
}


int mngShowAllCustomers(Customer customers[], int length) {
	int status = ERROR;
	status = crudCstmShowAll(customers, length);
	return status;
}

int createHarcordCustomer(Customer customers[], int length){
	char dmyCoName[51];
	char dmyCuit[13];
	char dmyAddress[51];
	char dmyLocation[51];
	int status;

	int i = _getFirstEmptyCustomerIndex(customers, length);
	if(i>=0){
		strcpy(dmyCoName, "Telefonica");
		strcpy(dmyCuit, "30-11223344-5");
		strcpy(dmyAddress, "Lima 1234");
		strcpy(dmyLocation, "CABA");
		status = crudCstmCreateMe(customers,i,dmyCoName, dmyCuit, dmyAddress, dmyLocation, length);
	}

	i = _getFirstEmptyCustomerIndex(customers, length);
	if(i>=0){
		strcpy(dmyCoName, "DATASOFT");
		strcpy(dmyCuit, "30-44556677-6");
		strcpy(dmyAddress, "Corrientes 2547");
		strcpy(dmyLocation, "CABA");
		status = crudCstmCreateMe(customers,i,dmyCoName, dmyCuit, dmyAddress, dmyLocation, length);
	}
	i = _getFirstEmptyCustomerIndex(customers, length);
	if(i>=0){
		strcpy(dmyCoName, "NESTLE");
		strcpy(dmyCuit, "30-88995521-9");
		strcpy(dmyAddress, "cucha cucha 555");
		strcpy(dmyLocation, "LANUS");
		status = crudCstmCreateMe(customers,i,dmyCoName, dmyCuit, dmyAddress, dmyLocation, length);
	}
	i = _getFirstEmptyCustomerIndex(customers, length);
	if(i>=0){
		strcpy(dmyCoName, "TERRABUSI");
		strcpy(dmyCuit, "30-56781423-5");
		strcpy(dmyAddress, "rocha 784");
		strcpy(dmyLocation, "QUILMES");
		status = crudCstmCreateMe(customers,i,dmyCoName, dmyCuit, dmyAddress, dmyLocation, length);
	}
	i = _getFirstEmptyCustomerIndex(customers, length);
	if(i>=0){
		strcpy(dmyCoName, "DIA");
		strcpy(dmyCuit, "31-54581253-3");
		strcpy(dmyAddress, "Mitre 750");
		strcpy(dmyLocation, "AVELLANEDA");
		status = crudCstmCreateMe(customers,i,dmyCoName, dmyCuit, dmyAddress, dmyLocation, length);
	}
	i = _getFirstEmptyCustomerIndex(customers, length);
	if(i>=0){
		strcpy(dmyCoName, "QUILMES");
		strcpy(dmyCuit, "30-51485759-6");
		strcpy(dmyAddress, "rocha 741");
		strcpy(dmyLocation, "QUILMES");
		status = crudCstmCreateMe(customers,i,dmyCoName, dmyCuit, dmyAddress, dmyLocation, length);
	}
	return status;
}


//===========Private functions============================
int _createTheCustomer(Customer customers[], int length) {
	char dmyCoName[51];
	char dmyCuit[13];
	char dmyAddress[51];
	char dmyLocation[51];

	int i = _getFirstEmptyCustomerIndex(customers, length);
	int status;

	if(i >= 0){
		printf("\n Ingrese Nombre de la empresa : \n");
		__fpurge(stdin);
		fgets(dmyCoName, 51, stdin);
		printf("\n Ingrese Direccion del cliente : \n");
		__fpurge(stdin);
		fgets(dmyAddress, 51, stdin);
		printf("\n Ingrese Localidad del cliente : \n");
		fgets(dmyLocation, 51, stdin);
		printf("\n Ingrese Cuit del cliente : \n");
		__fpurge(stdin);
		fgets(dmyCuit, 14, stdin);
		status = crudCstmCreateMe(customers,i,dmyCoName, dmyCuit, dmyAddress, dmyLocation, length);
	}else {
		printf("\n ERROR: NO hay mas lugar disponible \n");

	}
	return status;
}

int _updateTheCustomer(Customer customers[], int length) {
	char dmyAddress[51];
	char dmyLocation[51];
	int index;
	int status = ERROR;

	_listAllCustomersIds(customers, length);
	int id = _getIdToUpdateOrDelete();
	crudCstmGetIndexById(customers, id, length, &index);

	if(index>=0){
		printf("\n Ingrese nueva direccion del cliente : antes=%s \n", customers[index].adress);
		__fpurge(stdin);
		fgets(dmyAddress, 51, stdin);
		printf("\n Ingrese la nueva localidad del cliente: antes=%s \n", customers[index].location);
		fgets(dmyLocation, 51, stdin);
		status = crudCstmUpdateMe(customers,index,dmyAddress, dmyLocation, length);
	}
	return status;
}

int _deleteTheCustomerAndHisOrders(Customer customers[], int length, Order orders[], int ordLength) {
	int index;
	int status = ERROR;
	_listAllCustomersIds(customers, length);
	int id = _getIdToUpdateOrDelete();
	crudCstmGetIndexById(customers, id, length, &index);
	if(index>=0){
		status = crudCstmDeleteMe(customers,index,length);
		status = crudOrdsDeleteMe(orders, ordLength, id);
	}
	return status;
}

int _getFirstEmptyCustomerIndex(Customer customers[], int length){
	int notEmpty = TRUE;
	int i = 0;
	do{
		notEmpty = (customers[i].isEmpty  == FALSE);
		i++;
	}while((i < length) && notEmpty==TRUE);
	i = (notEmpty == TRUE)?-1:(i-1);
	return i;
}

void  _listAllCustomersIds(Customer customers[], int length){
	printf("\n======Clientes Ids==========\n");
	for(int i=0; i< length; i++){
		if(customers[i].isEmpty == FALSE)printf("\nID=%d",customers[i].id);
	}
	printf("\n=============================\n");
}

int _getIdToUpdateOrDelete(){
	int id;
	printf("\n Ingrese el id del cliente que desea modificar o eliminar\n");
	__fpurge(stdin);
	scanf("%d", &id);
	return id;
}

int _canUupdateOrDelete(Customer customers[], int length){
	return crudCstmCanUpdateDelete(customers, length);
}
