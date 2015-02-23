
void Server::readDatabase() 
{
	std::ifstream f;
	f.open("details.txt");
	int ctr=0;
	while(!f.eof())
	{
		userdetails temp;
		ctr++;
		f >> temp.userID;
		f >> temp.password;
		f >> temp.serverDirectory;
		f >> temp.clientDirectory;
		std::pair< std::string , userdetails > temppair( temp.userID , temp);

		userDetails.insert(temppair);

	}
	f.close();
	cout << " loaded user database #users= " << ctr << "\n";
}
