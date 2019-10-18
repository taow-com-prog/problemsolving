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
const int MAXN = 5e5 + 100;
const int LOG = 21;
const int mod = 1e9 + 7;
const int MX = (1e7 + 100) * 1.5;
typedef long long li;

template<class T1, class T2>
std::ostream &operator<<(std::ostream &out, const std::pair<T1, T2> &rhs) {
    out << "( " << rhs.first << " , " << rhs.second << " )";
    return out;
}

vector<int> g[MAXN];
int h[MAXN];
int val[MAXN];
map<int, int> dp[MAXN][2];

ll bin_pow(ll a, int n) {
    ll res = 1;
    while (n) {
        if (n & 1) {
            res = (res * a) % mod;
        }
        n >>= 1;
        a = (a * a) % mod;
    }
    return res;
}

ll inverse(ll a) {
    assert(a != 0);
    ll res = bin_pow(a, mod - 2);
    assert((a * res) % mod == 1);
    return res;
}

ll temp_res[2][MAXN];
int sum[MAXN];

int dfs(int v) {
    int mxh = h[v];

    sum[h[v]]++;
    int bigc = -1;
    int ch = 0;
    for (int to:g[v]) {
        h[to] = h[v] + 1;
        int mxto = dfs(to);
        ch++;
        if (mxto > mxh) {
            bigc = to;
            mxh = mxto;
        }
    }

    if (ch > 0) {
        if (ch > 1) {
            map<int, int> all_zero;
            map<int, int> all_val;
            int h2 = 0;
            for (int to:g[v]) {
                if (to == bigc)
                    continue;
                h2 = max(h2, val[to]);
            }
            for (int i = h[v] + 1; i <= h2; ++i) {
                all_zero[i] = 1;
                all_val[i] = 1;
            }
            for (int to:g[v]) {
                for (int i = h[to]; i <= val[to] && i <= h2; ++i) {
                    int x0 = dp[to][0][i];
                    int x1 = dp[to][1][i];
                    all_val[i] = (1ll * all_val[i] * (x0 + x1)) % mod;
                    all_zero[i] = (1ll * all_zero[i] * x0) % mod;
                }
            }

            for (int i = h[v] + 1; i <= h2; ++i) {
                temp_res[0][i] = temp_res[1][i] = 0;
            }
            for (int to:g[v]) {
                for (int i = h[to]; i <= val[to] && i <= h2; ++i) {
                    int x0 = dp[to][0][i];
                    int x1 = dp[to][1][i];
                    temp_res[1][i] += ((1ll * x1 * all_zero[i]) % mod * inverse(x0)) % mod;
                }
            }
            swap(dp[v][1], dp[bigc][1]);
            swap(dp[v][0], dp[bigc][0]);
            for (int i = h[v] + 1; i <= h2; ++i) {
                temp_res[1][i] %= mod;
                temp_res[0][i] = (all_val[i] - temp_res[1][i] + mod) % mod;
            }
            for (int i = h[v] + 1; i <= h2; ++i) {
                dp[v][1][i] = temp_res[1][i];
                dp[v][0][i] = temp_res[0][i];
            }
        } else {
            swap(dp[v][1], dp[bigc][1]);
            swap(dp[v][0], dp[bigc][0]);
        }
    }
    dp[v][1][h[v]] = 1;
    dp[v][0][h[v]] = 1;
    val[v] = mxh;
    dout << v << " : " << h[v] << " " << mxh << endl;
    return mxh;
}

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int p;
        cin >> p;
        g[p].pb(i);
    }

    int mxh = dfs(0);
    ll res = 0;
    dout << "mxh " << mxh << endl;
    for (int i = 0; i <= mxh; ++i) {
        ll val = dp[0][1][i];

        val = val * bin_pow(2, n + 1 - sum[i]);
        val %= mod;
        res += val;
        dout << "Res " << i<<" "<<sum[i] << " : " << val <<" "<<dp[0][1][i]<<" "<<n+1-sum[i]<< endl;
    }
    res %= mod;
    cout << res << "\n";
}

signed main() {
#ifdef zxc
    debug = 0;
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
    if (debug) {
        cerr << endl;
        cerr << endl << "time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
    }

}
