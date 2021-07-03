#include <bits/stdc++.h>
#include "AI.h"
using namespace std;

// Make a draw function for the board
class Connect_Four {
public:
  char board[6][7];
  bool states[7];
  bool isgamegoing = true;
  int turns = 0;
  // Class methods
  void draw() {
    // Prints out this current state and print out which column is which
    for (int i = 1; i <= 7; i++) {
      cout << i << " ";
    }
    cout << '\n';
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 7; j++) {
        cout << board[i][j] << " ";
      }
      cout << '\n';
    }
    return;
  }
  int check_input(int n) {
    int temp = n;
    while ((temp > 7 || temp < 1) || states[temp - 1]) {
      cout << "Invalid Number or full column\n";
      cin >> temp;
    }
    return temp;
  }

  int check_input_AI(int n) {
    int temp = n;
    while ((temp > 7 || temp < 1) || states[temp - 1]) {
      cout << "Invalid Number or full column\n";
      temp = random1();
    }
    return temp;
  }
  void player1() {
    turns++; cout << "Turn: " << turns << " , Player One to move!\n";
    // Check if its a number between 1-7
    bool flag = true;
    int n; cin >> n;
    while (flag) {
      n = check_input(n);
      // Check if its in column
      if (!states[n - 1]) {
        // we good
        flag = false;
      } else {
        continue;
      }
    }
    n--;
    for (int i = 5; i >= 0; i--) {
      if (board[i][n] == '.') {
        board[i][n] = 'x';
        if (i == 0) {
          states[n] = true;
        }
        break;
      }
    }
    draw();
    check_for_winner();
    game_state();
  }
  // This is what the ai chooses later
  void player2() {
    turns++; cout << "Turn: " << turns << " , Player Two to move!\n";
    cout << "Input a number from 1-7 inclusive: \n";
    bool flag = true;
    int n; cin >> n;
    while (flag) {
      n = check_input(n);
      // Check if its in column
      if (!states[n - 1]) {
        // we good
        flag = false;
      } else {
        continue;
      }
    }
    n--;
    for (int i = 5; i >= 0; i--) {
      if (board[i][n] == '.') {
        board[i][n] = 'o';
        if (i == 0) {
          states[n] = true;
        }
        break;
      }
    }
    draw();
    check_for_winner();
    game_state();
  }
  void computer() {
    turns++; cout << "Turn: " << turns << " , Computer to move!\n";
    bool flag = true;
    int n = random1();
    while (flag) {
      n = check_input_AI(n);
      // Check if its in column
      if (!states[n - 1]) {
        // we good
        flag = false;
      } else {
        continue;
      }
    }
    cout << "Computer chose: " << n << "!\n";
    n--;
    for (int i = 5; i >= 0; i--) {
      if (board[i][n] == '.') {
        board[i][n] = 'o';
        if (i == 0) {
          states[n] = true;
        }
        break;
      }
    }
    draw();
    check_for_winner();
    game_state();

  }
  void game_state() {
    if (turns == 42 && isgamegoing) {
      cout << "You managed to tie!\n";
    } else if (turns %2 == 0 && isgamegoing) {
      player1();
    } else if (turns %2 == 1 && isgamegoing) {
      computer();
    }
    return;
  }
  void check_for_winner() {
    // There are 3 cases where a player could win
    // Horizontal case:
    int oc = 0, xc = 0;
    for (int i = 0; i < 6; i++) {
      oc = 0, xc = 0;
      for (int j = 0; j < 6; j++) {
        if (board[i][j] == 'o' && board[i][j + 1] == 'o') {
          oc++, xc = 0;
        } else if (board[i][j] == 'x' && board[i][j + 1] == 'x') {
          xc++, oc = 0;
        } else {
          xc = 0, oc = 0;
        }
        // Check if theres a winner for the horizontal case
        if (xc == 3) {
          isgamegoing = false;
          cout << "Player One wins!\n";
          return;
        } else if (oc == 3) {
          isgamegoing = false;
          cout << "Player Two wins!\n";
          return;
        }
      }
    }
    // Vertical Case: flip i and j
    oc = 0, xc = 0;
    for (int j = 0; j < 7; j++) {
      oc = 0, xc = 0;
      for (int i = 5; i >= 0; i--) {
        if (board[i][j] == 'o' && board[i - 1][j] == 'o') {
          oc++, xc = 0;
        } else if (board[i][j] == 'x' && board[i - 1][j] == 'x') {
          xc++, oc = 0;
        } else {
          xc = 0, oc = 0;
        }
        // Check if theres a winner
        if (xc == 3) {
          isgamegoing = false;
          cout << "Player One wins!\n";
          return;
        } else if (oc == 3) {
          isgamegoing = false;
          cout << "Player Two wins!\n";
          return;
        }
      }
    }
    // Diagonal case(s)
    oc = 0, xc = 0;
    for (int a = 5; a >= 0; a--) {
      for (int b = 0; b < 7; b++) {
        int i = a, j = b, ni = i - 1, nj = j + 1;
        oc = 0, xc = 0;
        while (ni >= 0 && nj < 7) {
          if (board[i][j] == 'o' && board[ni][nj] == 'o') {
            oc++, xc = 0;
          } else if (board[i][j] == 'x' && board[ni][nj] == 'x') {
            xc++, oc = 0;
          } else {
            xc = 0, oc = 0;
          }
          if (xc == 3) {
            isgamegoing = false;
            cout << "Player One wins!\n";
            return;
          } else if (oc == 3) {
            isgamegoing = false;
            cout << "Player Two wins!\n";
            return;
          }
          i--, ni--;
          j++, nj++;
        }
      }
    }
    // Backwards diagonal
    oc = 0, xc = 0;
    for (int a = 0; a < 6; a++) {
      for (int b = 0; b < 7; b++) {
        int i = a, j = b, ni = i + 1, nj = j + 1;
        oc = 0, xc = 0;
        while (ni < 6 && nj < 7) {
          if (board[i][j] == 'o' && board[ni][nj] == 'o') {
            oc++, xc = 0;
          } else if (board[i][j] == 'x' && board[ni][nj] == 'x') {
            xc++, oc = 0;
          } else {
            xc = 0, oc = 0;
          }
          if (xc == 3) {
            isgamegoing = false;
            cout << "Player One wins!\n";
            return;
          } else if (oc == 3) {
            isgamegoing = false;
            cout << "Player Two wins!\n";
            return;
          }
          i++, ni++;
          j++, nj++;
        }
      }
    }
    return;
  }
  Connect_Four() {
    // Initialize the board
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 7; j++) {
        board[i][j] = '.';
      }
    }
    // Initialize the states
    for (int i = 0; i < 7; i++) {
      states[i] = false;
    }
    draw();
    player1();
  }
};
int main() {
  Connect_Four game;
  return 0;
}
