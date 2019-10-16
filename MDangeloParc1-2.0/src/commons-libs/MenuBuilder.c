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
#define  OPTION_9 "9-Salir\n"
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
	printf(MENU_FOOTER);
	__fpurge(stdin);
	scanf("%d", userSelection);
}
