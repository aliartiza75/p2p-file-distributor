
#ifndef	__FileMaking
#define	__FileMaking


#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<sstream>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include<sstream>
#include<fstream>
#include<inttypes.h>
#include <cstdlib>
#include <sys/timeb.h>
#include <sys/stat.h>
#include <math.h>       /* floor */


using namespace std;


// template to convert Number to string
template<typename T>
string NumberToString(T Number) {
	stringstream ss;
	ss << Number;
	return ss.str();
}


// templates end

// Simply gets the file size of file.

int getFileSize(ifstream *file) {

	file->seekg(0, ios::end);

	int filesize = file->tellg();

	file->seekg(ios::beg);

	return filesize;

}
////////////////////////////////////// makes file chunks
void chunkFile(char* fullFilePath, char *chunkName, int no_of_chunks,string destinationFolder) {

	const int dir_err = mkdir(destinationFolder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	ifstream fileStream, s;
	unsigned long chunkSize;

	s.open(fullFilePath);

	int size = getFileSize(&s);
	cout << "Size is : " << size << endl;
	chunkSize = ceil(size / no_of_chunks); // no of chunks
	cout << "Size is : " << chunkSize << endl;
	chunkSize--;
	fileStream.open(fullFilePath, ios::in | ios::binary);

	// File open a success
	if (fileStream.is_open()) {
		ofstream output;
		int counter = 1;

		string fullChunkName;
		// Create a buffer to hold each chunk

		char *buffer = new char[chunkSize];
		// Keep reading until end of file

		while (!fileStream.eof()) {

			// Build the chunk file name. Usually drive:\\chunkName.ext.N
			// N represents the Nth chunk

			fullChunkName.clear();
			fullChunkName.append(destinationFolder+"//");
			fullChunkName.append(chunkName);
			fullChunkName.append(".");

			//cout<<fullChunkName;
			// Convert counter integer into string and append to name.

			// char intBuf[10];
			string str = NumberToString(counter);
			// itoa(counter,intBuf,10);
			fullChunkName.append(str);

			// Open new chunk file name for output

			output.open(fullChunkName.c_str(),
					ios::out | ios::trunc | ios::binary);

			// If chunk file opened successfully, read from input and

			// write to output chunk. Then close.

			if (output.is_open()) {

				fileStream.read(buffer, chunkSize);

				// gcount() returns number of bytes read from stream.

				output.write(buffer, fileStream.gcount());

				output.close();

				counter++;

			}

		}

		// Cleanup buffer

		delete (buffer);

		// Close input file stream.

		fileStream.close();

		cout << "Chunking complete! " << counter - 1 << " files created."
				<< endl;

	}

	else {
		cout << "Error opening file!" << endl;
	}

} // chunkfile function end here

///////////////////////////////////////////////////////////////////////
// Finds chunks by "chunkName" and creates file specified in fileOutput

void joinFile(char *chunkName, char *fileOutput) {

	string fileName;

	// Create our output file

	ofstream outputfile;

	outputfile.open(fileOutput, ios::out | ios::binary);

	// If successful, loop through chunks matching chunkName

	if (outputfile.is_open()) {

		bool filefound = true;

		int counter = 1;

		int fileSize = 0;

		while (filefound) {

			filefound = false;

			// Build the filename

			fileName.clear();

			fileName.append(chunkName);

			fileName.append(".");

			char intBuf[10];

			string str = NumberToString(counter);

			fileName.append(str);

			// Open chunk to read

			ifstream fileInput;

			fileInput.open(fileName.c_str(), ios::in | ios::binary);

			// If chunk opened successfully, read it and write it to

			// output file.

			if (fileInput.is_open()) {

				filefound = true;

				fileSize = getFileSize(&fileInput);

				char *inputBuffer = new char[fileSize];

				fileInput.read(inputBuffer, fileSize);

				outputfile.write(inputBuffer, fileSize);

				delete (inputBuffer);

				fileInput.close();

			}

			counter++;

		}

		// Close output file.

		outputfile.close();

		cout << "File assembly complete!" << endl;

	}

	else {
		cout << "Error: Unable to open file for output." << endl;
	}

}
/*
int main() {

	char *path, *name, *combined_files;


	string filepath = "./A.txt"; // yahan par file ka path aur location day
	string filename = "B"; // yahan par aik name day jis name say parts banay gay
	string joined_files = "joind_files"; // ye us file ka name hai jo join honay k bad bnay gay

	path = &filepath[0];
	name = &filename[0];
	combined_files = &joined_files[0];

	chunkFile(path, name, 5,"N"); // is mein path file ka path ha
							  // name chunk ka name ha jis name par tu nay create karna ha
							  // 5 no of chunk files hain
	joinFile(name, combined_files);

	//cout<<udp_checksum(path, 15);


	string newFolder;

	cout << "Enter name of new project without spaces:\n";
	cin >> newFolder;



	return 0;
}
*/


#endif
