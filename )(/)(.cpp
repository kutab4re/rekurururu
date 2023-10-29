#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

int recursive_max(int* arr, int first, int second, int depth = 0) {
    cout << string(depth, ' ') << "recursive_max(arr, " << first << ", " << second << ")\n";
    if (first == second) {
        return arr[first];
    }
    else {
        int mid = (first + second) / 2;
        int left_max = recursive_max(arr, first, mid, depth + 1);
        int right_max = recursive_max(arr, mid + 1, second, depth + 1);
        return max(left_max, right_max);
    }
}

int fibonacci(int n, int depth = 0) {
    cout << string(depth, ' ') << "fibonacci(" << n << ")\n";
    if (n == 1 or n == 2)
        return 1;
    if (n < 1)
        return 0;
    else
        return fibonacci(n - 1, depth + 1) + fibonacci(n - 2, depth + 1);
}

int hanoi_tower(int n, char s1, char s2, char s3, int& moves, int depth = 0) {
    cout << string(depth, ' ') << "hanoi_tower(" << n << ", " << s1 << ", " << s2 << ", " << s3 << ")\n";
    if (n == 1) {
        moves++;
        cout << s1 << "->" << s3 << " ; ";
        return moves;
    }
    moves = hanoi_tower(n - 1, s1, s3, s2, moves, depth + 1);
    moves++;
    cout << s1 << "->" << s3 << " ; ";
    moves = hanoi_tower(n - 1, s3, s2, s1, moves, depth + 1);
    return moves;
}

bool safehorce(int x, int y, int n, int sol[8][8]) {
    return (x >= 0 && x < n && y >= 0 && y < n && sol[x][y] == -1);
}

int horcestep(int x, int y, int movei, int n, int sol[8][8], int x_mv[8], int y_mv[8], int depth = 0) {
    cout << string(depth * 2, ' ') << "horcestep(" << x << ", " << y << ", " << movei << ", " << n << ")\n";
    if (movei == n * n)
        return true;

    for (int k = 0; k < 8; k++) {
        int nextX = x + x_mv[k];
        int nextY = y + y_mv[k];
        if (safehorce(nextX, nextY, n, sol)) {
            sol[nextX][nextY] = movei;
            if (horcestep(nextX, nextY, movei + 1, n, sol, x_mv, y_mv, depth + 1))
                return true;
            else
                sol[nextX][nextY] = -1;
        }
    }

    return false;
}

void horcetour(int n, int startX, int startY) {
    int sol[8][8];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            sol[i][j] = -1;

    int xMove[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int yMove[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    sol[startX][startY] = 0;
    if (horcestep(startX, startY, 1, n, sol, xMove, yMove)) {
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

bool safequeen(int x, int y, int n, int* queen_p) {
    for (int i = 0; i < x; i++) {
        if (queen_p[i] == y || abs(i - x) == abs(queen_p[i] - y)) {
            return false;
        }
    }
    return true;
}

void queen(int x, int n, int* queen_p, int& solutions, int depth = 0) {
    cout << string(depth * 2, ' ') << "queen(" << x << ", " << n << ")\n";
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

    for (int y = 0; y < n; y++) {
        if (safequeen(x, y, n, queen_p)) {
            queen_p[x] = y;
            queen(x + 1, n, queen_p, solutions, depth + 1);
            queen_p[x] = -1;
        }
    }
}

void sol_queens(int n) {
    int* queenPositions = new int[n];
    for (int i = 0; i < n; i++) {
        queenPositions[i] = -1;
    }

    int solutions = 0;
    queen(0, n, queenPositions, solutions);
    cout << "Всего найдено решений: " << solutions << endl;

    delete[] queenPositions;
}

int main() {
    setlocale(LC_ALL, "ru");

    while (true) {
        cout << "Рекурсивные алгоритмы:\n1.Рекурсивный вариант поиска максимума массива\n2.Числа Фибоначи\n3.Ханойские башни\n4.Ход коня\n5.Расстановка ферзей\n6.Выход\n" << endl;
        cout << "/---------------------------------------------------------------/\n" << endl;

        int m;
        cout << "Введите номер алгоритма в соответствии с нумерацией в списке : "; cin >> m; cout << "\n";
        cout << "/---------------------------------------------------------------/\n" << endl;

        if (m == 6) {
            cout << "Выход из программы.\n";
            break;
        }

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
        else if (m == 2) {
            cout << "Числа Фибоначи\n";
            int fib_n;
            cout << "Введите номер элемента в последовательности: "; cin >> fib_n; cout << "\n";

            int result = fibonacci(fib_n);

            cout << "Элемент на позиции " << fib_n << ": " << result << "\n" << endl;
        }
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
        else if (m == 4) {
            cout << "Ход коня\n";
            int n, start_x, start_y;
            cout << "Введите размер шахматной доски: "; cin >> n;
            cout << "Введите начальные координаты коня (x y): "; cin >> start_x >> start_y; cout << "\n";

            horcetour(n, start_x, start_y);
            cout << "\n";
            cout << "/---------------------------------------------------------------/\n" << endl;
        }
        else if (m == 5) {
            cout << "Расстановка ферзей\n";
            int queens;
            cout << "Введите количество ферзей: "; cin >> queens; cout << "\n";

            sol_queens(queens);
            cout << "\n";
            cout << "/---------------------------------------------------------------/\n" << endl;
        }
        else {
            cout << "Неверный выбор. Попробуйте еще раз.\n";
        }
    }

    return 0;
}
