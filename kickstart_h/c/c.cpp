#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <set>

using namespace std;

#define COUT(x) cout << #x << " = " << (x) << " (L" << __LINE__ << ")" << endl

template<class T> void printvec(const vector<T>& v) {
  for (auto x : v) { cout << x << " "; }
  cout << endl;
}
template<class T> void printtree(const vector< vector<T> >& tree) {
  for (long long i = 0; i < tree.size(); ++i) {
    cout << i + 1 << ": "; printvec(tree[i]);
  }
}
template<class T, class U> void printmap(const map<T, U>& mp) {
  for (auto x : mp) { cout << x.first << "=>" << x.second << endl; }
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()
#define fr first
#define sc second
#define mp make_pair
#define pb push_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

const int N = 505, mod = 0;
int cnt[10], dp[N][11], odp[N][11];

void solve() {
  int sum = 0;
  for (int j = 1; j < 10; ++j) {
    cin >> cnt[j];
    if (cnt[j] > 20) {
      cnt[j] = 20 + (cnt[j] & 1);
    }
    sum += cnt[j];
  }
  memset(dp, 0, sizeof dp);
  dp[0][0] = 1;
  for (int j = 1; j < 10; ++j) {
    memcpy(odp, dp, sizeof dp);
    memset(dp, 0, sizeof dp);
    for (int pick = 0; pick <= cnt[j]; ++pick) {
      for (int lpick = 0; lpick + pick < N; ++lpick) {
    	  for (int lmod = 0; lmod < 11; ++lmod) {
    	    int nmod = (lmod + pick * j + (11 - j) * (cnt[j] - pick)) % 11;
    	    dp[lpick + pick][nmod] |= odp[lpick][lmod];
    	  }
    	}
    }
  }
  if (dp[sum / 2][0]) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }
}

int main() {
  int t;
  cin >> t;
  rep(i, t) {
    cout << "Case #" << i+1 << ": ";
    solve();
  }
}
