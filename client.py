def main():
    import socket
    SERVER_IP = "127.0.0.1"
    SERVER_PORT = 8326


    #Create a TCP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    #Connecting to remote computer 9090
    server_address = (SERVER_IP, SERVER_PORT)
    sock.connect(server_address)

    #Trying to catch an error in case the server suddenly disconnects
    try:
        
    #Rcieving a "welcome message"
        server_msg = sock.recv(1024)
        server_msg = server_msg.decode()
        print(server_msg)

        msg = "hello"
            
        sock.sendall(msg.encode())

    except Exception as e:
        print("The Server Disconnected!\n")
    sock.close()


if __name__ == "__main__":
    main()
