# libuv

## reading tests

uv_loop_t
uv_handle_t

uv_walk
uv_run

can_ipv6 

## test-async.c

- thread_cb(void* arg)
- uv_mutex_lock(), uv_mutex_unlock()
- uv_async_send()
- uv_async_t 

## test-default-loop-close

```c++
  loop = uv_default_loop();
  ASSERT(loop != NULL);

  ASSERT(0 == uv_timer_init(loop, &timer_handle));
  ASSERT(0 == uv_timer_start(&timer_handle, timer_cb, 1, 0));
  ASSERT(0 == uv_run(loop, UV_RUN_DEFAULT));
  ASSERT(1 == timer_cb_called);
  ASSERT(0 == uv_loop_close(loop));
```
기본 개념을 잘 보여준다. 

## test-tcp-connect-timeout 

```c++
  ASSERT_EQ(0, uv_ip6_addr("::1", 9999, &addr));

  r = uv_timer_init(uv_default_loop(), &timer);
  ASSERT_EQ(r, 0);

  /* Give it 1s to timeout. */
  r = uv_timer_start(&timer, timer_cb, 1000, 0);
  ASSERT_EQ(r, 0);

  r = uv_tcp_init(uv_default_loop(), &conn);
  ASSERT_EQ(r, 0);

  r = uv_tcp_connect(&connect_req,
                     &conn,
                     (const struct sockaddr*) &addr,
                     connect_local_cb);
  if (r == UV_ENETUNREACH)
    RETURN_SKIP("Network unreachable.");
  ASSERT_EQ(r, 0);

  r = uv_run(uv_default_loop(), UV_RUN_DEFAULT);
  ASSERT_EQ(r, 0);
```

loop와 cb로 처리 흐름을 만들고 사용한다. 
개별 기능에 대한 인터페이스는 다르게 사용할 수 있다. 

어떤 일이든 철저해야 재미도 있고 결과도 좋다. 



