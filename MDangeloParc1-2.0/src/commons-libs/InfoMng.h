/*
 * InfoMng.h
 *
 *  Created on: 17 oct. 2019
 *      Author: alumno
 */

#ifndef COMMONS_LIBS_INFOMNG_H_
#define COMMONS_LIBS_INFOMNG_H_

#include "../crud-libs/CrudOrders.h"
#include "../crud-libs/CrudCustomers.h"
#include "../commons-libs/Utils.h"

void customerWithMoreRecycledKg(Customer customers[], Order orders[],int cstLength, int ordLength);
void customerWithLessRecyblessKg(Customer customers[], Order orders[],int cstLength, int ordLength);
void customerWithMoreThan1000KgRecicled(Customer customers[], Order orders[],int cstLength, int ordLength);
void customerWithLessThan100KgRecicled(Customer customers[], Order orders[],int cstLength, int ordLength);
void customerWithMoreOrders(Customer customers[], Order orders[],int cstLength, int ordLength);
void customerWithMoreOrderStatus(Customer customers[], Order orders[],int cstLength, int ordLength, char *statusN);

void infoPrintCompletedOrds(Customer customers[], Order orders[],int cstLength, int ordLength);
void printPendingOrdersByLocation(Customer customers[], Order orders[],int cstLength, int ordLength);


#endif /* COMMONS_LIBS_INFOMNG_H_ */
