/*
    Algorithm:
        Pollard-Brent

    Complexity:
        O(sqrt(s(n))) expected
        where s(n) is the smallest prime divisor of n

    Tested:
        http://acm.timus.ru/problem.aspx?space=1&num=1854
        https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1333

    Notes:
        Use in conjuntion with miller_rabin test for primality
*/


ll pollard_brent (ll n, int itern = 19){
    for(auto p: {2, 3})if(n % p == 0)return p;
    ll b0 = rand ()% n, b1 = (mulmod(b0 , b0, n) + 2)% n, a = b1;
    for (int t = 0, sn = 1; t < itern; t++, sn <<= 1) {
        ll g = __gcd(abs(b1-b0), n);
        for (int len = 0; len < sn && (g == 1 || g == n); len ++) {
            b1 = mulmod(b1 , b1, n);    add(b1, 2, n);
            g = __gcd(abs(b1-b0), n);
        }
        b0 = a;
        a = b1;
        if (g != 1 && g != n) return g;
    }
    return 1;
}
