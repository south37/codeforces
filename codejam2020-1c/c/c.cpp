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

void solve() {
  ll n, d;
  cin >> n >> d;
  vector<ll> a(n);
  rep(i,n) {
    cin >> a[i];
  }
  map<ll,ll> cnts;
  rep(i,n) {
    ++cnts[a[i]];
  }

  // try 0
  {
    // Here, we try cut0, cut1, cut2
    for (auto& p : cnts) {
      if (p.second >= d) { // ok
        cout << 0 << endl;
        return;
      }
    }
  }
  // try 1
  {
    if (d <= 2) { // slice to 2.
      cout << 1 << endl;
      return;
    }
    if (cnts.size() > 1) {
      ll i = 0;
      ll sz = cnts.size();
      for (auto& p : cnts) {
        if (i == sz-1) { break; } // reached to last. no more larger value
        if (p.second+1 >= d) { // ok
          cout << 1 << endl;
          return;
        }
        ++i;
      }

      for (auto& p : cnts) {
        ll now = 2*p.first; // p is divided
        // cout << "p.first: " << p.first << endl;
        // cout << "p.second: " << p.second << endl;
        // cout << "d: " << d << endl;

        if (cnts.find(now) != cnts.end() && p.second + 2 >= d) {
          cout << 1 << endl;
          return;
        }
      }
    }
  }
  cout << 2 << endl;
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
