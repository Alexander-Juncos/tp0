#include "server.h"

int main(void) {
	logger = log_create("log.log", "Servidor", 1, LOG_LEVEL_DEBUG);

	int server_fd = iniciar_servidor();
	log_info(logger, "Servidor listo para recibir al cliente");
	int cliente_fd = esperar_cliente(server_fd);

	int tamanioLista = 0;
	char *data;
	PCB_data *pcb;

	t_list* lista;
	while (1) {
		int cod_op = recibir_operacion(cliente_fd);
		switch (cod_op) {
		case MENSAJE:
			recibir_mensaje(cliente_fd);
			break;
		case PAQUETE:
			lista = recibir_paquete(cliente_fd);
			tamanioLista = list_size(lista);
			log_info(logger, "Me llegaron los siguientes valores:\n");
			// list_iterate(lista, (void*) iterator);
			for (int i=0;i<tamanioLista;i++){
				data = list_get(lista, i);
				log_info(logger,"%d", *data);
			}
			break;
		case PCB:
			lista = recibir_pcb(cliente_fd);
			pcb = descargarData(lista);
			imprimirPcb(pcb);
			break;
		case -1:
			log_error(logger, "el cliente se desconecto. Terminando servidor");
			return EXIT_FAILURE;
		default:
			log_warning(logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}
	return EXIT_SUCCESS;
}

void iterator(char* value) {
	log_info(logger,"%s", value);
}

void imprimirPcb (PCB_data *pcb)
{
	log_info(logger,"%d", pcb->pid);
	log_info(logger,"%d", pcb->program_counter);
	log_info(logger,"%d", pcb->vQuantum);
	log_info(logger,"%d", pcb->regitros.AX);
	log_info(logger,"%d", pcb->regitros.BX);
	log_info(logger,"%d", pcb->regitros.CX);
	log_info(logger,"%d", pcb->regitros.DX);
	log_info(logger,"%d", pcb->regitros.EAX);
	log_info(logger,"%d", pcb->regitros.EBX);
	log_info(logger,"%d", pcb->regitros.ECX);
	log_info(logger,"%d", pcb->regitros.EDX);
}

PCB_data *descargarData (t_list *lista)
{	
	void * data;
	int tamanioLista = list_size(lista);
	log_info(logger, "tamaño lista: %i", tamanioLista);
	PCB_data * pcb = malloc(sizeof(PCB_data));
	data = list_get(lista, 0);
	pcb->pid = *(int*) data;
	// free(data);

	data = list_get(lista, 1);
	pcb->program_counter = *(int*) data;
	// free(data);

	data = list_get(lista, 2);
	pcb->vQuantum = *(int*) data;
	// free(data);

	data = list_get(lista, 3);
	pcb->regitros.AX = *(int*) data;
	// free(data);

	data = list_get(lista, 4);
	pcb->regitros.BX = *(int*) data;
	// free(data);

	data = list_get(lista, 5);
	pcb->regitros.CX = *(int*) data;
	// free(data);

	data = list_get(lista, 6);
	pcb->regitros.DX = *(int*) data;
	// free(data);

	data = list_get(lista, 7);
	pcb->regitros.EAX = *(int*) data;
	// free(data);

	data = list_get(lista, 8);
	pcb->regitros.EBX = *(int*) data;
	// free(data);

	data = list_get(lista, 9);
	pcb->regitros.ECX = *(int*) data;
	// free(data);

	data = list_get(lista, 10);
	pcb->regitros.EDX = *(int*) data;
	// free(data);

	return pcb;
}
