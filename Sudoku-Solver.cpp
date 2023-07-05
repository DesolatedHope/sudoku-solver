#include <iostream>
#include <vector>

using namespace std;

class Sudoku{
    public:
        Sudoku(){
            board.clear();
        }
        void solveSudoku(){
            bool k = solver(0, 0);
            return;
        }

        void printSudoku(){
            for(int i = 0; i < 9; i++){
                for(int j = 0; j < 9; j++){
                    cout << board[i][j] << " ";
                    if((j+1)%3 == 0){
                        cout << " ";
                    }
                }
                cout << "\n";
                if((i+1)%3 == 0){
                    cout << "\n";
                }
            }
        }

        bool isValidBoard(){
            vector<int> temp(10);
            vector<vector<int>> box(10, temp), row(10, temp), column(10, temp);
            for(int i = 0; i < 9; i++){
                for(int j = 0; j < 9; j++){
                    int p = (i/3)*3 + (j/3);
                    if(board[j][i] != 0){
                        column[j][board[j][i]]++;
                        if(column[j][board[j][i]] > 1){
                            return false;
                        }
                    }
                    if(board[i][j] != 0){
                        row[i][board[i][j]]++;
                        if(row[i][board[i][j]] > 1){
                            return false;
                        }
                        box[p][board[i][j]]++;
                        if(box[p][board[i][j]] > 1){
                            return false;
                        }
                    }
                }
            }
            return true;
        }

        void takeInput(){
            std::cout << "Enter the 9 x 9 Sudoku board below. Use '0' to denote an empty grid\n";
            for(int i = 0; i < 9; i++){
                vector<int> row(9);
                for(int j = 0; j < 9; j++){
                    cin >> row[j];
                }
                board.push_back(row);
            }
            cout << "\n";
        }
    private:
        bool inRow(int num, int r){
            for(int i = 0; i < 9; i++){
                if(board[r][i] == num){
                    return true;
                }
            }
            return false;
        }

        bool inColumn(int num, int c){
            for(int i = 0; i < 9; i++){
                if(board[i][c] == num){
                    return true;
                }
            }
            return false;
        }

        bool inBox(int num, int r, int c){
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    if(board[r+i][c+j] == num){
                        return true;
                    }
                }
            }
            return false;
        }

        bool solver(int r, int c) {
            if (r == 9) return true;
            if (c == 9) return solver(r + 1, 0);
            if (board[r][c] > 0) return solver(r, c + 1);
            for (int i = 1; i <= 9; i++) {
                if (!inRow(i, r) && !inColumn(i, c) && !inBox(i, r - r%3, c - c%3)) {
                    board[r][c] = i;
                    if (solver(r, c + 1)) {
                        return true;
                    }
                    board[r][c] = 0;
                }
            }
            return false;
        }
        vector<vector<int>> board;
};
int main(){
    Sudoku T;
    T.takeInput();
    if(!T.isValidBoard()){
        cout << "Not A Valid Sudoku Board\n";
    }
    else{
        T.solveSudoku();
        T.printSudoku();
    }
    return 0;
}