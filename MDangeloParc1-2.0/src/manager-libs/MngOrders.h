/*
 * MngOrders.h
 *
 *  Created on: 13 oct. 2019
 *      Author: monkey
 */

#ifndef MANAGER_LIBS_MNGORDERS_H_
#define MANAGER_LIBS_MNGORDERS_H_

#include "../crud-libs/CrudOrders.h"
#include "../crud-libs/CrudCustomers.h"
	int mngOrdersCreation(Order orders[], Customer customers[], int length, int custLength);
	int mngShowAllOrders(Order orders[], int length);
	int mngProcessOrders(Order orders[], int length);
#endif /* MANAGER_LIBS_MNGORDERS_H_ */
