def edge(v, w)
  "#{v} #{w}"
end

def sparse(v, e)
  p = 2.0 * e / (v * (v - 1))
  result = []
  100.times do |i|
    i.times do |j|
      result << edge(i, j) if rand < p
    end
  end
  result
end

def dense(v)
  [*0...v].combination(2).map { |a, b| edge(a, b) }
end

def write(filename, edges)
  File.open(filename, 'w') do |f|
    f.write(edges.join('   '))
    f.write("\n\n")
  end
end

write('sparse.txt', sparse(1000, 5000))
