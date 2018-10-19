typedef void (*recv_handler)(SOCKET, char *, int);

struct SESSION_DATA {
  recv_handler handler;
  SOCKET socket;
};

int socketListen(recv_handler);
int socketSend(SOCKET, char *, int);
