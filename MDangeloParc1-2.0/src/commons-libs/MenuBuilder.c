/**
 * @purpose: Create Menu and save user selection
 * @autor: mdangelo
 */
#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>

#define MENU_HEADER "\n*************MENU**************************\nPor favor elija una opcion\n"
#define  OPTION_1 "1-Alta Cliente\n"
#define  OPTION_2 "2-Modificar Cliente\n"
#define  OPTION_3 "3-Baja de Cliente\n"
#define  OPTION_4 "4-Crear Pedido\n"
#define  OPTION_5 "5-Procesar Pedido (residuos)\n"
#define  OPTION_6 "6-Imprimir clientes (estado pendiente)\n"
#define  OPTION_7 "7-Imprimir pedidos pendientes\n"
#define  OPTION_8 "8-Imprimir pedidos procesados\n"

#define  OPTION_9 "9 [A]-Imprimir cliente con mas Pendientes\n"
#define  OPTION_10 "10 [B]-Imprimir cliente con mas Completados\n"
#define  OPTION_11 "11 [C]-Imprimir cliente con mas Pedidos\n"
#define  OPTION_12 "12 [D]-Imprimir cliente que reciclo mas Kg\n"
#define  OPTION_13 "13 [E]-Imprimir cliente que reciclo menos Kg\n"
#define  OPTION_14 "14 [F]-Imprimir cant de clientes que reciclaron mas 1000kg\n"
#define  OPTION_15 "15 [G]-Imprimir cant de clientes que reciclaron menos 100kg\n"
#define  OPTION_16 "16 [H]-Imprimir pedidos Completados\n"
#define  OPTION_17 "17 [I]-Imprimir cantidad de Pedidos Pendientes por Localidad\n"
#define  OPTION_18 "18 [J]-Imprimir cantidad de PP reciclado por CLientes\n"
#define  OPTION_19 "19 [K]-Imprimir cantitad kg por: Tipo y Cuit-Cliente\n"


#define  OPTION_29 "29-Salir\n"
#define MENU_FOOTER "\n********************************************\n"


void mngbBuildMenuAndGetUserSelection(int *userSelection){
	printf(MENU_HEADER);
	printf(OPTION_1);
	printf(OPTION_2);
	printf(OPTION_3);
	printf(OPTION_4);
	printf(OPTION_5);
	printf(OPTION_6);
	printf(OPTION_7);
	printf(OPTION_8);
	printf(OPTION_9);
	printf(OPTION_10);
	printf(OPTION_11);
	printf(OPTION_12);
	printf(OPTION_13);
	printf(OPTION_14);
	printf(OPTION_15);
	printf(OPTION_16);
	printf(OPTION_17);
	printf(OPTION_18);
	printf(OPTION_19);

	printf(OPTION_29);
	printf(MENU_FOOTER);
	__fpurge(stdin);
	scanf("%d", userSelection);
}
