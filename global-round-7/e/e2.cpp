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
const int N = 3e5 + 7;

int add[4 * N];
int t[4 * N];

void upd(int v, int x) {
  add[v] += x;
  t[v] += x;
}

void push(int v) {
  if (add[v]) {
    upd(v * 2 + 1, add[v]);
    upd(v * 2 + 2, add[v]);
    add[v] = 0;
  }
}

void upd(int v, int l, int r, int tl, int tr, int x) {
  if (tl >= r || tr <= l) {
    return;
  }
  if (tl >= l && tr <= r) {
    upd(v, x);
  } else {
    int tm = (tl + tr) / 2;
    push(v);
    upd(v * 2 + 1, l, r, tl, tm, x);
    upd(v * 2 + 2, l, r, tm, tr, x);
    t[v] = min(t[v * 2 +1 ], t[v * 2 + 2]);
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;

  vector<int> p(n), q(n);
  vector<int> revP(n + 1);
  rep(i, n) {
    cin >> p[i];
    revP[p[i]] = i;
  }
  rep(i, n) {
    cin >> q[i];
    --q[i];
  }

  auto decrease = [&] (int x) {
    upd(0, 0, revP[x] + 1, 0, n, -1);
    if (t[0] >= 0) {
      return true;
    } else {
      upd(0, 0, revP[x] + 1, 0, n, 1);
      return false;
    }
  };

  int x = n;
  rep(i, n) {
    while (decrease(x)) x--;
    cout << x;
    if (i < n-1) {
      cout << ' ';
    }
    upd(0, 0, q[i] + 1, 0, n, 1);
  }
}
