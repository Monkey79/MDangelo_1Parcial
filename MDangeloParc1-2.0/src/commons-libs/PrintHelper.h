/*
 * PrintHelper.h
 *
 *  Created on: 14 oct. 2019
 *      Author: monkey
 */

#ifndef COMMONS_LIBS_PRINTHELPER_H_
#define COMMONS_LIBS_PRINTHELPER_H_

#include "../crud-libs/CrudOrders.h"
#include "../crud-libs/CrudCustomers.h"
	void checkAndShowCustomersOrdCantByOrderStatus(Customer customers[], Order orders[], char *status, int cstLength, int ordLength);
	void showOrdersCustomersByStatus(Customer customers[], Order orders[],char *status, int cstLength, int ordLength);
#endif /* COMMONS_LIBS_PRINTHELPER_H_ */
