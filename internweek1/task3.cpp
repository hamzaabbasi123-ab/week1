#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to display game instructions
void displayInstructions() {
    cout << "\n=== NUMBER GUESSING GAME ===" << endl;
    cout << "I'm thinking of a number between 1 and 100." << endl;
    cout << "Try to guess it! I'll give you hints along the way." << endl;
    cout << "Let's see how many attempts you need!" << endl;
    cout << "======================================" << endl;
}

// Function to play the game
void playGame() {
    // Initialize random seed
    srand(time(0));
    
    // Generate random number between 1 and 100
    int secretNumber = rand() % 100 + 1;
    int guess;
    int attempts = 0;
    
    cout << "\nI've picked a number. Start guessing!" << endl;
    
    // Game loop
    while(true) {
        cout << "Enter your guess (1-100): ";
        cin >> guess;
        attempts++;
        
        // Validate input
        if(cin.fail() || guess < 1 || guess > 100) {
            cin.clear(); // Clear error flag
            cin.ignore(1000, '\n'); // Discard invalid input
            cout << "Please enter a valid number between 1 and 100." << endl;
            continue;
        }
        
        // Check guess
        if(guess == secretNumber) {
            cout << "\n🎉 Congratulations! You guessed it!" << endl;
            cout << "The number was: " << secretNumber << endl;
            cout << "Number of attempts: " << attempts << endl;
            
            // Performance feedback
            if(attempts <= 5) {
                cout << "🌟 Excellent! You're a natural!" << endl;
            } else if(attempts <= 10) {
                cout << "👍 Good job! You're getting there!" << endl;
            } else {
                cout << "💪 Keep practicing! You'll get better!" << endl;
            }
            break;
        }
        else if(guess > secretNumber) {
            // Give hints based on how close the guess is
            if(guess - secretNumber > 20) {
                cout << "Way too high! ❄️" << endl;
            } else {
                cout << "Too high! ⬇️" << endl;
            }
        }
        else {
            // Give hints based on how close the guess is
            if(secretNumber - guess > 20) {
                cout << "Way too low! 🔥" << endl;
            } else {
                cout << "Too low! ⬆️" << endl;
            }
        }
    }
}

// Function to ask if player wants to play again
bool playAgain() {
    char choice;
    cout << "\nWould you like to play again? (y/n): ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

int main() {
    cout << "Welcome to the Number Guessing Game!" << endl;
    
    do {
        displayInstructions();
        playGame();
    } while(playAgain());
    
    cout << "\nThank you for playing! Goodbye! 👋" << endl;
    return 0;
}