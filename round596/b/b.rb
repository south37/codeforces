require 'set'

def solve
  n, k, d = gets.chomp.split.map(&:to_i)
  a = gets.chomp.split.map(&:to_i)

  cnt = 1000 # INF
  # We want to get th minimum cnt
  0.upto(n-d).each do |i|
    s = Set.new
    i.upto(i+d-1).each do |j|
      s << a[j]
    end
    if s.size < cnt
      cnt = s.size
    end
  end

  p cnt
end

t = gets.chomp.to_i
0.upto(t-1).each do
  solve
end
