/*

	Algorithm:
		Segment Tree Beats

	Complexity:
		O(n log(n))

	Tested:
    	http://acm.hdu.edu.cn/showproblem.php?pid=5306

	Notes:
		http://codeforces.com/blog/entry/57319
 */


struct segtree_beats{
	vector<int> mx; // max in node
	vector<int> mx2; // second (strict) max in node
	vector<int> mxc; // number of elements equal to mx
	vector<int> lazy_val;
	vector<ll> sum;

	static constexpr int oo = numeric_limits<int>::max();

	void init(int n, const vector<int>& A){
		int size = 1  << (33-__builtin_clz(n));
		mx.resize(size);
		mx2.resize(size);
		mxc.resize(size);
		lazy_val.resize(size);
		sum.resize(size);

		build(1, 0, n, A);
	}

	void update_vals(int nod){
		mx[nod] = max(mx[(nod << 1)], mx[(nod << 1)+1]);
		mxc[nod] = (mx[nod] == mx[(nod << 1)] ? mxc[nod << 1] : 0) + (mx[nod] == mx[(nod << 1) + 1] ? mxc[(nod << 1) + 1] : 0);

		if(mx[(nod << 1)] == mx[(nod << 1)+1]) mx2[nod] = max(mx2[(nod << 1)], mx2[(nod << 1)+1]);
		else if(mx[(nod << 1)] < mx[(nod << 1)+1]) mx2[nod] =  max(mx[nod << 1], mx2[(nod << 1) + 1]);
		else mx2[nod] = max(mx[(nod << 1) + 1], mx2[(nod << 1) ]);

		sum[nod] = sum[(nod << 1)] + sum[(nod << 1)+1];
	}

	void build( int p, int b, int e, const vector<int>& A){
	    if( b + 1 == e ){
	        mx[p] = A[b];
	        mx2[p] = -1;
	        mxc[p] = 1;
	        sum[p] = A[b];
	        lazy_val[p] = oo;
	        return;
	    }
	    int m = (b+e)>>1;

	    build(p << 1,  b, m, A);
	    build((p << 1) + 1,  m, e, A);

	    update_vals(p);

	    lazy_val[p] = oo;
	}

	void puttag(int p, int c){
		//assert(mx2[p] < c);
	    sum[p] -= (ll)(mx[p] - c) * mxc[p];
	    mx[p] = c;
	    lazy_val[p] = c;
	}
	void pushdown(int p ){
		if(mx[p << 1] > lazy_val[p]) puttag(p << 1, lazy_val[p]);
		if(mx[(p << 1) + 1] > lazy_val[p]) puttag(1 + (p << 1), lazy_val[p]);
		lazy_val[p] = oo;
	}


	void update_min(int p,  int b, int e, int bb, int ee, int c ){
	    if( mx[p] <= c ) return; // break_condition()

	    if( b + 1 == e ){ // leaf
	            mx[p] = c;
	            sum[p] = c;
	            return;
	    }

	    if( bb <= b && e <= ee && mx2[p] < c){ // tag_condition()
	    	puttag(p, c);
	        return;
	    }

	    if( lazy_val[p] != oo ) pushdown(p );

	    int m = (b+e)>>1;
	    if(bb < m)update_min( p << 1, b, m, bb, ee, c );
	    if(m < ee)update_min( 1 + (p << 1), m, e, bb, ee, c );

	    update_vals(p);
	}


	int query_max( int p, int b, int e, int bb, int ee ){

	    if( bb <= b && e <= ee ) return mx[p];

	    if( lazy_val[p] != oo ) pushdown(p );

	    int m = (b+e)>>1;
	    int ans = 0;
	    if(bb < m)ans = max(ans, query_max(p << 1,  b, m, bb, ee ));
	    if(m < ee)ans = max(ans, query_max( 1 + (p << 1), m, e,  bb, ee ));
	    return ans;
	}

	ll query_sum( int p, int b, int e, int bb, int ee ){

		if( bb <= b && e <= ee ) return sum[p];

		if( lazy_val[p] != oo ) pushdown( p);

		int m = (b+e)>>1;
		ll ans = 0;
		if(bb < m)ans += query_sum( p << 1, b, m, bb, ee );
		if(m < ee)ans += query_sum( 1 + (p << 1), m, e, bb, ee );
		return ans;
	}
};
