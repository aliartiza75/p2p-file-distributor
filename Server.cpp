/*
 * Server.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: waleed
 */
//============================================================================
// Name        : CnetProject_PeerToPeer.cpp
// Author      : Waleed Anjum
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include "unp.h"
#include <iostream>
#include<cstring>
#include <sstream>
#include "Packet.cpp"
#include "TrackerFileReading.cpp"

using namespace std;

class Serve {

	int PORT;
	const char* ipAddress;
	int sockfd;

	struct sockaddr_in addr;
	struct sockaddr_in my_addr;

	public:Packet *buff;

public:
	Serve() {

		buff = new Packet();
		ipAddress = "127.0.0.1";
		PORT = 1000;

	}

public:
	Serve(int portno) {
		ipAddress = "127.0.0.1";
		PORT = portno;
		buff = new Packet();

	}

	~Serve() {
		close(sockfd);

	}
public:
	void recieve(int size) {
		int addrlen1 = sizeof(addr);
		int a = recvfrom(sockfd, buff, sizeof(struct Packet), 0,
				(struct sockaddr*) &addr, (socklen_t *) &addrlen1);

		//return buff;
	}

public:
	int send(int size) {
		int addrlen1 = sizeof(addr);
		return sendto(sockfd, buff, sizeof(struct Packet), 0, (struct sockaddr*) &addr,
				addrlen1);
	}


public:	void show() {
		cout << buff[0].port << buff[0].chunk << buff[0].message << endl;
	}

public:
	void message(Packet arr) {

		//emptyBuff();
		*buff=arr;
	}

public:
	void initialize() {

		sockfd = socket(AF_INET, SOCK_DGRAM, 0);

		my_addr.sin_family = AF_INET;
		my_addr.sin_port = PORT;
		my_addr.sin_addr.s_addr = inet_addr(ipAddress);
		memset(&(my_addr.sin_zero), '\0', 8);

		int sizesocket = sizeof(my_addr);
		int err1 = bind(sockfd, (struct sockaddr *) &my_addr, sizesocket);

		if (err1 == -1)
			cout << "Error in binding port on server\n";

	}

};

int main() {


	//cout<<"Count:"<<count<<endl;


///**********************

	Serve *myserver = new Serve();
	(*myserver).initialize();

	while (1) {

		(*myserver).recieve(50);	//waiting for New Client
		string File=myserver[0].buff->file;
		
		cout << "Client Ask For Peers";
		//(*myserver).show();

		Packet *obj = new Packet();

		for (int i = 0; i < 100; i++) {
			(*obj).message[i] = '\0';
		}

		int pid = fork();
		if (pid != 0)
		{

			TrackerFileReader Tfile;
			Tfile.Load_file();

			vector<string> files=Tfile.filenames();

			for(int i=0 ; i<files.size();i++)
			{
				if(files[i]==File)
				{
					int pid1 = fork();
					if (pid1 != 0)
					{
						vector <int> chunks=Tfile.get_chunks(files[i]);
						for(int j=0;j<chunks.size();j++)
						{

							//cout<<File<<endl;
							int port=Tfile.find_port(files[i],chunks[j]);
							obj[0].setFile(files[i]);

							cout<<"Filename:"<<obj[0].file<<endl;
							obj[0].setMessage("Hand shake Message");
							obj[0].port=port;
							//cout<<obj[0].port<<endl;
							obj[0].chunk=chunks[j];

							(*myserver).message(*obj);
							(*myserver).send(50);

						}
					}
				//break;
				}

			}




		}

	//	(*myserver).~Serve();

	}

	/*
	 while(1)
	 {
	 Serve *myServer=new Serve();

	 (*myServer).initialize();


	 (*myServer).recieve(50);
	 (*myServer).show();

	 (*myServer).~Serve();
	 }
	 */
	//exit (0);
}

