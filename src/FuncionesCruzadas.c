/*
 * FuncionesCruzadas.c
 *
 *  Created on: 4 may. 2021
 *      Author: Montagut
 */

#include "FuncionesCruzadas.h"

int cruz_AltaDeCliente(sCliente* list, int longitud){
	int retorno=ERROR_PARAM;
	int idCliente;
	int i;
	if(list!=NULL&&longitud>0){
		if(cli_alta(list,longitud,&idCliente)==OK){
			i=cli_SearchById(list, longitud, idCliente);
			printf("\nSu ID de cliente unico es: %d\n",list[i].idCliente);
			system("pause");
			retorno=OK;
		}
	}
	return retorno;
}

int cruz_BajaDeCliente(sCliente*listClientes, int lenClientes,sCompraBarbijo*listBarbijos,int lenBarbijos){
	int idCliente;
	int respuesta;
	int i;
	int retorno=ERROR_PARAM;
	if(listClientes!=NULL && listBarbijos!=NULL && lenBarbijos>0 && lenClientes>0){
		retorno=ERROR_DATOS;
		if(utn_getIntLimiteMaxOMin(&idCliente, "\nIngrese el ID del cliente a dar de baja\n", "\nError. No se ingreso un ID valido\n",3,1,0,LIM_MIN)==OK
				&& cli_PrintById(listClientes,lenClientes,idCliente)==OK)
		{
			respuesta=com_bajaTotalCliente(listBarbijos,lenBarbijos,idCliente);
			if(respuesta==TRUE){
				cli_bajaConfirmada(listClientes,lenClientes,i);
				printf("\nBaja de cliente realizada.\n");
			}else{
				printf("\nSe ha cancelado la baja del cliente.\n");
			}
			retorno=OK;
		}
	}
	return retorno;
}

int cruz_RealizarCompra(sCompraBarbijo* listadoCompras,int lenCompras, sCliente* listadoClientes, int lenClientes){
	int idCliente;
	int idCompra;
	int i;
	int retorno=ERROR_PARAM;
	if(listadoCompras!=NULL && listadoClientes!=NULL && lenClientes>0 && lenCompras>0){
		retorno=ERROR_DATOS;
		if(utn_getIntLimiteMaxOMin(&idCliente, "\nIngrese el ID de cliente:\n", "\nError. No se ingreso un ID valido\n",3,1,0,LIM_MIN)==OK
				&&cli_SearchById(listadoClientes, lenClientes, idCliente)>=0)
		{
			if(cruz_AltaCompra(listadoCompras, lenCompras, &idCompra,idCliente,listadoClientes,lenClientes)==OK){
				retorno=OK;
				i=com_SearchById(listadoCompras, lenCompras, idCompra);
				printf("\nSu ID de compra es: %d\n",listadoCompras[i].idCompra);
				system("pause");
				i=cli_SearchById(listadoClientes, lenClientes, idCliente);
				listadoClientes[i].cantDeCompras++;
			}
		}else{
			printf("\nNo se encontro un cliente con ese ID\n");
		}
	}
	return retorno;
}

int cruz_AltaCompra(sCompraBarbijo* listCompras,int lenCompras,int *idCompra,int idCliente,sCliente*listClientes,int lenClientes){
    int retorno = ERROR_PARAM;
    int i;
    sCompraBarbijo auxiliarStruct;
    int opcion;
    int respuesta;
    if (listCompras!=NULL && lenCompras>0&&idCompra!=NULL&&listClientes!=NULL&&lenClientes>0){
    	retorno=ERROR_DATOS;
		i = com_SearchEmpty(listCompras, lenCompras);
		if(i>=0
				&& utn_getIntLimiteMaxOMin(&auxiliarStruct.cantBrabijos, "\nIngrese la cantidad de barbijos a comprar:\n", "\nError. No se ingreso una cantidad valida.\n",3,1,0,LIM_MIN)==OK
				&& utn_getDireccion(auxiliarStruct.direccion, sizeof(auxiliarStruct.direccion), "\nIngrese la direccion de entrega:\n", "\nError. No se ingreso una direccion valida.\n", 3)==OK
				&& utn_getString(auxiliarStruct.color, sizeof(auxiliarStruct.color), "\nIngrese el color de los barbijos:\n", "\nError. No se ingreso un color valido\n", 3)==OK
				)
		{
			auxiliarStruct.idCliente=idCliente;
			respuesta=cruz_ShowMenuModificarCompra(&opcion, &auxiliarStruct,listClientes,lenClientes);
			if(respuesta==OK&&opcion==5){
				retorno=OK;
				auxiliarStruct.idCompra = com_GenerateId();
				auxiliarStruct.isEmpty=FALSE;
				auxiliarStruct.cobro=PENDIENTE;
				listCompras[i]=auxiliarStruct;
				*idCompra=listCompras[i].idCompra;
			}
		}
    }
    return retorno;
}

int cruz_ShowMenuModificarCompra(int*opcion,sCompraBarbijo*structBuffer,sCliente*listadoClientes, int lenClientes){
	int retorno=ERROR_PARAM;
	char mensajePedido[ARRAY_LEN];
	int idExiste;
	if(structBuffer!=NULL&&opcion!=NULL&&listadoClientes!=NULL&&lenClientes>0){
		retorno=ERROR_DATOS;
		do{
			snprintf(mensajePedido,ARRAY_LEN,"\nSeleccione una opcion:\n\n"
												"1. Cambiar ID de cliente ( %d )\n"
												"2. Cambiar cantidad de barbijos ( %d )\n"
												"3. Cambiar direccion ( %s )\n"
												"4. Cambiar color de los barabijos ( %s )\n"
												"5. Confirmar y continuar\n"
												"6. Cancelar operacion\n",structBuffer->idCliente,structBuffer->cantBrabijos,structBuffer->direccion,structBuffer->color);
			retorno=utn_getInt(opcion,mensajePedido , "Error. No se ingreso una opcion valida", 2, 1, 5);
			if(retorno==OK){
				switch (*opcion){
					case 1:
						do{
							idExiste=TRUE;
							retorno=utn_getIntLimiteMaxOMin(&structBuffer->idCliente, "\nIngrese el nuevo ID de cliente", "\nError. No se ingreso un ID valido\n", 2,1,0,LIM_MIN);
							if(cli_SearchById(listadoClientes, lenClientes, structBuffer->idCliente)>=0){
								idExiste=FALSE;
								printf("\nNo se encontro un cliente con ese ID\n");
							}
						}while(idExiste==FALSE);
						break;
					case 2:
						retorno=utn_getIntLimiteMaxOMin(&structBuffer->cantBrabijos, "\nIngrese la nueva cantidad de barbijos", "\nError. No se ingreso una cantidad valida\n", 2,1,0,LIM_MIN);
						break;
					case 3:
						retorno=utn_getDireccion(structBuffer->direccion, sizeof(structBuffer->direccion), "\nIngrese la nueva direccion de entrega:\n", "\nError. No se ingreso una direccion valida.\n", 2);
						break;
					case 4:
						retorno=utn_getString(structBuffer->color, sizeof(structBuffer->color), "\nIngrese el nuevo color de los barbijos:\n", "\nError. No se ingreso un color valido\n", 2);
						break;
				}
			}
		}while(*opcion!=5&&*opcion!=6);
	}
	return retorno;
}
