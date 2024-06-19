# test_server.js

## Description

`test_server.js` is a Node.js program designed to connect to a server via TCP, send the messages "GRAPHIC\n" and "GRAPHIC", and display the responses received from the server. This program is useful for testing and debugging GUI connections with the server.

## Prerequisites

- Node.js installed on your machine. You can download and install Node.js from [nodejs.org](https://nodejs.org/).

## Installation

1. Clone this repository or download the `test_server.js` file.
2. Ensure Node.js is installed by running the following command in your terminal:

```sh
node -v
```

This command should display the installed Node.js version.

## Usage

### Running the Program

To run the program, execute the following command in your terminal:

```sh
node test_server.js <hostname> <port>
```

Replace `<hostname>` with the server's IP address or domain name, and `<port>` with the port number. For example:

```sh
node test_server.js 127.0.0.1 8080
```

### Example Output

```sh
Connected to server
Response from server: [response from server after "GRAPHIC\n"]
Second response from server: [response from server after "GRAPHIC"]
Connection closed
```

## Modification

### Changing the Sent Messages

If you want to modify the messages sent to the server, you can edit the following lines in `test_server.js`:

```javascript
// Send the message "GRAPHIC\n"
client.write('GRAPHIC\n');

// Send the message "GRAPHIC"
client.write('GRAPHIC');
```

Replace `'GRAPHIC\n'` and `'GRAPHIC'` with the messages you want to send.

### Adding Additional Steps

If you want to add additional steps after sending the messages, you can do so by adding handlers for the client's `data` and `close` events. For example:

```javascript
client.on('data', (data) => {
    console.log('Response from server: ' + data.toString());

    // Add additional steps here

    // Send the message "GRAPHIC"
    client.write('GRAPHIC');
    
    client.on('data', (newData) => {
        console.log('Second response from server: ' + newData.toString());
        
        // Add additional steps here

        client.destroy(); // Close the connection
    });
});
```

## Troubleshooting

### Common Errors

- **ERROR: connect ECONNREFUSED**: Ensure the server is running and that the IP address and port are correct.
- **ERROR: invalid hostname/IP address**: Check that the provided hostname or IP address is valid.
- **Usage: node test_server.js <hostname> <port>**: Ensure you provide both the hostname and port when running the program.

### Questions and Contributions

If you have any questions or suggestions, please open an issue on the GitHub repository. Contributions are also welcome. To contribute, please create a branch with your changes and open a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.