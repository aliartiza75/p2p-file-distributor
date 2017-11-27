/*
 * Server.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: Irtiza
 */
//============================================================================
// Name        : CnetProject_PeerToPeer.cpp
// Author      : Irtiza Ali
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
#include<vector>
#include<algorithm>
#include <fstream>
#include"FileMaking.cpp"
#include<csignal>
#include<signal.h>
#include<unistd.h>

#include<iostream>
#include<unistd.h>
#include<string>
#include<cstring>
#include<stdio.h>
#include<cstdlib>
#include<stdlib.h>
#include<sys/wait.h>
#include<pthread.h>

using namespace std;


void signal_handler1(int signo)
{
//	exit(signo);
	int pgid = getpgid(signo);
	kill(pgid, 15);

	//kill(getppid(),SIGTERM);
	//if(signo==0)
		kill(0,SIGTERM);
		//kill(getppid(signo),SIGTERM);

    //kills also all processes with same process group id which are its childs
}


//#include "unp.h"
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

public :void closeSocket(){
	close(sockfd);

}

public:
	void recieve(int size) {
		int addrlen1 = sizeof(addr);
		int a = recvfrom(sockfd, buff, sizeof(Packet), 0,
				(struct sockaddr*) &addr, (socklen_t *) &addrlen1);

		//return buff;
	}

public:
	int send(int size) {
		int addrlen1 = sizeof(addr);
		return sendto(sockfd, buff, sizeof(Packet), 0, (struct sockaddr*) &addr,
				addrlen1);
	}
public:
	void show() {
		cout << buff[0].chunk << buff[0].port << buff[0].message;

	}

public:
	void message(Packet arr) {

		*buff = arr;
		//emptyBuff();
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
			cout << "Error in binding port on server"<<PORT<<endl;

	}

};


//For Threading
int counter = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;



int main() {

	TrackerFileReader Tfile1;
	Tfile1.Load_file();

	Tfile1.makeFilesAccordingly();

	//*************************

	typedef void (*sig_t) (int) ;
	//sig_t signal(int sig, sig_t  signal_handler1);

	signal(SIGINT, signal_handler1);

	TrackerFileReader Tfile;
	Tfile.Load_file();

	vector<int> ports = Tfile.getUniquePorts();

	Serve *mypeer;
	bool flag=true;

	for (int i= 0; ((i < (ports.size()))and flag); i++) {

		int pid1 = fork();
		if (pid1 != 0) {

			//cout<<port<<endl;
			Packet obj;
			obj.setFile("B.txt");
			obj.setMessage("Hand shake Message Client2");
			obj.port = ports[i];
//			obj.chunk = chunks[j];

			mypeer = new Serve(ports[i]);
			mypeer[0].initialize();

			while(true){
				//cout<<"***"<<endl;
				mypeer[0].recieve(50);		//Waiting for Client to make Connection
				//int chunk=mypeer[0].buff[0].chunk;
				int pid = fork();
				if (pid != 0)
				{

					int chunk=mypeer[0].buff->chunk;
					string filename=mypeer[0].buff->file;
					cout<<"Recieve Filename:"<<filename<<endl;
					string message=mypeer[0].buff->message;
					int size=mypeer[0].buff->size;
					int port=mypeer[0].buff->port;


					obj.~Packet();
					//mypeer[0].~Serve();
					Packet temp;
					string sendmesg = "From Port no: " + NumberToString(ports[i]) +" Chunk: "+NumberToString(chunk);

					string openfile="Port"+NumberToString(port)+"/"+filename+"."+NumberToString(chunk);
					cout<<"Openinig File:"<<openfile<<endl;

					fstream file;
					file.open(openfile.c_str());

					if(file.is_open())
					{
						//cout<<"You made it"<<openfile;
					}
					else
					{
						cout<<"Error";
					}

					//string message;
					int count=0;
					while( getline(file,message,'\n'))
					{

						cout<<message<<endl;
						//cout<<" Message"<<count++<<message<<endl;
						temp.port=ports[i];
						temp.setMessage(message);
						mypeer[0].message(temp);
						mypeer[0].send(50);
						message = '\0';
					}

					file.close();
					temp.setMessage("$$$$");

					mypeer[0].send(50);
					cout<<"Close File"<<endl;

					mypeer[0].~Serve();

					mypeer[0].closeSocket();
					return 0;
					//exit(0);
				}//fork wala if


			}//while


		}

	}

	//raise(SIGINT);
	mypeer[0].closeSocket();//Deleting the Welcoming socket
	exit(0);
	//delete mypeer;
	//mypeer[0].closeSocket();
}

/*
 * Client2.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: waleed
 */
