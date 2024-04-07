def main():
    import socket
    SERVER_IP = "127.0.0.1"
    SERVER_PORT = 8326
    HELLO_MSG_LEN = 5

    #Trying to catch an error in the connecting process   
    try:
        #Create a TCP socket
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        #Connecting to remote computer 9090
        server_address = (SERVER_IP, SERVER_PORT)
        sock.connect(server_address)

    except Exception as e:
        print("Failed to connect:", e)

    #Trying to catch an error in case the server suddenly disconnects    
    try:
        
        #Rcieving a "welcome message"
        server_msg = sock.recv(HELLO_MSG_LEN)
        server_msg = server_msg.decode()
        print(server_msg)

        #Sending a response to the welcome message
        if (server_msg == "Hello"):
            msg = "Hello"
            sock.sendall(msg.encode())

    except Exception as e:
        print("The Server Disconnected!\n")

    sock.close()


if __name__ == "__main__":
    main()
