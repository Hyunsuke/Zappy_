### README.md

# Telnet Debugging for Server Responses

This project provides a guide for debugging server responses using the Telnet tool. Follow the instructions below to modify your server code and test it using Telnet.

## Modifications for Telnet Compatibility

To ensure the server responses are correctly handled by Telnet, you need to replace occurrences of `'\n'` with `'\r\n'` in specific files. Below are the changes required:

### 1. `run_commands_gui.c`

Modify the command handling to use `'\r\n'`:

```c
// Before
command = strtok(buffer, "\n");

// After
command = strtok(buffer, "\r\n");
```

### 2. `run_commands_ia.c`

Modify the command handling to use `'\r\n'`:

```c
// Before
command = strtok(buffer, "\n");

// After
command = strtok(buffer, "\r\n");
```

### 3. `handle_cmd.c`

Modify the team name handling and comparison to use `'\r\n'`:

```c
// Before
team_name = strtok(buffer, "\n");

// After
team_name = strtok(buffer, "\r\n");

// Before
if (strcmp(buffer, "GRAPHIC\n") == 0) {

// After
if (strcmp(buffer, "GRAPHIC\r\n") == 0) {
```

## Testing with Telnet

Once you have made the necessary changes to your server code, follow these steps to test your server using Telnet:

### 1. Start Your Server

Ensure your server is running and listening for connections.

### 2. Open Telnet

Open a terminal and start Telnet with the appropriate hostname and port. Replace `<hostname>` and `<port>` with your server's hostname and port number:

```sh
telnet <hostname> <port>
```

### 3. Send Commands

Type the commands you want to send to the server and press `Enter`. Telnet will display the server's responses. For example, to send the `GRAPHIC` command:

```sh
GRAPHIC
```

### 4. Debug Responses

Check the server responses displayed in Telnet to ensure they are correct. Use this feedback to further debug and refine your server's command handling and responses.

## Example Usage

Below is an example of a Telnet session to debug server responses:

```sh
$ telnet localhost 1234
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
GRAPHIC
# Server response will be displayed here
```

## Additional Tips

- **Multiple Connections**: You can open multiple Telnet sessions to test different scenarios simultaneously.
- **Logging**: Enable logging on your server to capture detailed information about the commands received and responses sent.
- **Automated Testing**: Consider using automated testing tools/scripts that mimic Telnet interactions for more extensive testing.

## Conclusion

By following the instructions in this guide, you can effectively debug your server responses using Telnet. Making the necessary modifications to handle `'\r\n'` will ensure compatibility with Telnet and provide a reliable method for testing and debugging.
