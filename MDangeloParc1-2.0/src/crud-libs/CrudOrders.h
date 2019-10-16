/**
 * @purpose: Take care all about create,read, delete, update Orders (Pedidos)
 * @autor: mdangelo
 */
#ifndef CRUD_LIBS_CRUDORDERS_H_
#define CRUD_LIBS_CRUDORDERS_H_

struct{
	int id; //AI
	int customerId;
	float kgTot;
	char status[11];
	float hdpe;
	float ldpe;
	float pp;
	int isEmpty;
}typedef Order;

	int crudOrdsInitializeAll(Order customers[], int length);
	int crudOrdsCreateMe(Order orders[], int i, int cstmId,float kgTot, int length);
	int crudOrdsUpdateMe(Order orders[], int i,float kgTot, int length);
	int crudOrdsUpdateMePlasticsKgs(Order orders[], int i,float hdpe,float ldpe,float pp, int length);
	int crudOrdsDeleteMe(Order orders[],int length, int cstmId);
	int crudOrdsGetIndexById(Order orders[], int id, int length, int *index);
	int crudOrdsShowAll(Order orders[], int length);

	int crudOrdsCanUpdateDelete(Order orders[], int length);

#endif /* CRUD_LIBS_CRUDORDERS_H_ */
