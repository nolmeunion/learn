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






