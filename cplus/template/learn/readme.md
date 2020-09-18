# template 

오래 전부터 본 거고 익숙해진 부분도 있지만 아직 잘 모르는 부분도 많다. 
게임을 오픈하고 당장 뭔가에 집중하기 어려운 시기라 공부를 며칠 한다. 

## 교재 

C++ Templates. the Complete Guide. 책과 Visual C++의 STL 구현을 위주로 본다. 
C++11, 14, 17 까지 추가되거나 변경된 내용을 살펴도록 한다. 

매우 간결하게 정리되도록 한다. C++ 표준이 복잡하지만 사용이 복잡할 일은 없어야 한다. 

## 준비 

const에 관한 습관 바꾸기 
- 항상 const를 앞에 두는 것만 사용해 왔다. 
- const char* const 와 같은 걸 사용하도록 한다. 
- char* const로 쓰도록 한다. 

https://dydtjr1128.github.io/cpp/2020/01/08/Cpp-const.html

타잎을 기준으로 앞의 const는 type에 대한 속성, type 이후에는 직전의 대상에 적용되는 속성 
type은 집합이고, const는 특정 타잎의 값/변수에 대한 decorator 성격(추가 속성)이다. 

## chap 2. 함수 템플릿

교재 2장의 함수 템플릿을 따라간다. 

타잎 추론이 매우 중요한 편의 기능이다. decltype으로 추가된 반환타잎 추론이 
문법에 비해서는 매우 편리한 기능이다. 언어 공간에서 변환을 통한 코드 생성은
프로그래머에게 강력한 도구가 된다.  마법의 재료 중 하나. 

### overloading (중복적재) 규칙

일반 함수가 딱 맞으면 일반 함수 사용.
없으면 template의 타잎 계산에 따라 맞으면 template을 사용. 
일반 함수가 없으면 max('a', 42.7)과 같이 타잎이 다를 경우 컴파일 오류 

### STL의 max 구현 

visual c++의 stl 구현에서 max 함수만 살펴본다. 

#### initializer_list 

라이브러리와 컴파일러 간의 타잎 인지와 변환이 있다. 
{1, 2, 3}와 같은 구조를 std::initializer_list<int>()로 변환한다. 

https://en.cppreference.com/w/cpp/utility/initializer_list

cppreference는 항상 정확한 정의와 명확한 예시를 제공한다. 

Initializer lists may be implemented as a pair of pointers or 
pointer and length. Copying a std::initializer_list does not copy the underlying objects.

visual c++은 포인터 두 개로 구현한다. _Elem* _First와 _Elem* _Last이다. 

C++ 14이후에는 내부 배열이 a temporary array of type const T[N] 로 변경되었다. 

in which each element is copy-initialized (except that narrowing conversions are invalid) 
from the corresponding element of the original initializer list.

복사 생성된다고 나오는데 메모리는 누가 들고 있을까? 


#### max의 구현 

constexpr 함수이다. 

noexcept(_Left < _Right)는 constexpr을 만족하는 지 확인하는 구문이다. 

Because the noexcept operator always returns true for a constant expression, 
it can be used to check if a particular invocation of a constexpr function takes 
the constant expression branch.





# concurrent_queue 

## push

push:
```c++
00007FF7B7C76650  mov         qword ptr [rsp+10h],rdx  
00007FF7B7C76655  mov         qword ptr [rsp+8],rcx  
00007FF7B7C7665A  push        rbp  
00007FF7B7C7665B  push        rdi  
00007FF7B7C7665C  sub         rsp,0E8h  
00007FF7B7C76663  lea         rbp,[rsp+20h]  
00007FF7B7C76668  mov         rdi,rsp  
00007FF7B7C7666B  mov         ecx,3Ah  
00007FF7B7C76670  mov         eax,0CCCCCCCCh  
00007FF7B7C76675  rep stos    dword ptr [rdi]  
00007FF7B7C76677  mov         rcx,qword ptr [rsp+108h]  
00007FF7B7C7667F  lea         rcx,[__E66F493D_concurrent_queue@h (07FF7B7EA70CAh)]  
00007FF7B7C76686  call        __CheckForDebuggerJustMyCode (07FF7B7C588A1h)  
        _Internal_move_push( &_Src );
00007FF7B7C7668B  mov         rdx,qword ptr [_Src]  
00007FF7B7C76692  mov         rcx,qword ptr [this]  
00007FF7B7C76699  call        qword ptr [__imp_Concurrency::details::_Concurrent_queue_base_v4::_Internal_move_push (07FF7B7EA2008h)]  
    }
00007FF7B7C7669F  lea         rsp,[rbp+0C8h]  
00007FF7B7C766A6  pop         rdi  
00007FF7B7C766A7  pop         rbp  
```

_Internal_move_push:

_Concurrent_queue_rep& r = *_My_rep;

r의 메모리 내용:
```c++
-		r	{_Head_counter={_M_value=0 } _Tail_counter={_M_value=0 } _Array=0x0000021b9f749380 {{_Head_page={_M_value=...} ...}, ...} }	Concurrency::details::_Concurrent_queue_rep &
    +		_Head_counter	{_M_value=0 }	Concurrency::details::_Subatomic<unsigned __int64>
    +		_Tail_counter	{_M_value=0 }	Concurrency::details::_Subatomic<unsigned __int64>
-		_Array	0x0000021b9f749380 {{_Head_page={_M_value=0x0000000000000000 <NULL> } _Head_counter={_M_value=0 } _Tail_page=...}, ...}	Concurrency::details::_Micro_queue[8]
-		[0]	{_Head_page={_M_value=0x0000000000000000 <NULL> } _Head_counter={_M_value=0 } _Tail_page={_M_value=0x0000000000000000 <NULL> } ...}	Concurrency::details::_Micro_queue
    +		_Head_page	{_M_value=0x0000000000000000 <NULL> }	Concurrency::details::_Subatomic<Concurrency::details::_Concurrent_queue_base_v4::_Page *>
    +		_Head_counter	{_M_value=0 }	Concurrency::details::_Subatomic<unsigned __int64>
    +		_Tail_page	{_M_value=0x0000000000000000 <NULL> }	Concurrency::details::_Subatomic<Concurrency::details::_Concurrent_queue_base_v4::_Page *>
    +		_Tail_counter	{_M_value=0 }	Concurrency::details::_Subatomic<unsigned __int64>
		_Page_mutex_flag	0	volatile long
```


Choose 함수: 

```c++
-- d:\agent\_work\2\s\src\vctools\crt\crtw32\h\concurrent_queue.h -------------

        __declspec(align(64))
        _Subatomic<_Ticket> _Head_counter;

        __declspec(align(64))
        _Subatomic<_Ticket> _Tail_counter;

        __declspec(align(64))
        _Micro_queue _Array[_N_queue];

        _Micro_queue& _Choose( _Ticket _K )
        {
00007FF89844CE50  mov         qword ptr [rsp+10h],rdx  
00007FF89844CE55  mov         qword ptr [rsp+8],rcx  
00007FF89844CE5A  sub         rsp,28h  
            // The formula here approximates LRU in a cache-oblivious way.
            return _Array[_Index(_K)];
00007FF89844CE5E  mov         rcx,qword ptr [_K]  
00007FF89844CE63  call        Concurrency::details::_Concurrent_queue_rep::_Index (07FF89844CEB0h)  
00007FF89844CE68  imul        rax,rax,28h  
00007FF89844CE6C  mov         rcx,qword ptr [this]  
00007FF89844CE71  lea         rax,[rcx+rax+80h]  
        }
00007FF89844CE79  add         rsp,28h  
00007FF89844CE7D  ret  
```

_Micro_queue::_Push 함수: 

```c++

    //------------------------------------------------------------------------
    // _Micro_queue
    //------------------------------------------------------------------------
    void _Micro_queue::_Push( void* item, _Ticket k, _Concurrent_queue_base& base, void (_Concurrent_queue_base:: *moveOp)(_Concurrent_queue_base_v4::_Page&, size_t, void*))
    {
00007FF89844D520  mov         qword ptr [rsp+20h],r9  
00007FF89844D525  mov         qword ptr [rsp+18h],r8  
00007FF89844D52A  mov         qword ptr [rsp+10h],rdx  
00007FF89844D52F  mov         qword ptr [rsp+8],rcx  
00007FF89844D534  sub         rsp,0D8h  
        static _Concurrent_queue_base::_Page dummy = {static_cast<_Concurrent_queue_base::_Page*>((void*)1), 0};
        k &= -_Concurrent_queue_rep::_N_queue;
00007FF89844D53B  mov         rax,qword ptr [k]  
00007FF89844D543  and         rax,0FFFFFFFFFFFFFFF8h  
00007FF89844D547  mov         qword ptr [k],rax  
        _Concurrent_queue_base::_Page* p = NULL;
00007FF89844D54F  mov         qword ptr [p],0  
        size_t index = (k/_Concurrent_queue_rep::_N_queue & base._Items_per_page-1);
00007FF89844D558  mov         rax,qword ptr [base]  
00007FF89844D560  mov         rax,qword ptr [rax+10h]  
00007FF89844D564  dec         rax  
00007FF89844D567  mov         qword ptr [rsp+50h],rax  
00007FF89844D56C  xor         edx,edx  
00007FF89844D56E  mov         rax,qword ptr [k]  
00007FF89844D576  mov         ecx,8  
00007FF89844D57B  div         rax,rcx  
00007FF89844D57E  mov         rcx,qword ptr [rsp+50h]  
00007FF89844D583  and         rax,rcx  
00007FF89844D586  mov         qword ptr [index],rax  
        if( !index )
00007FF89844D58B  cmp         qword ptr [index],0  
00007FF89844D591  jne         Concurrency::details::_Micro_queue::_Push+0C4h (07FF89844D5E4h)  
        {
            try
            {
                p = base._Allocate_page();
00007FF89844D593  mov         rax,qword ptr [base]  
00007FF89844D59B  mov         rax,qword ptr [rax]  
00007FF89844D59E  mov         rax,qword ptr [rax+20h]  
00007FF89844D5A2  mov         qword ptr [rsp+58h],rax  
00007FF89844D5A7  mov         rcx,qword ptr [base]  
00007FF89844D5AF  mov         rax,qword ptr [rsp+58h]  
00007FF89844D5B4  call        qword ptr [__guard_dispatch_icall_fptr (07FF8984AA4B0h)]  
00007FF89844D5BA  mov         qword ptr [rsp+60h],rax  
00007FF89844D5BF  mov         rax,qword ptr [rsp+60h]  
00007FF89844D5C4  mov         qword ptr [p],rax  
00007FF89844D5C9  jmp         Concurrency::details::_Micro_queue::_Push+0ABh (07FF89844D5CBh)  
            } catch (...)
            {
                // mark it so that no more pushes are allowed.
                invalid_page = &dummy;
                _SpinLock lock(_Page_mutex_flag);

                _Tail_counter = k+_Concurrent_queue_rep::_N_queue+1;
                if( _Concurrent_queue_base::_Page* q = _Tail_page )
                    q->_Next = static_cast<_Concurrent_queue_base::_Page*>(invalid_page);
                else
                    _Head_page = static_cast<_Concurrent_queue_base::_Page*>(invalid_page);
                _Tail_page = static_cast<_Concurrent_queue_base::_Page*>(invalid_page);
                throw;
            }
            p->_Mask = 0;
00007FF89844D5CB  mov         rax,qword ptr [p]  
00007FF89844D5D0  mov         qword ptr [rax+8],0  
            p->_Next = NULL;
00007FF89844D5D8  mov         rax,qword ptr [p]  
00007FF89844D5DD  mov         qword ptr [rax],0  
        }

        {
            _Push_finalizer finalizer( *this, k+_Concurrent_queue_rep::_N_queue );
00007FF89844D5E4  mov         rax,qword ptr [k]  
00007FF89844D5EC  add         rax,8  
00007FF89844D5F0  mov         r8,rax  
00007FF89844D5F3  mov         rdx,qword ptr [this]  
00007FF89844D5FB  lea         rcx,[rsp+90h]  
00007FF89844D603  call        Concurrency::details::_Micro_queue::_Push_finalizer::_Push_finalizer (07FF89844C770h)  
00007FF89844D608  nop  
            if( _Tail_counter!=k ) {
00007FF89844D609  mov         rax,qword ptr [this]  
00007FF89844D611  add         rax,18h  
00007FF89844D615  mov         rcx,rax  
00007FF89844D618  call        Concurrency::details::_Subatomic<unsigned __int64>::operator unsigned __int64 (07FF89844CA90h)  
00007FF89844D61D  cmp         rax,qword ptr [k]  
00007FF89844D625  je          Concurrency::details::_Micro_queue::_Push+184h (07FF89844D6A4h)  
                _SpinWaitBackoffNone spinWait;
00007FF89844D627  lea         rdx,[Concurrency::details::_UnderlyingYield (07FF8984A33A0h)]  
00007FF89844D62E  lea         rcx,[rsp+0A0h]  
00007FF89844D636  call        Concurrency::details::_SpinWait<1>::_SpinWait<1> (07FF898431110h)  
                do
                {
                    spinWait._SpinOnce();
00007FF89844D63B  lea         rcx,[rsp+0A0h]  
00007FF89844D643  call        Concurrency::details::_SpinWait<1>::_SpinOnce (07FF8984315C0h)  
                    // no memory. throws an exception
                    if( _Tail_counter&0x1 )
00007FF89844D648  mov         rax,qword ptr [this]  
00007FF89844D650  add         rax,18h  
00007FF89844D654  mov         rcx,rax  
00007FF89844D657  call        Concurrency::details::_Subatomic<unsigned __int64>::operator unsigned __int64 (07FF89844CA90h)  
00007FF89844D65C  and         rax,1  
00007FF89844D660  test        rax,rax  
00007FF89844D663  je          Concurrency::details::_Micro_queue::_Push+166h (07FF89844D686h)  
                        throw std::bad_alloc();
00007FF89844D665  lea         rcx,[rsp+0B8h]  
00007FF89844D66D  call        std::bad_alloc::bad_alloc (07FF898449690h)  
00007FF89844D672  lea         rdx,[_TI2?AVbad_alloc@std@@ (07FF8984CBA88h)]  
00007FF89844D679  lea         rcx,[rsp+0B8h]  
00007FF89844D681  call        _CxxThrowException (07FF8984A5EC2h)  
                } while( _Tail_counter!=k ) ;
00007FF89844D686  mov         rax,qword ptr [this]  
00007FF89844D68E  add         rax,18h  
00007FF89844D692  mov         rcx,rax  
00007FF89844D695  call        Concurrency::details::_Subatomic<unsigned __int64>::operator unsigned __int64 (07FF89844CA90h)  
00007FF89844D69A  cmp         rax,qword ptr [k]  
00007FF89844D6A2  jne         Concurrency::details::_Micro_queue::_Push+11Bh (07FF89844D63Bh)  
            }

            if( p )
00007FF89844D6A4  cmp         qword ptr [p],0  
00007FF89844D6AA  je          Concurrency::details::_Micro_queue::_Push+215h (07FF89844D735h)  
            {
                _SpinLock lock(_Page_mutex_flag);
00007FF89844D6B0  mov         rax,qword ptr [this]  
00007FF89844D6B8  add         rax,20h  
00007FF89844D6BC  mov         rdx,rax  
00007FF89844D6BF  lea         rcx,[rsp+70h]  
00007FF89844D6C4  call        Concurrency::details::_SpinLock::_SpinLock (07FF8984A2AF0h)  
00007FF89844D6C9  nop  
                if( _Concurrent_queue_base::_Page* q = _Tail_page )
00007FF89844D6CA  mov         rax,qword ptr [this]  
00007FF89844D6D2  add         rax,10h  
00007FF89844D6D6  mov         rcx,rax  
00007FF89844D6D9  call        Concurrency::details::_Subatomic<Concurrency::details::_Concurrent_queue_base_v4::_Page *>::operator Concurrency::details::_Concurrent_queue_base_v4::_Page * (07FF89844CA70h)  
00007FF89844D6DE  mov         qword ptr [rsp+48h],rax  
00007FF89844D6E3  cmp         qword ptr [rsp+48h],0  
00007FF89844D6E9  je          Concurrency::details::_Micro_queue::_Push+1DAh (07FF89844D6FAh)  
                    q->_Next = p;
00007FF89844D6EB  mov         rax,qword ptr [rsp+48h]  
00007FF89844D6F0  mov         rcx,qword ptr [p]  
00007FF89844D6F5  mov         qword ptr [rax],rcx  
00007FF89844D6F8  jmp         Concurrency::details::_Micro_queue::_Push+1EFh (07FF89844D70Fh)  
                else
                    _Head_page = p;
00007FF89844D6FA  mov         rax,qword ptr [this]  
00007FF89844D702  mov         rdx,qword ptr [p]  
00007FF89844D707  mov         rcx,rax  
00007FF89844D70A  call        Concurrency::details::_Subatomic<Concurrency::details::_Concurrent_queue_base_v4::_Page *>::operator= (07FF89844CA10h)  
                _Tail_page = p;
00007FF89844D70F  mov         rax,qword ptr [this]  
00007FF89844D717  add         rax,10h  
00007FF89844D71B  mov         rdx,qword ptr [p]  
00007FF89844D720  mov         rcx,rax  
00007FF89844D723  call        Concurrency::details::_Subatomic<Concurrency::details::_Concurrent_queue_base_v4::_Page *>::operator= (07FF89844CA10h)  
00007FF89844D728  nop  
            }
00007FF89844D729  lea         rcx,[rsp+70h]  
00007FF89844D72E  call        Concurrency::details::_SpinLock::~_SpinLock (07FF8984A2B70h)  
00007FF89844D733  jmp         Concurrency::details::_Micro_queue::_Push+22Eh (07FF89844D74Eh)  
            else
            {
                p = _Tail_page;
00007FF89844D735  mov         rax,qword ptr [this]  
00007FF89844D73D  add         rax,10h  
00007FF89844D741  mov         rcx,rax  
00007FF89844D744  call        Concurrency::details::_Subatomic<Concurrency::details::_Concurrent_queue_base_v4::_Page *>::operator Concurrency::details::_Concurrent_queue_base_v4::_Page * (07FF89844CA70h)  
00007FF89844D749  mov         qword ptr [p],rax  
            }

            (base.*moveOp)(*p, index, item);
00007FF89844D74E  mov         rax,qword ptr [moveOp]  
00007FF89844D756  mov         qword ptr [rsp+78h],rax  
00007FF89844D75B  mov         rax,qword ptr [rsp+78h]  
00007FF89844D760  mov         qword ptr [rsp+80h],rax  
00007FF89844D768  mov         r9,qword ptr [item]  
00007FF89844D770  mov         r8,qword ptr [index]  
00007FF89844D775  mov         rdx,qword ptr [p]  
00007FF89844D77A  mov         rcx,qword ptr [base]  
00007FF89844D782  mov         rax,qword ptr [rsp+80h]  
00007FF89844D78A  call        qword ptr [__guard_dispatch_icall_fptr (07FF8984AA4B0h)]  
            // If no exception was thrown, mark item as present.
            p->_Mask |= size_t(1)<<index;
00007FF89844D790  mov         rax,qword ptr [index]  
00007FF89844D795  mov         ecx,1  
00007FF89844D79A  mov         qword ptr [rsp+88h],rcx  
00007FF89844D7A2  movzx       ecx,al  
00007FF89844D7A5  mov         rax,qword ptr [rsp+88h]  
00007FF89844D7AD  shl         rax,cl  
00007FF89844D7B0  mov         rcx,qword ptr [p]  
00007FF89844D7B5  mov         rcx,qword ptr [rcx+8]  
00007FF89844D7B9  or          rcx,rax  
00007FF89844D7BC  mov         rax,rcx  
00007FF89844D7BF  mov         rcx,qword ptr [p]  
00007FF89844D7C4  mov         qword ptr [rcx+8],rax  
        }
00007FF89844D7C8  lea         rcx,[rsp+90h]  
00007FF89844D7D0  call        Concurrency::details::_Micro_queue::_Push_finalizer::~_Push_finalizer (07FF89844C9E0h)  
    }
00007FF89844D7D5  add         rsp,0D8h  
00007FF89844D7DC  ret  
```


# MPL 

## type traits 

is_integral<T>는 is_integral_v를 사용하고 _Is_any_of_v를 사용한다. 

```c++
// STRUCT TEMPLATE is_integral
template <class _Ty>
_INLINE_VAR constexpr bool is_integral_v = _Is_any_of_v<remove_cv_t<_Ty>, bool, char, signed char, unsigned char,
    wchar_t,
#ifdef __cpp_char8_t
    char8_t,
#endif // __cpp_char8_t
    char16_t, char32_t, short, unsigned short, int, unsigned int, long, unsigned long, long long, unsigned long long>;
```

xtr1common에 있다. 

```c++
// VARIABLE TEMPLATE _Is_any_of_v
template <class _Ty, class... _Types>
_INLINE_VAR constexpr bool _Is_any_of_v = // true if and only if _Ty is in _Types
    disjunction_v<is_same<_Ty, _Types>...>;
```

disjuction_v<is_same<_Ty, Type>, is_same<_Ty, Type>, ...>으로 확장된다. 


```c++
// STRUCT TEMPLATE disjunction
template <bool _First_value, class _First, class... _Rest>
struct _Disjunction { // handle true trait or last trait
    using type = _First;
};

template <class _False, class _Next, class... _Rest>
struct _Disjunction<false, _False, _Next, _Rest...> { // first trait is false, try the next trait
    using type = typename _Disjunction<_Next::value, _Next, _Rest...>::type;
};

template <class... _Traits>
struct disjunction : false_type {}; // If _Traits is empty, false_type

template <class _First, class... _Rest>
struct disjunction<_First, _Rest...> : _Disjunction<_First::value, _First, _Rest...>::type {
    // the first true trait in _Traits, or the last trait if none are true
};

template <class... _Traits>
_INLINE_VAR constexpr bool disjunction_v = disjunction<_Traits...>::value;
```
값이 아니라 타잎이라는 점을 명심해야 한다. 값은 없다. 타잎만 있다. 

_Is_any_of_v<int, bool, char, ...> 
==> disjuction_v<is_same<int, bool>, is_same<int, char>, ...> 
==> disjunction<is_same<int, bool>::value, is_same<int, char>, ..., is_same<int, int>>
==> disjunction<false, is_same<int, char>, ..., is_same<int, int>>
    : _Disjunction<false, is_same<int, char>, ..., is_same<int, int>>

어떤 템플릿 함수가 일치할 지 알아야 하고, 확장을 할 수 있어야 한다. 





