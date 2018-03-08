import socket
import sys
import subprocess

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

servaddr = ('localhost', 8888)

sock.bind(servaddr)

sock.listen(1)

while True:
    print "Waiting for connection"
    connection, cliaddr = sock.accept()
    try:
        print "Connection accepted"
        while True:
            data = connection.recv(16)
            if data:
                print "replying 'hello!'"
                connection.sendall('hello')
            else:
                print "no mas data, bye!"
                break

    finally:
        connection.close()

