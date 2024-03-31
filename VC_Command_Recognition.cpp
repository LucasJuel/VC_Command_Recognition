#include <iostream>
#include <string>
#include <portaudio.h>

using namespace std;

static void checkErr(PaError err){
    if(err != paNoError){
        cout << "PortAudio Error :" << Pa_GetErrorText(err) << endl;
        exit(EXIT_FAILURE); 
    }
}

int main(){
    PaError err;
    err = Pa_Initialize();
    checkErr(err);

    int numDevices = Pa_GetDeviceCount(); 
    cout << numDevices << endl;

    if(numDevices < 0){
        cerr << Pa_GetErrorText(numDevices) << endl;
        return 1;
    } else if(numDevices = 0){
        cout << "No devides available on this machine." << endl;
        return 1;
    }


    for(int i = 0; i < numDevices; i++){
        
    }   

    err = Pa_Terminate();
    checkErr(err);


    return EXIT_SUCCESS;
}