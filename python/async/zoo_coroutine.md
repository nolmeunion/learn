# coroutine 

https://hamait.tistory.com/830

파이썬은 우리나라에서도 잘 하는 사람들이 꽤 많아 보인다. 

```py
In [22]: def simple_gen():
    ...:     yield "Hello"
    ...:     yield "World"
    ...:

In [23]: g1 = simple_gen()

In [24]: g1
Out[24]: <generator object simple_gen at 0x00000137F228FAC8>

In [25]: type(g1)
Out[25]: generator

In [26]: next(g1)
Out[26]: 'Hello'

In [27]: next(g1)
Out[27]: 'World'

In [28]: next(g1)
---------------------------------------------------------------------------
StopIteration                             Traceback (most recent call last)
<ipython-input-28-b6af764d1389> in <module>
----> 1 next(g1)

StopIteration:
```

yield from은 iterator의미를 갖는 컨테이너에서 값을 돌려준다. 
- yield from 반복가능한객체
- yield from 이터레이터
- yield from 제너레이터객체


async / await는 native 코루틴이라 불린다. 
yield / yield from으로도 여전히 사용할 수 있다. 

future는 외부에서 보이는데 왜 future를 넣었을까? 
task는 내부 구현에 가까운 듯 하다. 


# concurrent.futures

```py
from concurrent.futures import ThreadPoolExecutor
from time import sleep
 
def return_after_5_secs(message):
    sleep(5)
    return message
 
pool = ThreadPoolExecutor(3)
 
future = pool.submit(return_after_5_secs, ("hello"))
print(future.done())
sleep(5)
print(future.done())
print(future.result())
```

파이썬에서 future는 task이며 실행기에서 실행된다. 

Executor는 ThreadPoolExecutor와 ProcessPoolExecutor가 있다. 
ProcessPoolExecutor가 제대로 동작하지 않는다. 


