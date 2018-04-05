#include <bits/stdc++.h>
const int MAX = 5e5 + 10;
typedef long long ll;
using namespace std;
const double EPS = 1e-6;
const int MOD = 1e9 + 7;
#define mul(a, b) ((ll)(a) * b % MOD)

void add(ll& a, ll b, ll p){
	a += b;
	if(a >= p)a -= p;
}

ll mulmod(ll a, ll b, ll p){
	ll s = 0;
	while(b > 0){
		if(b & 1)add(s, a, p);
		add(a, a, p);
		b >>= 1;
	}
	return s;
}

ll powmod(ll a, ll b, ll p){
	ll s = 1;
	while(b > 0){
		if(b & 1)s = mulmod(s, a, p);
		a = mulmod(a, a, p);
		b >>= 1;
	}
	return s;
}


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
		if (x == 1)	return true;
		for (int r = 0; r < s; ++r) {
			if (x == n - 1)	return true;
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
			b1 = mulmod(b1 , b1, n);
			add(b1, 2, n);
			g = __gcd(abs(b1-b0), n);
		}
		b0 = a;
		a = b1;
		if (g != 1 && g != n) return g;
	}
	return 1;
}

vector<ll> get_primes(ll n){
	vector<ll> primes;
	if(n == 1);
	else if(miller_rabin(n)){
		primes.push_back(n);
	}
	else{
		ll f = pollard_brent(n);
		assert(f != 1);
		primes = get_primes(f);
		auto part1 = get_primes(n / f);
		for(auto p : part1)primes.push_back(p);
		sort(primes.begin(), primes.end());
		primes.resize(unique(primes.begin(), primes.end()) - primes.begin());
	}
	return primes;
}

vector<pair<ll, int>> factor(ll n){
	vector<ll> primes = get_primes(n);
	vector<pair<ll, int>> ans;
	for(auto p: primes){
		int e = 0;
		while(n % p == 0){
			e++;
			n /= p;
		}
		ans.push_back({p, e});
	}
	return ans;

}

int main() {
    #ifdef LOCAL_DEBUG
    	freopen ("data.in", "r", stdin );
    	//freopen ("data.out", "w", stdout );
    #endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    #define endl '\n'

    ll n; cin >> n;
    vector<pair<ll, int>> factors = factor(n);
    ll ans = 1;
    for(auto p : factors){
    	for(int i = 1; i < p.second; i += 2)
    		ans *= p.first * p.first;
    }
    cout << ans << endl;

}
