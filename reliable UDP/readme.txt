to compile:

gcc -o server server.c
gcc -o client client.c

to run:
To run the server. Usage is:
"./server <PORT> <CHUNKSIZE>"
Ex: 
"./server 12000 500" will start a server on port 12000,
with chunk size of 500 bytes

Once the server is running, run the client. Usage is:
"./client <SERVER IP> <SERVER PORT> <CHUNK SIZE> <WINDOW SIZE>"
Ex:
"./client serverIP 12000 500 3" will instruct the client to
connect to the server at serverIP on port 12000 and send 3 chunks at a time
of 500 bytes.
