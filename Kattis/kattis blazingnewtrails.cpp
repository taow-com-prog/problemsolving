/*
    Used idea from this blog: https://codeforces.com/blog/entry/51201
    Lets binary search over the potential X. Add x to every special edge, if we can construct MST with k special edges it is good. Otherwise we can decrease or increase the value of X.
*/

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

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
const int MAXN = 2e5 + 100;
const int LOG = 22;
const int mod = 1e9 + 7;
const int MX = 1e6 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;
int spec_ver[MAXN];

struct edge {
    int a, b, c;
    int spec;

    edge(int a, int b, int c) : a(a), b(b), c(c) {
        spec = spec_ver[a] ^ spec_ver[b];
    }
};

int parent[MAXN];

void init(int n) {
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
    }
}

int get_parent(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = get_parent(parent[v]);
}

bool union_set(int a, int b) {
    a = get_parent(a);
    b = get_parent(b);
    if (a != b) {
        parent[b] = a;
        return true;
    }
    return false;
}


vector<edge> e;
int n;

template<typename T>
pll get_val(T fun) {
    sort(all(e), fun);
    init(n);
    ll cost = 0;
    int cnt = 0;
    for (auto &x:e) {
        if (union_set(x.a, x.b)) {
            cost += x.c;
            cnt += x.spec;
        }
    }
    return {cost, cnt};
}

void add_to_edges(int val) {
    for (auto &x:e) {
        if (x.spec)
            x.c += val;
    }
}

void solve() {
    int m, k, w;
    cin >> n >> m >> k >> w;
    for (int i = 1; i <= k; ++i) {
        int v;
        cin >> v;
        spec_ver[v] = 1;
    }
    init(n);

    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        e.emplace_back(edge(a, b, c));
        union_set(a,b);
    }
    for(int i=1;i<=n;++i){
        if(get_parent(i) != get_parent(1)){
            dout <<"NO MST "<<endl;
            cout << -1;
            return;
        }
    }
    auto f2 = [](edge &a, edge &b) -> bool {
        if (a.c != b.c)
            return a.c < b.c;
        return (a.spec ^ 1) < (b.spec ^ 1);
    };
    auto f1 = [](edge &a, edge &b) -> bool {
        if (a.c != b.c)
            return a.c < b.c;
        return (a.spec) < (b.spec);
    };


    int l = -1e6, r = 1e6;
    while (l <= r) {
        int mid = (l + r) >> 1;
        add_to_edges(mid);
        pll val1 = get_val(f1);
        pll val2 = get_val(f2);

        if (val1.se <= w && w <= val2.se) {
            cout << val1.fi - 1ll * mid * w;
            return;
        } else {
            if (val2.se < w) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        add_to_edges(-mid);
    }
    cout << -1;


}

signed main() {
#ifdef zxc
    debug = 1;
    freopen("../input.txt", "r", stdin);
    //  freopen("../output.txt", "w", stdout);
#else

#endif //zxc
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.setf(ios::fixed);
    cout.precision(20);

    int t = 1;
    while (t--)
        solve();

    if (debug)
        cerr << endl << "time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
}