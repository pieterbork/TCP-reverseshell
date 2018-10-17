import socket
import sys

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
servaddr = ('localhost', 8888)
sock.connect(servaddr)

while True:
    try:
        msg = input('command: ').encode()
        print("sending %s" % msg)
        sock.sendall(msg)
        
        data = sock.recv(1024)
        if data:
            print("received %s" % data)
        else:
            print("no response!")
    except:
        sock.close()
        break

        
