// MHE-Sudoku.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <math.h>
#include <time.h>

using namespace std;

class ToFill
{
public:
    int x, y;

    ToFill(int y, int x)
    {
        this->x = x;
        this->y = y;
    }
};

class Solution
{
public:
    int size;
    vector<vector<int>> grid;
    Solution()
    {
    }

    void resize(int s)
    {
        size = s;
        grid.resize(size);

        for (auto &row : grid)
        {
            row.resize(size);
        }
    }

    void SetValue(int y, int x, int n)
    {
        grid[y][x] = n;
    }
};

vector<int> SplitToInt(const string& s, char delim)
{
    vector<int> elems;
    stringstream ss(s);
    string number;
    while (getline(ss, number, delim))
    {
        elems.push_back(stoi(number));
    }
    return elems;
}

Solution Starting()
{
    Solution sol = Solution();

    ifstream file;
    
    file.open("sudoku.txt");

    int n;

    if (file.is_open())
    {
        string line;

        vector<string> numbers;

        int i = 0;

        sol.resize(100);

        while (getline(file, line))
        {
            vector<int> nums = SplitToInt(line, ',');

            for (int j = 0; j < nums.size(); j++)
            {
                sol.SetValue(i, j, nums[j]);
            }
            i++;
        }

        sol.resize(i);

        file.close();
    }
    
    return sol;
}

void ShowSudoku(Solution sol)
{
    for (int i = 0; i < sol.size; i++)
    {
        for (int j = 0; j < sol.size; j++)
        {
            cout << sol.grid[i][j] << " ";
        }
        cout << endl;
    }
}

int CheckRow(Solution sol, int row)
{
    int e;
    int tmp[100] = { 0 };
    
    for (int i = 0; i < sol.size; i++)
    {
        tmp[sol.grid[row][i]]++;
    }
    int sum = 0;

    for (int j = 0; j <= sol.size; j++)
    {
        if (tmp[j] > 0)
        {
            tmp[j]--;
        }
        sum = sum + tmp[j];
    }

    //cout << endl;

    e = sum;

    //cout << sum << endl;

    return e;
}

int CheckCol(Solution sol, int col)
{
    int e;
    int tmp[100] = { 0 };

    for (int i = 0; i < sol.size; i++)
    {
        tmp[sol.grid[i][col]]++;
    }

    int sum = 0;

    for (int j = 0; j <= sol.size; j++)
    {
        if (tmp[j] > 0)
        {
            tmp[j]--;
        }
        sum = sum + tmp[j];
    }

    e = sum;

    //cout << sum << endl;

    return e;
}

int CheckBlock(Solution sol, int bX, int bY, int n)
{
    int e;
    int tmp[100] = { 0 };
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            tmp[sol.grid[bX*n + i][bY*n + j]]++;
            //cout << solution[bX*n + i][bY*n + j] << " ";
        }
        //cout << endl;
    }

    //cout << endl << endl;

    int sum = 0;

    for (int j = 0; j <= n*n; j++)
    {
        if (tmp[j] > 0)
        {
            tmp[j]--;
        }
        sum = sum + tmp[j];
    }

    e = sum;

    //cout << sum << endl;

    return e;

}

int goal_function(Solution sol)
{
    int errors = 0;

    for (int i = 0; i < sol.size; i++)
    {
        errors += CheckRow(sol, i);
        errors += CheckCol(sol, i);
    }

    int bSize = sqrt(sol.size);

    for (int k = 0; k < bSize; k++)
    {
        for (int l = 0; l < bSize; l++)
        {
            errors += CheckBlock(sol, k, l, bSize);
        }
    }

    return errors;
}

int Factorial(int n)
{
    if (n > 1)
    {
        return n * Factorial(n - 1);
    }
    else
    {
        return 1;
    }
}

vector<int> Next(vector<int> &v)
{
    next_permutation(v.begin(), v.end());
    return v;
}

Solution GenerateSolutionBruteForce(Solution sudoku)
{
    Solution solution = Solution();

    solution.resize(sudoku.size);

    vector<int> g;
    g.resize(sudoku.size + 1);
    for (int a = 0; a < g.size(); a++)
    {
        g[a] = sudoku.size;
    }

    g[0] = 81;

    vector<ToFill> f;

    vector<int> v;

    for (int k = 0; k < sudoku.size; k++)
    {
        for (int l = 0; l < sudoku.size; l++)
        {
            if (sudoku.grid[k][l] != 0)
            {
                g[sudoku.grid[k][l]]--;
                solution.grid[k][l] = sudoku.grid[k][l];
                cout << sudoku.grid[k][l] << " " << g[sudoku.grid[k][l]] << endl;
            }
            else
            {
                f.push_back(ToFill(k, l));
            }
        }
        //cout << endl;
    }
    cout << endl << endl;

    cout << g[0] << endl;

    for (int i = 1; i <= 9; i++)
    {
        for (int j = g[i]; j > 0; j--)
        {
            v.push_back(i);
            cout << i;
        }
    }

    cout << endl << endl;

    cout << v.size();

    for (int m = 0; m < Factorial(v.size()); m++)
    {

        cout << Factorial(v.size());
        for (int n = 0; n < f.size(); n++)
        {
            solution.grid[f[n].y][f[n].x] = v[n];
        }
        int e = goal_function(solution);

        cout << e << endl;

        if (e == 0)
        {
            break;
        }
        else
        {
            v = Next(v);
        }
        
    }
    cout << endl << endl;
    return solution;
}

Solution ClearSudoku(Solution s)
{
    for (int k = 0; k < s.size; k++)
    {
        for (int l = 0; l < s.size; l++)
        {
            s.grid[k][l] = 0 ;
        }
    }

    return s;
}

int main()
{
    Solution sudoku = Starting();

    ShowSudoku(sudoku);

    cout << endl << endl;

    srand(time(NULL));

    Solution solution = GenerateSolutionBruteForce(sudoku);
    
    ShowSudoku(solution);
    
    //cout << endl << endl;

    //cout << goal_function(solution);
    
    //int errors = 1;
    //
    //while (errors > 0)
    //{
    //    Solution sol = GenerateSolutionBruteForce(sudoku);
    //    if (goal_function(sol) > 0)
    //    {
    //        errors = goal_function(sol);
    //        ClearSudoku(sol);
    //    }
    //    else
    //    {
    //        errors = 0;
    //        ShowSudoku(sol);
    //    }

    //    //cout << errors << endl;
    //}
}

