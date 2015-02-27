bool Client::Ping()
{
	writeToSocket( csock , REQUEST_PING );
	
	char buffer[INSTR_BUF_SIZE]; 
	
	readFromSocket( csock , buffer , INSTR_BUF_SIZE);

	string str (buffer);

	if( message.compare(ACCEPT_PING) == 0 )
	{
		return 1;
	} 
	else 
	{
		return 0;
	}

}