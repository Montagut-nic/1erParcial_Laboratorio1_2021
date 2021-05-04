/*
 * Compras.h
 *
 *  Created on: 4 may. 2021
 *      Author: Montagut
 */

#ifndef COMPRAS_H_
#define COMPRAS_H_

#include "utn.h"
#define DIR_LEN 64
#define COL_LEN 32
#define PENDIENTE 0
#define COBRADA 1

typedef struct{
	int idCompra;
	int idCliente;
	float precio;
	int cobro;
	int cantBrabijos;
	char direccion[DIR_LEN];
	char color[COL_LEN];
	int isEmpty;
} sCompraBarbijo;

int com_InitializeList(sCompraBarbijo* list, int len);
int com_SearchEmpty (sCompraBarbijo* list, int len);
int com_SearchById(sCompraBarbijo* list, int len, int id);
int com_SearchIdClienteByIdCompra(sCompraBarbijo* list, int len, int id);
int com_Print (sCompraBarbijo* list);
int com_PrintList(sCompraBarbijo* list, int len);
int com_PrintListByIdCliente(sCompraBarbijo* list, int len, int id);
int com_GenerateId();
int com_bajaTotalCliente(sCompraBarbijo* list,int len,int id);
int com_baja(sCompraBarbijo* list,int len,int idCompra);
int com_PagarCompra(sCompraBarbijo*list,int longitud,int idCompra);

#endif /* COMPRAS_H_ */
