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
const ll HALF = 15;

ll n;

void normalize(vector<int> & counts) {
  assert((ll)counts.size() == n);

  for (int i = n - 1; i >= 0; --i) {
    counts[i] -= counts[0];
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n;
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  }

  map<vector<int>, int> possible;

  // Set pattern of right 15 bits.
  rep(mask, 1 << HALF) {
    vector<int> counts(n, 0);
    rep(i, n) {
      counts[i] = __builtin_popcountll((a[i] & ((1<<HALF) - 1)) ^ mask);
    }
    normalize(counts);

    if (possible.find(counts) == possible.end()) {
      possible[counts] = mask;
      cout << "counts: "; printvec(counts);
      cout << "mask: " << mask << endl;
    }
  }

  // Search in left 15 bits.
  rep(mask, 1 << HALF) {
    vector<int> counts(n, 0);
    rep(i, n) {
      counts[i] = __builtin_popcountll((a[i] >> HALF) ^ mask);
    }
    normalize(counts);

    rep(i, n) {
      counts[i] *= -1;
    }
    if (possible.find(counts) != possible.end()) {
      int other = possible[counts];
      // printvec(counts);
      // cout << "other: " << other << endl;
      cout << (mask << HALF) + other << endl;
      return 0;
    }
  }
  cout << -1 << endl;
}
