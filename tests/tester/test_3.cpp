// Compilation :
//  g++ -o client test_3.cpp -pthread
// Run :
//  ./a.out <ip> <port>

#include <iostream>
#include <vector>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctime>

#define MESSAGE_SIZE 100
#define NUM_THREADS 200

void error(const std::string& msg) {
    perror(msg.c_str());
    exit(1);
}

// Génère des caractères aléatoires (y compris hors table ASCII standard)
void generate_random_message(char *message, size_t size) {
    for (size_t i = 0; i < size; i++) {
        message[i] = static_cast<char>(rand() % 256);  // Génère un octet aléatoire (0-255)
    }
}

struct ThreadData {
    std::string ip;
    int port;
};

void send_message(const ThreadData& data) {
    int sockfd;
    struct sockaddr_in serv_addr;

    // Création de la socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        error("Erreur de création de la socket");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(data.port);

    // Conversion de l'adresse IP
    if (inet_pton(AF_INET, data.ip.c_str(), &serv_addr.sin_addr) <= 0) {
        error("Adresse IP invalide");
    }

    // Connexion au serveur
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("Erreur de connexion");
    }

    // Création du message aléatoire
    char *message = new char[MESSAGE_SIZE];
    if (message == nullptr) {
        error("Erreur d'allocation de mémoire");
    }

    generate_random_message(message, MESSAGE_SIZE);

    // Envoi du message
    if (send(sockfd, message, MESSAGE_SIZE, 0) < 0) {
        error("Erreur d'envoi");
    }

    std::cout << "Message de " << MESSAGE_SIZE << " caractères aléatoires envoyé à " << data.ip << ":" << data.port << std::endl;

    // Libération de la mémoire et fermeture de la socket
    delete[] message;
    close(sockfd);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <IP> <Port>" << std::endl;
        return 1;
    }

    std::string ip = argv[1];
    int port = std::stoi(argv[2]);

    std::vector<std::thread> threads;
    ThreadData data = {ip, port};

    // Initialiser le générateur de nombres aléatoires
    srand(static_cast<unsigned int>(time(NULL)));

    // Créer et démarrer les threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threads.emplace_back(send_message, data);
    }

    // Attendre la fin de tous les threads
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    std::cout << "Tous les messages ont été envoyés." << std::endl;

    return 0;
}
