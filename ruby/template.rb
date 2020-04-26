def main
  t = gets.chomp.to_i
  t.times {
    solve
  }
end

def solve
  n = gets.chomp.to_i
  a, b, c = gets.chomp.split.map(&:to_i)
  # S = gets.chomp.chars
  p n
  p [a, b, c]
end

main
