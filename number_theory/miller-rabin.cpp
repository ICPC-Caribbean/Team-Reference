/*
    Algorithm:
        Miller–Rabin primality test

    Complexity:
        O(itern * log(n))

    Tested:
        http://acm.timus.ru/problem.aspx?space=1&num=1854
        https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1333

    Notes:
        Correct with probability at least 1 / 4 ^ itern
*/

bool miller_rabin(ll n, int itern = 20) {
    if (n <= 1 || (n > 2 && n % 2 == 0)) return false;

    function<bool(ll, int, ll, ll)> suspect = [&](ll a, int s, ll d, ll n) {
        ll x = powmod(a, d, n);
        if (x == 1) return true;
        for (int r = 0; r < s; ++r) {
            if (x == n - 1) return true;
            x = mulmod(x, x, n);
        }
        return false;
    };

    ll d = n - 1; int s = 0;
    while (d % 2 == 0) ++s, d /= 2;
    for (int i = 0; i < itern; i++){
        ll tst = rand() % (n - 1) + 1;
        if (__gcd(tst, n) > 1 || !suspect(tst, s, d, n))
            return false;
    }
    return true;
}
