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
#define VACIO 1
#define OCUPADO 0
#define MENOR_A_MAYOR -1
#define MAYOR_A_MENOR 1

typedef struct{
	int idCliente;
	char nombre[MAX_LEN];
	char apellido[MAX_LEN];
	char cuit[CUIT_LEN];
	int idRelation;
	int isEmpty;
	int cantDeCompras;
	int cantDeComprasPendientes;
} sCliente;

int cli_InitializeList(sCliente* list, int len);
int cli_SearchEmpty (sCliente* list, int len);
int cli_SearchById(sCliente* list, int len, int id);
int cli_SearchByCuit(sCliente* list, int len, char* cuit);
int cli_Print (sCliente* list);
int cli_PrintById(sCliente* list, int len,int id);
int cli_PrintList(sCliente* list, int len);
int cli_GenerateId();
int cli_alta(sCliente* list,int len,int *id);
int cli_bajaConfirmada(sCliente* list,int len,int i);
int cli_Modificar(sCliente* list,int len);
int cli_ShowMenuModificar(int*opcion,sCliente*structBuffer,sCliente*list,int len);


#endif /* CLIENTE_H_ */
