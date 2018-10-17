import subprocess
import socket
import sys

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
servaddr = ('localhost', 8888)
sock.bind(servaddr)
sock.listen(1)

while True:
    print("Waiting for connection")
    connection, cliaddr = sock.accept()
    try:
        print("Connection accepted")
        while True:
            data = connection.recv(1024).decode()
            if data:
                print("received {}".format(data))
                try:
                    result = subprocess.check_output(data.split())
                except Exception as e:
                    result = "There was an exception: {}".format(e).encode()
                try:
                    print(result)
                    connection.sendall(result)
                except:
                    print("Error trying to send!")
            else:
                print("no mas data, bye!")
                break
    except:
        connection.close()
        sock.close()
        break

