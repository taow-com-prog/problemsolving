/*
    I looked at the dp state (l,r,val)

    And could create folowwing solution. Lets find minimal value in the current array.
    Now we can easily put a token on each column not higher them this minimal value. 

    Then, problem divides in these subproblems
    1) put some x tokens in this array on height not higher than minimal
    2) decrease the height of the array on this minimal value
    3) run the same dp problem on left and right new created arrays after we delete this element, and we need to put there exactly k - x tokens,

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
const int MAXN = 412 + 100;
const int LOG = 22;
const int mod = 1e9 + 7;
const int MX = 1e6 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;

int a[MAXN];

ll fac[MX];
ll inv_fac[MX];

ll bin_pow(ll a, int n) {
    ll res = 1;
    while (n) {
        if (n & 1) {
            res = (res * a) % mod;
        }
        a = (a * a)%mod;
        n >>= 1;
    }
    return res;
}

inline ll mul(ll a, ll b) {
    return (a * b) % mod;
}

inline ll mul(ll a, ll b, ll c) {
    return mul(mul(a, b), c);
}

ll dp[MAXN][MAXN];
int n, k;

ll temp[MAXN];

ll get_c(int n, int k) {
    return mul(fac[n], mul(inv_fac[k], inv_fac[n - k]));
}

ll get_a(int n, int k) {
    return mul(fac[n], inv_fac[n - k]);
}

int get_sol(int l, int r, int mn) {
    if (l > r)
        return 0;
    int pos = -1;
    for (int i = l; i <= r; ++i) {
        if (pos == -1 || a[i] <= a[pos])
            pos = i;
    }
    dout <<" l "<<l  <<" "<< r <<" " <<pos<<endl;

    int left = get_sol(l, pos - 1, a[pos]);
    int right = get_sol(pos + 1, r, a[pos]);


    for (int i = 0; i <= k; ++i) {
        temp[i] = 0;
        for (int j = 0; j <= i; ++j) {
            temp[i] += mul(dp[left][j], dp[right][i - j]);
        }
        temp[i] %= mod;
    }
    temp[0] = 1;

    for (int i = 0; i <= k; ++i) {
        for (int j = 0; j <= i && j <= a[pos] - mn && j <= r - l + 1 && i-j <=r-l+1; ++j) {
            dp[pos][i] += mul(temp[i - j], mul(get_c(r-l+1 - (i-j), j), get_a(a[pos] - mn, j)));
            dout << pos <<" "<<i<<" - "<<" " <<j << " "<<dp[pos][i]<<" :: "<<temp[i-j]<<" "<<mul(get_c(r-l+1, j), get_a(a[pos] - mn, j))<<endl;
        }
        dp[pos][i] %= mod;
    }

    return pos;

}

void solve() {
    fac[0] = 1;
    inv_fac[0] = 1;
    for (int i = 1; i < MX; ++i) {
        fac[i] = (fac[i - 1] * i) % mod;
        inv_fac[i] = bin_pow(fac[i], mod - 2);
        assert(mul(fac[i], inv_fac[i]) == 1);
    }

    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    dp[0][0] = 1;

    cout << dp[get_sol(1, n, 0)][k];


}

signed main() {
#ifdef zxc
    debug = 1;
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
    while (t--)
        solve();
    if (debug)
        cerr << endl << "time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
}