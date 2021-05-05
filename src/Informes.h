/*
 * Informes.h
 *
 *  Created on: 4 may. 2021
 *      Author: Montagut
 */

#ifndef INFORMES_H_
#define INFORMES_H_

#include "Cliente.h"
#include "Compras.h"
#include "utn.h"
#include "FuncionesCruzadas.h"

typedef struct{
	int cantDeBarbijoMasComprado;
	char colorDeBarbijoMasComprado[COL_LEN];
	int cantComprasPendientes;
	int idCompraConPromedioDePrecioMasBajo;
	int idClienteMasComprasPagadas;
	int idClienteMasComprasPendientes;
	int isEmpty;
} sInforme;

int info_showColorQueSeComproMasVeces(sCompraBarbijo*listCompraBarbijo,int lenListCompras);
int info_CantidadDeComprasPendientes(sCompraBarbijo*listCompraBarbijo,int lenListCompras);
int info_CompraConPrecioPorUnidadMasBajo(sCompraBarbijo*listCompraBarbijo,int lenListCompras);
int info_ClienteConMasCompras(int pendientesOPagadas, sCliente*listadoClientes, int lenClientes);
int info_showMenuInformes(sCompraBarbijo*listCompraBarbijos,int lenListaCompras,sCliente*listClientes,int lenClientes);

#endif /* INFORMES_H_ */
