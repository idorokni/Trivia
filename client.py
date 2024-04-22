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
        loginJson = {"username" : "user1", "password" : "1234"}
        signupJson = {"username" : "user1", "password" : "1234", "mail" : "user1@gmail.com"}
        msg_code = 51
        listJsons = [
            (loginJson, 51), # Should get an error from server because the user isn't logged yet
            (signupJson, 52),
            (loginJson, 51),
            (loginJson, 51), # Should get an error from server because user is already logged
            (signupJson, 52) # Should get an error from server because user with this name is already signed
            ]

        for i in range (len(listJsons)):
        
            msg_bytes = listJsons[i][1].to_bytes(1, 'big') + (len(json.dumps(listJsons[i][0]))).to_bytes(4, 'little') + json.dumps(listJsons[i][0]).encode()
            msg_bytes = bytearray(msg_bytes)
            sock.sendall(msg_bytes)

        
            # Rcieving a response
            # Receive code (assuming 1 byte)
            code_byte = sock.recv(1)
            code = int.from_bytes(code_byte, byteorder='big')  # Convert bytes to int
            print("CODE IS:", code)

            # Receive length (assuming 4 bytes)
            length_byte = sock.recv(4)
            length = int.from_bytes(length_byte, byteorder='little')  # Convert bytes to int
            print("Length is:", length)
    
            # Receive message data
            server_msg = sock.recv(length).decode('utf-8')  # Decode bytes to string
            print("MSG:", server_msg)



    except Exception as e:
        print(e)

    sock.close()


if __name__ == "__main__":
    main()
