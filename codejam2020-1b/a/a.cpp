// ref. https://codingcompetitions.withgoogle.com/codejam/submissions/000000000019fef2/U251a2U

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <string.h>
#include <set>
#include <unordered_map>
#include <vector>

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

const int dx[] = {-1,0,1,0}, dy[] = {0,-1,0,1};
string dc = "WSEN";

void solve() {
  ll x, y;
  cin >> x >> y;
  auto f = [&](ll x, ll y) {
    return abs(x) + abs(y);
  };
  if (f(x,y)%2 == 0) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }

  ll s = 0;
  while ((1ll<<s)-1 < f(x,y)) { ++s; }
  // Here, (1ll<<s)+1 >= f(x,y). s is the size of nums.
  string ans;
  for (ll i = s-1; i >= 0; --i) {
    ll l = 1ll<<i;
    rep(v, 4) {
      ll nx = x+dx[v]*l, ny = y+dy[v]*l;
      if (f(nx,ny) <= (1ll<<i)-1) { // Here, we could erase contribution of 1ll<<i. We only check larger one of (x+y, x-y)
        x = nx; y = ny;
        ans += dc[v^2]; // Here, we decrease instead of increase, so opposite direction is selected.
        break;
      }
    }
  }
  reverse(all(ans));
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
    cout << "Case #" << (i+1) << ": ";
    solve();
  }
}
