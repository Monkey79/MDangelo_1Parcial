/**
 * @purpose: Take care all about create,read, delete, update.
 * @autor: mdangelo
 */
#ifndef CRUD_LIBS_CRUDCUSTOMERS_H_
#define CRUD_LIBS_CRUDCUSTOMERS_H_

struct{
	int id; //AI
	char companyName[50];
	char adress[30];
	char cuit[15];
	char location[30];
	int isEmpty;
}typedef Customer;
	int crudCstmInitializeAll(Customer customers[], int length);
	int crudCstmCreateMe(Customer customers[], int i, char coName[],char cuit[], char address[], char location[], int length);
	int crudCstmUpdateMe(Customer customers[], int i, char address[], char location[], int length);
	int crudCstmDeleteMe(Customer customers[], int i, int lengt);
	int crudCstmGetIndexById(Customer customers[], int id, int length, int *index);
	int crudCstmShowAll(Customer customers[], int length);
	int crudCstmShowAllIds(Customer customers[], int length);
	int crudCstmCanUpdateDelete(Customer customers[], int length);
#endif /* CRUD_LIBS_CRUDCUSTOMERS_H_ */
