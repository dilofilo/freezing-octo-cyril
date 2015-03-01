#include <iostream>
#include <vector>
using namespace std;

#define notg(i,k) (-1*((i-1)*subGraphs + k + 1)) 
#define g(i,k) ((i-1)*subGraphs + k + 1)
/*#define notA(index,k) (-1*(knbias + index*subGraphs + k))
#define A(index,k) (knbias+index*subGraphs + k)
#define B
*/
//#define B()

//typedef vector<vector<int> > Matrix;
int subGraphs=0;
int edges=0;
int vertices=0;
int knbias=0;
int clauseCounter=0;
int clauseCounter1=0;
int clauseCounter2=0;
int clauseCounter3=0;
int clauseCounter4=0;
//Matrix belonging;
//Matrix adjM;
vector<vector<int> > adjM;

void initialize();
void clause1();
void clause2();
void clause3();
void clause4();

//CAUTION: do not use scanf/printf
int main()
{
	//std::ios::sync_with_stdio(false);//for faster output 
	//cout<<"hi"<<endl;
	initialize();
	clause1();
	clause2();
	clause3();
	clause4();
	// cout<<"No of clauses "<<clauseCounter<<endl;
	// cout<<"No of clauses 1 "<<clauseCounter1<<endl;
	// cout<<"No of clauses 2 "<<clauseCounter2<<endl;
	// cout<<"No of clauses 3 "<<clauseCounter3<<endl;
	// cout<<"No of clauses 4 "<<clauseCounter4<<endl;
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
	// cout<<"knbias "<<knbias<<endl;
	// cout<<"vertices "<<vertices<<endl;
	// cout<<"edges "<<edges<<endl;
	// cout<<"subgraphs "<<subGraphs<<endl;

	adjM.resize(vertices, vector<int>(vertices));
	int a,b;
	//cout<<"resized"<<endl;
	for (int t = 0; t < edges; t++)
	{
		//scanf("%d %d", &a, &b);
		cin>>a>>b;
		//cout<<"intaking "<<a<<" "<<b<<endl;
		adjM[a-1][b-1] = 1;
		//cout<<"intaking "<<a<<" "<<b<<endl;
	}
	//cout<<"input done"<<endl;
}

//all edges belong to subgraphs
void clause1()
{
	//cout<<"clause 1 called"<<endl;
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
					clauseCounter+=3;
					clauseCounter1+=3;
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
				clauseCounter++;
				clauseCounter1++;

				
				
			}
		}
}

//No subset clause
void clause4()
{
	//cout<<"clause4 called"<<endl;
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
				clauseCounter+=3;
				clauseCounter4+=3;
			}

			knbias-=vertices;
			for (int i=1;i<=vertices;i++)
			{
				cout<<knbias<<" ";
				knbias++;
			}
			cout<<"0"<<endl;
			clauseCounter++;
			clauseCounter4++;

		}
}

void clause3()
{
	//cout<<"clause3 called"<<endl;
	for (int i=1; i<vertices; i++)
		for (int j=i+1; j<=vertices;j++)
		{
			for (int k=1; k<=subGraphs; k++)
			{
				if (!adjM[i-1][j-1] && !adjM[j-1][i-1])
				{
					cout<<notg(i,k)<<" "<<notg(j,k)<<" 0"<<endl;
					clauseCounter++;
					clauseCounter3++;
				}	
			}
			
		}
}

void clause2()
{
	//cout<<"clause2 called"<<endl;
	for (int k=1; k<=subGraphs; k++)
	{
		for (int i=1; i<=vertices; i++)
		{
			cout<<g(i,k)<<" ";
		}
		cout<<"0"<<endl;
		clauseCounter++;
		clauseCounter2++;
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