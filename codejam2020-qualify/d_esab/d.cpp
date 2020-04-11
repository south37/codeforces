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

ll testcase;
ll tryCnt = 0; // trial count.

char checkDigit(int idx) {
  // cerr << "testcase: " << testcase << endl;
  // cerr << "idx: " << idx << endl;
  // cerr << flush;

  ++tryCnt;

  cout << (idx+1) << endl;
  cout << std::flush;
  char digit;
  cin >> digit; // '0' or '1'
  return digit;
}

void flip(string& s) {
  ll n = s.size();
  rep(i, n) {
    if (s[i] == '0') {
      s[i] = '1';
    } else if (s[i] == '1') { // s[i] == '1'
      s[i] = '0';
    } else {
      // Do nothing
    }
  }
}

bool submitResult(const string& ans) {
  cout << ans << endl;
  cout << std::flush;

  char res;
  cin >> res;
  if (res == 'Y') { // correct answer
    return true;
  } else { // invalid answer
    cout << "Our answer is below. This is wrong." << endl;
    cout << ans << endl;
    cout << std::flush;
    abort();
  }
}

void solve(ll b) {
  if (b == 10) { // 10-case
    string ans(b, ' ');
    rep(i, b) {
      ans[i] = checkDigit(i);
    }
    bool res = submitResult(ans);
    if (res) { return; } else { abort(); }
  }

  string ans(b, ' ');

  // Here, we want to find the "same-pair" and "different-pair"
  // At first, find the "same-pair"
  ll sameId = -1;
  ll diffId = -1;
  rep(i, b/2) {
    // cerr << "i: " << i << endl;
    char c1 = checkDigit(i);
    // cerr << "b-1-i: " << b-1-i << endl;
    char c2 = checkDigit(b-1-i);
    if (c1 == c2) {
      sameId = i;
    } else { // c1 != c2
      diffId = i;
    }

    if (sameId >= 0 && diffId >= 0) {
      break;
    }
  }
  // We increment tryCnt to 0
  while (tryCnt % 10 != 0) {
    checkDigit(0);
  }

  // Here, tryCnt % 10 == 0. Next, some operation occurs
  // cerr << "sameId: " << sameId << endl;
  // cerr << "same: " << checkDigit(sameId) << "," << checkDigit(b-1-sameId)  << endl;
  // cerr << "diffId: " << diffId << endl;
  // cerr << "same: " << checkDigit(diffId) << "," << checkDigit(b-1-diffId)  << endl;
  // while (tryCnt % 10 != 0) {
  //   checkDigit(0);
  // }

  // Here, sameId or diffId > 0.
  if (sameId == -1) { // Here, all elements have different
    char diffLeft = checkDigit(diffId);

    int i = 0;
    while (tryCnt % 10 != 0) {
      ans[i] = checkDigit(i);
      ++i;
    }

    // Here, flip and
    while (true) {
      bool allCalculated = true;
      rep(j, b) {
        if (ans[j] == ' ') { // not yet calculated
          allCalculated = false;
        }
      }
      if (allCalculated) { break; }

      char diffLeft2 = checkDigit(diffId);
      // Here, we can distinguish the operation by check the { same, same2 }  and { diff, diff2 }

      bool diffChange = diffLeft != diffLeft2;
      diffLeft = diffLeft2;

      if (diffChange) {
        flip(ans);
      } else {
        // Do nothing
      }

      int j = 0;
      while (tryCnt % 10 != 0 && j < b) {
        if (ans[j] == ' ') { // not yet calculated
          ans[j] = checkDigit(j);
        }
        ++j;
      }
    }
    bool res = submitResult(ans);
    if (res) { return; } else { abort(); }
  }
  if (diffId == -1) { // diffId == -1. Here. all elements have same
    char sameLeft = checkDigit(sameId);

    int i = 0;
    while (tryCnt % 10 != 0) {
      ans[i] = checkDigit(i);
      ++i;
    }

    // Here, flip and
    while (true) {
      bool allCalculated = true;
      rep(j, b) {
        if (ans[j] == ' ') { // not yet calculated
          allCalculated = false;
        }
      }
      if (allCalculated) { break; }

      char sameLeft2 = checkDigit(sameId);
      // Here, we can distinguish the operation by check the { same, same2 }  and { diff, diff2 }

      bool sameChange = sameLeft != sameLeft2;
      sameLeft = sameLeft2;

      if (sameChange) {
        flip(ans);
      } else {
        // Do nothing
      }

      int j = 0;
      while (tryCnt % 10 != 0 && j < b) {
        if (ans[j] == ' ') { // not yet calculated
          ans[j] = checkDigit(j);
        }
        ++j;
      }
    }
    bool res = submitResult(ans);
    if (res) { return; } else { abort(); }
  }

  // Here, we have sameId and diffId. we can distinguish the operation by this information.
  while (tryCnt % 10 != 0) {
    checkDigit(0);
  }

  char sameLeft = checkDigit(sameId);
  char diffLeft = checkDigit(diffId);
  // cerr << "sameId: " << sameId << endl;
  // cerr << "sameLeft: " << sameLeft << endl;
  // cerr << "sameRight: " << checkDigit(b-1-sameId) << endl;
  // cerr << "diffId: " << diffId << endl;
  // cerr << "diffLeft: " << diffLeft << endl;
  // cerr << flush;
  // cerr << "diffRight: " << checkDigit(b-1-diffId) << endl;
  // ans[sameId] = sameLeft;
  // ans[b-1-sameId] = sameLeft;
  // ans[diffId] = diffLeft;
  // ans[b-1-diffId] = (diffLeft == '0') ? '1' : '0';
  // vector<char> same(2); // pair of { left, right }
  // vector<char> diff(2); // pair of { left, right }
  // same[0] = checkDigit(sameId); // left
  // same[1] = checkDigit(b - 1 - sameId); // right
  // diff[0] = checkDigit(diffId); // left
  // diff[1] = checkDigit(b - 1 - diffId); // right
  int i = 0;
  // rep(i, 8) {
  //   ans[i] = checkDigit(i);
  // }
  while (tryCnt % 10 != 0) {
    ans[i] = checkDigit(i);
    ++i;
  }

  int isReversed = 0;

  // ll i = 8;
  // while (i < b) {
  while (true) {
    bool allCalculated = true;
    rep(j, b) {
      if (ans[j] == ' ') { // not yet calculated
        allCalculated = false;
      }
    }
    if (allCalculated) { break; }

    // vector<char> same2(2); // pair of { left, right }
    // vector<char> diff2(2); // pair of { left, right }
    // same2[0] = checkDigit(sameId); // left
    // same2[1] = checkDigit(b - 1 - sameId); // right
    // diff2[0] = checkDigit(diffId); // left
    // diff2[1] = checkDigit(b - 1 - diffId); // right
    char sameLeft2 = checkDigit(sameId);
    char diffLeft2 = checkDigit(diffId);
    // Here, we can distinguish the operation by check the { same, same2 }  and { diff, diff2 }

    bool sameChange = sameLeft != sameLeft2;
    bool diffChange = diffLeft != diffLeft2;
    // cerr << "before same, after same: " << sameLeft << ", " << sameLeft2 << endl;
    // cerr << "before diff, after diff: " << diffLeft << ", " << diffLeft2 << endl;
    sameLeft = sameLeft2;
    diffLeft = diffLeft2;

    if (sameChange && diffChange) { // flip. 0 <-> 1
      // cerr << "flip" << endl;
      // cerr << "before flip: \"" << ans << "\"" << endl;
      flip(ans);
      // cerr << "after flip: \"" << ans << "\"" << endl;
    } else if (sameChange && !diffChange) { // both.
      // cerr << "both" << endl;
      isReversed ^= 1;
      // cerr << "before reverse: \"" << ans << "\"" << endl;
      reverse(all(ans));
      // cerr << "after reverse: \"" << ans << "\"" << endl;
      // cerr << "before flip: \"" << ans << "\"" << endl;
      flip(ans);
      // cerr << "after flip: \"" << ans << "\"" << endl;
    } else if (!sameChange && diffChange) { // reverse
      //cerr << "reverse" << endl;
      isReversed ^= 1;
      // cerr << "before reverse: \"" << ans << "\"" << endl;
      reverse(all(ans));
      // cerr << "after reverse: \"" << ans << "\"" << endl;
    } else { // nothing
      // cerr << "nothing" << endl;
      // Do nothing
    }
    // cerr << flush;

    // Here, ans is operated. We want to set value.
    // if (isReversed) {
    //   ll iter = 0;
    //   while (iter < 8 && i < b) {
    //     ans[b-1-i] = checkDigit(b-1-i);
    //     ++iter; ++i;
    //   }
    // } else {
    //   ll iter = 0;
    //   while (iter < 8 && i < b) {
    //     ans[i] = checkDigit(i);
    //     ++iter; ++i;
    //   }
    // }
    int j = 0;
    while (tryCnt % 10 != 0 && j < b) {
      if (ans[j] == ' ') { // not yet calculated
        ans[j] = checkDigit(j);
      }
      ++j;
    }
  }
  // Here, ans is calculated

  bool res = submitResult(ans);
  if (res) { return; }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll t, b;
  cin >> t >> b;
  // cerr << "t: " << t << endl;
  // cerr << "b: " << b << endl;
  rep(i, t) {
    testcase = i;
    tryCnt = 0;
    //cout << "Case #" << (i+1) << ": ";
    solve(b);
    //cout << endl;
  }
}
