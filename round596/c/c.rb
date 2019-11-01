require 'set'

def solve
  n, k, d = gets.chomp.split.map(&:to_i)
  a = gets.chomp.split.map(&:to_i)

  h = Hash.new # contains the count of each num.

  # We want to get th minimum cnt
  # We check [i, i+d-1] in each step. i is [0, n-d]
  0.upto(d-1).each do |j|
    h[a[j]] ||= 0
    h[a[j]] += 1
  end
  cnt = h.size

  min_cnt = cnt

  r = d # we already checked [0, d-1]
  while (r < n)
    l = (r - d + 1)  # e.g. if r = d, then l = 1. we check [l, r]
    # Now, check [l, r]

    h[a[r]] ||= 0
    h[a[r]] += 1
    if h[a[r]] == 1 # Just added
      cnt += 1
    end

    h[a[l-1]] -= 1
    if h[a[l-1]] == 0 # Just erased
      cnt -= 1
    end

    # p "[l, r]: #{[l, r]}"
    # p "cnt: #{cnt}"

    # For Debug
    # cnt = h.select { |k, v| v > 0 }.size

    if cnt < min_cnt
      min_cnt = cnt
    end

    r += 1
  end

  p min_cnt
end

t = gets.chomp.to_i
0.upto(t-1).each do
  solve
end
