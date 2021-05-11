/*
 * Informes.c
 *
 *  Created on: 4 may. 2021
 *      Author: Montagut
 */

#include "Informes.h"

int info_showMenuInformes(sCompraBarbijo*listCompraBarbijos,int lenCompras,sCliente*arrayPunterosCliente[],int lenClientes){
	int opcionInt;
	char mensaje[ARRAY_LEN];
	int retorno=ERROR_PARAM;
	if(listCompraBarbijos!=NULL&&lenCompras>0){
		retorno=ERROR_DATOS;
		do{
			snprintf(mensaje,ARRAY_LEN,"\nSeleccione alguna de las siguientes opciones:\n\n"
										"1) Color de barbijo que se compro mas veces\n"
										"2) Cantidad de compras pendientes\n"
										"3) Compra con precio por unidad mas bajo\n"
										"4) Cliente con mas compras pagadas\n"
										"5) Cliente con más compras pendientes\n"
										"6) Lista de compras pendientes de pago con información de la compra y del cliente\n"
										"7) Salir\n");
			if(utn_getInt(&opcionInt,mensaje, "\nError. No se ingreso una opcion valida\n",3,1,7)==OK){
				retorno=OK;
				switch(opcionInt){
					case 1:
						if(info_showColorQueSeComproMasVeces(listCompraBarbijos,lenCompras)!=OK){
							printf("\nNo se han realizado compras todavia.\n");
						}
						break;
					case 2:
						if(info_CantidadDeComprasPendientes(listCompraBarbijos, lenCompras)!=OK){
							printf("\nNo hay compras pendientes.\n");
						}
						break;
					case 3:
						if(info_CompraConPrecioPorUnidadMasBajo(listCompraBarbijos, lenCompras)!=OK){
							printf("\nNo se han pagado compras todavia.\n");
						}
						break;
					case 4:
						if(info_ClienteConMasCompras(COBRADA,arrayPunterosCliente,lenClientes)!=OK){
							printf("\nNo hay clientes con compras pagadas.\n");
						}
						break;
					case 5:
						if(info_ClienteConMasCompras(PENDIENTE,arrayPunterosCliente,lenClientes)!=OK){
							printf("\nNo hay clientes con compras pendientes.\n");
						}
						break;
					case 6:
						if(info_PrintComprasPendientesConCliente(listCompraBarbijos,lenCompras,arrayPunterosCliente,lenClientes)!=OK)
						{
							printf("\nNo hay compras pendientes.\n");
						}
						break;
				}

			}
		}while(opcionInt!=7);
	}
	return retorno;
}

int info_showColorQueSeComproMasVeces(sCompraBarbijo*listCompraBarbijo,int lenListCompras){
	int retorno=ERROR_PARAM;
	sCompraBarbijo listaAuxiliar[sizeof(listCompraBarbijo)];
	char colorMasComprado[COL_LEN];
	char colorAux[COL_LEN];
	int contadorAparicionesColor;
	int aparicionesColorMasComprado=0;
	int i;
	if(listCompraBarbijo!=NULL&&lenListCompras>0){
		retorno=ERROR_DATOS;
		*listaAuxiliar=*listCompraBarbijo;
		while(com_searchPrimerColor(listaAuxiliar, lenListCompras, colorAux, sizeof(colorAux))==OK){
			contadorAparicionesColor=0;
			for(i=0;i<lenListCompras;i++){
				if( com_buscadorColores(listaAuxiliar, lenListCompras, colorAux, sizeof(colorAux))==OK){
					contadorAparicionesColor++;
				}
			}
			if(contadorAparicionesColor>aparicionesColorMasComprado){
				aparicionesColorMasComprado=contadorAparicionesColor;
				strncpy(colorMasComprado,colorAux,sizeof(colorMasComprado));
			}
		}
		if(aparicionesColorMasComprado>0){
			retorno=OK;
			printf("\nEl color mas comprado fue %s\n",colorMasComprado);
		}
	}
	return retorno;
}

int info_CantidadDeComprasPendientes(sCompraBarbijo*listCompraBarbijo,int lenListCompras){
	int contadorPendientes=0;
	int retorno=ERROR_PARAM;
	if(listCompraBarbijo!=NULL&&lenListCompras>0){
		retorno=ERROR_DATOS;
		for(int i=0;i<lenListCompras;i++){
			if(listCompraBarbijo[i].isEmpty==FALSE && listCompraBarbijo[i].cobro==PENDIENTE ){
				contadorPendientes++;
			}
		}
		if(contadorPendientes>0){
			retorno=OK;
			printf("\nLa cantidad de compras pendientes es: %d\n",contadorPendientes);
		}
	}
	return retorno;
}

int info_CompraConPrecioPorUnidadMasBajo(sCompraBarbijo*listCompraBarbijo,int lenListCompras){
	int retorno=ERROR_PARAM;
	float precioPorUnidad;
	float precioPorUnidadMasBajo=0;
	sCompraBarbijo compraConPrecioPorUnidadMasBajo;
	if(listCompraBarbijo!=NULL&&lenListCompras>0){
		retorno=ERROR_DATOS;
		for(int i=0;i<lenListCompras;i++){
			if(listCompraBarbijo[i].isEmpty==FALSE&&listCompraBarbijo[i].cobro==COBRADA){
				precioPorUnidad=listCompraBarbijo[i].precio/listCompraBarbijo[i].cantBrabijos;
				if(precioPorUnidad>precioPorUnidadMasBajo){
					compraConPrecioPorUnidadMasBajo=listCompraBarbijo[i];
					precioPorUnidadMasBajo=precioPorUnidad;
				}
			}
		}
		if(precioPorUnidadMasBajo>0){
			retorno=OK;
			printf("\nLa compra con el precio por unidad mas bajo es:\n");
			com_Print(&compraConPrecioPorUnidadMasBajo);
			printf("\nCuyo precio por unidad es: %.2f\n",precioPorUnidadMasBajo);
		}
	}
	return retorno;
}

int info_ClienteConMasCompras(int pendientesOPagadas,sCliente*arrayPunterosCliente[],int lenClientes){
	int retorno=ERROR_PARAM;
	int i=0;
	sCliente* pClienteMasCompras;
	int cantMayor;
	if((pendientesOPagadas==PENDIENTE||pendientesOPagadas==COBRADA)&& arrayPunterosCliente!=NULL && lenClientes>0){
		retorno=ERROR_DATOS;
		for(;i<lenClientes;i++){
			if(pendientesOPagadas==COBRADA
					&& arrayPunterosCliente[i]!=NULL
					&& arrayPunterosCliente[i]->cantDeComprasPagadas>cantMayor)
			{
				cantMayor=arrayPunterosCliente[i]->cantDeComprasPagadas;
				pClienteMasCompras=arrayPunterosCliente[i];
			}
			if(pendientesOPagadas==PENDIENTE
					&& arrayPunterosCliente[i]!=NULL
					&& arrayPunterosCliente[i]->cantDeComprasPendientes>cantMayor)
			{
				cantMayor=arrayPunterosCliente[i]->cantDeComprasPendientes;
				pClienteMasCompras=arrayPunterosCliente[i];
			}
		}
		if(pendientesOPagadas==COBRADA&&cantMayor>0){
			printf("\nEl cliente con mas compras pagadas es:\n");
			cli_Print(pClienteMasCompras);
			printf("\nCon %d compras pagadas\n",pClienteMasCompras->cantDeComprasPagadas);
			retorno=OK;
		}
		if(pendientesOPagadas==PENDIENTE&&cantMayor>0){
			printf("\nEl cliente con mas compras pendientes es:\n");
			cli_Print(pClienteMasCompras);
			printf("\nCon %d compras pendientes\n",pClienteMasCompras->cantDeComprasPendientes);
			retorno=OK;
		}
	}
	return retorno;
}

int info_PrintComprasPendientesConCliente(sCompraBarbijo*listadoCompras,int lenCompras,sCliente*arrayPunterosCliente[],int lenClientes){
	int retorno=ERROR_PARAM;
	int i=0;
	int j;
	if(listadoCompras!=NULL && lenCompras>0 && arrayPunterosCliente!=NULL && lenClientes>0){
		retorno=ERROR_DATOS;
		for(;i<lenCompras;i++){
			if(listadoCompras[i].isEmpty==FALSE&&listadoCompras[i].cobro==PENDIENTE){
				com_Print(&listadoCompras[i]);
				j=cli_SearchIndexById(arrayPunterosCliente,lenClientes,listadoCompras[i].idCliente);
				cli_Print(arrayPunterosCliente[j]);
				retorno=OK;
			}
		}
	}
	return retorno;
}
