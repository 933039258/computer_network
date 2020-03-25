CS372-Fall 2019
Author: Peng Zhang
Due:11/3/2019
Program Client and Server to chat

To run the server:

chmod +x server.py    //permission

python server.py <port>  //port should be port number user entered


To run the client: need other window

gcc client.c

./a.out <flipX> <Port>  // run on the school server should change the X to 1,2,3 (eg. flip1)

XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
Running Example:

chmod +x server.py
python server.py 1239

Open other window and enter:

gcc client.c 
./a.out flip1 1239
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

Citation in the code: (Also included in the code)
1. https://oregonstate.instructure.com/courses/1771948/pages/week-4-socket-programming-and-the-transport-layer?module_item_id=18935950
2. https://beej.us/guide/bgnet/html/#cb85-36