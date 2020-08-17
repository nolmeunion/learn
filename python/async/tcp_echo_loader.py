# tcp echo client w/ multiple connections 

import asyncio
import sys

recv_count = 0

class EchoClient(asyncio.Protocol):
    def __init__(self):
        pass

    def connection_made(self, transport):
        transport.write("Hello Server".encode())
        self._transport = transport
        self._transport.write("Hello Server".encode())

    def data_received(self, data):
        #print('Data received: {!r}\n'.format(data.decode()))
        self._transport.write("Hello Server".encode())
        global recv_count
        recv_count += 1 

    def connection_lost(self, exc):
        #print('The server closed the connection')
        pass

async def main():
    global recv_count

    # Get a reference to the event loop as we plan to use
    # low-level APIs.
    loop = asyncio.get_event_loop()

    for i in range(1, 2048):
        await loop.create_connection( lambda: EchoClient(), '127.0.0.1', 8888)

    while True:
        await asyncio.sleep(10)
        print(f'PPS: {recv_count * 2 / 10.0}')
        recv_count = 0

loop = asyncio.ProactorEventLoop()
asyncio.set_event_loop(loop)

# work around to set _loop_factory
policy = asyncio.get_event_loop_policy()
policy._loop_factory = asyncio.ProactorEventLoop

asyncio.run(main())
