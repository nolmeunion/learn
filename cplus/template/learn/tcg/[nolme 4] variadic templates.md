# 놀미 4. variadic templates

## variadic templates 

### variadic templates by examples

```c++
00007FF7642EE48C  mov         edx,1  
00007FF7642EE491  mov         rcx,qword ptr [__imp_std::cout (07FF7643343A8h)]  
00007FF7642EE498  call        qword ptr [__imp_std::basic_ostream<char,std::char_traits<char> >::operator<< (07FF7643341C8h)]  
00007FF7642EE49E  mov         rcx,rax  
00007FF7642EE4A1  lea         rdx,[string "\n" (07FF764335324h)]  
00007FF7642EE4A8  call        std::operator<<<std::char_traits<char> > (07FF7642EBA80h)  
00007FF7642EE4AD  lea         rdx,[string "hello" (07FF764335744h)]  
00007FF7642EE4B4  mov         rcx,qword ptr [__imp_std::cout (07FF7643343A8h)]  
00007FF7642EE4BB  call        std::operator<<<std::char_traits<char> > (07FF7642EBA80h)  
00007FF7642EE4C0  mov         rcx,rax  
00007FF7642EE4C3  lea         rdx,[string "\n" (07FF764335324h)]  
00007FF7642EE4CA  call        std::operator<<<std::char_traits<char> > (07FF7642EBA80h)  
00007FF7642EE4CF  movss       xmm1,dword ptr [__real@40a00000 (07FF764338F34h)]  
00007FF7642EE4D7  mov         rcx,qword ptr [__imp_std::cout (07FF7643343A8h)]  
00007FF7642EE4DE  call        qword ptr [__imp_std::basic_ostream<char,std::char_traits<char> >::operator<< (07FF764334380h)]  
00007FF7642EE4E4  mov         rcx,rax  
00007FF7642EE4E7  lea         rdx,[string "\n" (07FF764335324h)]  
00007FF7642EE4EE  call        std::operator<<<std::char_traits<char> > (07FF7642EBA80h)  
```

릴리스 모드로 빌드하면 인라인과 최적화를 통해 variadic template 함수의 재귀호출이 사라진다. 
위와 같이 간단한 어셈블리는 이제 쉽게 읽을 수 있다. 


### sizeof... 

if constexpr (sizeof...(args) > 0 ) {
    print(args...);
}

이제 c++ 코딩할 때 컴파일 타임과 런 타임을 잘 구분해야 한다. 

c++은 세 가지 언어를 알아야 한다. TMPL, c++, 어셈블리. 
세 가지를 모두 잘 알면 c++은 매우 유용하다. 하나라도 모르면 위험하다. 


## fold expressions


## application of variadic templates

전에 타잎 리스트가 갖던 위치를 variadic template이 대체하고, 훨씬 편하게 사용할 수 있다. 

## variadic class templates and variadic expressions

```c++
template<typename... T>
void printDoubled (T const&... args)
{
print (args + args...);
}
```

pattern... 규칙을 따라 확장된다. 그래서 arg1 + arg1, arg2 + arg2, ... 가 된다. 

```c++
template<typename T1, typename... TN>
constexpr bool isHomogeneous (T1, TN...)
{
return (std::is_same<T1,TN>::value && ...); // since C++17
}
```

컴파일 타임 상수 함수를 메타함수로 구현한다. 



### variadic indices

```c++
template<typename C, typename... Idx>
void printElems (C const& coll, Idx... idx)
{
print (coll[idx]...);
}

std::vector<std::string> coll = {"good", "times", "say", "bye"};
printElems(coll,2,0,3);
```

### variadic class templates

당연 유용하다. Tuple, Variant가 대표적이다. 


### variadic deduction guides

```c++
namespace std {
template<typename T, typename... U> array(T, U...)
-> array<enable_if_t<(is_same_v<T, U> && ...), T>,
(1 + sizeof...(U))>;
}
```

이제 위의 코드도 알아볼 수 있다. 더 익숙해져야 자유롭게 된다. 


### variadic base classes and using 

```c++
template<typename... Bases>
struct Overloader : Bases...
{
using Bases::operator()...; // OK since C++17
};
```

위는 26.4절 볼 때 예시를 만들어 이해하도록 한다. 




