
#include <stdlib.h>
#include <sys/socket.h>

#include <iostream>

// Socket creation
int Socket(int domain, int type, int protocol);
// Socket bindind witch console infomation
void Bind(int socket, const sockaddr *address, socklen_t address_len);
// Start socket listening
void Listen(int socket, int backlog);
// attempt to connect socket
void Connect(int socket, const sockaddr *address, socklen_t address_len);
// attempt to accept connection to socket, return file descriptor if succeed
int Accept(int socket, sockaddr *address, socklen_t *address_len);
// wrapper for standart send function
void Send(int socket, const void *buffer, size_t length, int flags);
// wrapper for standart function recv
void Recv(int socket, void *buffer, size_t length, int flags);