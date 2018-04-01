/*
    Algorithm:
        Gauss

        A * x = b
        s.a.
            A \in R^{n*n}
            x, b \in R^{n}

    Complexity:
        O(n^3)

    Tested:
        http://www.spoj.com/problems/GS/

    Note:
        `a` must be of size `n * (n + 1)`
        First n columns from `a` forms `A`
        Last column from `a` form `b`

        Return number of solutions (0, 1, oo)
        If there is only one solution for the system
        it will be stored in `ans`
*/

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;

int gauss(vector<vector<double>> a, vector<double> &ans)
{
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col)
    {
        int sel = row;
        for (int i = row; i < n; ++i)
            if (abs(a[i][col]) > abs(a[sel][col]))
                sel = i;
        if (abs(a[sel][col]) < eps)
            continue;
        for (int i = col; i <= m; ++i)
            swap(a[sel][i], a[row][i]);
        where[col] = row;

        for (int i = 0; i < n; ++i)
            if (i != row)
            {
                double c = a[i][col] / a[row][col];
                for (int j = col; j <= m; ++j)
                    a[i][j] -= a[row][j] * c;
            }

        ++row;
    }

    ans.assign(m, 0);

    for (int i = 0; i < m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];

    for (int i = 0; i < n; ++i)
    {
        double sum = 0;
        for (int j = 0; j < m; ++j)
            sum += ans[j] * a[i][j];
        if (abs(sum - a[i][m]) > eps)
            return 0;
    }

    for (int i = 0; i < m; ++i)
        if (where[i] == -1)
            return oo;
    return 1;
}
