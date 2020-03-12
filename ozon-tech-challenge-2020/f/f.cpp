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

const ll INF = 1e12;
const ll MOD = 1000000007;  // 1e9 + 7

vector<ll> a;
ll n;

void add_prime(set<ll>& pf, ll num) {
  for (ll i = 2; i*i <= num; ++i) {
    if (num % i == 0) {
      while (num % i == 0) {
        num /= i;
      }
      pf.insert(i);
    }
  }
  if (num > 1) {
    pf.insert(num);
  }
}

// required operation for change a to divisable by num.
ll solve(ll num) {
  ll ans = 0;
  rep(i, n) {
    if (a[i] < num) {
      ans += num - a[i];
    } else {
      ans += min(a[i]%num, num - (a[i]%num));
    }
  }
  return ans;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n;
  a.resize(n);
  vector<ll> per; // the random number container

  rep(i, n) {
    cin >> a[i];
    per.push_back(i);
  }

  // shuffle per
  mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
  shuffle(all(per), mt);

  set<ll> pf; // prime factors
  rep(i, min(100ll, n)) {
    ll aa = a[per[i]];
    add_prime(pf, aa);
    add_prime(pf, aa+1);
    if (aa > 1) {
      add_prime(pf, aa-1);
    }
  }

  // Debug
  // while (!pf.empty()) {
  //   cout << *pf.begin() << endl;
  //   pf.erase(pf.begin());
  // }

  ll ans = n; // answer is at most n.
  for (ll num : pf) {
    ans = min(ans, solve(num));
  }
  cout << ans << endl;
}
