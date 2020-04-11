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
  ll h, w;
  cin >> h >> w;
  vector<vector<ll>> mat(h, vector<ll>(w));
  rep(r, h) {
    rep(c, w) {
      cin >> mat[r][c];
    }
  }
  // Here, mat has all information
  // we calculate in greedy way
  ll ans = 0;
  while(true) {
    bool changed = false;
    ll roundSum = 0;
    // calculate sum
    rep(r, h) rep(c, w) { roundSum += mat[r][c]; }
    ans += roundSum;

    vector<vector<bool>> eliminated(h, vector<bool>(w));

    // eiliminate
    rep(r, h) rep(c, w) {
      if (mat[r][c] == 0) { continue; } // skip eliminated onem

      // Here, we search all neibers;
      // find small r
      vector<ll> founds;
      for (int rr = r-1; rr >= 0; --rr) {
        if (mat[rr][c] > 0) { // found
          founds.push_back(mat[rr][c]);
        }
      }
      for (int rr = r+1; rr < h; ++rr) {
        if (mat[rr][c] > 0) { // found
          founds.push_back(mat[rr][c]);
        }
      }
      for (int cc = c-1; cc >= 0; --cc) {
        if (mat[r][cc] > 0) { // found
          founds.push_back(mat[r][cc]);
        }
      }
      for (int cc = c+1; cc < w; ++cc) {
        if (mat[r][cc] > 0) { // found
          founds.push_back(mat[r][cc]);
        }
      }
      // Here, founds has neibors
      if (founds.size() == 0) { continue; } // skip if no neiber
      ll average = 0;
      for (ll found : founds) { average += found; }
      if (average > founds.size() * mat[r][c]) { // too small
        // cout << "(r,c): " << r << "," << c << endl;
        // cout << "average: " << average << endl;
        changed = true;
        eliminated[r][c] = true;
      }
    }
    if (!changed) {
      break;
    } else {
      // ans += roundSum;
      rep(r, h) rep(c, w) {
        if (eliminated[r][c]) {
          mat[r][c] = 0;
        }
      }
    }
  }
  cout << ans;
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
    cout << endl;
  }
}
