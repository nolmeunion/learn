# reading xen definitive guide book 

OS 개발을 해보지 않아 잘 모르는 부분이 많지만 이 쪽도 한번 보자. 

OS, 네트워크, 데이터베이스, 언어와 컴파일러, 그래픽스가 중요한 영역이고 
네트워크와 데이터베이스, 언어와 컴파일러, 그래픽스는 좀 알지만 OS는 아직 잘 모른다는 생각이 많이 든다. 

원인을 모르게 연결이 끊어지는 현상과 디펜더 (EDR) 기능이 악화 시키는 현상의 원인을 파악하기 어렵기 때문에 
시작한 공부지만 좋은 기회로 삼도록 한다. 

가상화의 기반은 운영체제와 하드웨어이므로 해당 분야도 같이 본다면 좋겠다. 
가장 좋은 방법은 작은 OS를 하나 만들어 보는 것이다. 
부팅, 메모리, 프로세스, 디바이스, 파일 시스템, 이더넷/IP 통신까지 진행하면 
OS를 안다고 할 수 있다. 

Xen을 새로운 OS를 만드는 좋은 플래폼으로 책에서 소개하고 있다. 이는 디바이스 추상화를 하나의 인터페이스로 
단순화 할 수 있기 때문이다. 공부하면서 작은 OS를 Xen 상에 만드는 걸 목표로 할 수 있다. 

보기 보다는 만들어 보자. 


# The state of virtualization 

## what is virtualization? 

emulation과 비슷. 가상화로 하나의 시스템은 두 개 이상의 시스템처럼 보인다. 

대부분의 os는 가상화를 일부 포함한다. CPU를 여러 프로세스에서 사용할 때, 메모리 주소를 접근할 때 가상화가 사용된다. 또는 CPU와 메모리가 가상화되어 있다. (여러 개 있는 것처럼 동작한다) 

소켓 API는 네트워크 장치를 나만 쓰는 것처럼 사용할 수 있도록 한다. windowing 시스템도 스크린과 입력 장치가 프로세스 입장에서 혼자 쓰는 것처럼 사용할 수 있도록 가상화를 제공한다. 

Isolation, multiplexing. 

### cpu 가상화 

- interrupt
- save state 
- resume 

Popek and Goldberg. "Formal requirements for Virtualizable Third Generation Architectures" 
- Privileged instructions 
- Control sensitive instructions 
  - Updating virtual to physical memory mapping 
  - Communicating with devices 
  - Manipulating global configuration registers 
- Behavior sensitive instructions 
  - Those that behave in a defferent way depending on the configuration of resoures 

trap, kernel mode (cpu, registers)

알파 장비의 가상화는 PALCode의 실행만 가로채서 여러 OS를 돌릴 수 있게 해주면 된다. 

### I/O 가상화 

MMU (Memory Management Unit) : 주소 가상화. 
이에 따라 가상화가 쉬운 편이다. 

일반 장치는 어렵다. 

DMA. 물리 주소를 사용한다. 

주로 다양성 때문이다. 장치는 종류도 많고 커널과 통신하는 방법도 다르다. 
DMA가 매우 중요한 기법이므로 이와 비슷한 성능을 지원해야 한다. 

## why virtualize?

- sharing resources (multiplexing)
- isolation 
- migration 

## the first virtual machine 

IBM system/360, Model 67, zSeries . 


## the problem of x86 

LAR, LSL과 같이 세그먼트 정보를 갖고 오지만 트랩 불가능한 명령들이 있다. 이는 메모리 상태를 VM 단위로 알 수 없도록 한다. 

SIDT와 같이 특정 condition 레지스터들의 값을 변경하지만 로드 명령어가 없는 경우가 있다. 이런 명령들은 매번 트랩을 걸어서 상태를 얻어와야 하는 문제를 일으킨다. 

## some solutions 

### binrary rewriting 

바이너리를 변경하여 privileged 명령을 emulated 버전으로 변경한다. 

80~97% 정도의 호스트 머신 성능을 보여준다. 


### paravirtualization 

para는 further의 뜻인데 반가상화로 번역했다. 더가상화가 영어 의미에 맞는 걸로 보인다. 

what is the closest system to x86 that can virtualize?

emulation을 제공하는 대신에 OS를 컴파일 타임에 변경하여 ring 1에서 동작하도록 수정한다. 
hypercall을 제공하여 권한이 필요한 명령을 os 작성자가 사용할 수 있게 한다. 

1 push dword 0
2 mov eax , 1
3 push eax
4 int 80h

80h 인터럽트가 걸리면 하이퍼바이저를 호출하고 다시 OS 커널의 82h 핸들러를 호출한다. 

### hardware-assisted virtualization 

## the xen architecture 

hyperviser, kernel, userspace applications. 

### the hypervisor, the os, and the applications 


### the role of domain 0 

domain 0 is very important to a Xen system. 

- provides device drivers 
- 

TCP/IP 통신이 Xen에서 이루어지는 방식을 설명한다. AWS도 이렇지는 않겠지? 
```
First, it travels through the TCP/IP stack as it would
normally. The bottom of the stack, however, is not a normal network interface
driver. It is a simple piece of code that puts the packet into some shared memory.
The memory segment has been previously shared using Xen grant tables and
advertised via the XenStore.
The other half of the split device driver, running on the dom0 guest, reads
the packet from the buffer, and inserts it into the firewalling components of the
operating system—typically something like iptables or pf, which routes it as it
would a packet coming from a real interface. Once the packet has passed through
any relevant firewalling rules, it makes its way down to the real device driver.
This is able to write to certain areas of memory reserved for I/O, and may require
access to IRQs via Xen. The physical network device then sends the packet
```

Domain U Guest / Split device driver ==> Shared Memory ==> 
Domain 0 OS / Split device driver 
    ==> TCP/IP Stack (Routing/Bridging) 
    ==> Real Device Driver 
    ==> Physical Device 

