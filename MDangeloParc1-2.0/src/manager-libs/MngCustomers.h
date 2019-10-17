/*
 * mngCustomers.h
 *
 *  Created on: 12 oct. 2019
 *      Author: monkey
 */

#ifndef MANAGER_LIBS_MNGCUSTOMERS_H_
#define MANAGER_LIBS_MNGCUSTOMERS_H_

#include "../crud-libs/CrudCustomers.h"
#include "../crud-libs/CrudOrders.h"
	int createHarcordCustomer(Customer customers[], int length);
	int mngCustomerCreation(Customer customers[], int length);
	int mngCustomerModification(Customer customers[], int length);
	int mngCustomerDelete(Customer customers[], int length, Order orders[], int ordLength);
	int mngShowAllCustomers(Customer customers[], int length);
#endif /* MANAGER_LIBS_MNGCUSTOMERS_H_ */
