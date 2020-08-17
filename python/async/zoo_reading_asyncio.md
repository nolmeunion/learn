# asyncio 분석과 이해 

zzean 파일은 모든 폴더에 마지막 파일이 되도록 고안한 readme와 같다. 

asyncio는 coroutine, future / promise와 event loop에 기초하고 있다. 

async / await는 future를 만드는 방법이고 
event loop는 적절한 이벤트가 발생할 때 future가 완료되도록 한다. 

coroutine은 스택을 갖고 여러 번 실행할 수 있다는 개념을 갖고 
여러 번 상태를 갖고 호출 될 수 있는 오브젝트는 generator라고 한다. 

아직 개념이 확립 중이긴 하지만 C#을 시작으로 node.js를 거쳐 
c++까지 확산 중이다. 

## 콜 그래프로 시작하기 

tcp_echo_server.py 예제를 구글링으로 구할 수 있다. 가장 간단한 코드에 기초하여 
하나씩 살펴보도록 한다. asyncio 모듈은 singleton처럼 동작한다. 왜냐하면
글로벌 함수로 내부에 직접 접근 가능하기 때문이다. 

```python
async def start_server(client_connected_cb, host=None, port=None, *,
                       loop=None, limit=_DEFAULT_LIMIT, **kwds):
```

첫 함수가 client_connected_cb이다. reader와 writer를 아규먼트로 전달한다. 

```python
async def handle_echo(reader, writer):
```

예제의 콜백 함수이다. 

doc string 내용이 다음과 같다. 

```
    """Start a socket server, call back for each client connected.

    The first parameter, `client_connected_cb`, takes two parameters:
    client_reader, client_writer.  client_reader is a StreamReader
    object, while client_writer is a StreamWriter object.  This
    parameter can either be a plain callback function or a coroutine;
    if it is a coroutine, it will be automatically converted into a
    Task.

    The rest of the arguments are all the usual arguments to
    loop.create_server() except protocol_factory; most common are
    positional host and port, with various optional keyword arguments
    following.  The return value is the same as loop.create_server().

    Additional optional keyword arguments are loop (to set the event loop
    instance to use) and limit (to set the buffer limit passed to the
    StreamReader).

    The return value is the same as loop.create_server(), i.e. a
    Server object which can be used to stop the service.
    """
```

create_server()에 기능을 더한 함수이다. 실제로 코드도 그렇다. 

```python
  return await loop.create_server(factory, host, port, **kwds)
```

events.py 파일에 create_server()가 정의되어 있다. 여기에 정의된 함수는 인터페이스이다. 

```python
async def create_server(
        self, protocol_factory, host=None, port=None,
        *, family=socket.AF_UNSPEC,
        flags=socket.AI_PASSIVE, sock=None, backlog=100,
        ssl=None, reuse_address=None, reuse_port=None,
        ssl_handshake_timeout=None,
        start_serving=True):
    """A coroutine which creates a TCP server bound to host and port.

    The return value is a Server object which can be used to stop
    the service.

    If host is an empty string or None all interfaces are assumed
    and a list of multiple sockets will be returned (most likely
    one for IPv4 and another one for IPv6). The host parameter can also be
    a sequence (e.g. list) of hosts to bind to.

    family can be set to either AF_INET or AF_INET6 to force the
    socket to use IPv4 or IPv6. If not set it will be determined
    from host (defaults to AF_UNSPEC).

    flags is a bitmask for getaddrinfo().

    sock can optionally be specified in order to use a preexisting
    socket object.

    backlog is the maximum number of queued connections passed to
    listen() (defaults to 100).

    ssl can be set to an SSLContext to enable SSL over the
    accepted connections.

    reuse_address tells the kernel to reuse a local socket in
    TIME_WAIT state, without waiting for its natural timeout to
    expire. If not specified will automatically be set to True on
    UNIX.

    reuse_port tells the kernel to allow this endpoint to be bound to
    the same port as other existing endpoints are bound to, so long as
    they all set this flag when being created. This option is not
    supported on Windows.

    ssl_handshake_timeout is the time in seconds that an SSL server
    will wait for completion of the SSL handshake before aborting the
    connection. Default is 60s.

    start_serving set to True (default) causes the created server
    to start accepting connections immediately.  When set to False,
    the user should await Server.start_serving() or Server.serve_forever()
    to make the server to start accepting connections.
    """
    raise NotImplementedError
```

## base_events.py 읽기 
r
```python
"""Base implementation of event loop.

The event loop can be broken up into a multiplexer (the part
responsible for notifying us of I/O events) and the event loop proper,
which wraps a multiplexer with functionality for scheduling callbacks,
immediately or at a given time in the future.

Whenever a public API takes a callback, subsequent positional
arguments will be passed to the callback if/when it is called.  This
avoids the proliferation of trivial lambdas implementing closures.
Keyword arguments for the callback are not supported; this is a
conscious design decision, leaving the door open for keyword arguments
to modify the meaning of the API call itself.
"""
```

멀티플렉서가 입출력 이벤트를 통지하고 이벤트 루프가 콜백을 처리한다. 

```python

def _format_handle(handle):
    cb = handle._callback
    if isinstance(getattr(cb, '__self__', None), tasks.Task):
        # format the task
        return repr(cb.__self__)
    else:
        return str(handle)

```

handle의 _callback이 Task인 지를 보고 문자열로 만든다. 

subprocess 모듈을 사용한다. _format_pipe(fd) 함수에서 문자열로 만든다. 이와 같이 C++이나 
다른 코드에서도 사람이 읽을 수 있는 형태로 디버깅 정보를 만드는 건 중요하다. 

```python
def _set_reuseport(sock):
    if not hasattr(socket, 'SO_REUSEPORT'):
        raise ValueError('reuse_port not supported by socket module')
    else:
        try:
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
        except OSError:
            raise ValueError('reuse_port not supported by socket module, '
                             'SO_REUSEPORT defined but not implemented.')
```

예외를 사용하여 기능을 파악하는 동적인 설정 방법과 깔끔한 문장으로 설명한 내용이 인상적이다. 

_ip_addr_info() 함수도 배울 만하다. 

```python
def _run_until_complete_cb(fut):
    if not fut.cancelled():
        exc = fut.exception()
        if isinstance(exc, BaseException) and not isinstance(exc, Exception):
            # Issue #22429: run_forever() already finished, no need to
            # stop it.
            return
    futures._get_loop(fut).stop()
```

asyncio에서 future, task, coroutine이 함께 쓰인다. 이들 클래스 간의 관계를 파악하는 것이 중요하다. 

```python
class _SendfileFallbackProtocol(protocols.Protocol):
```
Protocol의 예시가 나온다. 

```python
 async def drain(self):
        if self._transport.is_closing():
            raise ConnectionError("Connection closed by peer")
        fut = self._write_ready_fut
        if fut is None:
            return
        await fut
```

_write_ready_fut를 await로 대기하는 지점을 만든다. 

```python
    def pause_writing(self):
        if self._write_ready_fut is not None:
            return
        self._write_ready_fut = self._transport._loop.create_future()
```
이벤트 루프에서 future를 만든다. 


```python
class Server(events.AbstractServer):
```
서버이시다. 

```python
 def __init__(self, loop, sockets, protocol_factory, ssl_context, backlog,
                 ssl_handshake_timeout):
```
이벤트 루프와 연결된다. sockets는 _start_serving()에서 listen 호출의 대상이다. 

```python
    def _start_serving(self):
        if self._serving:
            return
        self._serving = True
        for sock in self._sockets:
            sock.listen(self._backlog)
            self._loop._start_serving(
                self._protocol_factory, sock, self._ssl_context,
                self, self._backlog, self._ssl_handshake_timeout)
```

_loop의 _start_serving()이 궁금하지만 참아둔다. 

```python
    async def start_serving(self):
        self._start_serving()
        # Skip one loop iteration so that all 'loop.add_reader'
        # go through.
        await tasks.sleep(0, loop=self._loop)
```
c# 보다 파이썬의 단일 쓰레드 상의 await가 사용하기 편해 보인다. ThreadPoolExecutor()도 있기 때문에
꼭 단일 쓰레드로 실행되는 건 아니다. 더 살펴봐야 한다. 


```python
    async def serve_forever(self):
        if self._serving_forever_fut is not None:
            raise RuntimeError(
                f'server {self!r} is already being awaited on serve_forever()')
        if self._sockets is None:
            raise RuntimeError(f'server {self!r} is closed')

        self._start_serving()
        self._serving_forever_fut = self._loop.create_future()

        try:
            await self._serving_forever_fut
        except futures.CancelledError:
            try:
                self.close()
                await self.wait_closed()
            finally:
                raise
        finally:
            self._serving_forever_fut = None
```

```python
class BaseEventLoop(events.AbstractEventLoop):
```

```python
def run_forever(self):
    """Run until stop() is called."""
    self._check_closed()
    if self.is_running():
        raise RuntimeError('This event loop is already running')
    if events._get_running_loop() is not None:
        raise RuntimeError(
            'Cannot run the event loop while another loop is running')
    self._set_coroutine_origin_tracking(self._debug)
    self._thread_id = threading.get_ident()

    old_agen_hooks = sys.get_asyncgen_hooks()
    sys.set_asyncgen_hooks(firstiter=self._asyncgen_firstiter_hook,
                            finalizer=self._asyncgen_finalizer_hook)
    try:
        events._set_running_loop(self)
        while True:
            self._run_once()
            if self._stopping:
                break
    finally:
        self._stopping = False
        self._thread_id = None
        events._set_running_loop(None)
        self._set_coroutine_origin_tracking(False)
        sys.set_asyncgen_hooks(*old_agen_hooks)
```
self._run_once() 호출이 전부이다. 이제 public 함수들이 나온다. 

- run_until_complete()
- stop()
- close()
- time()
- call_later()
- call_at()
- call_soon()
- getaddrinfo()
- getnameinfo()
- sock_sendfile()
- async create_connection() 
  - _create_connection_transport()를 사용 
- sendfile()
- start_tls()
  - upgrade transport to TLS
- create_datagram_endpoint()
- async create_server() 
- async connect_accepted_socket()
- connect_read_pipe()
- connect_write_pipe()
- subprocess_shell()
- subprocess_exec()


중요한 구현인 _run_once() private 함수가 있다. 

```python
"""Run one full iteration of the event loop.

This calls all currently ready callbacks, polls for I/O,
schedules the resulting callbacks, and finally schedules
'call_later' callbacks.
"""
```

```python
# This is the only place where callbacks are actually *called*.
# All other places just add them to ready.
# Note: We run all currently scheduled callbacks, but not any
# callbacks scheduled by callbacks run this time around --
# they will be run the next time (after another I/O poll).
# Use an idiom that is thread-safe without using locks.

ntodo = len(self._ready)
for i in range(ntodo):
    handle = self._ready.popleft()
    if handle._cancelled:
        continue
    if self._debug:
        try:
            self._current_handle = handle
            t0 = self.time()
            handle._run()
            dt = self.time() - t0
            if dt >= self.slow_callback_duration:
                logger.warning('Executing %s took %.3f seconds',
                                _format_handle(handle), dt)
        finally:
            self._current_handle = None
    else:
        handle._run()
```


## coroutines.py 읽기 

파이썬의 coroutine과 generator, Awaitable 컬렉션에 대해 알아야 한다. 연습을 하고 돌아온다. 

여러 문서들을 둘러보고 ipython에서 실습도 진행했다. 
- generator coroutine
  - yield 
  - yield from 
  - send 
- nativie coroutine 
  - async, await 
- concurrent.futures 
  - executor 
  - submit(), done(), result() 

```python
def coroutine(func):
```
내부에 yield from을 사용하고, types.coroutine(func) 또는 CoroWrapper()를 wrapper로 돌려준다. 


## events.py 읽기 

```python
class Handle:
    """Object returned by callback registration methods."""
```

내부 구현에서 매우 중요한 역할을 한다. run_once() 함수에서 _run()을 호출한다. 

```python
class TimerHandle(Handle):
    """Object returned by timed callback registration methods."""
```

- AbstractServer
- AbstractEventLoop
- AbstractEventLoopPolicy 
- BaseDefaultEventLoopPolicy

public 함수들: 
- get_running_loop()
- get_event_loop_policy()
- set_event_loop_policy()
- get_event_loop()
- set_event_loop()
- new_event_loop()
- get_child_watcher()
- set_child_watcher()


## protocols.py 읽기 

```python
class BaseProtocol:
    """Common base class for protocol interfaces.

    Usually user implements protocols that derived from BaseProtocol
    like Protocol or ProcessProtocol.

    The only case when BaseProtocol should be implemented directly is
    write-only transport like write pipe
    """
```

아래가 인터페이스 함수들이다. 

- connection_made()
- connection_lost()
- pause_writing()
- resume_writing()

```python
class Protocol(BaseProtocol):
    """Interface for stream protocol.

    The user should implement this interface.  They can inherit from
    this class but don't need to.  The implementations here do
    nothing (they don't raise exceptions).

    When the user wants to requests a transport, they pass a protocol
    factory to a utility function (e.g., EventLoop.create_connection()).

    When the connection is made successfully, connection_made() is
    called with a suitable transport object.  Then data_received()
    will be called 0 or more times with data (bytes) received from the
    transport; finally, connection_lost() will be called exactly once
    with either an exception object or None as an argument.

    State machine of calls:

      start -> CM [-> DR*] [-> ER?] -> CL -> end

    * CM: connection_made()
    * DR: data_received()
    * ER: eof_received()
    * CL: connection_lost()
    """
```

추가 인터페이스 클래스들이다. 
- BufferedProtocol 
- DatagramProtocol 
- SubprocessProtocol 


## streams.py 읽기 

```python
async def open_connection(host=None, port=None, *,
                          loop=None, limit=_DEFAULT_LIMIT, **kwds):
    """A wrapper for create_connection() returning a (reader, writer) pair.

    The reader returned is a StreamReader instance; the writer is a
    StreamWriter instance.

    The arguments are all the usual arguments to create_connection()
    except protocol_factory; most common are positional host and port,
    with various optional keyword arguments following.

    Additional optional keyword arguments are loop (to set the event loop
    instance to use) and limit (to set the buffer limit passed to the
    StreamReader).

    (If you want to customize the StreamReader and/or
    StreamReaderProtocol classes, just copy the code -- there's
    really nothing special here except some convenience.)
    """
```

```python
async def start_server(client_connected_cb, host=None, port=None, *,
                       loop=None, limit=_DEFAULT_LIMIT, **kwds):
    """Start a socket server, call back for each client connected.

    The first parameter, `client_connected_cb`, takes two parameters:
    client_reader, client_writer.  client_reader is a StreamReader
    object, while client_writer is a StreamWriter object.  This
    parameter can either be a plain callback function or a coroutine;
    if it is a coroutine, it will be automatically converted into a
    Task.

    The rest of the arguments are all the usual arguments to
    loop.create_server() except protocol_factory; most common are
    positional host and port, with various optional keyword arguments
    following.  The return value is the same as loop.create_server().

    Additional optional keyword arguments are loop (to set the event loop
    instance to use) and limit (to set the buffer limit passed to the
    StreamReader).

    The return value is the same as loop.create_server(), i.e. a
    Server object which can be used to stop the service.
    """
```

두 개와 StreamReader, StreamWriter가 있으면 통신이 된다. 

```python
class FlowControlMixin(protocols.Protocol):
    """Reusable flow control logic for StreamWriter.drain().

    This implements the protocol methods pause_writing(),
    resume_writing() and connection_lost().  If the subclass overrides
    these it must call the super methods.

    StreamWriter.drain() must wait for _drain_helper() coroutine.
    """

    def pause_writing(self):
    def resume_writing(self):
    def connection_lost(self, exc):            
```

```python
class StreamReaderProtocol(FlowControlMixin, protocols.Protocol):
    """Helper class to adapt between Protocol and StreamReader.

    (This is a helper class instead of making StreamReader itself a
    Protocol subclass, because the StreamReader has other potential
    uses, and to prevent the user of the StreamReader to accidentally
    call inappropriate methods of the protocol.)
    """

    def connection_made(): pass
    def connection_lost(): pass
    def data_received(): pass
    def eof_received(): pass
```

```python
class StreamWriter:
    """Wraps a Transport.

    This exposes write(), writelines(), [can_]write_eof(),
    get_extra_info() and close().  It adds drain() which returns an
    optional Future on which you can wait for flow control.  It also
    adds a transport property which references the Transport
    directly.
    """

    def write(): pass
    def writelines():L pass
    def write_eof(): pass
    async def wait_closed(): pass
    async def drain(): pass
```

```python
class StreamReader:

    def set_transport(): pass

```


## future와 task 

```python
class Task(futures._PyFuture):  # Inherit Python Task implementation
                                # from a Python Future implementation.

    """A coroutine wrapped in a Future."""
```

Future로 포장한 코루틴이 Task. 간결하고 명확한 정의이다. 

그럼 future는 event loop에서 어떻게 동작하는가? 

```python
def create_future(self):
    """Create a Future object attached to the loop."""
    return futures.Future(loop=self)
```

base_events.py의 BaseEventLoop에 구현되어 있다. Future를 만들어서 둘려준다. 



# 파이썬 관련 

파이썬 공부가 많이 부족하기 때문에 새로 보는 것들을 적는다. 

```python
try:
    import ssl
except ImportError:  # pragma: no cover
    ssl = None
```
설치 여부를 알 수 없을 때 import를 실행하고 ImportError 예외에서 None으로 설정한다. 
동적인 언어의 특성이자 기법이다. 


```python
from . import constants
```

현재 디렉토리에서 다른 파일들 읽어 들어오기 기법이다. 

_ 는 private이다. 


```python
_HAS_IPv6 = hasattr(socket, 'AF_INET6')
```
import는 실행이기 때문에 위와 같이 함수 호출을 할 수 있다. 


```python
def repr(_o : object) -> str : ...
```

builtins.pyi에 있는 형식이다. 

eval(repr(obj)) == obj 를 대부분 만족한다고 한다. 즉, 자기 생성 코드이다. 

```python
    if proto not in {0, socket.IPPROTO_TCP, socket.IPPROTO_UDP} or \
            host is None:
        return None
```

{0, 1, 2}의 타잎은 set이다. 


s.decode('idna')

위에서 idna는 Internationalized Domain Names in Applications 인코딩으로 bytes이다. 

아래 링크에 설명이 나와 있다. 
https://docs.python.org/2.4/lib/module-encodings.idna.html


Abstract / Base / Concrete의 상속 구조도 괜찮아 보인다. 아래의 구조이다. 
```python
class BaseEventLoop(events.AbstractEventLoop):
```






