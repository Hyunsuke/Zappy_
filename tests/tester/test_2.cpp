// Compilation :
//  g++ -o client test_2.cpp -pthread
// Run :
//  ./a.out <ip> <port>

#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctime>
#include <stdexcept>

#define MESSAGE_SIZE 1000000

void error(const std::string& msg) {
    perror(msg.c_str());
    throw std::runtime_error(msg);
}

// Génère des caractères aléatoires (y compris hors table ASCII standard)
void generate_random_message(char *message, size_t size) {
    for (size_t i = 0; i < size; i++) {
        message[i] = static_cast<char>(rand() % 256);  // Génère un octet aléatoire (0-255)
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <IP> <Port>" << std::endl;
        return 1;
    }

    std::string ip = argv[1];
    int port = std::stoi(argv[2]);

    int sockfd;
    struct sockaddr_in serv_addr;

    try {
        // Initialiser le générateur de nombres aléatoires
        srand(static_cast<unsigned int>(time(NULL)));

        // Création de la socket
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            error("Erreur de création de la socket");
        }

        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);

        // Conversion de l'adresse IP
        if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0) {
            error("Adresse IP invalide");
        }

        // Connexion au serveur
        if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            error("Erreur de connexion");
        }

        // Création du message aléatoire
        std::vector<char> message(MESSAGE_SIZE);
        generate_random_message(message.data(), MESSAGE_SIZE);

        // Envoi du message
        if (send(sockfd, message.data(), MESSAGE_SIZE, 0) < 0) {
            error("Erreur d'envoi");
        }

        std::cout << "Message de " << MESSAGE_SIZE << " caractères aléatoires envoyé à " << ip << ":" << port << std::endl;

        // Fermeture de la socket
        close(sockfd);
    } catch (const std::runtime_error& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
