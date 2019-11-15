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
  ll n;
  cin >> n;
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  }
  ll m;
  cin >> m;
  vector<P> hero;
  rep(i, m) {
    ll p, s;
    cin >> p >> s;
    hero.emplace_back(s, p);
  }
  sort(all(hero)); // hero is sorted by s.
  reverse(all(hero)); // decreasing ordre. larger s, larger p is in front.

  // We need the "decreasing order" data struccture.
  vector<P> powers; // The sorted (p, s). increasing order by p, decreasing order by s.
  ll min_p = -1;
  rep(i, m) {
    ll s = hero[i].fr;
    ll p = hero[i].sc;
    if (p > min_p) {
      powers.emplace_back(p, s);
      min_p = p;
    }
  }
  // Now, we have powers.

  ll ans = 0;
  rep(i, n) {
    ll max_a = -1; // The maximmum power of monster
    for (int j = i; j < n; ++j) {
      chmax(max_a, a[j]);
      auto it = lower_bound(all(powers), mp(max_a, -1LL));
      // cout << "i: " << i << endl;
      // cout << "j: " << j << endl;
      // cout << "a[j]: " << a[j] << endl;
      // cout << (*it).fr << "," << (*it).sc << endl;
      if (it == powers.end()) { // no hero can beat this
        cout << -1 << endl;
        return;
      }
      // Now, we find one hero it can beat this.
      if ((*it).sc >= j - i + 1) {
        if (j == n-1) { // reach goal
          ++ans;
          i = n; // set n to exit.
          break;
        } else { // try next
          continue;
        }
      } else { // *it.sc < xx, so the hero can't reach here.
        // Now, (j-1) is the longuest match.
        i = j-1; //j is
        ++ans;
        break;
      }
    }
  }

  cout << ans << endl;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll t;
  cin >> t;
  rep(i, t) {
    // cout << i << endl;
    solve();
  }
}
