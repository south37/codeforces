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

void solve() {
  ll a, b, c;
  cin >> a >> b >> c;

  int ans = 0;
  rep(pattern, 1<<7) {
    int ta = a, tb = b, tc = c;
    int cand = 0;
    if ((pattern >> 0) & 1 && ta > 0) {
      --ta;
      ++cand;
    }
    if ((pattern >> 1) & 1 && tb > 0) {
      --tb;
      ++cand;
    }
    if ((pattern >> 2) & 1 && tc > 0) {
      --tc;
      ++cand;
    }
    if ((pattern >> 3) & 1 && ta > 0 && tb > 0) {
      --ta; --tb;
      ++cand;
    }
    if ((pattern >> 4) & 1 && tb > 0 && tc > 0) {
      --tb; --tc;
      ++cand;
    }
    if ((pattern >> 5) & 1 && ta > 0 && tc > 0) {
      --ta; --tc;
      ++cand;
    }
    if ((pattern >> 6) & 1 && ta > 0 && tb > 0 && tc > 0) {
      --ta; --tb; --tc;
      ++cand;
    }
    ans = max(ans, cand);
  }
  cout << ans << endl;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll t;
  cin >> t;
  rep(i, t) {
    solve();
  }
}
