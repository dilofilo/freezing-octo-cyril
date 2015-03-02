//This is a lab session's code.
/**
  @author : Haroun Habeeb (2013CS10225)
  */

#include <pthread.h>
#include <iostream>
#include <unistd.h>
//#include <mutex>

using namespace std;


// Global variables
static int printThis = 0;
static int lockHolder = 0;;
pthread_mutex_t locky = PTHREAD_MUTEX_INITIALIZER;

void * threadAFunction(void * arg) {


    int iA=0;
    while(iA<5) {

            pthread_mutex_lock(&locky);
                cout << "\n A" << iA << printThis;
                sleep(0.2);
                iA++;
            pthread_mutex_unlock(&locky);
            sleep(1);

        }
}

void * threadBFunction(void * arg) {
    int iB=0;
    while(iB < 5) {

            pthread_mutex_lock(&locky);
                cout << "\n B" << iB << printThis;
                printThis++;
                sleep(0.2);

                iB++;
            pthread_mutex_unlock(&locky);
        }


    }



void * threadCFunction(void * arg) {
    int iC = 0;
    while(iC < 5) {

        pthread_mutex_lock(&locky);
                cout << "\n C" << iC << printThis;
                printThis--;
                sleep(0.2);
                iC ++;
        pthread_mutex_unlock(&locky);
    }
}


int main( int args, char* argv[]) {

    pthread_t t1 , t2, t3;
    int i;

    pthread_create(&t1,NULL,threadAFunction,NULL);
    pthread_create(&t2,NULL,threadBFunction,NULL);
    pthread_create(&t3,NULL,threadCFunction,NULL);

    sleep(2);

}

