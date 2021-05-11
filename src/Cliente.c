/*
 * Cliente.c
 *
 *  Created on: 1 may. 2021
 *      Author: Montagut
 */

#include "cliente.h"

int idCliente_autoIncremental=0;

int cli_InitializeArrayPunterosCliente(sCliente* arrayPunterosCliente[],int len){
	sCliente** auxiliarCliente;
	int i=0;
	int retorno=ERROR_PARAM;
	if(arrayPunterosCliente!=NULL&&len>0){
		retorno=ERROR_DATOS;
		auxiliarCliente=(sCliente**)malloc(sizeof(sCliente*));
		if(auxiliarCliente!=NULL){
			auxiliarCliente=(sCliente**)realloc(auxiliarCliente,sizeof(sCliente*)*len);
			if(auxiliarCliente!=NULL){
				arrayPunterosCliente=auxiliarCliente;
				for(;i<len;i++){
					retorno=OK;
					arrayPunterosCliente[i]=NULL;
				}
			}
		}
	}
	return retorno;
}

int cli_SearchEmptyIndex(sCliente* arrayPunterosCliente[], int len){
	int retorno = ERROR_PARAM;
	int i=0;
	if(arrayPunterosCliente!=NULL && len>0){
		retorno=ERROR_DATOS;
		for (;i<len;i++){
			if(arrayPunterosCliente[i]==NULL){
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

int cli_SearchIndexById(sCliente* arrayPunterosCliente[], int len, int id){
	int i=0;
	int retorno=ERROR_PARAM;
	if(arrayPunterosCliente!=NULL && len>0 && id>0){
		for(; i<len; i++){
			retorno=ERROR_DATOS;
			if(arrayPunterosCliente[i]!=NULL && arrayPunterosCliente[i]->idCliente==id){
				retorno=i;
				break;
			}
		}
		if(retorno<0){
			printf("\nNo se encontro ese ID en el listado de clientes\n");
		}
	}
	return retorno;
}

int cli_SearchIndexByCuit(sCliente* arrayPunterosCliente[], int len, char* cuit){
	int i=0;
	int retorno=ERROR_PARAM;
	if(arrayPunterosCliente!=NULL && len>0 && cuit!=NULL){
		retorno=ERROR_DATOS;
		for(; i<len; i++){
			if(arrayPunterosCliente[i]!=NULL
				&& strncmp(arrayPunterosCliente[i]->cuit,cuit,sizeof(arrayPunterosCliente[i]->cuit))==0)
			{
				retorno=i;
				break;
			}
		}
		if(retorno<0){
			printf("\nNo se encontro ese CUIT en el listado de clientes\n");
		}
	}
	return retorno;
}

int cli_Print (sCliente* PunteroCliente){
	int retorno=ERROR_PARAM;
	if(PunteroCliente!=NULL){
		retorno = OK;
		printf("\nID: %d -- NOMBRE: %s / APELLIDO: %s / CUIT: %s / CANTIDAD DE COMPRAS: %d\n",
				PunteroCliente->idCliente,
				PunteroCliente->nombre,
				PunteroCliente->apellido,
				PunteroCliente->cuit,
				PunteroCliente->cantDeCompras);
	}
    return retorno;
}

int cli_PrintList(sCliente* arrayPunterosCliente[], int len){
	int retorno=ERROR_PARAM;
    int i=0;
    if(arrayPunterosCliente!=NULL && len>0){
		for(;i<len;i++){
			if(cli_Print(arrayPunterosCliente[i])==OK){
				retorno=OK;
			}
		}
    }
    return retorno;
}

int cli_PrintById(sCliente* arrayPunterosCliente[], int len,int id){
	int retorno=ERROR_PARAM;
	int i;
	if(arrayPunterosCliente!=NULL&&len>0&&id>0){
		retorno=ERROR_DATOS;
		i=cli_SearchIndexById(arrayPunterosCliente, len, id);
		if(i>=0&&arrayPunterosCliente[i]!=NULL){
			retorno = OK;
			cli_Print(arrayPunterosCliente[i]);
		}
	}
    return retorno;
}

int cli_GenerateId(void){
	return idCliente_autoIncremental+=1;
}

sCliente* cli_new(void){
	sCliente* auxiliarCli;
	auxiliarCli=(sCliente*)malloc(sizeof(sCliente));
	if(auxiliarCli!=NULL){
		auxiliarCli->apellido[0]='\0';
		auxiliarCli->cuit[0]='\0';
		auxiliarCli->nombre[0]='\0';
		auxiliarCli->cantDeCompras=0;
		auxiliarCli->cantDeComprasPagadas=0;
		auxiliarCli->cantDeComprasPendientes=0;
		auxiliarCli->idCliente=0;
		return auxiliarCli;
	}else{
		return NULL;
	}
}

int cli_alta(sCliente* arrayPunterosCliente[],int len,int *id){
    int retorno = ERROR_PARAM;
    int i;
    sCliente* auxPunteroCliente=cli_new();
    int opcion;
    int respuesta;
    int flagCuitRepetido;
    if (arrayPunterosCliente!=NULL && len>0 && id!=NULL && auxPunteroCliente!=NULL){
    	retorno=ERROR_DATOS;
		i = cli_SearchEmptyIndex(arrayPunterosCliente, len);
		if(i>=0
				&& utn_getNombre(auxPunteroCliente->nombre,sizeof(auxPunteroCliente->nombre),"\nIngrese su nombre:\n",
						"\nError. No se ingreso un nombre valido\n",3)==OK
				&& utn_getNombre(auxPunteroCliente->apellido,sizeof(auxPunteroCliente->apellido),"\nIngrese su apellido:\n",
						"\nError. No se ingreso un apellido valido\n",3)==OK )
		{
			do{
				flagCuitRepetido=FALSE;
				respuesta=utn_getCuit(auxPunteroCliente->cuit,sizeof(auxPunteroCliente->cuit),"\nIngrese su cuit:\n",
						"\nError. No se ingreso un cuit valido.\n",3);
				if(respuesta==OK
					&& cli_SearchIndexByCuit(arrayPunterosCliente, len, auxPunteroCliente->cuit)>=0)
				{
					flagCuitRepetido=TRUE;
					printf("\nEl cuit inrgesado ya esta registrado. Intente nuevamente.\n");
				}
			}while(flagCuitRepetido);
			if(respuesta==OK){
				respuesta=cli_ShowMenuModificar(&opcion,auxPunteroCliente,arrayPunterosCliente,len);
				if(respuesta==OK&&opcion==4){
					retorno=OK;
					auxPunteroCliente->idCliente = cli_GenerateId();
					arrayPunterosCliente[i]=auxPunteroCliente;
					*id=arrayPunterosCliente[i]->idCliente;
				}
			}
		}
    }
    return retorno;
}

int cli_bajaConfirmada(sCliente* arrayPunterosCliente[],int len,int i){
    int retorno=ERROR_PARAM;
    if(arrayPunterosCliente!=NULL && len>0 && i>=0 && arrayPunterosCliente[i]!=NULL){
		free(arrayPunterosCliente[i]);
		arrayPunterosCliente[i]=NULL;
		retorno=OK;
    }
    return retorno;
}

int cli_Modificar(sCliente* arrayPunterosCliente[],int len){
    int id;
    int i;
    int retorno=ERROR_PARAM;
    int respuesta;
    int opcion;
    sCliente* auxPunteroCliente=cli_new();
    if(len > 0 && arrayPunterosCliente != NULL && auxPunteroCliente!=NULL)
    {
    	retorno=ERROR_DATOS;
    	respuesta=utn_getIntLimiteMaxOMin(&id,"\nIngrese el ID del cliente a modificar: \n",
    			"\nUsted ha ingresado un ID incorrecto.\n",3,1,0,LIM_MIN);
    	if(respuesta==OK){
    		i=cli_SearchIndexById(arrayPunterosCliente, len, id);
    		if(i>=0 && arrayPunterosCliente[i]!=NULL){
    			(*auxPunteroCliente)=(*arrayPunterosCliente[i]);
    			retorno=cli_ShowMenuModificar(&opcion,auxPunteroCliente,arrayPunterosCliente,len);
    			if(retorno==OK&&opcion==4){
    				free(arrayPunterosCliente[i]);
    				arrayPunterosCliente[i]=auxPunteroCliente;
    			}
    		}
    	}
    }
    return retorno;
}

int cli_ShowMenuModificar(int*opcion,sCliente*auxPunteroCliente,sCliente*arrayPunterosCliente[],int len){
	int retorno=ERROR_PARAM;
	char mensajePedido[ARRAY_LEN];
	int flagCuitRepetido;
	if(auxPunteroCliente!=NULL && opcion!=NULL && arrayPunterosCliente!=NULL && len>0){
		retorno=ERROR_DATOS;
		do{
			snprintf(mensajePedido,ARRAY_LEN,"\nSeleccione una opcion:\n\n"
												"1. Cambiar nombre ( %s )\n"
												"2. Cambiar apellido ( %s )\n"
												"3. Cambiar cuit ( %s )\n"
												"4. Confirmar y continuar\n"
												"5. Cancelar operacion\n",
												auxPunteroCliente->nombre,
												auxPunteroCliente->apellido,
												auxPunteroCliente->cuit);
			retorno=utn_getInt(opcion,mensajePedido,"Error. No se ingreso una opcion valida", 2, 1, 5);
			if(retorno==OK){
				switch (*opcion){
					case 1:
						retorno=utn_getNombre(auxPunteroCliente->nombre,sizeof(auxPunteroCliente->nombre),
								"\nIngrese el nuevo nombre:\n","\nError. No se ingreso un nombre valido.\n", 2);
						break;
					case 2:
						retorno=utn_getNombre(auxPunteroCliente->apellido,sizeof(auxPunteroCliente->apellido),
								"\nIngrese el nuevo apellido:\n", "\nError. No se ingreso un apellido valido.\n", 2);
						break;
					case 3:
						do{
							flagCuitRepetido=FALSE;
							retorno=utn_getCuit(auxPunteroCliente->cuit,sizeof(auxPunteroCliente->cuit),
									"\nIngrese el nuevo cuit:\n", "\nError. No se ingreso un cuit valido\n", 2);
							if(retorno==OK && cli_SearchIndexByCuit(arrayPunterosCliente, len, auxPunteroCliente->cuit)>=0)
							{
								flagCuitRepetido=TRUE;
								printf("\nEl cuit inrgesado ya esta registrado. Intentelo nuevamente.\n");
							}
						}while(flagCuitRepetido);
						break;
				}
			}
		}while(*opcion!=4&&*opcion!=5);
	}
	return retorno;
}

