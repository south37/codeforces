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
  int n;
  cin >> n;
  vector<vector<int>> mat(n, vector<int>(n));
  rep(i, n) {
    rep(j, n) {
      cin >> mat[i][j];
    }
  }
  ll trace = 0;
  rep(i, n) {
    trace += mat[i][i];
  }
  // printtree(mat);

  ll row = 0, col = 0;
  // Check row
  rep(r, n) {
    // Here, we check mat[r]
    bool repeated = false;
    set<int> elements;
    rep(c, n) {
      if (elements.find(mat[r][c]) != elements.end()) { // repeated found
        repeated = true;
        break;
      }
      elements.insert(mat[r][c]);
    }
    if (repeated) {
      ++row;
    }
  }

  // Check col
  rep(c, n) {
    // Here, we check mat[x][c]
    bool repeated = false;
    set<int> elements;
    rep(r, n) {
      // cout << "mat["<<r<<"]["<<c<<"]: " << mat[r][c] << endl;
      if (elements.find(mat[r][c]) != elements.end()) { // repeated found
        // cout << "repeated" << endl;
        repeated = true;
        break;
      }
      elements.insert(mat[r][c]);
    }
    if (repeated) {
      // cout << "++c" << endl;
      ++col;
    }
  }

  cout << trace << " " << row << " " << col;
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
