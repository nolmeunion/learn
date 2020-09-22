# 놀미 6. move semantics and enable_if 

move semantics can be used to optimize copying and assignments by moving (“stealing”) internal resources from a source object to a destination object instead of copying those contents.

## perfect forwarding 

Suppose you want to write generic code that forwards the basic property of passed arguments:
• Modifyable objects should be forwarded so that they still can be modified.
• Constant objects should be forwarded as read-only objects.
• Movable objects (objects we can “steal” from because they are about to expire) should be forwarded as movable objects


```c++
void f (X& val) {
g(val); // val is non-const lvalue => calls g(X&)
}
void f (X const& val) {
g(val); // val is const lvalue => calls g(X const&)
}
void f (X&& val) {
g(std::move(val)); // val is non-const lvalue => needs std::move() to call g(X&&)
}
```
void f(X&& val) 에서 std::move를 쓰는 이유는 표준에 따르면 "move semantics is not passed through"이기 때문이다. 

```c++
template<typename T>
void f (T&& val) {
g(std::forward<T>(val)); // perfect forward val to g()
}
```

Note that std::move() has no template parameter and “triggers” move semantics for the passed
argument, while std::forward<>() “forwards” potential move semantic depending on a passed
template argument.
Don’t assume that T&& for a template parameter T behaves as X&& for a specific type X. `Different
rules apply!` However, syntactically they look identical:
- X&& for a specific type X declares a parameter to be an rvalue reference. It can only be bound to
a movable object (a prvalue, such as a temporary object, and an xvalue, such as an object passed
with std::move(); see Appendix B for details). It is always mutable and you can always “steal”
its value.2
- T&& for a template parameter T declares a forwarding reference (also called universal reference).3
It can be bound to a mutable, immutable (i.e., const), or movable object. Inside the function
definition, the parameter may be mutable, immutable, or refer to a value you can “steal” the
internals from.

universal reference (또는 forwarding reference)로 T&&를 사용한다. 템플릿 파라미터로 사용할 때 쓰인다. 

```c++
template <class _Ty>
_NODISCARD constexpr _Ty&& forward(
    remove_reference_t<_Ty>& _Arg) noexcept { // forward an lvalue as either an lvalue or an rvalue
    return static_cast<_Ty&&>(_Arg);
}

template <class _Ty>
_NODISCARD constexpr _Ty&& forward(remove_reference_t<_Ty>&& _Arg) noexcept { // forward an rvalue as an rvalue
    static_assert(!is_lvalue_reference_v<_Ty>, "bad forward call");
    return static_cast<_Ty&&>(_Arg);
}
```
visual c++17의 forward 정의는 위와 같다. 

https://modoocode.com/228
- reference collapsing rule (레퍼런스 겹침 규칙)
  - &, &&가 홀수, 짝수개로만 남는다. 

이에 따라 forward가 레퍼런스를 받아들이면 첫번째 foward가 호출되고 결과 타잎도 lvalue reference가 된다. 

## special member function templates


## disable templates with enable_if<>

SFINAE 기법 중 하나. 

## using enable_if<>

## using concepts to simplify enable_if<> expressions 

```c++
template<typename STR>
requires std::is_convertible_v<STR,std::string>
Person(STR&& n) : name(std::forward<STR>(n)) {
...
}
```
We can even specify the requirement as a general concept

```c++
template<typename T>
concept ConvertibleToString = std::is_convertible_v<T,std::string>;
```

and formulate this concept as a requirement:

```c++
template<typename STR>
requires ConvertibleToString<STR>
Person(STR&& n) : name(std::forward<STR>(n)) {
...
}
```

This also can be formulated as follows:
```c++
template<ConvertibleToString STR>
Person(STR&& n) : name(std::forward<STR>(n)) {
...
}
```

requires와 template alias와 비슷한 concept 선언으로 쉽게 사용할 수 있다. 

# Appendix B. Value categories

an expression evaluates to a value. it has a value type and a value category. 

## B.1 traditional lvalues and rvalues

전통적으로 lvalue와 rvalue만 있다. 

Lvalues are expressions that refer to actual values stored in memory or in a machine register. 

1989년 c 표준화할 때 int const x와 같이 왼쪽에 나올 수 없는 이름이 있는 값이 생겼다. 

class rvalue가 할당의 왼쪽에 올 수 있다. 

Rvalues are pure mathematical values (such as 7 or the character ’a’) that don’t necessarily have
any associated storage; they come into existence for the purpose of a computation but cannot be
referenced again once they have been used. 

### B.1.1 lvalue to rvalue conversions 

x = y 

y가 lvalue에서 rvalue로 변환된다. 이를 lvalue-to-rvalue conversion이라 한다. 


## B.2 value categories since c++11

core categories: 
- lvalue
- prvalue (pure rvalue) 
- xvalue (eXpiring value)

composite categories: 
- glvalue (generalized lvalue) : the union of lvalue and xvalue 
- rvalue : the union of xvalue and prvalue

c++17의 분류:
- A glvalue is an expression whose evaluation determines the identity of an object, bit-field, or
function (i.e., an entity that has storage).
- A prvalue is an expression whose evaluation initializes an object or a bit-field, or computes the
value of the operand of an operator.
- An xvalue is a glvalue designating an object or bit-field whose resources can be reused (usually
because it is about to “expire”—the “x” in xvalue originally came from “eXpiring value”).
- An lvalue is a glvalue that is not an xvalue.
- An rvalue is an expression that is either a prvalue or an xvalue.


expression -> glvalue | rvalue 

glvalue -> lvalue | xvalue 
rvalue -> prvalue | xvalue 


위에서 말한 glvalue, rvalue 등등은 expression을 뜻하고 그 값을 의미하는 것이 아니다. 


### B.2.1 temporary materialization 

temporary materialization은 prvalue-to-xvalue conversion으로 lvalue-to-rvalue conversion의 역에 해당한다. 

```c++
int f(int const& x);
int r = f(3);
```

f를 호출할 때 x는 glvalue 형식이다. f(3)으로 호출할 때 3은 prvalue이다. glvalue가 필요할 때 prvalue는 glvalue로 변환되는 것처럼 행동해야 하고 이 값을 표현하는 식이 xvalue (category)가 된다. 

```c++

class N {
public:
    N();
    N(N const&) = delete; // this class is neither copyable ...
    N(N&&) = delete; // ... nor movable
};

N make_N() {
    return N{}; // Always creates a conceptual temporary prior to C++17.
} // In C++17, no temporary is created at this point.

auto n = make_N();  // ERROR prior to C++17 because the prvalue needs a
                    // conceptual copy. OK since C++17, because n is
                    // initialized directly from the prvalue
```

With C++17 the prvalue N itself does not produce a temporary. Instead, it initializes an object
determined by the context: In our example, that object is the one denoted by n. No copy or move
operation is ever considered (this is not an optimization, but a language guarantee) and therefore the
code is valid C++17.

놀랍다. 

```c++
00007FF7A38C3E46  mov         rcx,qword ptr [rbp+0E0h]  
00007FF7A38C3E4D  call        `anonymous namespace'::N::N (07FF7A38C3B40h)  
00007FF7A38C3E52  mov         rax,qword ptr [rbp+0E0h]  
```

여전히 이해 안 되는 부분이 있으므로 더 찾아 본다. 

## checking value categories with decltype 

```c++
if constexpr (std::is_lvalue_reference<decltype((e))>::value) {
    std::cout << "expression is lvalue\n";
}
else if constexpr (std::is_rvalue_reference<decltype((e))>::value) {
    std::cout << "expression is xvalue\n";
}
else {
    std::cout << "expression is prvalue\n";
}
```

## B.4 reference types

```c++
int& lvalue();
int&& xvalue();
int prvalue();

std::is_same_v<decltype(lvalue()), int&> // yields true because result is lvalue
std::is_same_v<decltype(xvalue()), int&&> // yields true because result is xvalue
std::is_same_v<decltype(prvalue()), int> // yields true because result is prvalue

int& lref1 = lvalue(); // OK: lvalue reference can bind to an lvalue
int& lref3 = prvalue(); // ERROR: lvalue reference cannot bind to a prvalue
int& lref2 = xvalue(); // ERROR: lvalue reference cannot bind to an xvalue

int&& rref1 = lvalue(); // ERROR: rvalue reference cannot bind to an lvalue
int&& rref2 = prvalue(); // OK: rvalue reference can bind to a prvalue
int&& rref3 = xvalue(); // OK: rvalue reference can bind to an xrvalue
```

