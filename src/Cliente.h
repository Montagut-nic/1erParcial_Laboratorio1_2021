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
} sCliente;

typedef struct{
	int idCliente;
	char nombre[MAX_LEN];
	char apellido[MAX_LEN];
	float sueldo;
	int idRelation;
	int isEmpty;
} sClienteDOS;

int cli_InitializeList(sCliente* list, int len);
int cli_SearchEmpty (sCliente* list, int len);
int cli_SearchById(sCliente* list, int len, int id);
int cli_Print (sCliente* list);
int cli_PrintById(sCliente* list, int len,int id);
int cli_PrintList(sCliente* list, int len);
int cli_GenerateId();
int cli_alta(sCliente* list,int len,int *id);
int cli_baja(sCliente* list,int len);
int cli_bajaConfirmada(sCliente* list,int len,int i);
int cli_Modificar(sCliente* list,int len);
int cli_ShowMenuModificar(int*opcion,sCliente*structBuffer,sCliente*list,int len);
int cli_ordenarPorSTRINGCHAR(sCliente* list, int len);
int cli_ordenarPorNUMERICO(sCliente* list, int len);
int cli_ordenarPorSTRINGCHAR_NUMERICO(sCliente* list, int len);
int info_imprimirImportesContrataciones(sCliente* pContrataciones, int limiteContrataciones, sClienteDOS* pPantallas, int limitePantallas, char*auxiliarCuit);


#endif /* CLIENTE_H_ */
