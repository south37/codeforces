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

// Segment Tree
class SegTree {
public:
  SegTree(int _n) {
    n = 1;
    while (n < _n) { n *= 2; }
    n *= 2;
    add = vector<int>(2*n-1);
    t = vector<int>(2*n-1);
  }

  void update(int k, int x) {
    _update(0, 0, k, 0, n, x);
  }

  // target: [l, r). area: [tl, tr).
  void _update(int v, int l, int r, int tl, int tr, int x) {
    if (tl >= r || tr <= l) { return; } // not in range
    if (tl >= l && tr <= r) {
      update_one(v, x);
    } else {
      if (add[v]) {
        update_one(v*2+1, add[v]);
        update_one(v*2+2, add[v]);
        add[v] = 0;
      }

      _update(v*2+1, l, r, tl, (tl+tr)/2, x);
      _update(v*2+1, l, r, (tl+tr)/2, tr, x);
      t[v] = min(t[v*2+1], t[v*2+2]);
    }
  }

  // We need only the result of whole area, so return t[0].
  int query() {
    return t[0];
  }

private:
  void update_one(int v, int x) {
    add[v] += x;
    t[v] += x;
  }

  int n; // The size of source data. The power of 2.
  vector<int> add;
  vector<int> t;
};

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> p(n);
  vector<ll> revP(n); // idx of the value in p.
  vector<ll> q(n);
  rep(i, n) {
    cin >> p[i];
    revP[p[i]] = i;
  }
  rep(i, n) {
    cin >> q[i];
    --q[i]; // 0-indexed
  }

  SegTree st(n);
  auto decrease = [&] (int x) {
    st.update(revP[x] + 1, -1);
    if (st.query() >= 0) {
      return true;
    } else {
      st.update(revP[x] + 1, 1); // revert
      return false;
    }
  };
  int x = n;
  rep(i, n) {
    while (decrease(x)) { --x; }
    cout << x;
    if (i < n-1) {
      cout << " ";
    }
    st.update(q[i] + 1, 1);
  }
  cout << endl;
}
