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

int info_showMenuInformes(sCompraBarbijo*listCompraBarbijos,int lenCompras,sCliente*arrayPunterosCliente[],int lenClientes);
int info_showColorQueSeComproMasVeces(sCompraBarbijo*listCompraBarbijo,int lenListCompras);
int info_CantidadDeComprasPendientes(sCompraBarbijo*listCompraBarbijo,int lenListCompras);
int info_CompraConPrecioPorUnidadMasBajo(sCompraBarbijo*listCompraBarbijo,int lenListCompras);
int info_ClienteConMasCompras(int pendientesOPagadas,sCliente*arrayPunterosCliente[],int lenClientes);
int info_PrintComprasPendientesConCliente(sCompraBarbijo*listadoCompras,int lenCompras,sCliente*arrayPunterosCliente[],int lenClientes);

#endif /* INFORMES_H_ */
