






bool Client::Authenticate( string uID , string password , string&  )  
{
	/// Request for sending info.
	char buffer[INSTR_BUF_SIZE];

	writeToSocket( csock , AUTH );
	
	readFromSocket( csock , buffer , INSTR_BUF_SIZE );

	string str(buffer);

	if(str.compare(ACCEPT_AUTH_REQUEST) == 0 )
	{
		writeToSocket( csock , uID );

		readFromSocket( csock , buffer , INSTR_BUF_SIZE );

		writeToSocket( csock , password );

		readFromSocket( csock , buffer , INSTR_BUF_SIZE );

		string valid(buffer);

		if( valid.compare(VALID_USER) == 0 )
		{
			writeToSocket( csock , GIVE_DIR );

			readFromSocket( csock , );

			writeToSocket( csock , GIVE_DIR );

			readFromSocket( csock , )
		}
	} 
}