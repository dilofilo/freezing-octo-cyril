#include <poll.h>
#include "server.h"
void Server::mainAuthenticateUser(){
	//Accept authentication request.
	writeToSocket(csock , ACCEPT_AUTH_REQUEST);
	
	//Accept username
	
	string userid = "";
	getUsername(userid);
	//Accept password
	string passwd = "";
	getPassword(passwd);

	if( verifyUser( userid , passwd)) {

	} else {

	}
}

bool Server::getUsername( std::string& userid )
{
	// open the database and check username
	char usernameBuffer[INSTR_BUF_SIZE];
	readFromSocket(csock , usernameBuffer , INSTR_BUF_SIZE);
	writeToSocket(csock , ACCEPTED_USERNAME);
	string tempuid(usernameBuffer);
	userid = tempuid;
}

bool Server::getPassword( std::string& passwd )
{
	char passwordBuffer[INSTR_BUF_SIZE];
	if (readFromSocket(csock , passwordBuffer , INSTR_BUF_SIZE)) {

	} else {
		return false;
	}
	string password(passwordBuffer);
	passwd = password;
	return true;
}

bool Server::
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
