// as in editorial

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
const int MAXN = 1e6 + 100;
const int LOG = 21;
const int mod = 1e9 + 7;
typedef long long li;

template<class T1, class T2>
std::ostream &operator<<(std::ostream &out, const std::pair<T1, T2> &rhs) {
    out << "( " << rhs.first << " , " << rhs.second << " )";
    return out;
}


struct ModInt {
    ll val;

    ModInt() {
        val = 0;
    }

    ModInt(const ll &x) {
        val = x % mod;
        if (val < 0)
            val += mod;
    }

    ModInt(const ModInt &x) {
        val = x.val;
    }
};

const ModInt operator+(const ModInt &left, const ModInt &right) {
    return ModInt(left.val + right.val);
}

const ModInt operator-(const ModInt &left, const ModInt &right) {
    return ModInt(left.val - right.val);
}

const ModInt operator*(const ModInt &left, const ModInt &right) {
    return ModInt(left.val * right.val);
}


ModInt dp[601][601];
ModInt dps[601][601];

ModInt fac2[601];

int a[601], b[601];

void solve() {

    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= k; ++i) {
        cin >> a[i] >> b[i];
    }

    fac2[0] = 1;
    for (int i = 2; i <= 2 * n; i=i+2) {
        ModInt val = i - 1;
        fac2[i] = fac2[i - 2] * val;
    }

    ModInt ans = 0;

    for (int l = 2 * n; l >= 1; --l) {
        for (int r = l; r <= 2 * n; ++r) {
            if ((r - l + 1) % 2 == 1) {
                continue;
            }
            bool bad = false;
            int inside = 0;
            for (int i = 1; i <= k; ++i) {
                int c = (l <= a[i] && a[i] <= r) + (l <= b[i] && b[i] <= r);
                if (c == 1) {
                    bad = true;
                    break;
                }
                inside += c;
            }
            if(bad)
                continue;
            int len = r - l + 1;

            int X = len - inside;
            int Y = 2 * n - X - 2 * k;


            dp[l][r] = dps[l][r] = fac2[X];

            for (int mid = l + 1; mid < r; ++mid) {
                dp[l][r] = dp[l][r] - (dp[l][mid] * dps[mid + 1][r]);
            }


            ans = ans +  ( dp[l][r] * fac2[Y] );
        }
    }

    cout << ans.val<<"\n";

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
    for (int j = 1; j <= t; ++j) {
        solve();
    }
    if (debug) {
        cerr << endl;
        cerr << endl << "time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
    }

}
