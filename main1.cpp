#include <iostream>
using namespace std;


bool all_x_or_o(const char* board) {
    for (size_t i = 0; i != 9; i++) {
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

    const char c = choice == 1 ? 'X' : 'O';
    const int index = odg - 1;

    if (board[index] != 'O' && board[index] != 'X') {
        board[index] = c;
    }
    else {
        cout << "Mjesto je vec iskoristeno\n";
    }
}

void pc_choose(int choice, char* board) {
    int pc_odg = rand() % 9 + 1;
    int randomnum;
    const char pc = choice == 1 ? 'O' : 'X';
    const int index = pc_odg - 1;

    if (board[index] != 'O' && board[index] != 'X') {
        board[index] = pc;
    }
    else if (board[index] == 'O' || board[index] == 'X'){
        while(board[index] == 'O' || board[index] == 'X'){
            randomnum = rand() % 9 + 1;
            pc_odg = randomnum;
        }
        board[index] = pc;
    }
}

int main() {
    char board[9]{ '1','2','3','4','5','6','7','8','9' };

    const int choice = get_choice();
    if (choice != 1 && choice != 2) {
        cout << "Invalid choice\n";
        return -1;
    }
    while (!all_x_or_o(board)) {
        draw(board);
        cout << "Unesite broj gdje zelite unijeti X ili O\n";
        choose(choice, board);
        pc_choose(choice, board);
        if (all_x_or_o(board) == true) {
            draw(board);
        }
    }
    return 0;
}
