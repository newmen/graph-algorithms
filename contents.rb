# coding: utf-8

def get_contents(comment_begin)
  uses = `grep -r "#{comment_begin}" cpp`.chomp.split("\n")
  uses.map do |use|
    filename, comment = use.split(':', 2)
    num = comment.dup.strip
    num["// #{comment_begin} "] = ''
    num, _ = num.split(' ', 2)
    fnum, snum = num.split('.')
    comment['//'] = ''
    [fnum.to_i, snum.to_i, comment.strip, filename]
  end
end

def sort_contents(contents)
  contents.sort do |a, b|
    a[0] != b[0] ? a[0] <=> b[0] : a[1] <=> b[1]
  end
end

def repo_url
  return @repo_url if @repo_url
  own_url = `git config --get remote.origin.url`.chomp
  user_repo = own_url.match(':(.*)\.git')[1]
  @repo_url = "https://github.com/#{user_repo}"
end

def link_to(title, filename)
  "[#{title}](#{repo_url}/blob/master/#{filename})"
end

def make_contents(contents)
  sort_contents(contents).map do |_, _, comment, filename|
    "* #{link_to(comment, filename)}"
  end.join("\n")
end

program_contets = make_contents(get_contents('Программа'))
issue_contets = make_contents(get_contents('Упражнение'))

File.open('contents.md', 'w') do |f|
  f.write("### Программы из текста\n\n")
  f.write(program_contets)

  f.write("\n\n### Упражнения\n\n")
  f.write(issue_contets)
end
