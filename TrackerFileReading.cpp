/*
 * TrackerFileReading.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: irti
 */

#include <iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<algorithm>
#include"FileMaking.cpp"

using namespace std;


// template end

// template to conert String to Integer
template<typename T>
T StringToNumber(const string &Text) //Text not by const reference so that the function can be used with a
		{ //character array as argument
	stringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}
// template end

int StringToInt(string s) {
	int integer;
	std::istringstream ss(s);
	ss >> integer;
	return integer;
}

struct TrackerFile {
	// attributes
	string peer;
	string ip;
		int port;
	string File_name;
	string chunks[20];
};
// strcut end

class TrackerFileReader { // TrackerFileReader class
	string filename;
	TrackerFile *tracker;

public:
	TrackerFileReader() {
		filename = "Tracker";
		tracker = NULL;
	}
	int No_of_lines_in_File() {
		int _no_of_lines = 0;
		string line;
		fstream no_of_lines;
		no_of_lines.open("Tracker", ios::out | ios::in);
		while (getline(no_of_lines, line)) {
			_no_of_lines++;
		}

		return _no_of_lines;
	} // function ends

	void Load_file() {
		fstream Tracker_file;
		string line;
		tracker = new TrackerFile[No_of_lines_in_File()];

		Tracker_file.open(&filename[0], ios::out | ios::in);

		if (Tracker_file.is_open()) {
			//cout << "file is Open" << endl;

			//			while (getline (Tracker_file,line,'\t')) {  // loop to get particular values
			for (int i = 0; getline(Tracker_file, line, '\t'); i++) {
				if (i > 0) {
					tracker[i - 1].peer = line;
				}

				getline(Tracker_file, line, '\t');
//								cout<<line<<endl;
				if (i > 0) {
					tracker[i - 1].ip = line;
//								cout<<tracker[i-1].ip<<endl;
				}

				getline(Tracker_file, line, '\t');
				if (i > 0) {
					tracker[i - 1].port = StringToInt(line);
				}

				getline(Tracker_file, line, '\t');
				if (i > 0) {
					tracker[i - 1].File_name = line;
				}

				getline(Tracker_file, line, '\n');
				if (i > 0) {
					stringstream ss(line);
					for (int indexs = 0;
							getline(ss, tracker[i - 1].chunks[indexs], ',');
							indexs++) {
						//cout<<tracker[i].chunks[indexs]<<endl;
					} // internal for loop end
				}
			} // outer for end

		} // if condition end to check file is open

		else {
			//cout << "Cannot open" << endl;

		}

	} // function ends
	void Display_data() {
		for (int i = 0; i < No_of_lines_in_File() - 1; i++) {
			cout << "Tracker  : " << i << endl << endl;
			cout << tracker[i].peer << endl;
			cout << "IP    " << tracker[i].ip << endl;
			cout << tracker[i].port << endl;
			cout << tracker[i].File_name << endl;
			for (int j = 0; tracker[i].chunks[j] != "\0"; j++) {
				cout << tracker[i].chunks[j] << endl;
			} // inner for
		} // outer for
	} // function ends

	vector<int> get_chunks(string s) {
		vector<int> chunks;
		vector<int>::iterator it;
		for (int i = 0; i < No_of_lines_in_File() - 1; i++) {

			if (tracker[i].File_name == s) {
				for (int j = 0; tracker[i].chunks[j] != "\0"; j++) {
					int str = StringToInt(tracker[i].chunks[j]);

					it = find(chunks.begin(), chunks.end(), str);

					if (it != chunks.end()) {

					} else {

						chunks.push_back(str);
					}

				} // inner for
			} // if end

		} // for end
		return chunks;
	}
	int get_no_of_chunks(string s) {
		vector<int> chunks;
		vector<int>::iterator it;
		for (int i = 0; i < No_of_lines_in_File() - 1; i++) {

			if (tracker[i].File_name == s) {
				for (int j = 0; tracker[i].chunks[j] != "\0"; j++) {
					int str = StringToInt(tracker[i].chunks[j]);

					it = find(chunks.begin(), chunks.end(), str);

					if (it != chunks.end()) {

					} else {

						chunks.push_back(str);
					}

				} // inner for
			} // if end
		} // for end
		return chunks.size();
	} // get chunks end

	vector<int> getUniquePorts() {

		TrackerFileReader *Tfile1 = new TrackerFileReader();
		Tfile1[0].Load_file();
		vector<string> files = Tfile1[0].filenames();

		vector<int> ports;

		//	int count =0;
		for (int i = 0; i < files.size(); i++) {

			vector<int> chunks = Tfile1[0].get_chunks(files[i]);
			for (int j = 0; j < chunks.size(); j++) {
				int port = Tfile1[0].find_port(files[i], chunks[j]);

				//port = Tfile1[0].find_port(files[i], chunks[j]);
				vector<int>::iterator it;
				it = find(ports.begin(), ports.end(), port);
				if (it != ports.end()) {

				} else if (i != files.size() - 1) {
					ports.push_back(port);
					//cout<<port<<endl;
				}

			}

		}
		return ports;
	}

	vector<string> filenames() {
		vector<string> arr;
		string str;
		for (int i = 0; i < No_of_lines_in_File() - 1; i++) {
			str = tracker[i].File_name;
			vector<string>::iterator it;
			it = find(arr.begin(), arr.end(), str);

			if (it != arr.end()) {

			} else {

				arr.push_back(str);
				//get_chunks(str);

			}
		}
		for (unsigned int i = 0; i < arr.size(); i++) {
			//cout << arr[i] << endl;
		}
		return arr;

	} // function end

	string getFileName(int port) {

		for (int i = 0; i < No_of_lines_in_File() - 1; i++) {

			if (tracker[i].port == port) {
				return tracker[i].File_name;

				// inner for
			}
		} // outer for

		string filename;
		return filename;

	}

	void makeFilesAccordingly() {

		for (int i = 0; i < No_of_lines_in_File()-2; i++) {

			string filename  =  tracker[i].File_name;
			int port = tracker[i].port;

			int size=0;
			for (int j = 0; tracker[i].chunks[j] != "\0"; j++)
			{
				size++;

			}

			char* destinationName=new char[filename.length() + 1];
			strcpy(destinationName, filename.c_str());

			//cout<<"Destination:"<<destinationName<<endl;

			string folder="Port"+NumberToString(port);

			//cout<<"Folder:"<<folder<<endl;
			//cout<<"Size:"<<size<<endl;
			// vector<string> arr  = filenames() ;

			// for (unsigned int i = 0; i < arr.size(); i++) {
				if(port!=0)
				{
					cout<<"Chunking : "<<filename << endl;
					chunkFile(&filename[0], destinationName , size-1,folder); // is mein path file ka path ha
				}
			// }





		}
	}
	int find_port(string filename, int chunk) {
		int return_val;
		for (int i = 0; i < No_of_lines_in_File() - 1; i++) {

			if (tracker[i].File_name == filename) {
				for (int j = 0; tracker[i].chunks[j] != "\0"; j++) {
					int str = StringToInt(tracker[i].chunks[j]);
					if (str == chunk) {
						return_val = tracker[i].port;
						break;
					}

				} // inner for
			}
		} // outer for
		return return_val;
	}

};
