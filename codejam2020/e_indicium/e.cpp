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

vector<vector<ll>> ans;
vector<set<ll>> elements; // elments in each col.

bool backtrackAns(vector<ll>& traces, ll r, ll k) {
  int n = traces.size();
  if (r == n) { return true; } // reached to n

  ll traceNow = traces[r];
  vector<ll> otherRow;
  for (int i = 1; i <= n; ++i) {
    if (i != traceNow) {
      otherRow.push_back(i);
    }
  }
  do {
    ans[r][r] = traceNow;

    // Here, try current otherRow. i-row.
    int k = 0;
    rep(j, n) {
      if (j == r) {
        ans[r][j] = traceNow;
      } else { // j != r
        ans[r][j] = otherRow[k];
        ++k;
      }
    }

    // Try all cols in currnet row
    bool isDuplicated = false;
    rep(c, n) {
      if (elements[c].find(ans[r][c]) != elements[c].end()) { // duplicate
        isDuplicated = true;
        break;
      }
    }
    if (isDuplicated) {
      continue; // try next permutation
    } else {
      rep(c, n) { elements[c].insert(ans[r][c]); }
      bool res = backtrackAns(traces, r + 1, k);
      rep(c, n) { elements[c].erase(ans[r][c]); } // revert
      if (res) { return true; }
      // Here, try next permutation
    }
  } while (next_permutation(all(otherRow)));

  // Try all case, and can not found ans
  return false;
}

bool searchAns(vector<ll>& traces, ll k) {
  ll n = traces.size();
  ll s = 0; // sum of traces
  rep(i, n) {
    s += traces[i];
  }
  if (s != k) { return false; } // not valid

  // Here, traces is valid. we try (n-1)! ^ n cases
  ans = vector<vector<ll>>(n, vector<ll>(n));
  elements = vector<set<ll>>(n);
  return backtrackAns(traces, 0, k);
}

bool backtrack(vector<ll>& traces, ll i, ll k, ll pre, ll sum){
  ll n = traces.size();
  if (i == n) { // reached to last
    // Do check the validness
    // cout << "traces: "; printvec(traces);
    return searchAns(traces, k);
  }
  if (i == n-1) {
    ll now = k - sum;
    traces[i] = now;
    if (now < pre) { return false; } // not valid
    if (now > n) { return false; } // not valid
    return backtrack(traces, i+1, k, now, k);
  }

  // Here, we add traces[i] here
  for (int now = pre; now <= n; ++now) {
    if (sum + now > k) { break; } // too large
    sum += now;
    traces[i] = now;
    bool res = backtrack(traces, i+1, k, now, sum);
    if (res) { return true; }
    sum -= now;
  }

  return false;
}

void solve() {
  ll n, k;
  cin >> n >> k;
  // Here, we try ll case in greedy way

  vector<ll> traces(n);
  bool res = backtrack(traces, 0, k, 1, 0);

  if (res) {
    cout << "POSSIBLE" << endl;
    rep(i, n) {
      rep(j, n) {
        cout << ans[i][j];
        if (j < n-1) {
          cout << " ";
        }
      }
      cout << endl;
    }
  } else {
    cout << "IMPOSSIBLE" << endl;
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
    solve();
  }
}
