#include <iostream>
#include <cstdlib>
using namespace std;

constexpr int boardSize = 9;
char playerCharacter = '-';
char computerCharacter = '-';
bool winorloss = false;

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

bool get_mode(){
    int mode = 0;
    cout << "Da li zelite igrati protiv:\n1. Racunara\n2. Drugog igraca\n";
    cin >> mode;
    if(mode == 1) {
        return true;
    }
    else {
        return false;
    }
}

bool mode = get_mode();

void draw(const char* board) {
    cout << endl;
    cout << "| " << board[0] << " | " << board[1] << " | " << board[2] << " |\n"
         << "-------------\n"
         << "| " << board[3] << " | " << board[4] << " | " << board[5] << " |\n"
         << "-------------\n"
         << "| " << board[6] << " | " << board[7] << " | " << board[8] << " |\n\n";
}

void choose(char* board) {
    int odg = 0;
    cin >> odg;
    cout << endl;
    int index = odg - 1;

    if (board[index] != playerCharacter && board[index] != computerCharacter) {
        board[index] = playerCharacter;
    }
    else {
        cout << "Mjesto je vec iskoristeno\n";
        cin >> odg;
        index = odg - 1;
        board[index] = playerCharacter;
    }
}

void player2Choose(char* board) {
    int odg = 0;
    cin >> odg;
    cout << endl;
    int index = odg - 1;

    if (board[index] != playerCharacter && board[index] != computerCharacter) {
        board[index] = computerCharacter;
    }
    else {
        cout << "Mjesto je vec iskoristeno\n";
        cin >> odg;
        index = odg - 1;
        board[index] = computerCharacter;
    }
}

void pc_choose(char *board) {
    time_t current_time = time(nullptr);
    srand((unsigned)current_time);
    int pc_odg = rand() % boardSize + 1;

    int index = pc_odg - 1;
    if (board[index] != playerCharacter && board[index] != computerCharacter) {
        board[index] = computerCharacter;
    }
    else {
        while (board[index] == playerCharacter || board[index] == computerCharacter) {
            pc_odg = rand() % boardSize + 1;
            index = pc_odg - 1;
        }
        board[index] = computerCharacter;
    }
}

void win(const char *board) {
    for (int row = 0; row < 3; row++) {
        if (board[(row * 3) + 0] == playerCharacter
            && board[(row * 3) + 1] == playerCharacter
            && board[(row * 3) + 2] == playerCharacter) {
            if(mode) {
                cout << "Pobijedio si.";
            }
            else {
                cout << "1. igrac je pobijedio.";
            }
            winorloss = true;
        }
        else if(board[(row * 3) + 0] == computerCharacter
                && board[(row * 3) + 1] == computerCharacter
                && board[(row * 3) + 2] == computerCharacter) {
            if(mode) {
                cout << "Izgubio si.";
            }
            else {
                cout << "2. igrac je pobijedio.";
            }
            winorloss = true;
        }
    }
    for(int column = 0; column < 3; column++) {
        if (board[column + 0] == playerCharacter
            && board[column + 3] == playerCharacter
            && board[column + 6] == playerCharacter) {
            if(mode) {
                cout << "Pobijedio si.";
            }
            else {
                cout << "1. igrac je pobijedio.";
            }
            winorloss = true;
        }
        else if(board[column + 0] == computerCharacter
                && board[column + 3] == computerCharacter
                && board[column + 6] == computerCharacter) {
            if(mode) {
                cout << "Izgubio si.";
            }
            else {
                cout << "2. igrac je pobijedio.";
            }
            winorloss = true;
        }
    }
    if (board[0] == playerCharacter
        && board[4] == playerCharacter
        && board[8] == playerCharacter
        || board[2] == playerCharacter
        && board[4] == playerCharacter
        && board[6] == playerCharacter) {
        if(mode) {
            cout << "Pobijedio si.";
        }
        else {
            cout << "1. igrac je pobijedio.";
        }
        winorloss = true;
    }
    else if(board[0] == computerCharacter
            && board[4] == computerCharacter
            && board[8] == computerCharacter
            || board[2] == computerCharacter
            && board[4] == computerCharacter
            && board[6] == computerCharacter) {
        if(mode){
            cout << "Izgubio si.";
        }
        else {
            cout << "2. igrac je pobijedio.";
        }
        winorloss = true;
    }
}

int main() {
    char board[boardSize]{ '1','2','3','4','5','6','7','8','9' };

    const int choice = get_choice();
    playerCharacter = (choice == 1 ? 'X' : 'O');
    computerCharacter = (choice == 2 ? 'X' : 'O');
    if (choice != 1 && choice != 2) {
        cout << "Neispravan izbor\n";
        return -1;
    }
    while (!all_x_or_o(board)) {
        draw(board);
        win(board);
        if(winorloss){
            break;
        }
        if(!mode){
            cout << "1. igrac ";
        }
        cout << "\nUnesite broj gdje zelite unijeti X ili O\n";
        choose(board);
        if (all_x_or_o(board)) {
            draw(board);
            win(board);
            if(winorloss){
                break;
            }
            cout << "Izjednaceno je.";
            break;
        }
        if(!mode){
            draw(board);
            win(board);
            if(winorloss){
                break;
            }
            cout << "\n2. igrac\nUnesite broj gdje zelite unijeti X ili O\n";
            player2Choose(board);
        }
        if(mode){
            pc_choose(board);
        }
    }
    return 0;
}
