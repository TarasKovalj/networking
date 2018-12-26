void client_send_file(char * file_name, char * buffer, char buffer_size, int accepted_socket);
int client_create(struct sockaddr_in serv_addr);