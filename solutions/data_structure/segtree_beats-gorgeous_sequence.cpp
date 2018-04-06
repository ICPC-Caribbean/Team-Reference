#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

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
    struct node{
        int mx;      // max in node
        int mx2;     // second (strict) max in node
        int mxc;     // number of elements equal to mx
        int lazy;
        ll sum;
    };
    vector<node> data;

    static constexpr int oo = numeric_limits<int>::max();

    void init(const vector<int>& A){
        int n = A.size();
        data.resize(1  << (33-__builtin_clz(n)));
        build(1, 0, n, A);
    }

    void update_vals(node& nv, const node& left, const node& right){
        nv.mx = max(left.mx, right.mx);
        nv.mx2 = max(left.mx2, right.mx2);
        nv.mxc = 0;
        
        if(left.mx == nv.mx) nv.mxc += left.mxc;
        else nv.mx2 = max(nv.mx2, left.mx);
            
        if(right.mx == nv.mx) nv.mxc += right.mxc;
        else nv.mx2 = max(nv.mx2, right.mx);
        nv.sum = left.sum + right.sum;

        nv.lazy = oo;
    }

    void build( int p, int b, int e, const vector<int>& A){
        if( b + 1 == e ){
            data[p] = node{A[b], -1, 1, oo, A[b]};
            return;
        }
        int m = (b + e) >> 1;

        build(p << 1,  b, m, A);
        build((p << 1) + 1,  m, e, A);

        update_vals(data[p], data[p << 1], data[(p << 1) + 1]);
    }

    void puttag(node& cur, int c){
        //assert(data[p].mx2 < c);
        cur.sum -= (ll)(cur.mx - c) * cur.mxc;
        cur.mx = c;
        cur.lazy = c;
    }
    void pushdown( int p){
        node& cur = data[p];
        if(data[p << 1].mx > cur.lazy) puttag(data[p << 1], cur.lazy);
        if(data[(p << 1) + 1].mx > cur.lazy) puttag(data[1 + (p << 1)], cur.lazy);
        cur.lazy = oo;
    }


    void update_min( int p, int b, int e, int bb, int ee, int c ){

        if( data[p].mx <= c ) return; // break_condition()

        if( b + 1 == e ){ // leaf
                data[p].mx = c;
                data[p].sum = c;
                return;
        }

        if( bb <= b && e <= ee && data[p].mx2 < c){ // tag_condition()
            puttag(data[p], c);
            return;
        }

        if( data[p].lazy != oo ) pushdown(p);

        int m = ( b + e ) >> 1;
        if(bb < m)update_min( p << 1, b, m , bb, ee, c);
        if(m < ee)update_min( (p << 1)+1, m, e, bb, ee, c);
        update_vals(data[p], data[p << 1], data[(p << 1) + 1]);
    }


    int query_max( int p, int b, int e, int bb, int ee ){

        if( bb <= b && e <= ee ) return data[p].mx;

        if( data[p].lazy != oo ) pushdown(p);

        int ans = 0, m = (b + e) >> 1;
        if(bb < m) ans = max(ans, query_max( p << 1, b, m, bb, ee));
        if(m < ee) ans = max(ans, query_max( (p << 1)+1, m, e , bb, ee) );

        return ans;
    }

    ll query_sum( int p, int b, int e, int bb, int ee ){

        if( bb <= b && e <= ee ) return data[p].sum;

        if( data[p].lazy != oo ) pushdown(p);

        ll ans = 0;
        int m = (b + e) >> 1;
        if(bb < m) ans += query_sum( p << 1, b, m, bb, ee);
        if(m < ee) ans += query_sum( (p << 1)+1, m, e , bb, ee);

        return ans;
    }
};

int main() {
    #ifdef LOCAL_DEBUG
        freopen ("data.in", "r", stdin );
        //freopen ("data.out", "w", stdout );
    #endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    #define endl '\n'

    int tests; cin >> tests;
    while(tests--){
        int n, k;
        cin >> n >> k;
        vector<int> A(n);
        for( int i = 0; i < n ; i ++ ) cin >> A[i];

        segtree_beats S;
        S.init(A);

        while( k -- ){
            int s;
            int a, b, c;
            cin >> s >> a >> b; a--;

            if( s == 0 ){
                cin >> c;
                S.update_min( 1, 0, n, a, b,  c);
            }
            else if( s == 1 ) cout <<  S.query_max(1, 0, n, a, b) << endl;
            else cout << S.query_sum(1, 0, n, a, b) << endl;
        }
    }

}
