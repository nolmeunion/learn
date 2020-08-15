import re

re.sub('apple|orange', 'fruit', 'apple box orange tree')

s = ' "server_no" : 131'

s_r = re.sub('(\s+)("\w+")\s*:\s*(.*)', '\\1 \\2 : 472', s)

print(s_r)

# re에서 group이 메모리로 동작한다. 


