// http://www.spoj.com/problems/VFMUL

#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef complex<double> point;

void fft(point a[], int n, int sign = +1)
{
	const double theta = 8 * sign * atan(1.0) / n; 
	for (int i = 0, j = 1; j < n - 1; ++j)
	{
		for (int k = n >> 1; k > (i ^= k); k >>= 1);
		if (j < i) swap(a[i], a[j]);
	}
	for (int m, mh = 1; (m = mh << 1) <= n; mh = m)
		for (int i = 0, irev = 0; i < n; i += m)
		{
			point w = exp(point(0, theta * irev));
			for (int k = n >> 2; k > (irev ^= k); k >>= 1);
			for (int j = i; j < mh + i; ++j)
			{
				int k = j + mh;
				point x = a[j] - a[k];
				a[j] += a[k];
				a[k] = w * x;
			}
		}
}

typedef long long ll;

// this only works if intermediate values are less than 10^15
vector<ll> convolve(const vector<int> &a, const vector<int> &b)
{
	int n = a.size() + b.size() - 1, m = 1;
	while (m < n) m *= 2;
	vector<point> p(m), pa(m), pb(m);
	for (int i = 0; i < m; ++i)
	{
		int x = (i < a.size() ? a[i] : 0);
		int y = (i < b.size() ? b[i] : 0);
		p[i].real(x); p[i].imag(y);
	}
	fft(p.data(), m, +1);
	for (int i = 0; i < m; ++i)
	{
		int j = (m - i) & (m - 1);
		point u = p[i], v = conj(p[j]);
		pa[i] = (u + v) * point(0.5, 0);
		pb[i] = (u - v) * point(0, -0.5);
	}
	// pa = fft(a), pb = fft(b)
	for (int i = 0; i < m; ++i)
	{
		p[i] = pa[i] * pb[i];
		p[i] /= m;
	}
	fft(p.data(), m, -1);
	vector<ll> ans(n);
	for (int i = 0; i < n; ++i)
		ans[i] = llround(real(p[i]));
	return ans;
}

const int WIDTH = 5;
const ll RADIX = 100000; // = 10^WIDTH

vector<int> parse_int(const string &s)
{
	int n = s.length();
	int m = (n + WIDTH - 1) / WIDTH;
	vector<int> v(m);
	for (int i = 0; i < m; ++i)
	{
		int b = n - WIDTH * i, x = 0;
		for (int a = max(0, b - WIDTH); a < b; ++a)
			x = x * 10 + s[a] - '0';
		v[i] = x;
	}
	return v;
}

void print(vector<ll> v)
{
	int i, N = v.size();
	ll c = 0;
	for (i = 0; i < N; ++i)
	{
		c += v[i];
		v[i] = c % RADIX;
		c /= RADIX;
	}
	while (c > 0)
	{
		v.emplace_back(c % RADIX);
		c /= RADIX;
		++N;
	}
	for (i = N - 1; i > 0 && v[i] == 0; --i);
	cout << v[i];
	for (i--; i >= 0; i--)
		cout << setw(WIDTH) << setfill('0') << v[i];
	cout << endl;
}

int main()
{
#ifdef jcg
	assert(freopen("input.in", "r", stdin));
	// assert(freopen("output.out", "w", stdout));
#else
#endif

	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;

	while (cases--)
	{
		string a, b;
		cin >> a >> b;
		print(convolve(parse_int(a), parse_int(b)));
	}

	return 0;
}
