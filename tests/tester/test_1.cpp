// Compilation :
//  g++ -o client test_1.cpp -pthread
// Run :
//  ./a.out <ip> <port>

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>

#define MESSAGE_SIZE 1000000

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <IP> <Port>" << std::endl;
        exit(1);
    }

    const char *ip = argv[1];
    int port = std::atoi(argv[2]);

    int sockfd;
    struct sockaddr_in serv_addr;

    // Création de la socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        error("Erreur de création de la socket");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Conversion de l'adresse IP
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        error("Adresse IP invalide");
    }

    // Connexion au serveur
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("Erreur de connexion");
    }

    // Création du message à envoyer
    std::vector<char> message(MESSAGE_SIZE, 'A'); // Utilise un vecteur pour la gestion automatique de la mémoire

    // Envoi du message
    if (send(sockfd, message.data(), MESSAGE_SIZE, 0) < 0) {
        error("Erreur d'envoi");
    }

    std::cout << "Message de " << MESSAGE_SIZE << " caractères envoyé à " << ip << ":" << port << std::endl;

    // Fermeture de la socket
    close(sockfd);

    return 0;
}
