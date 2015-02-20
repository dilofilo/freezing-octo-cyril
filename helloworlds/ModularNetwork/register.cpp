#include <poll.h>
void Server::mainRegisterUser()
{
	std::string regOutput;

	if(registerUser(regOutput)==1) {
		std::cout<<"Registered.\n";
	} else {
		std::cout<<"Problem with registration."<<"\n";
	}

	int n = write(csock , regOutput.c_str() , regOutput.size());
     	if (n < 0)  {
     		error("ERROR writing to socket");
     	}

}

bool Server::registerUser( std::string& output )
{
	/// Add the username and password to the database.
	std::string enu = "Enter the Username to be Registered.";
 	std::string enp = "Enter the Password to be Registered.";
 	std::string end = "Enter the Directory of the Client Side.";
 	output = "Unknown Error ... not Registered.";

 	int n = write(csock , enu.c_str() , enu.size());
 	if (n < 0)  {
 		error("ERROR writing to socket");
 	}
	
 	/// Getting the Username



	char* instBuffer[255];
	int readSize = read( csock , instBuffer , 255);
	if ( readSize < 0 ) 
	{
		std::cout << " weird reading error ... from readValue... getInstruction()\n";
		exit(1);
	} 
	
	else 
	{
		std::string tempString( instBuffer );
		std::string tempsring3("../serverdirectories/" + tempString);
			
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
				
				n = write(csock , end.c_str() , end.size());
			
				/// Getting the Client Side Directory.

				bzero(instBuffer,255);
				readSize = read( csock , instBuffer , 255);
				if ( readSize < 0 ) 
				{
					std::cout << " weird reading error ... from readValue... getInstruction() \n";
					exit(1);
				} 

				else
				{
					std::string tempString2( instBuffer );

					userdetails temp;

					temp.userID = tempString;
					temp.password = tempString1;
					temp.serverDirectory = tempString3;
					temp.clientDirectory = tempString2;

					std::pair < string , userdetails > temppair( temp.userID , temp);
					userDetails.insert(temppair);

					std::ofstream f;
					f.open("details.txt" , ios::app );
					f<<"\n";
					f<<tempString<<" "<<tempString1<<" "<<tempString3<<" "<<tempString2;
					f.close();
					output = "Registered.";
					return 1;
				}
			}
	
	}
	return 0;
}