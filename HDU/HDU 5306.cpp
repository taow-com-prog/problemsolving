/*
    The same as in editorial.
*/

//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int inf_int = 1e9 + 100;
const ll inf_ll = 1e18;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef long double dbl;
#define pb push_back
const double pi = 3.1415926535898;
#define dout if(debug) cout
#define fi first
#define se second
#define sp setprecision
#define sz(a) (int(a.size()))
#define all(a) a.begin(),a.end()
bool debug = 0;
const int MAXN = 1e6 + 100;
const int LOG = 25;
const int mod = 1e9 + 7;
const int MX = 1e6 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;


int a[MAXN];
struct vertex {
    int mx; // maximum value
    int mx2; // second maximum
    int push_mx; // new mx
    int cnt_mx; // number of this max
    ll sum; // sum of all
};

vertex t[4 * MAXN];

#define left v<<1,tl,tm
#define right v<<1|1,tm+1,tr

void combine(int v) {
    int v1 = v << 1, v2 = v << 1 | 1;
    t[v].mx = max(t[v1].mx, t[v2].mx);
    t[v].sum = t[v1].sum + t[v2].sum;
    t[v].mx2 = max(t[v1].mx2, t[v2].mx2);
    if (min(t[v1].mx, t[v2].mx) != t[v].mx) {
        t[v].mx2 = max(t[v].mx2, min(t[v1].mx, t[v2].mx));
    }
    t[v].cnt_mx = 0;
    if (t[v1].mx == t[v].mx) {
        t[v].cnt_mx += t[v1].cnt_mx;
    }
    if (t[v2].mx == t[v].mx) {
        t[v].cnt_mx += t[v2].cnt_mx;
    }
    assert(t[v].push_mx == -1);
}

void build(int v, int tl, int tr) {
    if (tl == tr) {
        t[v].mx = a[tl];
        t[v].mx2 = 0;
        t[v].push_mx = -1;
        t[v].cnt_mx = 1;
        t[v].sum = a[tl];
    } else {
        int tm = (tl + tr) >> 1;
        t[v].push_mx = -1;
        build(left);
        build(right);
        combine(v);
    }
}

void upd_mx(int v) {
    dout << "upd_mx  "<<v <<" - "<<t[v].push_mx<<endl;
    if (t[v].push_mx == -1)
        return;
    if (t[v].mx <= t[v].push_mx)
        return;
    assert(t[v].mx2 <= t[v].push_mx);
    t[v].sum -= 1ll * t[v].mx * t[v].cnt_mx;
    t[v].mx = t[v].push_mx;
    t[v].sum += 1ll * t[v].mx * t[v].cnt_mx;

    dout << t[v].mx <<" "<<t[v].sum << endl;
}

void push(int v) {
    if (t[v].push_mx != -1) {
        int to = v << 1;
        if (t[to].push_mx == -1) {
            t[to].push_mx = t[v].push_mx;
        } else {
            t[to].push_mx = min(t[v].push_mx, t[to].push_mx);
        }
        upd_mx(to);

        to = v << 1 | 1;
        if (t[to].push_mx == -1) {
            t[to].push_mx = t[v].push_mx;
        } else {
            t[to].push_mx = min(t[v].push_mx, t[to].push_mx);
        }
        upd_mx(to);
        t[v].push_mx = -1;
    }
}

void update(int v, int tl, int tr, int l, int r, int x) {
    if (l > tr || r < tl || t[v].mx <= x)
        return;
    if (l <= tl && tr <= r && t[v].mx2 <= x) {
        dout << "here stopped "<<tl <<" "<<tr <<" "<<x<<endl;
        if (t[v].push_mx == -1) {
            t[v].push_mx = x;
        } else {
            t[v].push_mx = min(t[v].push_mx, x);
        }
        upd_mx(v);
    } else {
        int tm = (tl + tr) >> 1;
        push(v);
        update(left, l, r, x);
        update(right, l, r, x);
        combine(v);
    }
}

ll get(int v, int tl, int tr, int l, int r) {
    if (l > tr || r < tl)
        return 0;
    if (l <= tl && tr <= r) {
        return t[v].sum;
    } else {
        int tm = (tl + tr) >> 1;
        push(v);
        ll res = get(left, l, r) + get(right, l, r);
        combine(v);
        return res;
    }
}

int get_mx(int v, int tl, int tr, int l, int r) {
    if (l > tr || r < tl)
        return 0;
    if (l <= tl && tr <= r) {
        return t[v].mx;
    } else {
        int tm = (tl + tr) >> 1;
        push(v);
        int res = max(get_mx(left, l, r), get_mx(right, l, r));
        combine(v);
        return res;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    build(1, 1, n);
    for (int i = 1; i <= m; ++i) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 0) {
            int val;
            cin >> val;
            update(1, 1, n, l, r, val);
        } else if (t == 1) {
            cout << get_mx(1,1,n,l,r)<<"\n";
        } else {
            cout << get(1,1,n,l,r)<<"\n";
        }
    }

}

signed main() {
#ifdef zxc
    debug = 0;
    freopen("../input.txt", "r", stdin);
    //freopen("../output.txt", "w", stdout);
#else
    //freopen("roboherd.in", "r", stdin);
    //freopen("roboherd.out", "w", stdout);

#endif //zxc
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.setf(ios::fixed);
    cout.precision(20);

    int t = 1;
    cin >> t;
    while (t--)
        solve();
    if (debug)
        cerr << endl << "time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
}