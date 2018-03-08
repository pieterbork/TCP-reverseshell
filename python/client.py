import socket
import sys

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

servaddr = ('localhost', 8888)

sock.connect(servaddr)

try:
    msg = "hello, sir."
    print "sending %s" % msg
    sock.sendall(msg)
    
    while True:
        data = sock.recv(16)
        if data:
            print "received %s" % data
        else:
            print "no mas!"
            break

finally:
    sock.close()
        
