/*
	As in editorial
*/

//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int inf_int = 1e8 + 100;
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
const int mod = 924844033;
const int MX = 5e5 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;


int dp[22][22][22][22];

int x[100], y[100];
int N;


int get_dp(int mn_x, int mx_x, int mn_y, int mx_y) {
    if (dp[mn_x][mx_x][mn_y][mx_y] != -1)
        return dp[mn_x][mx_x][mn_y][mx_y];
    int &res = dp[mn_x][mx_x][mn_y][mx_y];
    res = inf_int;
    bool flag = true;
    for (int i = 0; i < N; ++i) {
        if (mn_x <= x[i] && x[i] <= mx_x && mn_y <= y[i] && y[i] <= mx_y)
            continue;
        flag = false;
        int mn_x1 = min(mn_x, x[i]);
        int mx_x1 = max(mx_x, x[i]);
        int mn_y1 = min(mn_y, y[i]);
        int mx_y1 = max(mx_y, y[i]);


        int add = max(max(abs(mn_x - x[i]), abs(mx_x - x[i])),
                      max(abs(mn_y - y[i]), abs(mx_y - y[i])));
        for (int j = 0; j < N; ++j) {
            if (i == j)
                continue;
            if (mn_x <= x[j] && x[j] <= mx_x && mn_y <= y[j] && y[j] <= mx_y) {
                continue;
            }
            if (mn_x1 <= x[j] && x[j] <= mx_x1 && mn_y1 <= y[j] && y[j] <= mx_y1) {
                add += max(max(abs(mn_x1 - x[j]), abs(mx_x1 - x[j])),
                           max(abs(mn_y1 - y[j]), abs(mx_y1 - y[j])));
            }
        }
        res = min(res, add + get_dp(mn_x1, mx_x1, mn_y1, mx_y1));
    }
    if (flag)
        res = 0;
    return res;
}

class EllysChessboard {
public:
    int minCost(vector<string> board) {
        vector<pii> vs;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] == '#') {
                    vs.pb({i + j, i - j});
                }
            }
        }

        int mn_val = 100;
        for (pii x:vs) {
            mn_val = min(mn_val, min(x.fi, x.se));
        }
        for (pii &x:vs) {
            x.se -= mn_val;
        }
        N = sz(vs);
        for (int i = 0; i < sz(vs); ++i) {
            x[i] = vs[i].fi;
            y[i] = vs[i].se;
        }
        if(N == 0)
            return 0;

        memset(dp,-1,sizeof dp);
        int res = inf_int;
        for(int i= 0;i<N;++i){
            res = min(res, get_dp(x[i],x[i],y[i],y[i]) );
        }
        return res;


    }
};