#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	valor = config_get_string_value(config, "CLAVE");
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");

	// Loggeamos el valor de config
	log_info(logger, valor);

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion);	

	// Armamos y enviamos el paquete
	// paquete(conexion);
	// paqueteTest(conexion);
	PCB_data *pcb = malloc(sizeof(PCB_data));
	pcb->pid = 15;
	pcb->program_counter = 20;
	pcb->vQuantum = 0;
	pcb->regitros.AX = 40;
	pcb->regitros.BX = 50;
	pcb->regitros.CX = 60;
	pcb->regitros.DX = 70;
	pcb->regitros.EAX = 140;
	pcb->regitros.EBX = 150;
	pcb->regitros.ECX = 160;
	pcb->regitros.EDX = 170;

	paquetePCB(conexion, pcb);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("tp0.log", "NUEVO_LOG", true, LOG_LEVEL_INFO);

	if (nuevo_logger == NULL) {
		
		perror("Error al iniciar log");
		exit(EXIT_FAILURE);
	}

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = config_create("/home/utnso/tp0/client/cliente.config");

	if (nuevo_config == NULL) {

		perror("Error al iniciar config");
		exit(EXIT_FAILURE);
	}

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	while (strcmp(leido, "")) {

		log_info(logger, leido);
		free(leido);
		leido = readline("> ");
	}

	// ¡No te olvides de liberar las lineas antes de regresar!
	free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete
	leido = readline ("> ");
	while (strcmp(leido, "")) {
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);// +1 para char fin str
		free(leido);
		leido = readline ("> ");
	}
	
	// Se envia paquete al finalizar input
	enviar_paquete(paquete, conexion); 

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	free(leido);
	eliminar_paquete(paquete);
}

void paqueteTest(int conexion)
{
	t_paquete* paquete = crear_paquete();
	int* data = malloc(sizeof(int));
	*data = 0;
	agregar_a_paquete(paquete, data, sizeof(int));
	*data = 1;
	agregar_a_paquete(paquete, data, sizeof(int));
	*data = 2;
	agregar_a_paquete(paquete, data, sizeof(int));
	*data = 3;
	agregar_a_paquete(paquete, data, sizeof(int));
	
	// Se envia paquete al finalizar input
	enviar_paquete(paquete, conexion); 

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	eliminar_paquete(paquete);
}

void paquetePCB(int conexion, PCB_data *pcb)
{
	t_paquete* paquete = crear_paquete_pcb();
	
	agregar_a_paquete(paquete,&(pcb->pid),sizeof(pid_t));
	agregar_a_paquete(paquete,&(pcb->program_counter),sizeof(uint32_t));
	agregar_a_paquete(paquete,&(pcb->vQuantum),sizeof(uint16_t));

	agregar_a_paquete(paquete,&(pcb->regitros.AX),sizeof(uint16_t));
	agregar_a_paquete(paquete,&(pcb->regitros.BX),sizeof(uint16_t));
	agregar_a_paquete(paquete,&(pcb->regitros.CX),sizeof(uint16_t));
	agregar_a_paquete(paquete,&(pcb->regitros.DX),sizeof(uint16_t));
	agregar_a_paquete(paquete,&(pcb->regitros.EAX),sizeof(uint32_t));
	agregar_a_paquete(paquete,&(pcb->regitros.EBX),sizeof(uint32_t));
	agregar_a_paquete(paquete,&(pcb->regitros.ECX),sizeof(uint32_t));
	agregar_a_paquete(paquete,&(pcb->regitros.EDX),sizeof(uint32_t));

	// Se envia paquete al finalizar input
	enviar_paquete(paquete, conexion); 

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}