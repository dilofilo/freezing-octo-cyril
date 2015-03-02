#ifndef SYNC_CPP
#define SYNC_CPP
#include "client.h"
#include "clientdefinitions.h"
#include "../../common/instructions.h"
#include "../../common/communications.h"

#include <unordered_map>
#include <boost/filesystem.hpp>

using namespace std;
bool Client::handleSync() {
//    string syncreq(SYNC_REQUEST);
//    conn.writeToSocket(syncreq); //Write sync request
//    string tempfile = user.userID + LOG_FILE_SUFFIX;
//    conn.readFromSocket_file(tempfile); //Assert : File ready.
//    set<string>  filenames;
//    unordered_map<string , int> fileversions; //Valid for all files.
//    unordered_map<string , string> fileowners; //File owners.
//    populateFileData_login_normal(filenames , fileversions , fileowners);
//    populateFileData_login_shared(filenames , fileversions , fileowners);
    //Need to figure out which files to upload and download, then send appropriate download requests.

     string syncreq(SYNC_REQUEST);
     conn.writeToSocket(syncreq); //Write sync request

     getServerFiles_login();
     this->dropboxpage->updateServerFiles();

     unordered_map <string,int> myclisync , myservsync;
     unordered_map <string,int>::iterator itsy,it;

     string sync_server_filename = user.userID + "/" + CLIENT_SYNC_DIR + "/" +SERVER_LOG;
     string sync_client_filename = user.userID + "/" + CLIENT_SYNC_DIR + "/" + user.userID + CLIENT_SYNC_DIR ;


     HarmanGetHashSync( sync_client_filename , myclisync , 1);
     HarmanGetHashSync( sync_server_filename , myservsync , 0);

     for(itsy = myclisync.begin(); itsy != myclisync.end(); itsy++){
         f1>>file>>ver;
         it = myservsync.find(itsy->first);
          if ( it == myservsync.end() ){
              // The file is on the client side but not on the server side.
              // Upload the file to the server


          }
          else{
              // The file is on both the client and server side
              //If the client has higher version
              if(itsy->second > it->second){
                // Upload the latest file to the server.
                  data.filename = itsy.first;
                  data.other_user.userID = user.userID;

                  eventHandler(UPLOAD_FILE);

              }
              if(itsy->second < it->second){
                //Download the latest file using itsy->first and itsy->second

              }


                myservsync.erase(itsy->first);

          }

     }

     // To handle the files on the server but not on the client side
     for ( itsy = myservsync.begin(); itsy!=myservsync.end(); itsy++ ){
         // Download the file using filename = itsy->first and the version as itsy->second



     }


    return true;
}

void Client::HarmanGetHashSync( string filename , unordered_map& mymap , int iscli){

    mymap.clear();
    ifstream f1;
    f1.open(filename);
    string file,trash;
    int ver;
    unordered_map< string , int >::iterator it;

    if(iscli){
        while(f1){

            f1>>file>>trash>>ver;
            it = mymap.find (file);
            if ( it == mymap.end() ){
                mymap.insert(file);
                mymap[file]= 1;
            }
            else{
                mymap[file]+=1;
            }

        }

        f1.close();
    }
    else{
        while(f1){

            f1>>file>>ver;
            it = mymap.find (file);
            if ( it == mymap.end() ){
                mymap.insert(file);
                mymap[file]= 1;
            }
            else{
                mymap[file]+=1;
            }

        }

        f1.close();
    }

}



void Client::getServerFiles_login() { //Puts them into the dropbox.
    //Assert : The Server is sending log files accross.
    string syncfilename = user.userID + "/" + CLIENT_SYNC_DIR + "/" +SERVER_LOG;
    //Put file into that file name.
    conn.readFromSocket_file(syncfilename); //Read and saved the file in the Client directory. Need to remove this file once done.
    //Assert : saved the first Log File already.
    /* log keeping idea : filename,filepath, owner, */
    //CLEAR THE DROPBOX HASHTABLES
    this->dropboxpage->filenames.clear();
    this->dropboxpage->fileowners.clear();
    this->dropboxpage->fileversions.clear();

    populateFileData_login_normal( this->dropboxpage->filenames , this->dropboxpage->fileversions , this->dropboxpage->fileowners); //Populate the maps.

    std::string cont(CONTINUE);
    conn.writeToSocket(cont); //Write a continue.

    string sharefilename = user.userID + "/" + CLIENT_SHARE_DIR +"/" +  SERVER_LOG;
    conn.readFromSocket_file(sharefilename); //Read the shared files
    populateFileData_login_shared( this->dropboxpage->filenames , this->dropboxpage->fileversions , this->dropboxpage->fileowners); //Populate the maps.
    //These maps need to go to dropboxpage.
}

void Client::populateFileData_login_normal(std::set<string>& fn , unordered_map<string , int>& fv , unordered_map<string , string>& fo) {

    //Read the file and use it aptly.
    string tfn = user.userID + "/" + CLIENT_SYNC_DIR + "/" + SERVER_LOG;
    string trash;

    fstream reader(tfn , ios::in);
    reader >> trash; reader >> trash ; reader >> trash ; reader >> trash ; //Useless line was sent to me.
    //File is of the form : filename , version
    while(!reader.eof()) {
        string fname;
        int version;
        reader >> fname;
        reader >> version;
        fn.insert(fname);
        fv[fname] += 1;
        fo[fname] = user.userID;
    }
    reader.close();
}



void Client::populateFileData_login_shared(std::set<string>& fn , unordered_map<string , int>& fv , unordered_map<string , string>& fo) {
    string tfn = user.userID + "/" + CLIENT_SHARE_DIR + "/" + SERVER_LOG;
    fstream reader(tfn , ios::in);
    //File is of the form : filename , version
    string trash; reader >> trash ; reader >> trash ; reader >> trash  ;reader >> trash ;reader >> trash ;//useless line was sent to me.
    while(!reader.eof()) {
        string fname;
        string owner;
        reader >> fname;
        reader >> owner;
        fn.insert(fname);
        fo[fname] = owner;
        fv[fname] = 1; //Sets the version of the file to 1.
    }
    reader.close();
} //Assert : Read the file.


#endif
