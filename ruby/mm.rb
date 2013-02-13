BASE = [
  %w(0 0 1 0 0 1),
  %w(1 0 0 0 0 0),
  %w(0 1 0 0 0 0),
  %w(0 0 1 0 1 0),
  %w(0 0 0 0 0 1),
  %w(0 0 0 0 1 0)
]

def make_bmatrix
  i = 0
  BASE.map do |row|
    i, j = i + 1, 0
    row.map do |x|
      j += 1
      x == '1' || (block_given? && yield(i - 1, j - 1))
    end
  end
end

def sq_bmatrix(a, b)
  result = Array.new(a.size) { Array.new(a.size, false) }
  a.size.times do |s|
    a.size.times do |t|
      a.size.times { |i| result[s][t] ||= a[s][i] && b[i][t] }
    end
  end
  result
end

def print_bmatrix(matrix)
  matrix.each do |row|
    row.each do |x|
      print (x ? '1' : '0').rjust(2)
    end
    puts
  end
  puts
end

def mul_bmarix(name, matrix, depth, prev_result = nil)
  @depth = depth unless prev_result

  puts "#{name} ** #{@depth - depth + 1}:"
  prev_result ||= matrix
  print_bmatrix(prev_result)
  return if depth == 1
  mul_bmarix(name, matrix, depth - 1, sq_bmatrix(prev_result, matrix))
end

az = make_bmatrix
mul_bmarix('AZ', az, 20)

puts '-' * BASE.size * 2
puts

ao = make_bmatrix { |i, j| i == j }
mul_bmarix('AO', ao, 5)
