#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;
// Recursive function to find the maximum element in an array
int recursive_max(int* arr, int first, int second, int depth = 0) {
    // display the current function call
    cout << string(depth, ' ') << "recursive_max(arr, " << first << ", " << second << ")\n";
    // base case
    if (first == second) {
        return arr[first];
    }
    // divide the array into two halves and find the maximum
    else {
        int mid = (first + second) / 2;
        int left_max = recursive_max(arr, first, mid, depth + 1);
        int right_max = recursive_max(arr, mid + 1, second, depth + 1);
        return max(left_max, right_max);
    }
}
// recursive function to calculate the nth fibonacci number
int fibonacci(int n, int depth = 0) {
    // display the current function call
    cout << string(depth, ' ') << "fibonacci(" << n << ")\n";
    // base case
    if (n == 1 or n == 2)
        return 1;
    if (n < 1)
        return 0;
    // sum of the previous two Fibonacci numbers
    else
        return fibonacci(n - 1, depth + 1) + fibonacci(n - 2, depth + 1);
}
// recursive function to solve the Tower of Hanoi
int hanoi_tower(int n, char s1, char s2, char s3, int& moves, int depth = 0) {
    // display the current function call
    cout << string(depth, ' ') << "hanoi_tower(" << n << ", " << s1 << ", " << s2 << ", " << s3 << ")\n";
    // base case
    if (n == 1) {
        moves++;
        cout << s1 << "->" << s3 << " ; ";
        return moves;
    }
    // move (n-1) disks from source to auxiliary pole
    moves = hanoi_tower(n - 1, s1, s3, s2, moves, depth + 1);
    // move the remaining one disk from source to destination
    moves++;
    cout << s1 << "->" << s3 << " ; ";
    // move the (n-1) disks from auxiliary pole to destination
    moves = hanoi_tower(n - 1, s3, s2, s1, moves, depth + 1);
    return moves;
}
// helper function to check if a horse move is safe on a chessboard
bool safehorse(int x, int y, int n, int sol[8][8]) {
    return (x >= 0 && x < n && y >= 0 && y < n && sol[x][y] == -1);
}
// recursive function to solve the horse tour
int horsestep(int x, int y, int movei, int n, int sol[8][8], int x_mv[8], int y_mv[8], int depth = 0) {
    // display the current function call
    cout << string(depth * 2, ' ') << "horcestep(" << x << ", " << y << ", " << movei << ", " << n << ")\n";
    // base case
    if (movei == n * n)
        return true;
    // try all possible moves for the horse
    for (int k = 0; k < 8; k++) {
        int nextX = x + x_mv[k];
        int nextY = y + y_mv[k];
        // check if the move is safe
        if (safehorse(nextX, nextY, n, sol)) {
            // mark the current square as visited
            sol[nextX][nextY] = movei;
            // recursively attempt the next move
            if (horsestep(nextX, nextY, movei + 1, n, sol, x_mv, y_mv, depth + 1))
                return true;
            // backtrack if the move doesn't lead to a successful tour
            else
                sol[nextX][nextY] = -1;
        }
    }

    return false;
}
// Function to initiate the horse tour and print the solution
void horsetour(int n, int startX, int startY) {
    int sol[8][8];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            sol[i][j] = -1;
    // possible moves for the horse
    int xMove[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int yMove[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    // start the tour from the specified position
    sol[startX][startY] = 0;

    if (horsestep(startX, startY, 1, n, sol, xMove, yMove)) {
        cout << "Решение существует:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << setw(2) << sol[i][j] << " ";
            cout << endl;
        }
    }
    else {
        cout << "Решение не существует.\n";
    }
}
// helper function to check if a queen can be placed safely
bool safequeen(int x, int y, int n, int* queen_p) {
    for (int i = 0; i < x; i++) {
        if (queen_p[i] == y || abs(i - x) == abs(queen_p[i] - y)) {
            return false;
        }
    }
    return true;
}
// recursive function to solve the N-Queens
void queen(int x, int n, int* queen_p, int& solutions, int depth = 0) {
    // display the current function call
    cout << string(depth * 2, ' ') << "queen(" << x << ", " << n << ")\n";
    // base case
    if (x == n) {
        cout << "Решение " << solutions + 1 << ":\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (queen_p[i] == j) {
                    cout << "1 ";
                }
                else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
        cout << endl;
        solutions++;
        return;
    }
    // try placing the queen in each column of the current row
    for (int y = 0; y < n; y++) {
        if (safequeen(x, y, n, queen_p)) {
            // place the queen and recursively proceed to the next row
            queen_p[x] = y;
            queen(x + 1, n, queen_p, solutions, depth + 1);
            // reset the placement
            queen_p[x] = -1;
        }
    }
}
// function to find and print all solutions to the N-Queens
void sol_queens(int n) {
    int* queenPositions = new int[n];
    for (int i = 0; i < n; i++) {
        queenPositions[i] = -1;
    }
    // variable to count the number of solutions found
    int solutions = 0;
    queen(0, n, queenPositions, solutions);
    cout << "Всего найдено решений: " << solutions << endl;

    delete[] queenPositions;
}
// main function
int main() {
    setlocale(LC_ALL, "ru");

    while (true) {
        cout << "Рекурсивные алгоритмы:\n1.Рекурсивный вариант поиска максимума массива\n2.Числа Фибоначи\n3.Ханойские башни\n4.Ход коня\n5.Расстановка ферзей\n6.Выход\n" << endl;
        cout << "/---------------------------------------------------------------/\n" << endl;

        int m;
        cout << "Введите номер алгоритма в соответствии с нумерацией в списке : "; cin >> m; cout << "\n";
        cout << "/---------------------------------------------------------------/\n" << endl;
        // out of the program
        if (m == 6) {
            cout << "Выход из программы.\n";
            break;
        }
        // print recursive_max
        if (m == 1) {
            cout << "Рекурсивный вариант поиска максимума массива\n";
            int n;
            cout << "Введите размер массива: "; cin >> n; cout << "\n";

            int* arr = new int[n];

            cout << "Сформированный массив : {";
            for (int i = 0; i < n; ++i) {
                arr[i] = rand() % 40;
                cout << setw(2) << arr[i];
                if (i < n - 1) {
                    cout << ", ";
                }
            }
            cout << "}\n";

            int result = recursive_max(arr, 0, n - 1);

            cout << "Максимум массива: " << result << "\n" << endl;

            delete[] arr;
            cout << "/---------------------------------------------------------------/\n" << endl;
        }
        // print fibonacci
        else if (m == 2) {
            cout << "Числа Фибоначи\n";
            int fib_n;
            cout << "Введите номер элемента в последовательности: "; cin >> fib_n; cout << "\n";

            int result = fibonacci(fib_n);

            cout << "Элемент на позиции " << fib_n << ": " << result << "\n" << endl;
        }
        // print hanoi_tower
        else if (m == 3) {
            cout << "Ханойские башни\n";
            int disks;
            cout << "Введите количество дисков: "; cin >> disks; cout << "\n";
            int moves = 0;
            hanoi_tower(disks, '1', '2', '3', moves);
            cout << "\nКоличество перестановок: " << moves << endl;
            cout << "\n";
            cout << "/---------------------------------------------------------------/\n" << endl;

        }
        //print horsetour
        else if (m == 4) {
            cout << "Ход коня\n";
            int n, start_x, start_y;
            cout << "Введите размер шахматной доски: "; cin >> n;
            cout << "Введите начальные координаты коня (x y): "; cin >> start_x >> start_y; cout << "\n";

            horsetour(n, start_x, start_y);
            cout << "\n";
            cout << "/---------------------------------------------------------------/\n" << endl;
        }
        // print sol_queens
        else if (m == 5) {
            cout << "Расстановка ферзей\n";
            int queens;
            cout << "Введите количество ферзей: "; cin >> queens; cout << "\n";

            sol_queens(queens);
            cout << "\n";
            cout << "/---------------------------------------------------------------/\n" << endl;
        }
        // incorrect choice
        else {
            cout << "Неверный выбор. Попробуйте еще раз.\n";
        }
    }

    return 0;
}
