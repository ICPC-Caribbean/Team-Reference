/*
    Algorithm:
        Find number of partitions of n

    Complexity:
        O(n**(3/2))

    Tested:
        http://coj.uci.cu/24h/problem.xhtml?pid=3980

    Note:
        https://en.wikipedia.org/wiki/Partition_(number_theory)
        https://en.wikipedia.org/wiki/Pentagonal_number_theorem
*/
typedef long long ll;

ll partition(ll n)
{
    vector<ll> dp(n + 1);
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1, r = 1; i - (3 * j * j - j) / 2 >= 0; j++, r *= -1)
        {
            dp[i] += dp[i - (3 * j * j - j) / 2] * r;
            if (i - (3 * j * j + j) / 2 >= 0)
                dp[i] += dp[i - (3 * j * j + j) / 2] * r;
        }
    return dp[n];
}

