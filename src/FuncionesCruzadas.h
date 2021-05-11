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
#include <string.h>
#include <windows.h>
#include "Cliente.h"
#include "Compras.h"
#include "utn.h"

int cruz_AltaDeCliente(sCliente* arrayPunterosCliente[], int longitud);
int cruz_BajaDeCliente(sCliente*arrayPunterosCliente[],int lenClientes,sCompraBarbijo*listBarbijos,int lenBarbijos);
int cruz_RealizarCompra(sCompraBarbijo*listadoCompras,int lenCompras,sCliente*arrayPunterosCliente[],int lenClientes);
int cruz_AltaCompra(sCompraBarbijo* listCompras,int lenCompras,int *idCompra,sCliente*arrayPunterosCliente[],int lenClientes);
int cruz_ShowMenuModificarCompra(int*opcion,sCompraBarbijo*compraBuffer,sCliente*arrayPunterosCliente[],int lenClientes);
int cruz_PagarCompra(sCliente*arrayPunterosCliente[],int lenClientes,sCompraBarbijo*listadoCompras,int lenCompras);
int cruz_CancelarCompra(sCompraBarbijo*listadoCompras,int lenCompras,sCliente*arrayPunterosCliente[],int lenClientes);
int cruz_InitListas(sCliente*arrayPunterosCliente[],int lenListaClientes,sCompraBarbijo*listaCompras,int lenListaCompras);

#endif /* FUNCIONESCRUZADAS_H_ */
