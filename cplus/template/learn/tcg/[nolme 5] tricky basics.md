# 놀미 5. tricky basics 

## typename 

## zero initialization 

## this->

이건 모르고 있던 사실이다. 템플릿을 잘 쓰지 않아서 그랬나 보다. 


## templates for raw arrays and string literals

19.3.1에서 더 다룬다. 배열을 이렇게 쓸 일이 있는가? 

## member templates

```c++
template<typename T>
template<typename T2>
Stack<T>& Stack<T>::operator= (Stack<T2> const& op2)
{
elems.clear(); // remove existing elements
elems.insert(elems.begin(), // insert at the beginning
op2.elems.begin(), // all elements from op2
op2.elems.end());
return *this;
}
```

위와 같이 다른 타잎 파라미터를 갖는 템플릿 함수나 템플릿 클래스를 템플릿 클래스 내부에 가질 수 있다. 


### specialization of member function templates


### the .template construct 

https://stackoverflow.com/questions/610245/where-and-why-do-i-have-to-put-the-template-and-typename-keywords

```
Some names denote types or templates. In general, whenever a name is encountered it is necessary to determine whether that name denotes one of these entities before continuing to parse the program that contains it. The process that determines this is called name lookup.
```

If a name can't be looked up until the actual template arguments are known - then it's called a dependent name (it "depends" on the template parameters).

템플릿 아규먼트를 알아야 이름을 찾을 수 있을 때 이 이름을 템플릿 파라미터에 의존하는 이름이라고 한다. 

So there has to be a way to tell the compiler that certain names are types and that certain names aren't.

A name used in a template declaration or definition and that is dependent on a template-parameter is assumed not to name a type unless the applicable name lookup finds a type name or the name is qualified by the keyword typename.

템플릿 선언이나 정의에 사용된 이름은 타잎 이름으로 찾을 수 있거나 typename으로 명시되어야 타잎으로 간주된다. 


What if we can't know yet whether the name is a template when parsing the code? We will need to insert template immediately before the template name, as specified by 14.2/4. This looks like:

```c++
t::template f<int>(); // call a function template
```

Template names can not only occur after a :: but also after a -> or . in a class member access. You need to insert the keyword there too:

```c++
this->template f<int>(); // call a function template
```

### generic lambdas and member templates

```c++
[] (auto x, auto y) {
return x + y;
}
```

위는 아래와 같다. 

```c++
class SomeCompilerSpecificName {
public:
SomeCompilerSpecificName(); // constructor only callable by compiler
template<typename T1, typename T2>
auto operator() (T1 x, T2 y) const {
return x + y;
}
};
```

## variable templates

```c++
template <typanem T> 
constexpr T pi{3.14159265358979};
```

extern linkage를 갖는다. 


### variable temlates for data members

```c++
template<typename T>
class MyClass {
public:
static constexpr int max = 1000;
};

template<typename T>
int myMax = MyClass<T>::max;
```

### type traits suffix_v 

std::is_const_v<T> := std::is_const<T>::value


## template template parameters


```c++
template<typename T, template<typename Elem, typename = std::allocator<Elem>> class Cont = std::deque>
class Stack {
private:
    Cont<T> elems; // elements
public:
    void push(T const&); // push element
    void pop(); // pop element
    T const& top() const; // return top element
    bool empty() const { // return whether the stack is empty
        return elems.empty();
    }

    // assign stack of elements of type T2
    template<typename T2,
        template<typename Elem2,
        typename = std::allocator<Elem2>
    >class Cont2>
    Stack<T,Cont>& operator= (Stack<T2,Cont2> const&);

    // to get access to private members of any Stack with elements of type T2:
    template<typename, template<typename, typename>class>
    friend class Stack;
}
};
```

class 대신 typename을 c++17부터 쓸 수 있다. 

