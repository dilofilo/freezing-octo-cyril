#ifndef FILE_UPLOAD_CPP
#define FILE_UPLOAD_CPP
#include "client.h"

#include <fstream>
#include "../../common/communications.h"
#include "../../common/instructions.h"
#include "clientdefinitions.h"

#include <boost/filesystem.hpp>

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
    //Get path relative to the present working directory.
    string p = filename;
    string cwd = (boost::filesystem::current_path()).string();
    cwd += user.userID + "/" + CLIENT_SYNC_DIR + "/";
    p = p.substr( cwd.size() + 1 );
    return p;
}

bool Client::uploadNewFile() {
    //ASSERT : data.filetype == FILE_TYPE_NEW
    std::string filename = this->data.filename; //Entire path.
    //reader.open(filename ); //In mode.
    //Need to process file name.
    //TODO : PROCESS FILE NAME. ADD IT TO MY DATABASE.
    std::string filename_processed = processFileName(filename); //Processes the file name.

    conn.writeToSocket(filename_processed); //cout-ing the filename on server side works.
    std::string cont;
    conn.readFromSocket(cont);

    conn.writeToSocket_file( filename , NEW_FILE);

    conn.readFromSocket( cont );
    std::string t(CONTINUE);
    conn.writeToSocket(t);

    string version;
    conn.readFromSocket(version);
    int ver = atoi( version.c_str() );
    //need to add to file.
    this->addToFileLog(this->user.userID , filename_processed , filename , ver);

    conn.writeToSocket(t);
    this->getServerFiles_login();
    this->dropboxpage->updateServerFiles();
    return true;
}


// FORMAT : filename path version\n
bool Client::addToFileLog(string uid, string fname , string fname_withpath , int version) {
    //Add fname to the file called uid.
    string olfile = uid + "/" + CLIENT_SYNC_DIR + "/" + uid + CLIENT_SYNC_DIR;
    string newfile = uid + "/" + CLIENT_SYNC_DIR + "/" + uid + CLIENT_SYNC_DIR + LOG_FILE_SUFFIX;
    fstream reader(olfile , ios::in);
    bool found = true;
    fstream writer(newfile , ios::out);
    while( !reader.eof() ) {
        string file , path , v;

        reader >> file;
        reader >> path;
        reader >> v;
        if ( fname == file ) { //FILE FOUND!
            writer << fname << " " <<  fname_withpath << " " ;
            writer << " " << to_string(version) << "\n";
            found = false;
        } else {
            writer << file << " " <<  path << " ";
            writer << " " << v << "\n";
        }
    }
    if ( found ) {
        writer << fname << " " << fname_withpath << " " << to_string(version) << "\n";
    }
    reader.close();
    writer.close();
    //rename tuid to uid.
    boost::filesystem::path p(olfile);
    boost::filesystem::path ptemp(newfile);
    boost::filesystem::rename(ptemp , p);

    return true;
}

#endif
