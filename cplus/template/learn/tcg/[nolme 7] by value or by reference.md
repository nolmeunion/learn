# 놀미 7. by value or by reference 


## passing by value 

### passing by value decays 

## passing by reference

### passing by value does not decay 

### passing by nonconstant reference 

### passing by forwarding reference

forwarding reference or universal reference

```c++
template<typename T>
void passR (T&& arg) {      // arg declared as forwarding reference
...
}

std::string s = "hi";
passR(s);                   // OK: T deduced as std::string& (also the type of arg)
passR(std::string("hi"));   // OK: T deduced as std::string, arg is std::string&&
passR(returnString());      // OK: T deduced as std::string, arg is std::string&&
passR(std::move(s));        // OK: T deduced as std::string, arg is std::string&&
passR(arr);                 // OK: T deduced as int(&)[4] (also the type of arg)
```

## using std::ref() and std::cref() 

```c++
template <>
struct minus<void> {
    template <class _Ty1, class _Ty2>
    constexpr auto operator()(_Ty1&& _Left, _Ty2&& _Right) const
        noexcept(noexcept(static_cast<_Ty1&&>(_Left) - static_cast<_Ty2&&>(_Right))) // strengthened
        -> decltype(static_cast<_Ty1&&>(_Left) - static_cast<_Ty2&&>(_Right)) {
        return static_cast<_Ty1&&>(_Left) - static_cast<_Ty2&&>(_Right);
    }

    using is_transparent = int;
};
```

이제 이런 건 읽을 수 있다. 더 놀자!



