#ifndef FILE_UPLOAD_CPP
#define FILE_UPLOAD_CPP
#include "client.h"

#include <fstream>
#include "../../common/communications.h"

bool Client::handleUpload() {
    //Assume that file name is given in data.
    //Read a continue first.
    //Write C_TO_S first?
    std::string cmd( C_TO_S_FILE );
    conn.writeToSocket(cmd);
    std::string cont;
    conn.readFromSocket(cont); //Continue.
    uploadNewFile(); //Who cares for the other two?
    return true;
}
std::string Client::processFileName( std::string filename ) {
    unsigned lastdir = 1 + filename.find_last_of("/");
    return filename.substr(lastdir);
}

bool Client::uploadNewFile() {
    //ASSERT : data.filetype == FILE_TYPE_NEW
    ofstream f;
    f.open("MYTEST.txt");
    std::string filename = this->data.filename; //Entire path.
    f<<(filename);
    f.close();
    std::fstream reader;
    //reader.open(filename ); //In mode.
    //Need to process file name.
    //TODO : PROCESS FILE NAME. ADD IT TO MY DATABASE.
    std::string filename_processed = processFileName(filename); //Processes the file name.
    cout<<"Processed the filename"<<endl;
    conn.writeToSocket(filename_processed); //cout-ing the filename on server side works.
    std::string cont;
    conn.readFromSocket(cont);
    cout<<cont<<endl;
    conn.writeToSocket_file( filename , NEW_FILE);
    cout<<" DONE "<<endl;
    conn.readFromSocket( cont );
    std::string t(CONTINUE);
    conn.writeToSocket(t);
    string version;
    conn.readFromSocket(version);
    int ver = atoi( version.c_str() );
    //need to add to file.
    this->addToFileLog(this->user.userID , filename_processed , filename , ver);
    return true;
}

bool Client::uploadDiffFile() { //UNIMPLEMENTED
    /*
     *The server calculates the diff file. The reason is processing speed ( assuming that the server is actually a server )
     *      The other part of the rationale is data transfer. We are minimizing data transferred by the user.
    */
    std::string filename = this->data.filename;
    std::fstream reader( filename );
    conn.writeToSocket(filename);
    return conn.writeToSocket_file( filename , DIFF_FILE);

}

bool Client::uploadRemoteDiff() { //UNIMPLEMENTED
    std::string filename = this->data.filename;
    std::fstream reader(filename);
    /*
     *TODO :
     *Figure out this part.
    */
}

// FORMAT : filename path version\n
bool Client::addToFileLog(string uid, string fname , string fname_withpath , int version) {
    //Add fname to the file called uid.
    fstream reader(uid , ios::in);
    string tuid = uid+ "_temp";
    fstream writer((tuid) , ios::out);
    while( !reader.eof() ) {
        string file , path;
        int v;
        reader >> file;
        reader >> path;
        reader >> v;
        if ( fname == file ) { //FILE FOUND!
            writer << file << " " <<  path;
            writer << " " << version << "\n";
        } else {
            writer << file << " " <<  path;
            writer << " " << v << "\n";
        }
    }
    reader.close();
    writer.close();
}

#endif
