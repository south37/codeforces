def main
  t = gets.chomp.to_i
  t.times { solve }
end

def solve
  # n = gets.chomp.to_i
  n, k = gets.chomp.split.map(&:to_i)
  # S = gets.chomp.chars

  if (k == 1)
    # Here, we should check the oddness of n
    if (n%2 == 1)
      print "YES\n"
      return
    else
      print "NO\n"
      return
    end
  end

  # Here, k >= 2
  # minimum k-1 sum is k_sum. [0, k-2]
  k_sum = (k-1)*(k-1)
  remain = n - k_sum
  if (remain % 2 == 1 && remain > (2*k - 3))
    print "YES\n"
  else
    print "NO\n"
  end
end

main
