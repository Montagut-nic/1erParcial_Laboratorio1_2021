/*
 * FuncionesCruzadas.h
 *
 *  Created on: 4 may. 2021
 *      Author: Montagut
 */

#ifndef FUNCIONESCRUZADAS_H_
#define FUNCIONESCRUZADAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Cliente.h"
#include "Compras.h"
#include "utn.h"

int cruz_AltaDeCliente(sCliente* list, int longitud);
int cruz_BajaDeCliente(sCliente*listClientes, int lenClientes,sCompraBarbijo*listBarbijos,int lenBarbijos);
int cruz_RealizarCompra(sCompraBarbijo* listadoCompras,int lenCompras, sCliente* listadoClientes, int lenClientes);
int cruz_AltaCompra(sCompraBarbijo* listCompras,int lenCompras,int *idCompra,int idCliente,sCliente*listClientes,int lenClientes);
int cruz_ShowMenuModificarCompra(int*opcion,sCompraBarbijo*structBuffer,sCliente*listadoClientes, int lenClientes);
int cruz_PagarCompra(sCliente* listadoClientes,int lenClientes,sCompraBarbijo* listadoCompras,int lenCompras);
int cruz_RealizarCompra(sCompraBarbijo* listadoCompras,int lenCompras, sCliente* listadoClientes, int lenClientes);
int cruz_CancelarCompra(sCompraBarbijo*listadoCompras,int lenCompras, sCliente*listadoClientes, int lenClientes);

#endif /* FUNCIONESCRUZADAS_H_ */
