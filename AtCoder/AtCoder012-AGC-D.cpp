/*
 Like in editorial
**/

//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <string>
#include <stdio.h>
#include <time.h>
#include <map>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int inf_int = 1e9 + 100;
const ll inf_ll = 1e18;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef long double dbl;
#define pb push_back
#define eb emplace_back
const double pi = 3.1415926535898;
#define dout if(debug) cout
#define fi first
#define se second
#define sp setprecision
#define sz(a) (int(a.size()))
#define mp make_pair
#define all(a) a.begin(),a.end()
bool debug = 0;
const int MAXN = 4e5 + 100;
const int LOG = 21;
const int mod = 1e9 + 7;
const int MX = (1e7 + 100) * 1.5;
typedef long long li;
const li MOD = 1000000000949747713ll;

template<class T1, class T2>
std::ostream &operator<<(std::ostream &out, const std::pair<T1, T2> &rhs) {
    out << "( " << rhs.first << " , " << rhs.second << " )";
    return out;
}

vector<pii> a[MAXN];
int parent[MAXN];
int siz[MAXN];

int get_parent(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = get_parent(parent[v]);
}

void union_set(int a, int b) {
    a = get_parent(a);
    b = get_parent(b);
    if (a != b) {
        parent[b] = a;
        siz[a] += siz[b];
    }
}

map<int, int> mapik[MAXN];


int CLR[MAXN], COST[MAXN];

ll bin_pow(ll a, int n) {
    ll res = 1;
    while (n) {
        if (n & 1) {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        n >>= 1;
    }
    return res;
}

ll inverse(ll a) {
    return bin_pow(a, mod - 2);
}

void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
        siz[i] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        int clr, cost;
        cin >> clr >> cost;
        a[clr].pb({cost, i});
        CLR[i] = clr;
        COST[i] = cost;
    }
    vector<pii> min_clr;
    for (int i = 1; i <= n; ++i) {
        if (a[i].empty())
            continue;
        sort(all(a[i]));
        min_clr.pb(a[i][0]);
        for (int j = 1; j < sz(a[i]); ++j) {
            if (a[i][j].fi + a[i][0].fi <= x) {
                union_set(a[i][0].se, a[i][j].se);
            }
        }
    }
    sort(all(min_clr));
    for (int j = 1; j < sz(min_clr); ++j) {
        if (min_clr[j].fi + min_clr[0].fi <= y) {
            union_set(min_clr[j].se, min_clr[0].se);
        }
    }

    auto top = min_clr[0];
    int id = top.se;
    for(int i = 1; i <= n;++i){
        if(CLR[i] != CLR[id] && COST[i] + COST[id] <= y){
            union_set(i,id);
        }
    }
    if(min_clr.size() > 1){
        auto top2 = min_clr[1];
        for(auto cur : a[CLR[id]]){
            int id = cur.se;
            if(COST[id] + COST[top2.se] <= y){
                union_set(id,top2.se);
            }
        }
    }


    for (int i = 1; i <= n; ++i) {
        mapik[get_parent(i)][CLR[i]]++;
    }

    ll ans = 1;

    for (int i = 1; i <= n; ++i) {
        if (get_parent(i) == i) {
            for (int j = 0; j < siz[i]; ++j) {
                ans = ans * (j + 1);
                ans %= mod;
            }
        }
    }


    dout <<"ans " <<ans<<endl;

    for (int i = 1; i <= n; ++i) {
        for (auto x:mapik[i]) {
            int cnt = x.se;
            ll fac = 1;
            for (int j = 1; j <= cnt; ++j) {
                fac = (fac * j) % mod;
            }
            ans = (ans * inverse(fac)) % mod;
        }
    }
    cout << ans;
}

signed main() {
#ifdef zxc
    debug = 0;
   // freopen("../input.txt", "r", stdin);
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
