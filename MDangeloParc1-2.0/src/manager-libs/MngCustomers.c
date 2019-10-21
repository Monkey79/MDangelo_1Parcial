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
	char dmyCuit[15];
	char dmyAddress[51];
	char dmyLocation[30];
	int status;

	int i = _getFirstEmptyCustomerIndex(customers, length);
	if(i>=0){
		strcpy(dmyCoName, "Telefonica");
		strcpy(dmyCuit, "30-11223344-5");
		strcpy(dmyAddress, "Lima 1234");
		strcpy(dmyLocation, "CABA");
		status = crudCstmCreateMe(customers,i,dmyCoName, dmyCuit, dmyAddress, dmyLocation, length);
	}
	char dmyCoName2[51];
	char dmyCuit2[15];
	char dmyAddress2[51];
	char dmyLocation2[30];

	i = _getFirstEmptyCustomerIndex(customers, length);
	if(i>=0){
		strcpy(dmyCoName2, "DATASOFT");
		strcpy(dmyCuit2, "30-44556677-6");
		strcpy(dmyAddress2, "Corrientes 2547");
		strcpy(dmyLocation2, "CABA");
		status = crudCstmCreateMe(customers,i,dmyCoName2, dmyCuit2, dmyAddress2, dmyLocation2, length);
	}
	char dmyCoName3[51];
	char dmyCuit3[15];
	char dmyAddress3[51];
	char dmyLocation3[30];

	i = _getFirstEmptyCustomerIndex(customers, length);
	if(i>=0){
		strcpy(dmyCoName, "NESTLE");
		strcpy(dmyCuit, "30-88995521-9");
		strcpy(dmyAddress, "cucha cucha 555");
		strcpy(dmyLocation3, "LANUS");
		status = crudCstmCreateMe(customers,i,dmyCoName3, dmyCuit3, dmyAddress3, dmyLocation3, length);
	}

	char dmyCoName4[51];
	char dmyCuit4[15];
	char dmyAddress4[51];
	char dmyLocation4[30];
	i = _getFirstEmptyCustomerIndex(customers, length);
	if(i>=0){
		strcpy(dmyCoName, "TERRABUSI");
		strcpy(dmyCuit, "30-56781423-5");
		strcpy(dmyAddress, "rocha 784");
		strcpy(dmyLocation4, "QUILMES");
		status = crudCstmCreateMe(customers,i,dmyCoName4, dmyCuit4, dmyAddress4, dmyLocation4, length);
	}

	char dmyCoName5[51];
	char dmyCuit5[15];
	char dmyAddress5[51];
	char dmyLocation5[30];
	i = _getFirstEmptyCustomerIndex(customers, length);
	if(i>=0){
		strcpy(dmyCoName, "DIA");
		strcpy(dmyCuit, "31-54581253-3");
		strcpy(dmyAddress, "Mitre 750");
		strcpy(dmyLocation5, "AVELLANEDA");
		status = crudCstmCreateMe(customers,i,dmyCoName5, dmyCuit5, dmyAddress5, dmyLocation5, length);
	}

	char dmyCoName6[51];
	char dmyCuit6[15];
	char dmyAddress6[51];
	char dmyLocation6[30];
	i = _getFirstEmptyCustomerIndex(customers, length);
	if(i>=0){
		strcpy(dmyCoName, "QUILMES");
		strcpy(dmyCuit, "30-51485759-6");
		strcpy(dmyAddress, "rocha 741");
		strcpy(dmyLocation6, "QUILMES");
		status = crudCstmCreateMe(customers,i,dmyCoName6, dmyCuit6, dmyAddress6, dmyLocation6, length);
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
