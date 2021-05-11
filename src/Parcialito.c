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
#include "FuncionesCruzadas.h"
#include "Informes.h"
#include "utn.h"
#include "Compras.h"
#include "Cliente.h"

#define QTY_CLI 100
#define QTY_COM 1000

int main(void) {
	setbuf(stdout,NULL);
	sCliente* listadoPunterosCliente[0] ;
	sCompraBarbijo listadoDeCompras[QTY_COM];
	int respuesta;
	int opcionInt;
	char mensaje[ARRAY_LEN];

	if(listadoPunterosCliente!=NULL){
		if(cruz_InitListas(listadoPunterosCliente,QTY_CLI,listadoDeCompras,QTY_COM)==OK)
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
							cruz_AltaDeCliente(listadoPunterosCliente,QTY_CLI);
							break;
						case 2:
							cli_Modificar(listadoPunterosCliente, QTY_CLI);
							break;
						case 3:
							cruz_BajaDeCliente(listadoPunterosCliente, QTY_CLI, listadoDeCompras, QTY_COM);
							break;
						case 4:
							 cruz_RealizarCompra(listadoDeCompras, QTY_COM, listadoPunterosCliente, QTY_CLI);
							break;
						case 5:
							cruz_PagarCompra(listadoPunterosCliente, QTY_CLI, listadoDeCompras, QTY_COM);
							break;
						case 6:
							cruz_CancelarCompra(listadoDeCompras, QTY_COM, listadoPunterosCliente, QTY_CLI);
							break;
						case 7:
							if(cli_PrintList(listadoPunterosCliente, QTY_CLI)!=OK){
								printf("\nNo hay clientes cargados para mostrar.\n");
							}
							break;
						case 8:
							info_showMenuInformes(listadoDeCompras, QTY_COM, listadoPunterosCliente, QTY_CLI);
							break;
					}
				}
			}while(opcionInt!=9);
		}
	}
	return EXIT_SUCCESS;
}
