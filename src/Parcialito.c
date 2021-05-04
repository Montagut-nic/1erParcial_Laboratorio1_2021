/*
 ============================================================================
 Name        : Parcialito.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Cliente.h"
#include "Compras.h"
#include "FuncionesCruzadas.h"

#define QTY_CLI 100
#define QTY_COM 1000

int main(void) {
	setbuf(stdout,NULL);
	sCliente listadoDeClientes[QTY_CLI];
	sCompraBarbijo listadoDeCompras[QTY_COM];
	int respuesta;
	int opcionInt;
	char mensaje[ARRAY_LEN];
	int idCompra;
	int idCliente;
	int i;
	if(cli_InitializeList(listadoDeClientes,QTY_CLI)==OK
			&& com_InitializeList(listadoDeCompras,QTY_COM)==OK)
	{
		do{
			snprintf(mensaje,ARRAY_LEN,"\nSeleccione alguna de las siguientes opciones:\n\n"
									"1) Alta de cliente\n"
									"2) Modificar datos de cliente\n"
									"3) Baja de cliente\n"
									"4) Realizar compra\n"
									"5) Pagar compra\n"
									"6) Cancelar compra\n"
									"7) Imprimir clientes\n"
									"8) Informar\n"
									"9) Salir\n");
			respuesta=utn_getInt(&opcionInt, mensaje,"\nError. No se ingreso una opcion valida.\n", 5, 1, 11);
			if(respuesta==OK){
				switch(opcionInt){
					case 1:
						cruz_AltaDeCliente(listadoDeClientes,QTY_CLI);
						break;
					case 2:
						cli_Modificar(listadoDeClientes, QTY_CLI);
						break;
					case 3:
						cruz_BajaDeCliente(listadoDeClientes, QTY_CLI, listadoDeCompras, QTY_COM);
						break;
					case 4:
						 cruz_RealizarCompra(listadoDeCompras, QTY_COM, listadoDeClientes, QTY_CLI);
						break;
					case 5:
						if(utn_getIntLimiteMaxOMin(&idCompra,"\nIngrese el ID de la venta:\n","\nError. No se ingreso un ID valido\n",2,1,0,LIM_MIN)==OK){
							idCliente=com_SearchIdClienteByIdCompra(listadoDeCompras, QTY_COM, idCompra);
							if(idCliente>0){
								i=cli_SearchById(listadoDeClientes, QTY_CLI, idCliente);
								cli_Print(&listadoDeClientes[i]);
								com_PagarCompra(listadoDeCompras, QTY_COM, idCompra);
							}else{
								printf("\nNo se encontro una venta con ese ID.\n");
							}
						}
						break;
					case 6:
						if(utn_getIntLimiteMaxOMin(&idCompra,"\nIngrese el ID de la venta:\n","\nError. No se ingreso un ID valido\n",2,1,0,LIM_MIN)==OK){
							idCliente=com_SearchIdClienteByIdCompra(listadoDeCompras, QTY_COM, idCompra);
							if(idCliente>0){
								i=cli_SearchById(listadoDeClientes, QTY_CLI, idCliente);
								cli_Print(&listadoDeClientes[i]);
								com_baja(listadoDeCompras, QTY_COM, idCompra);
							}else{
								printf("\nNo se encontro una venta con ese ID.\n");
							}
						}
						break;
					case 7:
						cli_PrintList(listadoDeClientes, QTY_CLI);
						break;
					case 8:
						break;
				}
			}
		}while(opcionInt!=9);
	}
	return EXIT_SUCCESS;
}
