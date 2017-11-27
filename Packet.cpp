/*
 * Packet.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: Irtiza
 */

#ifndef	__Bean_h
#define	__Bean_h

#include <string>

using namespace std;

struct Packet {
public:
//int a,b;
	int port, chunk;
	int last;
	char file[10];

	static const int size = 1000;
	char message[size];

	Packet() {
		port=0;
		chunk=0;
		last=0;
		setFile("");
		setMessage("");
	}

	Packet(const Packet& a) {
//	this->a=a.a;
//	this->b=a.b;
		last = a.last;
		port = a.port;
		chunk = a.chunk;
		setFile(a.file);
		setMessage(a.message);

	}

	void operator=(Packet a) {

//	this->a=a.a;
//	this->b=a.b;
		port = a.port;
		chunk = a.chunk;
		setFile(a.file);
		setMessage(a.message);
		last = a.last;
	}

	void setMessage(string mesg) {

		strcpy(message, mesg.c_str());
	}
	void setFile(string mesg) {
	//	for (int i = 0; i < mesg.size(); i++) {
			//if((message[i]>="A")and (message[i]<="z"))
			strcpy(file, mesg.c_str());
				}
	//}

};

#endif	/* __Bean*/
