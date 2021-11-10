/**
 * @File    : socket_APIs.cpp
 * @Brief   : the socket() API
 * @Author  : Wei Li
 * @Date    : 2021-11-08
*/

/** The socket() API
 * All POSIX socket programming starts with the creation of a socket file descriptor using the socket() API
 * 
 * man 2 socket
 * int socket(int domain, int type, int protocol);
 * 
 * #param 1: domain define the address type, AF_INET for IPv4 or AF_INET6 for IPv6.
 * #param 2: type field usually takes on SOCK_STREAM for TCP connection or SOCK_DGRAM for UDP connection.
 * #param 3: protocol field will be set to 0, telling the API to use the default protocol for whichever socket type is specified.
 * #return : socket file descriptor is returned.
 * 
 * The bind() and connect() APIs
 * 
 * man 2 bind
 * int bind(int socket, const struct sockaddr *address, socklen_t address_len);
 * 
 * #param 1: socket is the socket file descriptor.
 * #param 2: address is IP address + port_number.
 * #param 3: the total size of the address structure(bytes).
 * 
 * man 2 connect
 * int connect(int socket, const struct sockaddr *address, socklen_t address_len);
 * 
 * The listen() and accept() APIs
 * 
 * man 2 listen
 * int listen(int socket, int backlog);
 * 
 * #param 1: socket is the socket file descriptor.
 * #param 2: backlog limits the total number of outstanding connections that may be made.
 * 
 * man 2 accept
 * int accept(int socket, struct sockaddr *address, socket_t *address_len);
 * 
 * The send(), recv(), sendto(), and recvfrom() APIs
 * 
 * man 2 send
 * ssize_t send(int socket, const void *buffer, size_t length, int flags);
 * 
 * #param 1: socket is the socket file descriptor.
 * #param 2: the buffer wish to send.  
 * #param 3: the length of the buffer wish to send.  
 * #param 4: various different settings for how you wish to send the buffer, most case is set to 0.  
 * 
 * man 2 sendto
 * ssize_t sendto(int socket, const void *buffer, size_t length, int flags, const struct sockaddr *dest_addr, socklen_T dest_len);
 * 
 * man 2 recv
 * ssize_t recv(int socket, void *buffer, size_t length, int flags);
 * 
 * man 2 recvfrom
 * ssize_t recvfrom(int socket, void *restrict buffer, size_t length, int flags, struc sockaddr *restrict address, socklen_t *restrict address_len);
 * 
 */

#include <iostream>

int main(int argc, char** argv)
{
    
    return 0;
}
