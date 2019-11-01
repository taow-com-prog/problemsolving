// as in editorial

//
// Created by Ильдар Ялалов on 28.10.2019.
//

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

ll x[MAXN],y[MAXN];

ll dx[4] = {1,-1,0,0};
ll dy[4] = {0,0,1,-1};

char dc[4] = {'L','R','D','U'};

void solve() {
    int n;
    cin >> n;
    for(int i = 1;i<=n;++i){
        cin >> x[i] >> y[i];
        dout << x[i]<<" "<<y[i]<<endl;
    }
    for(int i=1;i<=n;++i){
        if(((x[i]+y[i])&1) != ((x[1]+y[1])&1)){
            cout << -1;
            return;
        }
    }
    vector<int> vals;
    if((x[1] + y[1])%2==0){
        vals.pb(1);
    }

    for(int i=0;i<=30;++i){
        vals.pb(1<<i);
    }

    reverse(all(vals));

    vector<string> ans;
    for(int i=1;i<=n;++i){
        ll x0 = x[i];
        ll y0 = y[i];


        ll x1,y1;

        string cur;
        for(int d : vals){
            char val;
            for(int j = 0;j < 4;++j){
                ll x = x0 + dx[j] * d;
                ll y = y0 + dy[j] * d;
                if(j == 0 || (abs(x) + abs(y)) <= abs(x1) + abs(y1)){
                    x1 = x;
                    y1 = y;
                    val = dc[j];
                }
            }
            dout <<x1 <<" "<<y1<<endl;
            x0 = x1;
            y0 = y1;
            cur.pb(val);
        }
        ans.pb(cur);
        assert(x0 == 0 && y0 == 0);
    }

    cout << sz(vals)<<"\n";
    for(auto x: vals){
        cout <<x <<" ";
    }
    cout <<"\n";
    for(auto x:ans){
        cout << x <<"\n";
    }

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
    if (debug)
        cerr << endl << "time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
}
