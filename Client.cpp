/*
 * Client.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: Irtiza
 */
#include "unp.h"
#include <iostream>
#include<cstring>
#include<fstream>
#include <sstream>
#include "Packet.cpp"

#include<iostream>
#include<unistd.h>
#include<string>
#include<cstring>
#include<stdio.h>
#include<cstdlib>
#include<stdlib.h>
#include<sys/wait.h>
#include<pthread.h>
#include<vector>

using namespace std;
int counter = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;


class Client{
	int sockfd;
	struct sockaddr_in serv_addr;
	struct sockaddr_in addr;
	int port;

public :Packet *obj;

	public: Client(){
		port=1000;
		obj=new Packet();
	}
	public: Client(const Client & a)
	{
		sockfd=a.sockfd;
		port=a.port;
		addr=a.addr;
		serv_addr=a.serv_addr;
		this->obj=a.obj;

	}
	public: Client(int portno){
		port=portno;
		obj=new Packet();
	}
	~Client(){
		close(sockfd);


	}


	public: void initialize(){

		sockfd=socket(AF_INET,SOCK_DGRAM,0);
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = port;
		serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


	}

	public: void send(int size){

		int servlen=sizeof(serv_addr);
		int a=sendto(sockfd,obj,sizeof(struct Packet), 0, (struct sockaddr*)&serv_addr ,servlen);

	}

	public: void recieve(int size)
	{
		int addrlen=sizeof(addr);
		int a=recvfrom(sockfd,obj,sizeof(struct Packet),0, (struct sockaddr*)& addr ,(socklen_t *) & addrlen);


	}

	public :Packet show(){
		//cout<<obj[0].a<<obj[0].b<<obj[0].message<<endl;
		return *obj;


	}

	public :void message(Packet a){
		*obj=a;

	}


};
struct getFile{
	Client client;
	string filename;

};

//***********************************************************************************************************
void * print_message(void * ptr) {



	getFile  obj_forThread =*((getFile *) ptr);

	Client myClient1=obj_forThread.client;

	string filename=obj_forThread.filename;

	ofstream f(filename.c_str(), std::ofstream::app);
	if(f.good())
	{
		cout<<"File is open"<<endl;
	}

	cout<<"File name:"<<obj_forThread.filename<<endl;

	vector<string > filecontent;
	string message;
	string arr [200];

	(myClient1).send(50); //For Peer 2 , Connection


	int ten=0;
	pthread_mutex_lock(&mtx);
		do{
			cout<<ten<<endl;
			(myClient1).recieve(50);	//Recieve From Peer2
		//	cout<<"  Get Message No: "<<ten<<"Message: "<<(myClient1).obj->message<<endl;

			filecontent.push_back((myClient1).obj->message);
			f<<(myClient1).obj->message<<endl;
			cout<<(myClient1).obj->message;
			//arr[ten]  = message;
			message="/0";
			ten++;
		}while(message!="$$$$");


		f.close();

	void * re=arr;

	pthread_mutex_unlock(&mtx);
	return re;

}


int main()
{

		pthread_t thread1;
		pthread_mutex_init(&mtx, NULL);

		cout<<"Initiate Conversation"<<endl;
		Client *myClient=new Client();
		(*myClient).initialize();
		string File="A.txt";

		Packet *obj=new Packet();


		obj->setFile(File);

		(*myClient).message(*obj);
		(*myClient).send(50); //inititate conversation Send To Server


		int count=0;
		while(1)
		{
//			count++;
			(*myClient).recieve(50); //Recieve from Server
			//cout<<"Server Send:"<<(*myClient).obj->message<<(*myClient).obj->port<<(*myClient).obj->file<<(*myClient).obj->chunk<<endl;

			int pid=fork();

			if(pid!=0)//for serving Client To
			{

				int port=(*myClient).obj->port;
				int chunk=(*myClient).obj->chunk;
				string  filename="\0" , send_filename ;

				filename="Client/";

				filename.append((*myClient).obj->file);
				send_filename = (*myClient).obj->file;
				count++;

				delete myClient;
				delete obj;



				cout<<"File name:"<<send_filename<<endl;

				Client *myClient1=new Client(port);
				(*myClient1).initialize();

				Packet *obj1=new Packet();
				(*obj1).chunk=chunk;
				(*obj1).port=port;
				(*obj1).setFile(send_filename) ;
				obj[0].setMessage("New Connection");

				//cout<<"***"<<endl;
				(*myClient1).message(*obj1);

				getFile obj_tothread;
				obj_tothread.client=(*myClient);
				obj_tothread.filename=filename;

				cout<<obj_tothread.filename<<endl;
				pthread_create(&thread1 , NULL, print_message, ((void *)(&obj_tothread )) );

				void * status;
				pthread_join(thread1, &status);


	//			vector<string> returnValue=(*((vector <string> *)status));

				string *arr=(*((string **)status));
				//	Client myClient1=*((Client *) ptr);


				/*
			vector<string> v= *(vector(a));

			for(int k=0;k<v.size();k++)
			{
				cout<<v[k]<<endl;
			}
			 */
			//recieving

//				break;
//				delete myClient1;
//				delete obj1;
			}


		}


		//************************************************
/*
		cout<<"Connecting with peer";

		Client *myClient1=new Client(port);
		cout<<"***";

		(*myClient1).initialize();

		string str=	"Hellow ,this message is from client 1";
		Packet *obj1=new Packet();
		(*obj1).a=10;
		(*obj1).b=400;

		for(int i=0;i<100;i++)
		{
			obj1[0].message[i]='a';

		}
		(*myClient1).message(*obj1);
		//(*myClient).show();
		(*myClient1).send(50);

*/


exit (0);
}
