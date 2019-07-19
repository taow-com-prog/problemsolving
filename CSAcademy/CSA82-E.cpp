/*
    add edges from 0 vertex to i with weigth f[i]

    If mst contains less than k edges, that is an answwer.

    Otherwise binary search of value x, such that you will have not more than k edges from 0 - to i.
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
const int MAXN = 2000 + 100;
const int LOG = 25;
const int mod = 1e9 + 7;
const int MX = 1 * (1e7 + 100);
typedef long long li;
const li MOD = 1000000000949747713ll;

int f[MAXN];
int d[MAXN][MAXN];

struct edge {
    int a, b, c;

    bool operator<(const edge &o) const {
        return c < o.c;
    }
};

int parent[MAXN];

void init_dsu(int n) {
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
    if (a == b)
        return false;
    parent[b] = a;
    return true;
}

vector<edge> edges, spec_edges;

void add_all(int val) {
    for (auto &x:spec_edges) {
        x.c += val;
    }
}

int n;

pll get_mst1() {
    init_dsu(n + 1);

    int i1 = 0, i2 = 0;
    ll cost = 0;
    int cnt = 0;
    while (i1 < sz(spec_edges) || i2 < sz(edges)) {
        if (i1 < sz(spec_edges) && i2 < sz(edges)) {
            if (spec_edges[i1].c == edges[i2].c) {
                if (union_set(spec_edges[i1].a, spec_edges[i1].b)) {
                    cost += spec_edges[i1].c;
                    cnt++;
                }
                i1++;
            } else if (spec_edges[i1].c < edges[i2].c) {
                if (union_set(spec_edges[i1].a, spec_edges[i1].b)) {
                    cost += spec_edges[i1].c;
                    cnt++;
                }
                i1++;
            } else {
                if (union_set(edges[i2].a, edges[i2].b)) {
                    cost += edges[i2].c;
                }
                i2++;
            }
        } else if (i1 < sz(spec_edges)) {
            if (union_set(spec_edges[i1].a, spec_edges[i1].b)) {
                cost += spec_edges[i1].c;
                cnt++;
            }
            i1++;
        } else {
            if (union_set(edges[i2].a, edges[i2].b)) {
                cost += edges[i2].c;
            }
            i2++;
        }
    }
    return {cost, cnt};
}

pll get_mst2() {
    init_dsu(n + 1);

    int i1 = 0, i2 = 0;
    ll cost = 0;
    int cnt = 0;
    while (i1 < sz(spec_edges) || i2 < sz(edges)) {
        if (i1 < sz(spec_edges) && i2 < sz(edges)) {
            if (spec_edges[i1].c == edges[i2].c) {
                if (union_set(edges[i2].a, edges[i2].b)) {
                    cost += edges[i2].c;
                }
                i2++;
            } else if (spec_edges[i1].c < edges[i2].c) {
                if (union_set(spec_edges[i1].a, spec_edges[i1].b)) {
                    cost += spec_edges[i1].c;
                    cnt++;
                }
                i1++;
            } else {
                if (union_set(edges[i2].a, edges[i2].b)) {
                    cost += edges[i2].c;
                }
                i2++;
            }
        } else if (i1 < sz(spec_edges)) {
            if (union_set(spec_edges[i1].a, spec_edges[i1].b)) {
                cost += spec_edges[i1].c;
                cnt++;
            }
            i1++;
        } else {
            if (union_set(edges[i2].a, edges[i2].b)) {
                cost += edges[i2].c;
            }
            i2++;
        }
    }
    return {cost, cnt};
}

void solve() {
    int m;
    cin >> n >> m;
    edges.clear();
    spec_edges.clear();
    for (int i = 1; i <= n; ++i) {
        cin >> f[i];
        spec_edges.pb({i, n + 1, f[i]});
    }
    for (int i = 1; i <= n; ++i) {
        for (int e = 1; e <= n; ++e) {
            cin >> d[i][e];
            if (i < e) {
                edges.pb({i, e, d[i][e]});
            }
        }
    }
    sort(all(spec_edges));
    sort(all(edges));

    auto x = get_mst1();
    dout <<"start "<< x.fi << " "<<x.se<<endl;
    if (x.se <= m) {
        cout << x.fi << "\n";
        return;
    }

    int l = -1e9, r = 1e9;
    while (l <= r) {
        int mid = (l + r) >> 1;
        add_all(mid);
        auto x2 = get_mst1();
        auto x1 = get_mst2();
        assert(x2.se >= x1.se);
        dout <<"MId "<<mid <<" "<<x1.fi<<" "<<x1.se <<" -- "<<x2.fi<<" "<<x2.se<<endl;
        if (x1.se <= m && m <= x2.se) {
            cout << x1.fi - m * mid << "\n";
            return;
        }
        if (x1.se > m) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }

        add_all(-mid);
    }

}

signed main() {
#ifdef zxc
    debug = 1;
    freopen("../input.txt", "r", stdin);
    //freopen("../output.txt", "w", stdout);
#else

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