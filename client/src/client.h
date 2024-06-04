#ifndef CLIENT_H_
#define CLIENT_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include "utils.h"

typedef struct{
    uint16_t AX;             //Registro Numérico de propósito general
    uint16_t BX;             //Registro Numérico de propósito general
    uint16_t CX;             //Registro Numérico de propósito general
    uint16_t DX;             //Registro Numérico de propósito general
    uint32_t EAX;           //Registro Numérico de propósito general
    uint32_t EBX;           //Registro Numérico de propósito general
    uint32_t ECX;           //Registro Numérico de propósito general
    uint32_t EDX;           //Registro Numérico de propósito general
}registros_generales;

typedef struct{
    pid_t pid;
    uint32_t program_counter;
    uint16_t vQuantum;
    registros_generales regitros; 
}PCB_data;

t_log* iniciar_logger(void);
t_config* iniciar_config(void);
void leer_consola(t_log*);
void paquete(int);
void paqueteTest(int conexion);
void paquetePCB(int conexion, PCB_data *pcb);
void terminar_programa(int, t_log*, t_config*);

#endif /* CLIENT_H_ */
