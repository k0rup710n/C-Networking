//Works on Windows and on Linux
#include "Client.h"

int main(int argc, char *argv[]){
#if defined(_WIN32)
	if (argc < 2) {
		printf("[+] Usage: File.exe [IPv4/Domain/IPv6] [Port | Protocol (e.g : http)]\n(Port/Protocol can be ommited, if you give no port it will use port 80 by default)\n");
		printf("[+] Example: File.exe google.com http\n");
		printf("[+] Example: File.exe mywebsite.com ftp\n");
		printf("[+] Example: File.exe mywebsite.com 80\n");
		return 1;
	}
	WSADATA d;
	if (WSAStartup(MAKEWORD(2, 2), &d)) {
		printf("Failed to initialize.\n");
		return 1;
	}
#endif

	printf("Configuring remote address...\n");
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;
	struct addrinfo* peer_address;
	if (getaddrinfo(argv[1], argv[2] ? argv[2] : "80", &hints, &peer_address)) {
		printf("getaddrinfo() failed. (%d)\n", GETSOCKETERRNO());
		return 1;
	}
	char address_buffer[100];
	char service_buffer[100];
	getnameinfo(peer_address->ai_addr, peer_address->ai_addrlen, address_buffer, sizeof(address_buffer), service_buffer, sizeof(service_buffer), NI_NUMERICHOST);
	printf("Address : %s\n", address_buffer);
	printf("Protocol/Service : %s\n", service_buffer);
}
