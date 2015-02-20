#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <stdio.h>

using namespace std;

int main()
{
	ofstream f1;
	f1.open("temp.txt" , ios::out);
	ifstream f;
	f.open("testing.txt" , ios::in);
	char temp[256];
	while(!f.eof())
	{
		for( int i =0; i<256; i++)
		{
			f.get(temp[i]);
		}
		
		cout<<temp<<endl;
		usleep(100000);	
		
	}

	return 0;
}