def main():
    import socket
    import json
    SERVER_IP = "127.0.0.1"
    SERVER_PORT = 8326

    # Trying to catch an error in the connecting process   
    try:
        #Create a TCP socket
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        #Connecting to remote computer 9090
        server_address = (SERVER_IP, SERVER_PORT)
        sock.connect(server_address)

    except Exception as e:
        print("Failed to connect:", e)

    # Trying to catch an error in case the server suddenly disconnects    
    try:
        
        # Sending a signup message
        loginJson = {"username" : "user1", "password" : "1234", "mail" : "user1@gmail.com"}
        msg_code = 51
        
        msg_bytes = msg_code.to_bytes(1, 'big') + (len(json.dumps(loginJson))).to_bytes(4, 'little') + json.dumps(loginJson).encode()
        msg_bytes = bytearray(msg_bytes)
        sock.sendall(msg_bytes)

        
        # Rcieving a response
        server_msg = sock.recv(1024)
        server_msg = server_msg.decode()
        print(server_msg)


    except Exception as e:
        print(e)

    sock.close()


if __name__ == "__main__":
    main()
