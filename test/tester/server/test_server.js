/*
** EPITECH PROJECT, 2024
** test_server.js
** File description:
** Main for testing debugging connection GUI to server
*/

const net = require('net');

if (process.argv.length !== 4) {
    console.error(`Usage: ${process.argv[1]} <hostname> <port>`);
    process.exit(1);
}

const hostname = process.argv[2];
const port = parseInt(process.argv[3], 10);

const client = new net.Socket();

client.connect(port, hostname, () => {
    console.log('Connected to server');

    // Envoi du message "GRAPHIC\n"
    client.write('GRAPHIC\n');
});

client.on('data', (data) => {
    console.log('Response from server: ' + data.toString());

    // Envoi du message "GRAPHIC"
    client.write('GRAPHIC');
    // Lecture de la nouvelle réponse du serveur (optionnel)
    client.on('data', (newData) => {
        console.log('Second response from server: ' + newData.toString());
        client.destroy(); // Fermer la connexion
    });
});

client.on('close', () => {
    console.log('Connection closed');
});

client.on('error', (err) => {
    console.error('ERROR: ' + err.message);
    process.exit(1);
});
