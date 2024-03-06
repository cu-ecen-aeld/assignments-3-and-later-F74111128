#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>

#define PORT 9000
#define DATA_FILE "/var/tmp/aesdsocketdata"

int server_fd;

void signal_handler(int sig) {
    if (sig == SIGINT || sig == SIGTERM) {
        syslog(LOG_INFO, "Caught signal, exiting");
        close(server_fd);
        remove(DATA_FILE);
        exit(EXIT_SUCCESS);
    }
}

void send_data_to_client(int client_socket) {
    FILE *fp = fopen(DATA_FILE, "r");
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        send(client_socket, buffer, strlen(buffer), 0);
    }
    fclose(fp);
}

int main(int argc, char *argv[]) {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    bool daemon_mode = 0;

    if (argc > 1 && strcmp(argv[1], "-d") == 0) {
        daemon_mode = 1;
    }

    if (daemon_mode) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        if (pid > 0) {
            exit(EXIT_SUCCESS); // Parent process exits
        }
        // Child process continues
        umask(0); // Unmask the file mode
    }
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    while (true) {
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(address.sin_addr), client_ip, INET_ADDRSTRLEN);
        syslog(LOG_INFO, "Accepted connection from %s", client_ip);

        char buffer[1024];
        ssize_t bytes_received;
        FILE *fp = fopen(DATA_FILE, "a+");

        while ((bytes_received = recv(new_socket, buffer, sizeof(buffer), 0)) > 0) {
            buffer[bytes_received] = '\0';
            fprintf(fp, "%s", buffer);

            char *newline = strchr(buffer, '\n');
            if (newline != NULL) {
                fflush(fp);
                send_data_to_client(new_socket);
                memset(buffer, 0, sizeof(buffer));
            }
        }

        close(new_socket);
        fclose(fp);
        syslog(LOG_INFO, "Closed connection from %s", client_ip);
    }
}