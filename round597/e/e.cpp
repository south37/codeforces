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
    cout << i + 1 << ": ";
    printvec(tree[i]);
  }
}
template<class T, class U> void printmap(const map<T, U>& mp) {
  for (auto x : mp) { cout << x.first << "=>" << x.second << endl; }
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int grid[10][10];

int main(int argc, char** argv) {
  rep(i, 10) {
    rep(j, 10) {
      cin >> grid[i][j];
    }
  }

  // flat:
  // 99, 98, ... 90
  // 80, 81, ... 89
  // .
  // .
  // .
  //  0,  1, ...  9
  int flat[10][10];
  rep(i, 10) {
    rep(j, 10) {
      flat[i][j] = (9-i)*10 + ((i&1) ? j : 9-j);
    }
  }

  int d = 1; // "->" at first
  int x = 9; // vertical
  int y = 0; // horizontal
  vector<int> arr(100);
  rep(i, 100) {
    arr[i] = flat[x-grid[x][y]][y];

    if (y+d == -1 || y+d == 10) { // at the edge of a row. (y,d) = (9,1) or (0,-1)
      d *= -1;
      --x;
    } else {
      y += d;
    }
  }

  // printvec(arr);

  vector<double> dp(100);
  dp[99] = 0;
  for (int i = 98; i >= 0; --i) {
    dp[i] = 1;
    int c = 0; // The count of summed dp.
    for (int r = 1; r <= 6; ++r) { // try 6 times. [i+1, i+6]
      if (i + r >= 100) { continue; }
      dp[i] += min(dp[i+r], dp[arr[i+r]]) / 6;
      ++c;
    }
    dp[i] = 6 * dp[i] / c;
  }

  cout << setprecision(10) << fixed << dp[0] << endl;
}
