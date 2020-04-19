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

string checkResult(ll x, ll y) {
  // cerr << "testcase: " << testcase << endl;
  // cerr << "idx: " << idx << endl;
  // cerr << flush;

  cout << x << " " << y << endl;
  cout << std::flush;
  string res;
  cin >> res; // '0' or '1'
  return res;
}

ll N = 1e9;

ll calcLeft(ll y) {
  ll left;
  {
    ll l = -N-1;
    ll r = -N+105;
    // found the boundary of [f, t]
    while (r - l > 1) {
      ll m = (r+l) / 2;
      string res = checkResult(m, y);
      if (res == "HIT") {
        r = m;
      } else {
        l = m;
      }
    }
    // Here, r is ok
    left = r;
  }
  return left;
}

ll calcRight(ll y) {
    ll right;
    {
      ll l = N-105;
      ll r = N+1;
      // found the boundary of [t, f]
      while (r - l > 1) {
        ll m = (r+l) / 2;
        string res = checkResult(m, y);
        if (res == "HIT") {
          l = m;
        } else {
          r = m;
        }
      }
      // Here, r is ok
      right = l;
    }
    return right;
}

// return the diameter at y
ll g(ll y) {
  ll left = calcLeft(y);
  ll right = calcRight(y);
  return right - left;
}

void hit_center(ll y) {
  ll left = calcLeft(y);
  ll right = calcRight(y);
  ll x = (left + right)/2;
  string res = checkResult(x, y);
  if (res == "CENTER") {
    return;
  } else {
    // Here, invalid
    abort();
  }
}

void solve() {
  ll a, b;
  cin >> a >> b;
  // check left in binary search
  // Do 3-min in y-direction

  ll l = -105;
  ll r = 105;
  rep(iter, 10) {
    ll c1 = (l*2+r)/3;
    ll c2 = (l+r*2)/3;
    if (g(c1) > g(c2)) {
      l = c1;
    } else {
      r = c2;
    }
  }
  // Here, l is the result
  hit_center(l);
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
