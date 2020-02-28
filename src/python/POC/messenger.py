import socket
import sys
import select

def client():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((input("enter IP: "), 31337))
    message(s)

def server():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(("0.0.0.0", 31337))
    s.listen(1)
    client, _ = s.accept()
    message(client)


def message(s):
    while 1:
        read_list = [sys.stdin, s]
        # Get the list sockets which are readable
        read_sockets, _, error_sockets = select.select(read_list, [], [])
        for sock in read_sockets:
        #incoming message from remote server
            if sock == s:
                data = sock.recv(1024)
                if not data :
                    print('\nDisconnected from other')
                    sock.close()
                    return
                else :
                    #print data
                    print(data.decode("utf-8"))
            #user entered a message
            else :
                msg = sys.stdin.readline()
                s.send(msg.encode())
        for sock in error_sockets:
            if s == sock:
                sock.close()
                return

if input(">>> ") == "client":
    client()
else:
    server()