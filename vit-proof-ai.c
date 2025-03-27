/*
    ===================================
    Snake Game in C++ (Console Version)
    ===================================
    
    Game Objective:
    - The player controls a snake that moves around a board.
    - The snake eats fruits that appear randomly on the board.
    - Each time the snake eats a fruit, it grows in size.
    - The game ends if the snake collides with the wall or itself.

    Controls:
    - Press 'W' to move UP
    - Press 'A' to move LEFT
    - Press 'S' to move DOWN
    - Press 'D' to move RIGHT
    - Press 'X' to quit the game

    Features:
    - The snake starts in the middle of the board.
    - The fruit appears at a random location each time it is eaten.
    - The snake moves in one direction until changed by user input.
    - The player's score increases with each fruit eaten.
*/

#include <iostream>  // Standard input/output operations
#include <conio.h>   // Console input handling (_kbhit, _getch)
#include <windows.h> // Windows-specific functions (Sleep, system("cls"))

using namespace std;

// The size of the game board
const int width = 20;   // Width of the playing area
const int height = 17;  // Height of the playing area

// Variables to store snake and fruit positions
int x, y;               // Position of the snake's head
int fruitX, fruitY;     // Position of the fruit
int score;              // Player's score

// Arrays to store the snake's tail positions
int tailX[100], tailY[100]; // Holds up to 100 segments of tail
int nTail;                  // Number of tail segments

// Enum to define the movement directions of the snake
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir; // Variable to track the current direction of the snake

// Flag to indicate if the game is over
bool gameOver;

// Function to initialize the game
void Setup() {
    gameOver = false;  // Set the game state to running
    dir = STOP;        // The snake does not move initially

    // Place the snake at the center of the board
    x = width / 2;
    y = height / 2;

    // Generate a random position for the fruit
    fruitX = rand() % width;
    fruitY = rand() % height;

    // Initialize the score and reset the snake's length
    score = 0;
    nTail = 0;
}

// Function to draw the game board
void Draw() {
    system("cls"); // Clears the console screen (Windows-only)

    // Draw the top boundary
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    // Draw the main game area (walls, snake, fruit)
    for (int i = 0; i < height; i++) { // Loop through rows
        for (int j = 0; j < width; j++) { // Loop through columns
            if (j == 0) cout << "#"; // Left wall

            if (i == y && j == x) // Draw the snake's head
                cout << "O";
            else if (i == fruitY && j == fruitX) // Draw the fruit
                cout << "F";
            else {
                bool print = false;
                
                // Loop through tail positions to check if the snake's body is here
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Draw a part of the snake's tail
                        print = true;
                    }
                }
                
                if (!print) cout << " "; // Empty space
            }

            if (j == width - 1) cout << "#"; // Right wall
        }
        cout << endl;
    }

    // Draw the bottom boundary
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    // Display the current score
    cout << "Score: " << score << endl;
}

// Function to handle player input
void Input() {
    if (_kbhit()) { // If a key has been pressed
        switch (_getch()) { // Read the pressed key
        case 'a':
            if (dir != RIGHT) dir = LEFT; // Prevents reversing direction
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
            if (dir != UP) dir = DOWN;
            break;
        case 'x':
            gameOver = true; // Quit game
            break;
        }
    }
}

// Function to update the game logic
void Logic() {
    // Store the previous position of the head
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    // Move the tail forward
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) { // Loop through tail segments
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Move the snake's head in the chosen direction
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // Check if the snake hits the wall (Game Over)
    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;

    // Check if the snake collides with itself (Game Over)
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    // Check if the snake eats the fruit
    if (x == fruitX && y == fruitY) {
        score += 10; // Increase score
        fruitX = rand() % width; // Generate new fruit position
        fruitY = rand() % height;
        nTail++; // Increase the snake's length
    }
}

// Main function to run the game loop
int main() {
    Setup(); // Initialize game settings

    while (!gameOver) { // Keep running until the game ends
        Draw();    // Redraw the board
        Input();   // Process player input
        Logic();   // Update the game state
        Sleep(100); // Control game speed (100ms delay)
    }

    // Display final score when the game ends
    cout << "Game Over! Your final score was: " << score << endl;
    return 0;
}
