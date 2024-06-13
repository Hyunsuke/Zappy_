### README.md

# Chat System

A real-time chat application with features such as message search, emoji support, typing indicators, and dark mode.

## Features

- **Real-time Messaging**: Send and receive messages instantly.
- **Typing Indicator**: See when other users are typing.
- **Emoji Support**: Add emojis to your messages using an emoji picker.
- **Search Messages**: Search through chat history with a search bar.
- **Dark Mode**: Toggle between light and dark themes.
- **Connection Statistics**: View connection status, total messages sent, last message, and response time.

## Prerequisites

- Node.js
- npm (Node Package Manager)

## Installation

1. **Install dependencies**:
    ```sh
    npm install express socket.io net body-parser emoji-picker-element
    ```

## Usage

1. **Start the server**:
    ```sh
    node server.js
    ```

2. **Open your browser and navigate to**:
    ```
    http://localhost:3000
    ```

3. **Connect to the chat server**:
    - Enter the hostname and port in the left panel and click `Connect`.

4. **Send messages**:
    - Enter your message in the input box and press `Enter` or click `Send`.

5. **Search messages**:
    - Use the search bar above the chat to filter messages.

6. **Toggle dark mode**:
    - Click the `Toggle Theme` button to switch between light and dark themes.

## Project Structure

```
.
├── public
│   ├── index.html
│   ├── style.css
│   └── socket.io.js (loaded from the socket.io package)
├── server.js
├── package.json
└── README.md
```

### File Descriptions

- **public/index.html**: The main HTML file for the chat application.
- **public/style.css**: The CSS file for styling the chat application.
- **server.js**: The server-side code to handle socket connections.
- **package.json**: The package configuration file, containing scripts and dependencies.

## Code Explanation

### server.js

```javascript
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

io.on('connection', (socket) => {
    console.log('New client connected');

    socket.on('connect_to_server', ({ hostname, port }) => {
        client = new net.Socket();
        client.connect(port, hostname, () => {
            console.log('Connected to server');
            socket.emit('receive_message', { message: 'Connected to server' });
        });

        client.on('data', (data) => {
            socket.emit('server_response', { response: data.toString().replace(/\n/g, '\\n').replace(/\r/g, '\\r').replace(/\0/g, '\\0'), timestamp: Date.now() });
        });

        client.on('error', (err) => {
            console.error('Connection error: ', err);
            socket.emit('receive_message', { message: 'Connection error: ' + err.message });
        });
    });

    socket.on('send_message', ({ message, timestamp }) => {
        if (client) {
            client.write(message, (err) => {
                if (err) {
                    console.error('Error sending message: ', err);
                    socket.emit('receive_message', { message: 'Error sending message: ' + err.message });
                } else {
                    console.log(`Message sent: ${message}`);
                }
            });
        } else {
            socket.emit('receive_message', { message: 'Not connected to server' });
        }
    });

    socket.on('typing', () => {
        socket.broadcast.emit('typing');
    });

    socket.on('stop_typing', () => {
        socket.broadcast.emit('stop_typing');
    });

    socket.on('disconnect', () => {
        console.log('Client disconnected');
        if (client) {
            client.destroy();
        }
    });
});

const port = 3000;
server.listen(port, () => {
    console.log(`Server running at http://localhost:${port}/`);
});
```

### public/index.html

Contains the HTML structure for the chat application. Key features include:
- A connection form to enter the hostname and port.
- A chatbox to display messages and send new ones.
- A search bar to filter messages.
- An emoji picker for adding emojis to messages.
- A typing indicator to show when someone is typing.
- Statistics to display connection status, total messages, last message, and response time.

### public/style.css

Handles the styling for the chat application, including light and dark themes, button transitions, and chatbox layout.

### Additional Features

#### Emoji Picker

To add emojis to your messages:
- Use the `<emoji-picker></emoji-picker>` element.
- Append the selected emoji to the message input field when an emoji is clicked.

#### Typing Indicator

To show when someone is typing:
- Emit 'typing' and 'stop_typing' events.
- Display a typing indicator when these events are received.

#### Search Messages

To filter messages:
- Use the search input field.
- Filter messages based on the text entered in the search bar.

### Contributing

Feel free to fork this repository and submit pull requests. For major changes, please open an issue first to discuss what you would like to change.

### License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
