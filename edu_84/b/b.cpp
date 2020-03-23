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
  ll n;
  cin >> n;
  set<ll> st; // represents remaining prince
  vector<ll> unused_dauter;
  rep(i, n) { st.insert(i); }
  rep(i, n) {
    ll k;
    cin >> k;
    vector<ll> targets(k); // target princes
    rep(i, k) {
      cin >> targets[i];
      --targets[i]; // 0-indexed
    }

    // Check the presence of prince
    auto stTarget = st.begin();
    bool isFound = false;
    rep(j, k) {
      if (targets[j] < *stTarget) { continue; } // skip small one.
      // Here, targets[j] >= stTarget
      if (targets[j] == *stTarget) { // found
        st.erase(stTarget);
        isFound = true;
        break;
      }
      // Here, targets[j] > stTarget
      auto it = st.lower_bound(targets[j]);
      if (it == st.end()) { // not found
        break;
      }
      if (targets[j] == *it) { // found
        st.erase(it);
        isFound = true;
        break;
      } else { // targets[j] > *it
        stTarget = it;
      }
    }
    if (!isFound) {
      unused_dauter.push_back(i);
    }
  }

  // Here, check the count
  if (st.size() == 0) { // all st is used
    cout << "OPTIMAL" << endl;
  } else {
    cout << "IMPROVE" << endl;
    cout << unused_dauter[0] + 1 << " " << (*st.begin()) + 1<< endl;
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
    solve();
  }
}
