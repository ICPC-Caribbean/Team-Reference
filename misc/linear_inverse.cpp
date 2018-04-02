/*
    Algorithm:
        Modular inverse of the first n integers

    Complexity:
        O(n)

    Tested:
        http://codeforces.com/contest/938/problem/E
        http://codeforces.com/blog/entry/16524#comment-415976
*/

void inverse(int n){
    vector<int> fak(n + 1, 1);
    for (int i = 1; i <= n; ++i)
        fak[i] = 1LL * i * fak[i - 1] % mod;

    vector<int> ifak(n + 1);
    ifak[n] = modpow(fak[n], mod - 2); // inverse of the last element O(log mod)

    for (int i = n - 1; ~i; --i)
        ifak[i] = 1LL * ifak[i + 1] * (i + 1) % mod;

    // Inverse of all factorials are already computed

    vector<int> inv(n + 1);
    for (int i = 1; i <= n; ++i)
        inv[i] = 1LL * ifak[i] * fak[i - 1] % mod;

    return inv;
}
