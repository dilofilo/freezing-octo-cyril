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

//     cout << " I'M GONNA SYNC! \n";
//     string syncreq(SYNC_REQUEST);
//     conn.writeToSocket(syncreq); //Write sync request
//     cout << "SYNC FOR ME< BIATCH \n";

//     getServerFiles_login();
//     cout << " SERVER FILES GAWT \n";
//     this->dropboxpage->updateServerFiles();
//     cout << "Update server files() \n";
    //Use the present files to do the syncing.
     std::set<string> fns;
     unordered_map <string,int> myclisync , myservsync;
     std::unordered_map<string,int>::iterator itsy , it;
     std::unordered_map<string , string> fos; //Not used.

     string sync_client_filename = user.userID + "/" + CLIENT_SYNC_DIR + "/" + user.userID + CLIENT_SYNC_DIR ;
     populateFileData_login_normal(fns , myservsync , fos);//Populates it with server side stuff.

     //Now, to populate the lists from the client side.
     fstream readClientLog;
     string fn,p,v; //FileName , Path , Version.
     readClientLog.open(sync_client_filename , ios::in);
     while( !readClientLog.eof() ) { //populate the tables with the client side log.
         readClientLog >> fn;
         readClientLog >> p;
         readClientLog >> v;
         if ( fn=="" ) continue;
         fns.insert(fn);
         myclisync[fn] = atoi(v.c_str());
     }
     readClientLog.close();


     cout << "printing clientsync \n";
     for(itsy = myclisync.begin(); itsy != myclisync.end(); itsy++){
         cout<<itsy->first<<" "<<itsy->second<<endl;
     }
     cout << "printing servsync \n";
     for(itsy = myservsync.begin(); itsy != myservsync.end(); itsy++){
         cout<<itsy->first<<" "<<itsy->second<<endl;
     }
     cout << "entering itsy bitsy loop\n";

     for(itsy = myclisync.begin(); itsy != myclisync.end(); itsy++){
     cout << "entered itsy bitsy loop\n";

         it = myservsync.find(itsy->first);
          if ( it == myservsync.end() ){// The file is on the client side but not on the server side...Upload the file onto the server.
              cout<<"Writing to server  1"<<endl;
              boost::filesystem::path cwd_p(boost::filesystem::current_path());
              string cwd = cwd_p.string();
              data.filename = cwd + itsy->first;
              data.other_user.userID = user.userID;
              cout << "file=" << data.filename << " || owner=" << data.other_user.userID << "\n";
              this->eventHandler(UPLOAD_FILE);
          } else{// The file is on both the client and server side
              if(itsy->second > it->second){//If the client has higher version
                // Upload the latest file to the server.
                  cout<<"Writing to server 2"<<endl;
                  boost::filesystem::path cwd_p(boost::filesystem::current_path());
                  string cwd = cwd_p.string();
                  data.filename = cwd + itsy->first;
                  data.other_user.userID = user.userID;
                  cout << "file=" << data.filename << " || owner=" << data.other_user.userID << "\n";
                  eventHandler(UPLOAD_FILE);
              }
              if(itsy->second < it->second){//Download the latest file using itsy->first and itsy->second
                  cout<<"Writing to client 3"<<endl;
                  data.filename = it->first;
                  data.other_user.userID = user.userID;
                  cout << "file=" << data.filename << " || owner=" << data.other_user.userID << "\n";
                  eventHandler(DOWNLOAD_FILE);
              }
              //Dont need to do anything when their versions are equal.
              myservsync.erase(itsy->first); //GET RID OF FILES THAT ARE ON THE CLIENT.
          }
     }
     cout << "just before the special \n";
     // To handle the files on the server but not on the client side
     for ( itsy = myservsync.begin(); itsy!=myservsync.end(); itsy++ ){
         // Download the file using filename = itsy->first and the version as itsy->second
         if ( itsy->first == "" ) {

         } else {
             cout<<"Writing to for"<<endl;
             data.filename = itsy->first;
             data.other_user.userID = user.userID;
             eventHandler(DOWNLOAD_FILE);
         }
     }
     return true;
}

void Client::HarmanGetHashSync( string filename , unordered_map<string,int>& mymap , int iscli){

    mymap.clear();
    fstream f1;
    f1.open(filename.c_str() , ios::in);
    string file,trash;
    string ver;
    unordered_map< string , int >::iterator it;

    if(iscli==1) { //Reading client side sync file
        while(!f1.eof()){

            f1>>file;
            f1>>trash;
            f1>>ver;

            it = mymap.find (file);
            if ( it == mymap.end() ) {
                if ( file== "") {
                    //Random null string, we hate you.
                } else {
                    mymap[file]= 1;
                }
            }
            else{
                if ( file=="") {
                } else {
                    mymap[file] = atoi(ver.c_str());
                }
            }
        }
    }
    else{ //reading server side sync side.
        cout << " reading server side sync file\n";
        string trash;
        f1>>trash;
        cout << "##TRASH=" << trash << "\n";
        f1>>trash;
        cout << "##TRASH=" << trash << "\n";
        f1>>trash;
        cout << "##TRASH=" << trash << "\n";
        f1>>trash;
        cout << "##TRASH=" << trash << "\n";
        while(!f1.eof()){
            cout << "entered while loop\n";
            f1>>file;
            f1>>ver;
            cout << "encountered file=" << file << "\n";
            it = mymap.find (file);
            if ( it == mymap.end() ){
                if ( file == "") {
                } else {
                    mymap[file]= 1;
                }
            }
            else{
                if ( file=="" ) {
                    //Random Null character, ew hate you so much.
                } else {
                    mymap[file]+=1;
                }

            }
        }
    }
    f1.close();
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
