# sample server

서버는 이게 거의 다 일 듯. 타이머 등록과 실행 정도만 있으면 된다. 

```py
class HTTPProtocol(asyncio.Protocol):
    def __init__(self):
        self.connection = h11.Connection(h11.SERVER)
    def connection_made(self, transport):
        self.transport = transport
    def data_received(self, data):
        self.connection.receive_data(data)
        while True:
           event = self.connection.next_event()
            if isinstance(event, h11.Request):
                self.send_response(event)
            elif (
                isinstance(event, h11.ConnectionClosed)
                or event is h11.NEED_DATA or event is h11.PAUSED
            ):
                break
        if self.connection.our_state is h11.MUST_CLOSE:
            self.transport.close()
    def send_response(self, event):
        body = b"%s %s" % (event.method.upper(), event.target)
        headers = [
            ('content-type', 'text/plain'),
            ('content-length', str(len(body))),
        ]
        response = h11.Response(status_code=200, headers=headers)
        self.send(response)
        self.send(h11.Data(data=body))
        self.send(h11.EndOfMessage())
      
    def send(self, event):
        data = self.connection.send(event)
        self.transport.write(data)
```

## 에코 서버 완결편 

tcp_echo_server.py와 tcp_echo_loader.py로 테스트 진행. 

```python

ValueError: too many file descriptors in select()

c:\app\python37\lib\selectors.py in _select(self, r, w, _, timeout)
    312     if sys.platform == 'win32':
    313         def _select(self, r, w, _, timeout=None):
--> 314             r, w, x = select.select(r, w, w, timeout)
    315             return r, w + x, []
    316     else:
```

windows_event 쪽이 실행되어야 하는데 제대로 지정이 되지 않았다. 


```python
# work around to set _loop_factory
policy = asyncio.get_event_loop_policy()
policy._loop_factory = asyncio.ProactorEventLoop
```

위와 같이 해야 한다고 한다. Policy를 하나 만들어 제공해야 한다. 

3천 개 이상 연결도 잘 처리한다. 

