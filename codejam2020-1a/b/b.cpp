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

// dir: 0 .. left to right, 1 .. right to left
void printrow(int r, int dir) {
  int w = r + 1;
  if (dir == 0) { // left to right
    rep(c, w) {
      cout << r+1 << " " << c+1 << endl;
    }
  } else { // right to left
    for (int c = w-1; c >= 0; --c) {
      cout << r+1 << " " << c+1 << endl;
    }
  }
}

void solve_in_greedy(ll n) {
  ll remain = n;
  ll r = 0;
  while (remain > 0) {
    cout << r+1 << " " << 1 << endl;
    --remain;
    ++r;
  }
}

void solve() {
  ll n;
  cin >> n;

  if (n <= 31) {
    // solve in greedy way
    solve_in_greedy(n);
    return;
  }
  vector<bool> used(31); // used[i] .. using 2^i
  {
    ll remain = n - 31; // decrease for moving
    for (ll i = 30; i >= 0; --i) {
      if (remain >= (1ll<<i)) {
        remain -= 1ll<<i;
        used[i] = true;
      }
    }
  }
  // Here, all information is calclated
  // cout << "used:"; printvec(used);

  ll remain = n;
  int dir = 0;
  for (int r = 0; r <= 30; ++r) {
    if (used[r]) {
      printrow(r, dir);
      dir ^= 1; // flip
      remain -= (1ll<<r);
    } else { // not used. only move
      if (dir == 0) { // next, left to right. so should print left
        cout << r+1 << " " << 1 << endl;
      } else {
        cout << r+1 << " " << r+1 << endl;
      }
      --remain;
    }
  }

  // Here, remain may remaining
  ll r = 31;
  while (remain > 0) {
    if (dir == 0) {
      cout << r+1 << " " << 1 << endl;
    } else {
      cout << r+1 << " " << r+1 << endl;
    }
    --remain;
    ++r;
  }
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
    cout << endl;
    solve();
  }
}
