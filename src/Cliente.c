/*
 * Cliente.c
 *
 *  Created on: 1 may. 2021
 *      Author: Montagut
 */

#include "cliente.h"

int idCliente_autoIncremental=0;

int cli_InitializeList(sCliente* list, int len){
	int retorno=ERROR_PARAM;
	int i=0;
	if (list!=NULL && len>0){
		for (;i<len;i++){
			list[i].isEmpty=VACIO;
		}
		retorno = OK;
	}
	return retorno;
}

int cli_SearchEmpty (sCliente* list, int len){
	int retorno = ERROR_PARAM;
	int i=0;
	if(list!=NULL && len>0){
		retorno=ERROR_DATOS;
		for (;i<len;i++){
			if (list[i].isEmpty==VACIO){
				retorno=i;
				break;
			}
		}
		if(retorno<0){
			printf("\nNo hay espacios libres en el listado de clientes\n");
		}
	}
    return retorno;
}

int cli_SearchById(sCliente* list, int len, int id){
	int i=0;
	int retorno=ERROR_PARAM;
	if(list!=NULL && len>0 && id<=len && id>0){
		for(; i<len; i++){
			retorno=ERROR_DATOS;
			if(list[i].idCliente==id){
				retorno=i;
				break;
			}
		}
	}
	return retorno;
}

int cli_SearchByCuit(sCliente* list, int len, char* cuit){
	int i=0;
	int retorno=ERROR_PARAM;
	if(list!=NULL && len>0 && cuit!=NULL){
		for(; i<len; i++){
			retorno=ERROR_DATOS;
			if(strncmp(list[i].cuit,cuit,sizeof(list[i].cuit))==0){
				retorno=i;
				break;
			}
		}
	}
	return retorno;
}

int cli_Print (sCliente* list){
	int retorno=ERROR_PARAM;
	if(list!=NULL&&list->isEmpty==OCUPADO){
		retorno = OK;
		printf("\nID: %d -- NOMBRE: %s / APELLIDO: %s / CUIT: %s / CANTIDAD DE COMPRAS: %d\n",list->idCliente,list->nombre,list->apellido, list->cuit,list->cantDeCompras);

	}
    return retorno;
}

int cli_PrintList(sCliente* list, int len){
	int retorno=ERROR_PARAM;
    int i=0;
    if(list!=NULL && len>0){
		for(;i<len;i++){
			if(cli_Print(&list[i])==OK){
				retorno=OK;
			}
		}
    }
    return retorno;
}

int cli_PrintById(sCliente* list, int len,int id){
	int retorno=ERROR_PARAM;
	int i;
	if(list!=NULL&&len>0&&id>0){
		retorno=ERROR_DATOS;
		i=cli_SearchById(list, len, id);
		if(i>=OK&&list[i].isEmpty==FALSE){
			retorno = OK;
			cli_Print(&list[i]);
		}else{
			printf("No se ha encontrado un cliente con ese ID");
		}
	}
    return retorno;
}

int cli_GenerateId(){
	return idCliente_autoIncremental+=1;
}

int cli_alta(sCliente* list,int len,int *id){
    int retorno = ERROR_PARAM;
    int i;
    sCliente auxiliarStruct;
    int opcion;
    int respuesta;
    int flagCuitRepetido;
    if (list!=NULL && len>0&&id!=NULL){
    	retorno=ERROR_DATOS;
		i = cli_SearchEmpty(list, len);
		if(i>=0
				&& utn_getNombre(auxiliarStruct.nombre,sizeof(auxiliarStruct.nombre),"\nIngrese su nombre:\n","\nError. No es un nombre valido\n",3)==OK
				&& utn_getNombre(auxiliarStruct.apellido,sizeof(auxiliarStruct.apellido),"\nIngrese su apellido:\n","\nError. No es un apellido valido\n",3)==OK
				)
		{
			do{
				flagCuitRepetido=FALSE;
				respuesta=utn_getCuit(auxiliarStruct.cuit,sizeof(auxiliarStruct.cuit),"\nIngrese su cuit:\n","\nError. No es un cuit valido.\n",3);
				if(respuesta==OK && cli_SearchByCuit(list, len, auxiliarStruct.cuit)>=0){
					flagCuitRepetido=TRUE;
					printf("\nEl cuit inrgesado ya esta registrado. Intente nuevamente.\n");
				}
			}while(flagCuitRepetido);
			if(respuesta==OK){
				respuesta=cli_ShowMenuModificar(&opcion, &auxiliarStruct,list,len);
				if(respuesta==OK&&opcion==4){
					retorno=OK;
					auxiliarStruct.idCliente = cli_GenerateId();
					auxiliarStruct.isEmpty=OCUPADO;
					auxiliarStruct.cantDeCompras=0;
					auxiliarStruct.cantDeComprasPagadas=0;
					auxiliarStruct.cantDeComprasPendientes=0;
					list[i]=auxiliarStruct;
					*id=list[i].idCliente;
				}
			}
		}
    }
    return retorno;
}

int cli_bajaConfirmada(sCliente* list,int len,int i){
    int retorno=ERROR_PARAM;
    if(list!=NULL&&len>0&&i>=0&&list[i].isEmpty==OCUPADO){
		list[i].isEmpty=VACIO;
		retorno=OK;
    }
    return retorno;
}

int cli_Modificar(sCliente* list,int len){
    int id;
    int i;
    int retorno=ERROR_PARAM;
    int respuesta;
    int opcion;
    sCliente auxiliarStruct;
    if(len > 0 && list != NULL)
    {
    	retorno=ERROR_DATOS;
    	respuesta=utn_getInt(&id, "\nIngrese el ID del cliente a modificar: \n", "\nUsted ha ingresado un ID incorrecto.\n", 5, 1, len);
    	if(respuesta==OK){
    		i=cli_SearchById(list, len, id);
    		if(i>=0&&list[i].isEmpty==OCUPADO){
    			auxiliarStruct=list[i];
    			retorno=cli_ShowMenuModificar(&opcion,&auxiliarStruct,list,len);
    			if(retorno==OK&&opcion==4){
    				list[i]=auxiliarStruct;
    			}
    		}else{
    			printf("\nNo hay ningun cliente con ese ID.\n");
    		}
    	}
    }
    return retorno;
}

int cli_ShowMenuModificar(int*opcion,sCliente*structBuffer,sCliente*list,int len){
	int retorno=ERROR_PARAM;
	char mensajePedido[ARRAY_LEN];
	int flagCuitRepetido;
	if(structBuffer!=NULL&&opcion!=NULL&&list!=NULL&&len>0){
		retorno=ERROR_DATOS;
		do{
			snprintf(mensajePedido,ARRAY_LEN,"\nSeleccione una opcion:\n\n"
												"1. Cambiar nombre ( %s )\n"
												"2. Cambiar apellido ( %s )\n"
												"3. Cambiar cuit ( %s )\n"
												"4. Confirmar y continuar\n"
												"5. Cancelar operacion\n",structBuffer->nombre,structBuffer->apellido,structBuffer->cuit);
			retorno=utn_getInt(opcion,mensajePedido , "Error. No se ingreso una opcion valida", 2, 1, 5);
			if(retorno==OK){
				switch (*opcion){
					case 1:
						retorno=utn_getNombre(structBuffer->nombre,sizeof(structBuffer->nombre),"\nIngrese el nuevo nombre:\n","\nError. No se ingreso un nombre valido.\n", 2);
						break;
					case 2:
						retorno=utn_getNombre(structBuffer->apellido,sizeof(structBuffer->apellido),"\nIngrese el nuevo apellido:\n", "\nError. No se ingreso un apellido valido.\n", 2);
						break;
					case 3:
						do{
							flagCuitRepetido=FALSE;
							retorno=utn_getCuit(structBuffer->cuit,sizeof(structBuffer->cuit),"\nIngrese el nuevo cuit:\n", "\nError. No se ingreso un cuit valido\n", 2);
							if(retorno==OK&&cli_SearchByCuit(list, len, structBuffer->cuit)>=0){
								flagCuitRepetido=TRUE;
								printf("\nEl cuit inrgesado ya esta registrado. Intente nuevamente.\n");
							}
						}while(flagCuitRepetido);
						break;
				}
			}
		}while(*opcion!=4&&*opcion!=5);
	}
	return retorno;
}

