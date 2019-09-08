// dp[v] - the mask of the type of vertices in the subtree of vertex v

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
const int MAXN = 1e5 + 100;
const int LOG = 21;
const int mod = 998244353;
const int MX = 1e3 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;

template<class T1, class T2>
std::ostream &operator<<(std::ostream &out, const std::pair<T1, T2> &rhs) {
    out << "( " << rhs.first << " , " << rhs.second << " )";
    return out;
}

vector<int> g[MAXN];

int dp[MAXN];

int cnt[32];

void dfs(int v, int p) {
    for (int to:g[v]) {
        if (to == p)
            continue;
        dfs(to, v);
    }

    memset(cnt, 0, sizeof cnt);
    for (int to:g[v]) {
        if (to == p)
            continue;
        for (int i = 0; i < 30; ++i) {
            if (dp[to] & (1 << i)) {
                cnt[i]++;
            }
        }
    }
    int last = 0;
    for (int i = 0; i < 30; ++i) {
        if (cnt[i] > 1)
            last = i + 1;
    }
    for (int i = last; i < 30; ++i) {
        if (cnt[i] == 0) {
            last = i;
            break;
        } else {

        }
    }
    int res = (1 << last);
    for (int i = last + 1; i < 30; ++i) {
        if (cnt[i] > 0) {
            res = res | (1 << i);
        }
    }
    dp[v] = res;
}

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    dfs(1, -1);
    int res = 0;
    for (int i = 0; i < 30; ++i) {
        if (dp[1] & (1 << i))
            res = i;
    }
    cout << res << endl;

}

signed main() {
#ifdef zxc
    debug = 1;
    // freopen("../input.txt", "r", stdin);
    // freopen("../output.txt", "w", stdout);
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