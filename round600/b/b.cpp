// base. https://pastebin.com/whyCzpvV

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

const ll borne = (int)(1e6) + 6;
const int WAIT=0, ENTERED=1, LEFT=2;
int state[borne];

bool solve() {
  ll n;
  cin >> n;
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  }

  vector<int> cur;
  vector<int> res;
  int ofs = 0; // The number in office

  rep(i, n) {
    // cout << "i: " << i << endl;
    // cout << "a[i]: " << a[i] << endl;
    int ev = a[i];
    int guy = abs(ev);
    cur.push_back(guy);
    if (ev > 0) { // enter
      if (state[guy] != WAIT) {
        return false;
      }
      state[guy] = ENTERED;
      ++ofs;
    } else { // leave
      if (state[guy] != ENTERED) {
        return false;
      }
      state[guy] = LEFT;
      --ofs;
    }
    // End day when the number in office is 0
    if (ofs == 0) {
      res.push_back(cur.size());
      for (int x : cur) {
        state[x] = WAIT;
      }
      cur.clear();
    }
  }

  if (!cur.empty()) {
    return false;
  }

  ll sz = res.size();
  cout << sz << endl;
  rep(i, sz) {
    cout << res[i];
    if (i + 1 < sz) {
      cout << " ";
    } else {
      cout << endl;
    }
  }
  return true;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  if (!solve()) {
    cout << -1 << endl;
  }
}
