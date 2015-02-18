/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <string>

#define MAX_CLIENTS 100

using namespace std;


const int portno =10001;

class Server 
{
	struct sockaddr_in servAddr;
	int nClients; 
	vector <struct sockaddr_in> vecCliAddr;
	vector<int> vecSockfd;

public:
	Server()
	{
		vecCliAddr.resize(MAX_CLIENTS);
     	nClients = 0;
     	struct sockaddr_in temp;
        bzero((char *) &temp, sizeof(temp)); 	
     	temp.sin_family = AF_INET;
     	temp.sin_addr.s_addr = INADDR_ANY;
    	temp.sin_port = htons(portno);		

    	servAddr = temp;

    	nClients = vecCliAddr.size();
    	vecSockfd.push_back(socket(AF_INET, SOCK_STREAM, 0));
    	//vecSockfd[0] = socket(AF_INET, SOCK_STREAM, 0);
       
        if (vecSockfd[0] < 0) {
        	error("ERROR opening socket");
        }
       
        if (bind(vecSockfd[0], (struct sockaddr *) &servAddr,sizeof(servAddr)) < 0) {
            error("ERROR on binding");
        }

	}

	void auhenticate (string username, string password)
	{
		/// Verifies Username and Password 
	}

	void getclient(int n)
	{
		if ( n >= MAX_CLIENTS) {
			//Fail.
			cout << "Too many clients\n";
		} else {	
			listen(vecSockfd[n],5);
			int clilen = sizeof(vecCliAddr[n]);
	    	int newsockfd = accept(vecSockfd[n],(struct sockaddr *) &vecCliAddr[n], (socklen_t*) &clilen);
	    	execute(newsockfd);
		}
	}

	void execute (int newsockfd)
	{	
		
     char buffer[256];

		string s;
		while(1)
		{
			bzero(buffer,256);		
			
			listen(newsockfd,5);

		    int n = read(newsockfd,buffer,255);
     		if (n < 0) { 
     			error("ERROR reading from socket");
   			}
   			printf("Here is the message: %s\n",buffer);
    		cin>>s;
     		n = write(newsockfd,s.c_str(),s.size());
     		if (n < 0)  {
     			error("ERROR writing to socket");
     		}

     	}
	}

	void error(const char *msg)
	{
	    cout<<msg<<"\n";
   		exit(1);
	}	


};

int main(int argc, char *argv[])
{
    Server mainServer; 

    mainServer.getclient(0);

    
    //  int sockfd, newsockfd, portno;
    //  socklen_t clilen;
    //  char buffer[256];
    //  struct sockaddr_in serv_addr, cli_addr;
    //  int n;
    //  if (argc < 2) {
    //      fprintf(stderr,"ERROR, no port provided\n");
    //      exit(1);
    //  }
    //  sockfd = socket(AF_INET, SOCK_STREAM, 0);
     
    //  if (sockfd < 0) 
    //     error("ERROR opening socket");
    //  bzero((char *) &serv_addr, sizeof(serv_addr));
     
    // // portno = atoi(argv[1]);
     
    //  serv_addr.sin_family = AF_INET;
    //  serv_addr.sin_addr.s_addr = INADDR_ANY;
    //  serv_addr.sin_port = htons(portno);
     
    //  if (bind(sockfd, (struct sockaddr *) &serv_addr,
    //           sizeof(serv_addr)) < 0) 
    //           error("ERROR on binding");
    //  listen(sockfd,5);
     

    //  if (newsockfd < 0) 
    //       error("ERROR on accept");
    //  bzero(buffer,256);
    
    //  n = read(newsockfd,buffer,255);
    //  if (n < 0) error("ERROR reading from socket");
    //  printf("Here is the message: %s\n",buffer);
    
    //  n = write(newsockfd,"I got your message",18);
    //  if (n < 0) error("ERROR writing to socket");
    
    //  close(newsockfd);
    //  close(sockfd);

     return 0; 
}