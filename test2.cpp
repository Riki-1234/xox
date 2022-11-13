#include <iostream>
#include <cstdlib>
using namespace std;

constexpr int boardSize = 9;
char playerCharacter = '-';
char computerCharacter = '-';
int freeslot[boardSize];

bool all_x_or_o(const char* board) {
    for (size_t i = 0; i != boardSize; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            return false;
        }
    }
    return true;
}

int get_choice() {
    int choice = 0;
    cout << "1. X\n2. O\n";
    cin >> choice;
    cout << endl;
    return choice;
}

void draw(const char* board) {
    cout << "| " << board[0] << " | " << board[1] << " | " << board[2] << " |\n"
         << "-------------\n"
         << "| " << board[3] << " | " << board[4] << " | " << board[5] << " |\n"
         << "-------------\n"
         << "| " << board[6] << " | " << board[7] << " | " << board[8] << " |\n\n";
}

void choose(int choice, char* board) {
    int odg = 0;
    cin >> odg;
    cout << endl;
    int index = odg - 1;

    if (board[index] != playerCharacter && board[index] != computerCharacter) {
        board[index] = playerCharacter;
        freeslot[index] = odg;
    }
    else {
        cout << "Mjesto je vec iskoristeno\n";
        cin >> odg;
        index = odg - 1;
        board[index] = playerCharacter;
        freeslot[index] = odg;
    }
}

void pc_choose(int choice, char* board) {
    time_t current_time = time(NULL);
    srand((unsigned)current_time);
    int pc_odg = rand() % boardSize + 1;

    int index = pc_odg - 1;
    if (board[index] != playerCharacter && board[index] != computerCharacter) {
        board[index] = computerCharacter;
        freeslot[index] = pc_odg;
    }
    else {
        while (board[index] == playerCharacter || board[index] == computerCharacter) {
            pc_odg = rand() % boardSize + 1;
            index = pc_odg - 1;
        }
        board[index] = computerCharacter;
        freeslot[index] = pc_odg;
    }
}

int main() {
    char board[boardSize]{ '1','2','3','4','5','6','7','8','9' };

    const int choice = get_choice();
    playerCharacter = (choice == 1 ? 'X' : 'O');
    computerCharacter = (choice == 2 ? 'X' : 'O');
    if (choice != 1 && choice != 2) {
        cout << "Invalid choice\n";
        return -1;
    }
    while (!all_x_or_o(board)) {
        draw(board);
        cout << "\nUnesite broj gdje zelite unijeti X ili O\n";
        choose(choice, board);
        pc_choose(choice, board);
        cout << freeslot;
        if (all_x_or_o(board)) {
            draw(board);
        }
    }
    return 0;
}
