typedef void (*recv_handler)(SOCKET, char *, int);
int socketListen(recv_handler);
int socketSend(SOCKET, char *, int);
