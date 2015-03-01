#include <iostream>
#include <vector>
using namespace std;

#define notg(i,k) (-1*((k-1)*vertices + i + 1)) 
#define g(i,k) ((k-1)*vertices + i + 1)
/*#define notA(index,k) (-1*(knbias + index*subGraphs + k))
#define A(index,k) (knbias+index*subGraphs + k)
#define B
*/
//#define B()

typedef vector<vector<int> > Matrix;
int subGraphs=0;
int edges=0;
int vertices=0;
int knbias=0;
Matrix belonging;
Matrix adjM;

void initialize();
void clause1();
void clause2();
void clause3();
void clause4();

//CAUTION: do not use scanf/printf
int main()
{
	//std::ios::sync_with_stdio(false);//for faster output 
	cout<<"hi"<<endl;
	initialize();
	clause1();
	clause2();
	clause3();
	clause4();
}


// initialises the adjacency matrix
void initialize()
{
	//scanf("%d %d %d", &vertices, &edges, &subGraphs);
	cin>>vertices;
	cin>>edges;
	cin>>subGraphs;
	knbias=subGraphs*vertices+1;
	//Error handling
	cout<<"knbias "<<knbias<<endl;
	cout<<"vertices "<<vertices<<endl;
	cout<<"edges "<<edges<<endl;
	cout<<"subgraphs "<<subGraphs<<endl;

	adjM.resize(vertices, vector<int>(vertices,0));
	int a,b;
	for (int t = 0; t < edges; t++)
	{
		//scanf("%d %d", &a, &b);
		cin>>a>>b;
		adjM[a][b] = 1;

	}
}

//all edges belong to subgraphs
void clause1()
{
	//vector<vector<int> > A;
	
	for (int i=1; i<=vertices; i++)
		for (int j=1;j<=vertices; j++)
		{
			if (adjM[i-1][j-1])
			{
				for( int k=1; k<=subGraphs; k++ )
				{
					//A[index][k] or not(gik) or not(gjk)-addclause
					//cout<<A(index,k)<<" "<<notg(i,k)<<" "<<notg(j,k)<<" 0"<<endl; 
					cout<<knbias<<" "<<notg(i,k)<<" "<<notg(j,k)<<" 0"<<endl; 
					//not(A[index][k]) or gik - addclause
					//cout<<notA(index,k)<<" "<<g(i,k)<<" 0"<<endl;
					cout<<-1*knbias<<" "<<g(i,k)<<" 0"<<endl;
					//not(A[index][k])or gjk - addclause
					//cout<<notA(index,k)<<" "<<g(j,k)<<" 0"<<endl;
					cout<<-1*knbias<<" "<<g(j,k)<<" 0"<<endl;
					knbias++;	
				}

				//or over all k A[l][k]-addclause
				knbias-=subGraphs;
				for (int k=1; k<=subGraphs; k++)
				{
					cout<<knbias<<" ";
					knbias++;
				}
				cout<<"0"<<endl;	//to finish this loooong clause
				
				
			}
		}
}

//No subset clause
void clause4()
{
	
	for (int k=1; k<=subGraphs; k++)
		for (int l=1; l<=subGraphs; l++)
		{
			if (l==k)
				continue;				//(l!=k)
			for (int i=1; i<=vertices; i++)
			{
				cout<<knbias<<" "<<notg(i,k)<<" "<<notg(i,l)<<" 0"<<endl;
				cout<<-1*knbias<<" "<<g(i,k)<<" 0"<<endl;
				cout<<-1*knbias<<" "<<g(i,l)<<" 0"<<endl;
				knbias++;
			}

			knbias-=vertices;
			for (int i=1;i<=vertices;i++)
			{
				cout<<knbias<<" ";
				knbias++;
			}
			cout<<"0"<<endl;

		}
}

void clause3()
{
	for (int i=1; i<vertices; i++)
		for (int j=i+1; j<=vertices;j++)
		{
			for (int k=1; k<=vertices; k++)
			{
				if (!adjM[i][j] && !adjM[j][i])
				{
					cout<<notg(i,k)<<" "<<notg(j,k)<<" 0"<<endl;
				}	
			}
			
		}
}

void clause2()
{
	for (int k=1; k<=subGraphs; k++)
	{
		for (int i=1; i<=vertices; i++)
		{
			cout<<g(i,k)<<" ";
		}
		cout<<"0"<<endl;
	}
}


/*void addClause(//decide) //to add a clause to minisat input
{

}
*/
// struct OR{
// 	vector<int> a; 
// 	int sz;
	/*bool evaluate()
	{

		for (int i = 0; i < sz; i++)
		return false;
	}
	*/
	/*void initialize(vector<int>& b){a = b;}

			if (a[i] == 1) return true;

	void push(int b){

		a.push_back(b); sz++;
	}
*/
	/*void pushComplement(int b)            //how do you plan to display not(b)?
	{
		if (b) a.push(0);
		else a.push(1);
	}
	*/


//};


/*
vector<OR> createCompletenessClause(vector<int>& subgraph, const Matrix& adj)
{
	vector<OR> a;
	int sz = (int) adj.size(); // number of vertices
	a.reserve(sz*sz);

	for (int i = 0; i < sz; i++)
		for (int j = i+1; j < sz; i++)
		{
			OR s;
			s.pushComplement(subgraph[i])
			s.pushComplement(subgraph[j]);
			s.push(adj[i][j]);
			a[i*sz + j] = s;
		}

	return a;
}

vector<OR> createNodeClause(const Matrix& adj, const Matrix& belonging)
{
	vector<OR> a;
	int k = (int) belonging.size();
	a.reserve(belonging.size());

	for (int i = 0; i < (int) adj.size(); i++)
	{
		OR s;
		for (int l = 0; l< k; i++)
			s.push(belonging[i][k]);
		a[i] = s;
	}

	return a;
}
*/