/*
 * Utils.h
 *
 *  Created on: 19 oct. 2019
 *      Author: monkey
 */

#ifndef COMMONS_LIBS_UTILS_H_
#define COMMONS_LIBS_UTILS_H_

#include "../crud-libs/CrudCustomers.h"
#include "../crud-libs/CrudOrders.h"

void utlsGetOrdersByCustomerId(Customer custm,Order ordersVc[],int ordLength, Order ordersByCstmVc[]);
void utlsGetCleanString(char source[], char dest[]);
int utilsGetPlasticType();
int utilGetCustomerIdByCuit(Customer customers[], int cstmLength);


#endif /* COMMONS_LIBS_UTILS_H_ */
