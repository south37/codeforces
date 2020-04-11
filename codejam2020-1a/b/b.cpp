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

void solve_for_small_n(ll n) {
  if (n == 1) {
    cout << "1 1" << endl;
    return;
  } else if (n == 2) {
    cout << "1 1" << endl;
    cout << "2 1" << endl;
    return;
  } else if (n == 3) {
    cout << "1 1" << endl;
    cout << "2 1" << endl;
    cout << "3 1" << endl;
    return;
  } else { // n >= 4
    cout << "1 1" << endl;
    cout << "2 1" << endl;
    cout << "3 2" << endl; // (2, 1)
    ll remain = n - 4;
    // Here, our position is (2, 1)
    // start from here, and increment in greedy way
    ll r = 2;
    while (remain > 0) {
      // Here, we do "(r, 1)" pair. It is rC1 = r.
      ++r;
      if (remain >= r) {
        remain -= r;
        cout << r + 1 << " " << 2 << endl;
      } else { // reached to small remaining
        break;
      }
    }
    --r; // decrease.
    // Here, we do small remaining
    while (remain > 0) {
      cout << r + 1 << " " << 1 << endl; // (r, 0)
      --remain;
      ++r;
    }
  }
}

void solve() {
  ll n;
  cin >> n;
  // Here, we calculate all case.
  // start from (0, 0). (n, k) is nCk.

  if (n <= 1000) {
    solve_for_small_n(n);
    return;
  }

  vector<vector<ll>> pascal(34); // 33C16 > 1e9. we need only this
  pascal[0].resize(1);
  pascal[0][0] = 1;
  rep(r, 34) {
    pascal[r].resize(r+1);
    pascal[r][0] = 1;
    pascal[r][pascal[r].size()-1] = 1;
    for (int k = 1; k < pascal[r].size()-1; ++k) {
      pascal[r][k] = pascal[r-1][k-1] + pascal[r-1][k];
    }
  }

  // For Debug
  // rep(r, 34) {
  //   printvec(pascal[r]);
  // }

  // vector<ll> fact(41); // 40C20 = 1e11. we need only this
  // fact[0] = 1;
  // for (ll i = 1; i <= 40; ++i) { fact[i] = fact[i-1] * i; }
  // printvec(fact);

  // Here, we consider large n.
  // we fetch center number in greedy way.
  ll remain = n;
  ll r = 0;
  while (remain > 0) {
    assert(r <= 33);

    ll k = r/2;

    // Here, we calculate rCk
    // ll cont = comb[r];
    // cont *= fact[r];
    // cont /= fact[k];
    // cont /= fact[r-k];
    ll cont = pascal[r][k];
    // cout << "remain: " << remain << endl;
    // cout << r<<"C"<<k<<": " << cont << endl;
    if (remain < cont * 2) {
      break;
    } else { // remain >= cont
      cout << r + 1 << " " << k + 1 << endl;
      remain -= cont;
    }
    ++r;
  }
  // Here, r is not printed yet.
  --r;
  ll k = r / 2;
  // Here, we get contribution from (r-1,k-1)
  while (remain > 0) {
    --r;
    --k;
    if (k >= 0) {
      // Calc rCk
      ll cont = pascal[r][k];
      // ll cont = comb[r];
      // cont *= fact[r];
      // cont /= fact[k];
      // cont /= fact[r-k];

      assert(remain >= cont);
      // cout << "remain: " << remain << endl;
      // cout << r<<"C"<<k<<": " << cont << endl;
      cout << r + 1 << " " << k + 1 << endl;
      remain -= cont;
    } else { // k < 0
      break;
    }
  }
  ++r;
  // Here, r is remaining, but k reached to 0.
  // we start from (r, 0) and go along (r+i, 0)
  while (remain > 0) {
    if (remain >= r) {
      cout << r + 1 << " 2" << endl;
      remain -= r;
      ++r;
    } else {
      break;
    }
  }
  // Here, r is not printed yet.
  --r;
  while (remain > 0) {
    cout << r + 1<< " 1" << endl;
    remain -= 1;
    ++r;
  }

  // Here, remain == 0
  return;
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
