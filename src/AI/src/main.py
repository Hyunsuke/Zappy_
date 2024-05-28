#!/usr/bin/env python3

import socket
import sys
from sys import argv, exit, stdout
import time

def parse_arguments():
    for i in argv:
        if (i == "-p"):
            port = int(argv[argv.index(i) + 1])
        elif (i == "-n"):
            name = argv[argv.index(i) + 1]
        elif (i == "-h"):
            host = argv[argv.index(i) + 1]
    return port, name, host

def create_socket(host, port):
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((host, port))
        return s
    except socket.error as e:
        print(f"Socket error: {e}")
        sys.exit(1)

def initial_handshake(sock, team_name):
    try:
        welcome_message = sock.recv(1024).decode().strip()
        if welcome_message != "WELCOME":
            raise ValueError("Did not receive welcome message")

        sock.sendall(f"{team_name}\n".encode())
        client_num = int(sock.recv(1024).decode().strip())
        world_dimensions = sock.recv(1024).decode().strip().split()
        width, height = int(world_dimensions[0]), int(world_dimensions[1])

        print(f"Connected to server. Client number: {client_num}")
        print(f"World dimensions: {width}x{height}")

        return client_num, width, height
    except Exception as e:
        print(f"Handshake error: {e}")
        sys.exit(1)

def send_command(sock, command):
    try:
        sock.sendall(f"{command}\n".encode())
        response = sock.recv(1024).decode().strip()
        return response
    except socket.error as e:
        print(f"Error sending command '{command}': {e}")
        return None

def move_forward(sock):
    return send_command(sock, "Forward")

def turn_right(sock):
    return send_command(sock, "Right")

def turn_left(sock):
    return send_command(sock, "Left")

def look(sock):
    return send_command(sock, "Look")

def inventory(sock):
    return send_command(sock, "Inventory")

def broadcast(sock, message):
    return send_command(sock, f"Broadcast {message}")

def main_loop(sock):
    try:
        while True:
            # Example of moving forward and looking around
            print("Moving forward...")
            response = move_forward(sock)
            print(f"Response: {response}")

            print("Looking around...")
            response = look(sock)
            print(f"Response: {response}")

            # Implement additional logic as needed

            # Sleep for a short duration to simulate time passing
            time.sleep(1)
    except KeyboardInterrupt:
        print("Terminating AI client.")
    finally:
        sock.close()

if __name__ == "__main__":
    try:
        port, name, host = parse_arguments()
        sock = create_socket(host, port)
        client_num, world_width, world_height = initial_handshake(sock, name)
        main_loop(sock)
    except BaseException as error:
        stdout.write(str(type(error).__name__) + ": {}\n".format(error))
        exit(84)
