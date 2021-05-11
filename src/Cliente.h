/*
 * Cliente.h
 *
 *  Created on: 1 may. 2021
 *      Author: Montagut
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "utn.h"

#define MAX_LEN 64
#define MENOR_A_MAYOR -1
#define MAYOR_A_MENOR 1

typedef struct{
	int idCliente;
	char nombre[MAX_LEN];
	char apellido[MAX_LEN];
	char cuit[CUIT_LEN];
	int cantDeCompras;
	int cantDeComprasPendientes;
	int cantDeComprasPagadas;
} sCliente;

int cli_InitializeArrayPunterosCliente(sCliente* arrayPunterosCliente[],int len);
int cli_SearchEmptyIndex(sCliente* arrayPunterosCliente[], int len);
int cli_SearchIndexById(sCliente* arrayPunterosCliente[], int len, int id);
int cli_SearchIndexByCuit(sCliente* arrayPunterosCliente[], int len, char* cuit);
int cli_Print (sCliente* PunteroCliente);
int cli_PrintList(sCliente* arrayPunterosCliente[], int len);
int cli_PrintById(sCliente* arrayPunterosCliente[], int len,int id);
int cli_GenerateId(void);
sCliente* cli_new(void);
int cli_alta(sCliente* arrayPunterosCliente[],int len,int *id);
int cli_bajaConfirmada(sCliente* arrayPunterosCliente[],int len,int i);
int cli_Modificar(sCliente* arrayPunterosCliente[],int len);
int cli_ShowMenuModificar(int*opcion,sCliente*auxPunteroCliente,sCliente*arrayPunterosCliente[],int len);


#endif /* CLIENTE_H_ */
