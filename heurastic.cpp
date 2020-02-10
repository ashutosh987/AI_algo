#include <bits/stdc++.h>
using namespace std;
int SIZE = 8;
int opt_cost = SIZE;
struct ChessData
{
    string board;
    int cost;
    long int heuristic;
    ChessData(string board, int cost, long int heuristic)
        : board(board), cost(cost), heuristic(heuristic)
    {
    }
};

long int fact(int x)
{
    long int fact = 1;
    for (long int i = 1; i <= x; i++)
        fact *= x;
    return fact;
}

long int comb(int a, int b)
{
    return fact(a) / (fact(b) * fact(a - b));
}

ChessData initChessBoard()
{
    string arr;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            arr += '0';
    return ChessData(arr, 0, 0);
}

int find(string arr)
{
    int i;
    for (i = 0; i < SIZE; i++)
    {
        int flag = 0;
        for (int j = 0; j < SIZE; j++)
        {
            if (arr[SIZE * i + j] == '1')
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            return i;
    }
    return i;
}

long int gen_heuristic(string arr)
{
    long int conf = 0;
    for (int i = 0; i < SIZE; i++)
    {
        int rowSum = 0;
        int colSum = 0;
        for (int j = 0; j < SIZE; j++)
        {
            rowSum += arr[SIZE * i + j] - '0';
            colSum += arr[SIZE * j + i] - '0';
        }
        conf += comb(rowSum, 2) + comb(colSum, 2);
    }
    for (int i = 0; i < SIZE; i++)
    {
        int leftSum = 0;
        int rightSum = 0;
        for (int j = 0; j + i < SIZE; j++)
        {
            leftSum += arr[SIZE * j + j + i] - '0';
            rightSum += arr[SIZE * (j + i) + j] - '0';
        }
        conf += comb(leftSum, 2) + comb(rightSum, 2);
    }
    for (int i = 0; i < 2 * SIZE - 1; i++)
    {
        int leftSum = 0;
        int rightSum = 0;
        if (i < SIZE)
        {
            for (int j = 0; i - j >= 0; j++)
            {
                leftSum += arr[SIZE * j + i - j] - '0';
            }
        }
        else
        {
            for (int j = i - SIZE + 1; j < SIZE; j++)
            {
                rightSum += arr[SIZE * j + i - j] - '0';
            }
        }
        conf += comb(leftSum, 2) + comb(rightSum, 2);
    }
    return conf;
}

void display(string arr)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (arr[SIZE * i + j] == '1')
                printf("* ");
            else
                printf("_ ");
        }
        printf("\n");
    }
}
struct compareBoard
{
    bool operator()(ChessData const &c1, ChessData const &c2)
    {
        return c1.cost > c2.cost;
    }
};

int main()
{
    ChessData sol = initChessBoard();

    priority_queue<ChessData, vector<ChessData>, compareBoard> ucs;
    int count = 1;
    ucs.push(sol);

    while (!(ucs.empty()))
    {

        ChessData c = ucs.top();
        ucs.pop();
        string probableAns = c.board;

        if (c.cost + c.heuristic > opt_cost)
            continue;

        int i = find(probableAns);

        if (i == SIZE)
        {
            cout << "Solution Number" << count << "\n";
            display(probableAns);
            cout << "\n\n";
            count++;
        }
        else
        {

            for (int j = 0; j < SIZE; j++)
            {
                probableAns = probableAns.substr(0, SIZE * i + j) + "1" + probableAns.substr(SIZE * i + j + 1);
                ucs.push(ChessData(probableAns, c.cost + 1, gen_heuristic(probableAns)));
                probableAns = c.board;
            }
        }
    }
    return 0;
}