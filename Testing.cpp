/*
 * Testing.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: Irtiza
 */


#include<iostream>
#include <sys/select.h>

using namespace std;

int main(){

	int SocketId=10;


	return 0;
}

void timeoutwait(int Socketfd){

	fd_set SocketSet;

	FD_ZERO(&SocketSet);
	FD_SET(Socketfd,&SocketSet);
	struct timeval Timeout;

	Timeout.tv_usec = 0;
	Timeout.tv_sec = 5;
	Timeout.tv_usec = 0;
	select(Socketfd+1,&SocketSet,NULL,NULL,&Timeout);

}
