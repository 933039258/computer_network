# CS372-Fall 2019
# Author: Peng Zhang
# Due:11/3/2019
# Program server
from socket import *
import sys #use for read command line


if __name__ == '__main__':
	if len(sys.argv) != 2: #port number must in command line, so check it!
		print "Please enter python server.py <port number> to run it!"
		exit(1)
		if ((sys.argv[1]).isdigit()) == False: #check if the prot is a number
			print "Port must be a number!"
		exit(1)
    
    # Some of the following code that provided by Week 4 Materials - Leture 15
    # Citation: https://oregonstate.instructure.com/courses/1771948/pages/week-4-socket-programming-and-the-transport-layer?module_item_id=18935950
	Port = sys.argv[1]
	Socket = socket(AF_INET, SOCK_STREAM)
	Socket.bind(('',int(Port)))
	Socket.listen(1);

	#receive and sent the messages
	bol = 1
	name = ""
	while bol: # if the name more than 10 or empty, it will do loop
		name = raw_input("Please enter a one-word name that up to 10 characters: ")
		if len(name) == 0:
			bol = 1
			print "The name cannot be empty\n"
		elif len(name) > 10:
			bol = 1
			print "The name cannot more than 10 characters\n"
		else:
			bol = 0
	print "The server is ready to receive"
   
	while 1: # while loop for the server to connect to the client
		s=0
		connt_Socket, address = Socket.accept() # waiting for the client (incoming request)
		print "You have already connected: {}".format(address) #if connect successful, print address
		client = connt_Socket.recv(1024) # read bytes, get the client name
		connt_Socket.send(name) # send the server user's name 
		
		receive="" #reveive message from client
		quit=""
		n=1
		while 1: # while loop to receive and sent until quit or nothing received
			receive = connt_Socket.recv(501)[0:-1] #read all messages from client
			if receive =="":
				print "The client has entered \quit or nothing. **Disconnected** \n We are waiting for next connection now..."
				quit = "qu"
				break
			print "{}> {}".format(client,receive)
			send=""
			while n: #check the message if it is more than 0 and less than 500
				send = raw_input("{}> ".format(name)) # get message from user to send
				if len(send)>500:
					print "Your message cannot more than 500 characters\n"
					n=1
				elif len(send) == 0:
					n=1
					print "Your message cannot be empty\n"
				else:
					n=0

			if send =="\quit": # disconnect if enter \quit 
				print "The server is disconnected!\n"
				s=1
				break #(end the inside while loop)
			connt_Socket.send(send); # send message to client
			n=1 #repeat the input loop
		if s == 1 : # end the outside while loop
			break
		qt=""
		if quit == "qu":
			qt=raw_input("You can enter q to exit or enter anything to wait for next connection > ")
		if qt=="q":
			break
		else:
			print "Waiting for next connection..."
			continue
		connt_Socket.close()
