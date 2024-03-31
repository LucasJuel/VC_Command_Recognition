#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
    // string name;
    
    // vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};
    // cout << "Enter you name: ";

    // getline(std::cin, name);
    // for(const string& word : msg){
    //     cout << word << " ";
    // }

    // cout << endl << "Hello " << name << "!" << endl;
    // return 0;

    //Number guessing game.
    int randomNumber;
    bool guessed = false;

    srand(time(0));

    randomNumber = rand() % 10 + 1;
    cout << "Welcome to the number guessing game! " << endl;

    while(!guessed){
        string guess;
        cout << "What is your guess? ";
        getline(std::cin, guess);

        try {
            int guessNum = std::stoi(guess);
            if(guessNum > randomNumber){
                cout << "Your guess was too large." << endl;
            } else if (guessNum < randomNumber){
                cout << "Your guess was too small." << endl;
            } else {
                cout << "Contratulations you've won!" << endl;
                guessed = true;
            }
        } catch (const invalid_argument& e){
            cerr << "Invalid guess (" << e.what() << ")" << endl;
        }


    }
    cout << "The number was: " << randomNumber << endl;
    return 0;
}