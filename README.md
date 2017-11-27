p2p File Distributor
===================

[![N|Solid](http://3.bp.blogspot.com/-MlkFMAWDZ8s/TcEfyKnAXWI/AAAAAAAAABk/9ddo6AToWJI/s1600/P2P_peer-to_peer.png)](https://nodesource.com/products/nsolid)


It is C++ based project which transfers the file on the LAN from one client to other.

----------


Server Side
-------------

> **Server Side Architecture:**

 - In peer to peer, Server has the Tracker file. When server becomes live it reads the tracker file and save the     
 data in a structure named as TrackerFile which is an attributes in TrackerFileReader class.
 - TrackerFileReader is a class which do operation on the TrackerFile structure.
 - Server will send separate message for each chunk of file with its IP and Port to that client


Client Side
-------------

> **Client Side Architecture:**

 - On client side when client becomes live, it sends server, file name and chunk name it needs.
 - Server in return sends the IP and Port of the Peer that has that file chunks.
 - When client have the IP and Port no. It sends requests the peer for file chunks.
 - Client terminates connection with server and initiate a new connection with that peer.
 - Peer sends back the packets of the chunks.
 - Client writes the data of those packets in a file.


RELIABLE DATA TRANSFER PROTOCOL LAYER
-------------
> **Packets:**
Packets are used to transfer data from one peer to another peer. It have port, chunk, and message as data member. We have set a particular packet size if the size becomes greater than that size then it will be further divided in to multiple packets. 

> **Checksum:**
Unit16_t is being used for checksum, which is a 16 bit unsigned integer. If the Packet length is odd, then padding will be added. The sum’s carry will be added back to the result of the sum. In the end 1’s complement of the sum’s result will be returned.
> **ACK NAK:**
For ACK NAK Boolean variable is used as a flag. If it is true then it means it is ack and if it is false then it means it is a nak. If the peer gets an ack then it means that segment was transferred successfully. After then a new segment will be inserted in the window. If nak is received then it means that segment was not transferred successfully. Then the whole window will be sent back to the client.
> **Timeout:**
Select is used for timeout. If ack was not received by the peer from the client in a specified time then whole window will be sent by the peer to the client.
int makeTimeOutAfter=10;
This variable has been used to timeout for that particular packet.




Go back N
-------------
- > **Sending Window Size:**
A variable has been used for window size. Which can be used to increase and decrease window size.

- > **ACK and NAK:**
A constant variable is used to initialize the size of the window. So window size can be changed due to need. Segment will be send one by one by the Peer to the client. If ack is received then new segment will be added in the window and it nak is received then whole window will be sent back to the client. If peer receive ack for the first packet then it means that is the ack for the whole window that was sent to client.
int DontSendAckFor=6; 
This variable has been used to send NAK for that particular packet that has been sent by peer to client.

-  > **Packet Corruption:**
If a packet is found to be corrupt then whole window will be send again.
int MakePacketCorrupt=8; 
This variable has been used to make every 8th packet corrupt.

- >**ACK and NAK:**
Pipelining is done in this project. Packets in window in sent one by one, when ack is received for the first packet it means that a packet has been sent successfully and new packets are added to window.	
