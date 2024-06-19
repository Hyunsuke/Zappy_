const express = require('express');
const http = require('http');
const socketIo = require('socket.io');
const net = require('net');
const bodyParser = require('body-parser');

const app = express();
const server = http.createServer(app);
const io = socketIo(server);

app.use(bodyParser.json());
app.use(express.static('public'));

let client = null;
let lastSentData = '';

io.on('connection', (socket) => {
    console.log('New client connected');

    socket.on('connect_to_server', ({ hostname, port }) => {
        client = new net.Socket();
        client.connect(port, hostname, () => {
            console.log('Connected to server');
            socket.emit('receive_message', { message: 'Connected to server' });
        });

        client.on('data', (data) => {
            const dataString = data.toString().replace(/\n/g, '\\n').replace(/\r/g, '\\r').replace(/\0/g, '\\0');
            if (dataString !== lastSentData) {
                lastSentData = dataString;
                socket.emit('server_response', { response: dataString, timestamp: Date.now() });
            }
        });

        client.on('error', (err) => {
            console.error('Connection error: ', err);
            socket.emit('receive_message', { message: 'Connection error: ' + err.message });
        });
    });

    socket.on('send_message', ({ message, timestamp }) => {
        if (client) {
            const formattedMessage = message.replace(/\\n/g, '\n');
            client.write(formattedMessage, (err) => {
                if (err) {
                    console.error('Error sending message: ', err);
                    socket.emit('receive_message', { message: 'Error sending message: ' + err.message });
                } else {
                    console.log(`Message sent: ${formattedMessage}`);
                }
            });
        } else {
            socket.emit('receive_message', { message: 'Not connected to server' });
        }
    });

    socket.on('disconnect', () => {
        console.log('Client disconnected');
        if (client) {
            client.destroy();
        }
    });
});

const port = 3001;
server.listen(port, () => {
    console.log(`Server running at http://localhost:${port}/`);
});
