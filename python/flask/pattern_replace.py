# goal: to replace a string in a pattern 
# example: "hello" : 3312
# we want to replace 3312 which follows from "hello" :
import re

s1 = '"hello": 3312'
s2 = '"hello" :   3315'

# replace the number after "hello" : to another number

s_r = re.sub('(\s*)("\w+")\s*:\s*(.*)', '\\1 \\2 : 472', s1)
print(s_r)

s_r = re.sub('(\s*)("\w+")\s*:\s*(.*)', '\\1 \\2 : 2', s2)
print(s_r)

