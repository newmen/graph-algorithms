require 'benchmark'

N = 1000
# M = N * N
M = ((1 + N) * N * 0.5).to_i

def check(hash_func_name, each_inform = true)
  checker = {}
  has_error = 0
  (0..N).each do |i|
    b = (M == N * N) ? 0 : i
    (b..N).each do |j|
      h = send(hash_func_name, i, j)
      if checker[h]
        has_error += 1
        puts "#{hash_func_name}(#{i}, #{j}) = #{h}" if each_inform
      else
        checker[h] = true
      end
    end
  end
  "#{hash_func_name} conflicts: #{has_error} (#{100.0 * has_error / (M)}%)"
end

def h_and(i, j); i & j; end
def h_3and(i, j); i & j & (M - 1); end

def m_str(i, j, m)
  h = i % m
  (h * N + j) % m
end

def h_str(i, j); m_str(i, j, M); end
def h_ustr(i, j); m_str(i, j, M + 1); end
def h_dstr(i, j); m_str(i, j, M - 1); end
def h_lstr(i, j); m_str(i, j, M * 2); end
def h_llstr(i, j); m_str(i, j, M * 10); end

def h_rnd(i, j)
  a, b = 31415, 27183
  [i, j].inject(0) do |h, x|
    a = a * b % (M - 1)
    h = (a * h + x) % M
  end
end

def h_pair(i, j); "#{i}-#{j}"; end

def h_xor(i, j); i ^ j; end
def h_seek(i, j); j + 0x9e3779b9 + (i << 6) + (i >> 2); end
def h_or_seek(i, j); (i << 19) | (j << 7); end # 1
def h_seek_or_and(i, j); (i << 16) | (j & 0xffff); end # 4
def h_mul_xor(i, j); (i * 0x1f1f1f1f) ^ j; end
def h_cantor(i, j); ((i + j) * (i + j + 1) / 2) + j; end # 3
def h_seek_xor(i, j); (j << 16) ^ i; end # 2
def h_and_seek_or_and(i, j); ((j & 0xffff) << 16) | (i & 0xffff); end # 5

bad = %w( h_and h_3and h_str h_ustr h_dstr h_rnd h_xor h_seek )
good = %w( h_lstr h_llstr  h_pair h_mul_xor )
best = %w( h_or_seek h_seek_or_and h_cantor h_seek_xor h_and_seek_or_and )

best.each do |hash_func_name|
  msg = nil
  bm = Benchmark.measure { msg = check(hash_func_name, N < 11) }
  puts "#{msg.ljust(50)} -> #{bm}"
end
