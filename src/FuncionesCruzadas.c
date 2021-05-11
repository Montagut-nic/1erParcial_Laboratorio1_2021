/*
 * FuncionesCruzadas.c
 *
 *  Created on: 4 may. 2021
 *      Author: Montagut
 */

#include "FuncionesCruzadas.h"

int cruz_AltaDeCliente(sCliente* arrayPunterosCliente[], int longitud){
	int retorno=ERROR_PARAM;
	int idCliente;
	int i;
	if(arrayPunterosCliente!=NULL && longitud>0){
		if(cli_alta(arrayPunterosCliente,longitud,&idCliente)==OK){
			i=cli_SearchIndexById(arrayPunterosCliente, longitud, idCliente);
			printf("\nSu ID de cliente unico es: %d\n",arrayPunterosCliente[i]->idCliente);
			system("pause");
			retorno=OK;
		}
	}
	return retorno;
}

int cruz_BajaDeCliente(sCliente*arrayPunterosCliente[],int lenClientes,sCompraBarbijo*listBarbijos,int lenBarbijos){
	int idCliente;
	int respuesta;
	int i;
	int retorno=ERROR_PARAM;
	if(arrayPunterosCliente!=NULL && listBarbijos!=NULL && lenBarbijos>0 && lenClientes>0){
		retorno=ERROR_DATOS;
		if(utn_getIntLimiteMaxOMin(&idCliente, "\nIngrese el ID del cliente a dar de baja\n",
				"\nError. No se ingreso un ID valido\n",3,1,0,LIM_MIN)==OK
			&& cli_PrintById(arrayPunterosCliente,lenClientes,idCliente)==OK)
		{
			i=cli_SearchIndexById(arrayPunterosCliente,lenClientes,idCliente);
			if(i>=0){
				respuesta=com_bajaTotalCliente(listBarbijos,lenBarbijos,idCliente);
				if(respuesta==TRUE){
					cli_bajaConfirmada(arrayPunterosCliente,lenClientes,i);
					retorno=OK;
					printf("\nBaja de cliente realizada.\n");
				}else{
					printf("\nSe ha cancelado la baja del cliente.\n");
				}
			}
		}
	}
	return retorno;
}

int cruz_RealizarCompra(sCompraBarbijo*listadoCompras,int lenCompras,sCliente*arrayPunterosCliente[],int lenClientes){
	int idCompra;
	int i;
	int j;
	int retorno=ERROR_PARAM;
	if(listadoCompras!=NULL && arrayPunterosCliente!=NULL && lenClientes>0 && lenCompras>0){
		retorno=ERROR_DATOS;
		if(cruz_AltaCompra(listadoCompras, lenCompras, &idCompra,arrayPunterosCliente,lenClientes)==OK){
			retorno=OK;
			i=com_SearchById(listadoCompras, lenCompras, idCompra);
			printf("\nSu ID de compra es: %d\n",listadoCompras[i].idCompra);
			system("pause");
			j=cli_SearchIndexById(arrayPunterosCliente,lenClientes,listadoCompras[i].idCliente);
			arrayPunterosCliente[j]->cantDeCompras+=1;
			arrayPunterosCliente[j]->cantDeComprasPendientes+=1;
		}

	}
	return retorno;
}

int cruz_AltaCompra(sCompraBarbijo* listCompras,int lenCompras,int *idCompra,sCliente*arrayPunterosCliente[],int lenClientes){
    int retorno = ERROR_PARAM;
    int i;
    sCompraBarbijo auxiliarCompra;
    int opcion;
    int respuesta;
    int idCliente;
    if (listCompras!=NULL && lenCompras>0 && idCompra!=NULL && arrayPunterosCliente!=NULL && lenClientes>0){
    	retorno=ERROR_DATOS;
		i = com_SearchEmpty(listCompras, lenCompras);
		if(i>=0)
		{
			if(utn_getIntLimiteMaxOMin(&idCliente, "\nIngrese el ID de cliente:\n",
					"\nError. No se ingreso un ID valido\n",3,1,0,LIM_MIN)==OK
					&&cli_SearchIndexById(arrayPunterosCliente,lenClientes,idCliente)>=0)
			{
				if(utn_getIntLimiteMaxOMin(&auxiliarCompra.cantBrabijos,"\nIngrese la cantidad de barbijos a comprar:\n",
							"\nError. No se ingreso una cantidad valida.\n",3,1,0,LIM_MIN)==OK
						&& utn_getDireccion(auxiliarCompra.direccion,sizeof(auxiliarCompra.direccion),
							"\nIngrese la direccion de entrega:\n","\nError. No se ingreso una direccion valida.\n",3)==OK
						&& utn_getString(auxiliarCompra.color,sizeof(auxiliarCompra.color),
								"\nIngrese el color de los barbijos:\n","\nError. No se ingreso un color valido.\n",3)==OK)
				{
					auxiliarCompra.idCliente=idCliente;
					respuesta=cruz_ShowMenuModificarCompra(&opcion,&auxiliarCompra,arrayPunterosCliente,lenClientes);
					if(respuesta==OK&&opcion==5){
						retorno=OK;
						auxiliarCompra.idCompra = com_GenerateId();
						auxiliarCompra.isEmpty=FALSE;
						auxiliarCompra.cobro=PENDIENTE;
						listCompras[i]=auxiliarCompra;
						*idCompra=listCompras[i].idCompra;
					}
				}
			}
		}else{
			printf("\nNo hay espacios libres en el listado de compras\n");
		}
    }
    return retorno;
}

int cruz_ShowMenuModificarCompra(int*opcion,sCompraBarbijo*compraBuffer,sCliente*arrayPunterosCliente[],int lenClientes){
	int retorno=ERROR_PARAM;
	char mensajePedido[ARRAY_LEN];
	int idExiste;
	if(compraBuffer!=NULL && opcion!=NULL && arrayPunterosCliente!=NULL && lenClientes>0){
		retorno=ERROR_DATOS;
		do{
			snprintf(mensajePedido,ARRAY_LEN,"\nSeleccione una opcion:\n\n"
												"1. Cambiar ID de cliente ( %d )\n"
												"2. Cambiar cantidad de barbijos ( %d )\n"
												"3. Cambiar direccion ( %s )\n"
												"4. Cambiar color de los barabijos ( %s )\n"
												"5. Confirmar y continuar\n"
												"6. Cancelar operacion\n",
												compraBuffer->idCliente,
												compraBuffer->cantBrabijos,
												compraBuffer->direccion,
												compraBuffer->color);
			retorno=utn_getInt(opcion,mensajePedido,"Error. No se ingreso una opcion valida",2,1,5);
			if(retorno==OK){
				switch (*opcion){
					case 1:
						do{
							idExiste=TRUE;
							retorno=utn_getIntLimiteMaxOMin(&compraBuffer->idCliente,"\nIngrese el nuevo ID de cliente",
									"\nError. No se ingreso un ID valido\n",2,1,0,LIM_MIN);
							if(cli_SearchIndexById(arrayPunterosCliente,lenClientes,compraBuffer->idCliente)<0){
								idExiste=FALSE;
							}
						}while(idExiste==FALSE);
						break;
					case 2:
						retorno=utn_getIntLimiteMaxOMin(&compraBuffer->cantBrabijos,"\nIngrese la nueva cantidad de barbijos",
							"\nError. No se ingreso una cantidad valida\n", 2,1,0,LIM_MIN);
						break;
					case 3:
						retorno=utn_getDireccion(compraBuffer->direccion,sizeof(compraBuffer->direccion),
							"\nIngrese la nueva direccion de entrega:\n","\nError. No se ingreso una direccion valida.\n",2);
						break;
					case 4:
						retorno=utn_getString(compraBuffer->color,sizeof(compraBuffer->color),
							"\nIngrese el nuevo color de los barbijos:\n","\nError. No se ingreso un color valido\n",2);
						break;
				}
			}
		}while(*opcion!=5&&*opcion!=6);
	}
	return retorno;
}

int cruz_PagarCompra(sCliente*arrayPunterosCliente[],int lenClientes,sCompraBarbijo*listadoCompras,int lenCompras){
	int idCompra;
	int idCliente;
	int i;
	int retorno=ERROR_PARAM;
	if(arrayPunterosCliente!=NULL && lenClientes>0 && listadoCompras!=NULL && lenCompras>0){
		retorno=ERROR_DATOS;
		if(utn_getIntLimiteMaxOMin(&idCompra,"\nIngrese el ID de la venta:\n",
				"\nError. No se ingreso un ID valido\n",2,1,0,LIM_MIN)==OK)
		{
			i=com_SearchById(listadoCompras, lenCompras, idCompra);
			if(i>=0){
				idCliente=com_SearchIdClienteByIdCompra(listadoCompras, lenCompras, idCompra);
				i=cli_SearchIndexById(arrayPunterosCliente, lenClientes, idCliente);
				cli_Print(arrayPunterosCliente[i]);
				if(com_PagarCompra(listadoCompras, lenCompras, idCompra)==OK){
					retorno=OK;
					arrayPunterosCliente[i]->cantDeComprasPagadas++;
					arrayPunterosCliente[i]->cantDeComprasPendientes--;
				}
			}else{
				printf("\nNo se encontro una venta con ese ID.\n");
			}
		}
	}
	return retorno;
}

int cruz_CancelarCompra(sCompraBarbijo*listadoCompras,int lenCompras,sCliente*arrayPunterosCliente[],int lenClientes){
	int idCompra;
	int idCliente;
	int i;
	int retorno=ERROR_PARAM;
	if(listadoCompras!=NULL && arrayPunterosCliente!=NULL && lenCompras>0 && lenClientes>0){
		retorno=ERROR_DATOS;
		if(utn_getIntLimiteMaxOMin(&idCompra,"\nIngrese el ID de la venta:\n","\nError. No se ingreso un ID valido\n",
				2,1,0,LIM_MIN)==OK)
		{
			idCliente=com_SearchIdClienteByIdCompra(listadoCompras, lenCompras, idCompra);
			if(idCliente>0){
				i=cli_SearchIndexById(arrayPunterosCliente,lenClientes,idCliente);
				if(i>=0){
					cli_Print(arrayPunterosCliente[i]);
					if(com_baja(listadoCompras, lenCompras, idCompra)==OK){
						arrayPunterosCliente[i]->cantDeCompras--;
						arrayPunterosCliente[i]->cantDeComprasPendientes--;
					}
					retorno=OK;
				}
			}else{
				printf("\nNo se encontro una venta con ese ID.\n");
			}
		}
	}
	return retorno;
}

int cruz_InitListas(sCliente*arrayPunterosCliente[],int lenListaClientes,sCompraBarbijo*listaCompras,int lenListaCompras)
{
	int retorno=ERROR_PARAM;
	if(arrayPunterosCliente!=NULL && listaCompras!=NULL && lenListaClientes>0 && lenListaCompras>0){
		retorno=ERROR_DATOS;
		if(cli_InitializeArrayPunterosCliente(arrayPunterosCliente, lenListaClientes)==OK
			&& com_InitializeList(listaCompras, lenListaCompras)==OK)
		{
			retorno=OK;
		}
	}
	return retorno;
}
