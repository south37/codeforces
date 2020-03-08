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
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, m;
  cin >> n >> m;

  vector<ll> ans(n);
  vector<ll> sumCnt(2*n + 1, 0); // sumCnt[i] .. [i/2]. The number of pairs (x,y) which forms x+y=i

  ll remain = m;
  ll j;
  for (j = 0; j < n; ++j) {
    if (remain <= sumCnt[j+1]) { break; }
    remain -= sumCnt[j+1];
    ans[j] = j+1;
    rep(i, j) {
      ++sumCnt[(i+1) + (j+1)];
    }
  }
  if (j == n) { // reached to last
    cout << -1 << endl;
    return 0;
  }

  ll x = j+1;
  while (remain != sumCnt[x]) {
    ++x;
  }
  ans[j] = x;

  ll maxSum;
  if (j == 0) { // m == 0
    maxSum = ans[j];
  } else {
    maxSum = ans[j-1] + ans[j];
  }
  ll cur = maxSum + 1;
  for (int i = j+1; i < n; ++i) {
    ans[i] = cur;
    cur += 2*(maxSum+1);
  }

  rep(i, n) {
    cout << ans[i];
    if (i != n-1) {
      cout << " ";
    }
  }
  cout << endl;
  return 0;
}
