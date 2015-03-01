#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
	ifstream fil1;
	ifstream fil2;
	fil1.open(argv[1]);
	fil2.open(argv[2]);
	string soln;
	int vertices=1;
	int subGraphs=1;
	fil2>>soln;

	if (soln=="SAT")
	{
		int reader;
		fil1>>reader;
		vertices*=reader;
		fil1>>reader;
		fil1>>reader;
		subGraphs*=reader;
		for (int j=1;j<=subGraphs;j++)
		{
			vector<int> members;
			for (int i=1;i<=vertices;i++)
			{

				fil2>>reader;
				if (reader > 0)
					members.pushback(reader-(j-1)*vertices);
			}
			cout<<"#"<<j<<" "<<members.size()<<endl;
			for (int i=1;i<members.size();i++)
			{
				cout<<members[i]<<" ";
			}
			cout<<endl;

		}	
	}
	else
	{
		cout<<"0"<<endl;
	}
}