#include <iostream>
#include <string>
#include <cstring>
#include <portaudio.h>

using namespace std;

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 512

static void checkErr(PaError err){
    if(err != paNoError){
        cout << "PortAudio Error :" << Pa_GetErrorText(err) << endl;
        exit(EXIT_FAILURE); 
    }
}

static inline float max(float a, float b){
    return a > b ? a : b;
}

static int patestCallBack(
    const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags,
    void* userData
){
    float* in = (float*)inputBuffer;
    (void) outputBuffer;

    int dispSize = 100;
    printf("\r");

    float volL = 0;
    float volR = 0;

    for(unsigned long i = 0; i < framesPerBuffer; i+=2){
        volL = max(volL, std::abs(in[i]));
        volR = max(volR, std::abs(in[i+1]));
    }

    for (int i = 0; i < dispSize; i++){
        float barProp = i / (float)dispSize;
        if(barProp <= volL && barProp <= volR){
            printf("█");
        } else if (barProp <= volL){
            printf("▀");
        } else if (barProp <= volR){
            printf("▄");
        } else {
            printf(" ");
        }
    }

    fflush(stdout);

    return 0;
}

int main(){
    PaError err;
    err = Pa_Initialize();
    checkErr(err);

    int numDevices = Pa_GetDeviceCount(); 
    cout << numDevices << endl;

    if(numDevices < 0){
        cerr << Pa_GetErrorText(numDevices) << endl;
        exit(EXIT_SUCCESS);
    } else if(numDevices == 0){
        cout << "No devides available on this machine." << endl;
        exit(EXIT_SUCCESS);
    }

    const PaDeviceInfo* deviceInfo;
    for(int i = 0; i < numDevices; i++){
        deviceInfo = Pa_GetDeviceInfo(i);
        printf("Device %d\n", i);
        printf(" Name: %s\n", deviceInfo -> name);
        printf(" maxInputChannel: %d\n", deviceInfo -> maxInputChannels);
        printf(" maxOutputChannel: %d\n", deviceInfo -> maxOutputChannels);
        printf(" SampleRate: %f\n", deviceInfo -> defaultSampleRate);
    }   

    int device = 1;

    PaStreamParameters inputParam;
    PaStreamParameters outputParam;

    memset(&inputParam, 0, sizeof(inputParam));
    inputParam.channelCount = 2;
    inputParam.device = device;
    inputParam.hostApiSpecificStreamInfo = NULL;
    inputParam.sampleFormat = paFloat32;
    inputParam.suggestedLatency = Pa_GetDeviceInfo(device) -> defaultLowInputLatency;

    memset(&outputParam, 0, sizeof(outputParam));
    outputParam.channelCount = 2;
    outputParam.device = device;
    outputParam.hostApiSpecificStreamInfo = NULL;
    outputParam.sampleFormat = paFloat32;
    outputParam.suggestedLatency = Pa_GetDeviceInfo(device) -> defaultLowInputLatency;

    PaStream* stream;
    err = Pa_OpenStream(
        &stream,
        &inputParam,
        &outputParam,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paNoFlag,
        patestCallBack,
        NULL
    );
    checkErr(err);

    err = Pa_StartStream(stream);
    checkErr(err);

    Pa_Sleep(10 * 1000);

    err = Pa_StopStream(stream);
    checkErr(err);

    err = Pa_CloseStream(stream);
    checkErr(err);
    err = Pa_Terminate();
    checkErr(err);


    return EXIT_SUCCESS;
}