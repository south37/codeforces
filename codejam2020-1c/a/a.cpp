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

string dir = "ENWS";
ll dx[4] = { 1, 0, -1, 0 };
ll dy[4] = { 0, 1, 0, -1 };

void solve() {
  ll x, y;
  cin >> x >> y;
  string M;
  cin >> M;
  ll m = M.size();
  vector<ll> dirs(m);
  rep(i,m) {
    rep(j,4) {
      if (dir[j] == M[i]) {
        dirs[i] = j;
        break;
      }
    }
  }
  // printvec(dirs);

  // Here, dirs has directions. start from (x,y);
  if (x == 0 && y == 0) {
    cout << 0 << endl;
    return;
  }
  rep(i,m) {
    ll d = dirs[i];

    x += dx[d];
    y += dy[d];
    if (abs(x) + abs(y) <= i+1) { // can reach
      cout << i+1 << endl;
      return;
    }
  }
  cout << "IMPOSSIBLE" << endl;
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
