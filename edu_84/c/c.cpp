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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  // n*m. n=h, m=w
  ll n, m, k;
  cin >> n >> m >> k;

  vector<ll> x(k);
  vector<ll> y(k);
  vector<ll> xt(k); // target
  vector<ll> yt(k); // target
  vector<ll> xdiff(k); // target - initial
  vector<ll> ydiff(k); // target - initial
  rep(i, k) {
    cin >> x[i] >> y[i];
    --x[i]; --y[i]; // 0-indexed
  }
  rep(i, k) {
    cin >> xt[i] >> yt[i];
    --xt[i]; --yt[i]; // 0-indexed
  }

  // rep(i, k) {
  //   xdiff[i] = xt[i] - x[i]
  //   ydiff[i] = yt[i] - y[i]
  // }

  // Here, (xdiff, ydiff) is calculated.
  // We want to know the route to get all.

  // We calculate the path from (0,0) in the greedy way.
  // vector<set<P>> distances(k+1); // distance from i. which include

  // Here, we go through left bottom and paint all.
  // 1. down n-1, left m-1
  // 2. cycle
  string ans;
  rep(i, n-1) {
    ans += 'D';
  }
  rep(i, m-1) {
    ans += 'L';
  }

  string cycle;
  // Here, we start cycle. up n-1, right m-1, down n-2, left m-2, ...
  int widthDir = 0; // 0 means right, 1 means left.
  int verDir = 0; // 0 means up, 1 means down.
  ll widthLen = m-1;
  ll verLen = n;
  while (verLen > 0 || widthLen > 0) {
    rep(iter, verLen) {
      if (verDir == 0) {
        cycle += 'U';
      } else {
        cycle += 'D';
      }
    }
    // flip
    verDir = (verDir == 0) ? 1 : 0;
    // shrink
    --verLen;

    rep(iter, widthLen) {
      if (widthDir == 0) {
        cycle += 'R';
      } else {
        cycle += 'L';
      }
    }
    // flip
    widthDir = (widthDir == 0) ? 1 : 0;
    // shrink
    --widthLen;
  }

  ans += cycle.substr(1);
  cout << ans.size() << endl;
  cout << ans << endl;
}
