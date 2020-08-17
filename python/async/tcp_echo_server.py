import asyncio
import sys

class EchoServer(asyncio.Protocol):

    def connection_made(self, transport):
        #peername = transport.get_extra_info('peername')
        #print('Connection from {}'.format(peername))
        self.transport = transport

    def data_received(self, data):
        #message = data.decode()
        #print('Data received: {!r}'.format(message))

        #print('Send: {!r}'.format(message))
        self.transport.write(data)

        #print('Close the client socket')
        #self.transport.close()

    def connection_lost(self, exc):
        #print('The server closed the connection')
        pass


async def main():
    # Get a reference to the event loop as we plan to use
    # low-level APIs.
    loop = asyncio.get_event_loop()

    server = await loop.create_server(
        lambda: EchoServer(),
        '127.0.0.1', 8888)

    async with server:
        await server.serve_forever()

loop = asyncio.ProactorEventLoop()
asyncio.set_event_loop(loop)

# work around to set _loop_factory
policy = asyncio.get_event_loop_policy()
policy._loop_factory = asyncio.ProactorEventLoop

asyncio.run(main())
