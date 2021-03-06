#include <poll.h>
#include "server.h"
void Server::mainAuthenticateUser()
{
	std::string authOutput;

	if(authenticateUser(authOutput)==1) {
		std::cout<<"Authenticated."<<"\n";
	} else {
		std::cout<<"Problem with authentication."<<"\n";
	}

	int n = write(csock , authOutput.c_str() , authOutput.size());
     	if (n < 0)  {
     		error("ERROR writing to socket");
     	}
}

bool Server::checkUsername( std::string& uID )
{
	// open the database and check username
	 unordered_map< std::string, struct userdetails > :: iterator got = userDetails.find (uID);
     if ( got == userDetails.end() )  
     {	// Not Found
     	return false;
   	 } else {
    	// Username Exists.
    	user.userID = got->first;
    	tempPW = (got->second).password;
    	return true;
    }
}

bool Server::checkPassword( std::string pw )
{
	 if(pw.compare(tempPW) == 0)	return 1;

	 return 0;
}

bool Server::authenticateUser(std::string& output)
{
     	
 	std::string enu = "Enter the Username";
 	std::string enp = "Enter the Password";
 	output = "Unknown Error ... not authenticated.";

 	int n = write(csock , enu.c_str() , enu.size());
 	if (n < 0)  {
 		error("ERROR writing to socket");
 	}
	
 	/// Getting the Username

	char instBuffer[255];
	int readSize = read( csock , instBuffer , 255);
	if ( readSize < 0 ) 
	{
		std::cout << " weird reading error ... from readValue... getInstruction() \n";
		exit(1);
	} 
	
	else 
	{
		std::string tempString( instBuffer );
		if(checkUsername(tempString) == 1)
		{
			
			n = write(csock , enp.c_str() , enp.size());
			
			/// Getting the Password.

			bzero(instBuffer,255);
			readSize = read( csock , instBuffer , 255);
			if ( readSize < 0 ) 
			{
				std::cout << " weird reading error ... from readValue... getInstruction() \n";
				exit(1);
			} 
	
			else 
			{
				std::string tempString1( instBuffer );
				if(checkPassword(tempString1) == 1)
				{
					return 1;
					output = "Authenticated.";
				}

				else 
				{
					output = " Invalid Password. ";
				}
			}
		
		}

		else
		{
			output = " Invalid Username ";
		}

	return 0;
	
	}

} 
