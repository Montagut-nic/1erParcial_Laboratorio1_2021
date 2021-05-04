/*
 * Compras.c
 *
 *  Created on: 4 may. 2021
 *      Author: Montagut
 */
#include "Compras.h"

int idCompra_autoIncremental=0;

int com_InitializeList(sCompraBarbijo* list, int len){
	int retorno=ERROR_PARAM;
	int i=0;
	if (list!=NULL && len>0){
		for (;i<len;i++){
			list[i].isEmpty=TRUE;
		}
		retorno = OK;
	}
	return retorno;
}

int com_SearchEmpty (sCompraBarbijo* list, int len){
	int retorno = ERROR_PARAM;
	int i=0;
	if(list!=NULL && len>0){
		for (;i<len;i++){
			if (list[i].isEmpty==TRUE){
				retorno=i;
				break;
			}
		}
	}
    return retorno;
}

int com_SearchById(sCompraBarbijo* list, int len, int id){
	int i=0;
	int retorno=ERROR_PARAM;
	if(list!=NULL && len>0 && id<=len && id>0){
		for(; i<len; i++){
			if(list[i].idCompra==id){
				retorno=i;
				break;
			}
		}
	}
	return retorno;
}

int com_SearchIdClienteByIdCompra(sCompraBarbijo* list, int len, int id){
	int i=0;
	int retorno=ERROR_PARAM;
	if(list!=NULL && len>0 && id<=len && id>0){
		for(; i<len; i++){
			if(list[i].idCompra==id){
				retorno=list[i].idCliente;
				break;
			}
		}
	}
	return retorno;
}

int com_Print (sCompraBarbijo* list){
	int retorno=ERROR_PARAM;
	if(list!=NULL&&list->isEmpty==FALSE){
		retorno =ERROR_DATOS;
		if(list->cobro==PENDIENTE){
			retorno = OK;
			printf("\nID DE COMPRA: %d -- COLOR: %s / DIRECCION: %s / CANTIDAD: %d / ESTADO: PENDIENTE\n",list->idCompra,list->color,list->direccion, list->cantBrabijos);
		}else if (list->cobro==COBRADA){
			retorno = OK;
			printf("\nID DE COMPRA: %d -- COLOR: %s / DIRECCION: %s / CANTIDAD: %d / ESTADO: COBRADA / IMPORTE: %.2f \n",list->idCompra,list->color,list->direccion, list->cantBrabijos,list->precio);
		}
	}
    return retorno;
}

int com_PrintList(sCompraBarbijo* list, int len){
	int retorno=ERROR_PARAM;
    int i=0;
    if(list!=NULL && len>0){
    	retorno=OK;
		for(;i<len;i++){
			com_Print(&list[i]);
		}
    }
    return retorno;
}

int com_PrintListByIdCliente(sCompraBarbijo* list, int len, int id){
	int retorno=ERROR_PARAM;
    int i=0;
    if(list!=NULL && len>0&&id>0){
    	retorno=ERROR_DATOS;
		for(;i<len;i++){
			if(list[i].idCliente==id&&list[i].isEmpty==FALSE){
				retorno=OK;
				com_Print(&list[i]);
			}
		}
    }
    return retorno;
}

int com_GenerateId(){
	return idCompra_autoIncremental+=1;
}

int com_bajaTotalCliente(sCompraBarbijo* list,int len,int idCliente){
    int i;
    int respuesta;
    int confirmacion;
    int retorno=ERROR_PARAM;
    if(list!=NULL&&len>0&&idCliente>0){
    	retorno=ERROR_DATOS;
    	printf("\nCompras del cliente:\n");
		if(com_PrintListByIdCliente(list, len, idCliente)!=OK){
			printf("\nNo ha realizado ninguna compra todavia.\n");
		}
		respuesta=utn_getInt(&confirmacion, "\nEsta es toda informacion del cliente.\nTodo sera dado de baja, desea continuar? [CONTINUAR:1] [CANCELAR:0]\n","\nError. No se ingreso una opcion valida. Ingrese 1 o 0.\n",3,0,1);
		if(respuesta==OK){
			if(confirmacion==TRUE){
				for(i=0;i<len;i++){
					if(list[i].isEmpty==FALSE&&list[i].idCliente==idCliente){
						list[i].isEmpty=TRUE;
					}
				}
			}
			retorno=confirmacion;
		}
    }
    return retorno;
}

int com_baja(sCompraBarbijo* list,int len,int idCompra){
    int retorno=ERROR_PARAM;
    int i;
    int respuesta;
    if(list!=NULL&&len>0&&idCompra>0){
    	retorno=ERROR_DATOS;
    	i=com_SearchById(list,len,idCompra);
		if(i>=0&&list[i].isEmpty==FALSE){
			if(list[i].cobro==COBRADA){
				if(utn_getInt(&respuesta, "\nSeguro desea cancelar la compra?\n[SI:1] [NO:0]\n", "\nError. No se ingreso una opcion valida.\n",2,0,1)==OK
						&& respuesta==TRUE){
					list[i].isEmpty=TRUE;
					printf("\nCompra cancelada.\n");
				}else{
					printf("\nLa compra no se ha cancelado\n");
				}
			}else{
				printf("\nError. Solo se puede cancelar una compra pendiente\n");
			}
			retorno=OK;
		}
    }
    return retorno;
}



int com_Modificar(sCompraBarbijo* list,int len){
    int id;
    int i;
    int retorno=ERROR_PARAM;
    int respuesta;
    int opcion;
    sCompraBarbijo auxiliarStruct;
    if(len > 0 && list != NULL)
    {
    	retorno=ERROR_DATOS;
    	respuesta=utn_getInt(&id, "\nIngrese el ID del cliente a modificar: \n", "\nUsted ha ingresado un ID incorrecto.\n", 5, 1, len);
    	if(respuesta==OK){
    		i=com_SearchById(list, len, id);
    		if(i>=0&&list[i].isEmpty==FALSE){
    			auxiliarStruct=list[i];
    			retorno=com_ShowMenuModificar(&opcion,&auxiliarStruct);
    			if(retorno==OK&&opcion==5){
    				list[i]=auxiliarStruct;
    			}
    		}else{
    			printf("\nNo hay ningun cliente con ese ID.\n");
    		}
    	}
    }
    return retorno;
}



int com_PagarCompra(sCompraBarbijo*list,int longitud,int idCompra){
	int retorno=ERROR_PARAM;
	int i;
	int respuesta;
	sCompraBarbijo auxiliar;
	if(list!=NULL && longitud>0 && idCompra>0){
		retorno=ERROR_DATOS;
		i=com_SearchById(list, longitud, idCompra);
		respuesta=utn_getFloatLimiteMinOMax(&auxiliar.precio, "\nIngrese el importe pagado:\n", "\nError. No se ingreso un importe valido\n", 2, 1, 0,LIM_MIN);
		if(respuesta==OK){
			retorno=OK;
			if(utn_getInt(&respuesta, "\nLa venta pasara a estar cobrada.\nDesea confirmar? [SI:1] [NO:0]\n", "\nError. No se ingreso una opcion valida.\n", 3, 0, 1)==OK
					&& respuesta==TRUE){
				list[i].precio=auxiliar.precio;
				list[i].cobro=COBRADA;
				printf("\nCarga de importe confirmado\n");
			}else{
				printf("\nCarga de importe cancelado\n");
			}
		}
	}
	return retorno;
}

int com_ordenarPorSTRINGCHAR(sCompraBarbijo* list, int len){
	int flagSwap;
	int retorno=ERROR_PARAM;
    sCompraBarbijo auxiliarEntidad;
    int i=0;
    if(list!=NULL&&len>0){
    	retorno=OK;
		do{
			flagSwap=0;
			for(;i<len-1;i++){
				if(list[i].isEmpty==TRUE||list[i+1].isEmpty==TRUE){
					continue;
				}
				if(strncmp(list[i].color,list[i+1].color,COL_LEN)>0){
					flagSwap=1;
					auxiliarEntidad=list[i];
					list[i]=list[i+1];
					list[i+1]=auxiliarEntidad;
				}
			}
			len--;
		}while(flagSwap);
    }
    return retorno;
}
