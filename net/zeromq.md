# zeromq

node
  listen
  connect
  set( timer )

queue 

task 
  <timer_1, tcb_1>
  <timer_2, tcb_2>
  ...
  <message_1, mcb_1>
  <message_2, mcb_2>
  ...

data, objects

queue를 메세징 프레임워크로 본다 ==> zmq

queue를 채널로 본다. ==> wise

queue 대기와 쓰레드 처리가 통합되어 있다. ==> R2M 

libuv:
- queue가 없고 stream으로 전달. io object에 바이트 큐. 
- 이후 처리는 알아서 한다. 


