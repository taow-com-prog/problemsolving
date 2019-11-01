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
const int MAXN = 1e5 + 100;
const int LOG = 21;
const int mod = 1e9 + 7;
const int MX = 1e6;
typedef long long li;

template<class T1, class T2>
std::ostream &operator<<(std::ostream &out, const std::pair<T1, T2> &rhs) {
    out << "( " << rhs.first << " , " << rhs.second << " )";
    return out;
}

void solve() {
    int n, k;
    cin >> n >> k;
    deque<int> d;
    int total = 0;
    for (int i = 1; i <= n; ++i) {
        char a;
        cin >> a;
        if (a == 'A') {
            d.push_back(0);
        } else {
            d.push_back(1);
        }
    }


    if(k > 2 * n){
        if(k % 2 == 0){
            k = 2 * n + 2;
        } else{
            k = 2 * n + 1;
        }
    }
    for (int i = 1; i <= k; ++i) {
        if ((d.front() ^ total) == 0) {
            d.pop_front();
            d.push_front(total ^ 1);
        } else {
            d.pop_front();
            total ^= 1;
            d.push_back(total);
        }
    }

    while (!d.empty()) {
        int res = d.front(); d.pop_front();
        res = res ^ total;

        if(res == 0){
            cout <<"A";
        } else{
            cout <<"B";
        }
    }

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
