/*
    Algorithm:
        Manacher

    Complexity:
        O(n)

    Tested:
        http://www.spoj.com/problems/LPS/
*/

vector<int> manacher(const string &s)
{
    int n = 2 * s.length();
    vector<int> rad(n);

    for (int i = 0, j = 0, k; i < n; i += k, j = max(j - k, 0))
    {
        for (; i >= j && i + j + 1 < n
            && s[(i - j) / 2] == s[(i + j + 1) / 2]; ++j);
        rad[i] = j;
        for (k = 1; i >= k &&
            rad[i] >= k && rad[i - k] != rad[i] - k; ++k)
            rad[i + k] = min(rad[i - k], rad[i] - k);
    }

    return rad;
}

// True if s[b:e] is palindrome [b, e] closed interval
bool is_pal(const vector<int> &rad, int b, int e)
{
    int n = rad.size() / 2;
    return b >= 0 && e < n && rad[b + e] >= e - b + 1;
}
