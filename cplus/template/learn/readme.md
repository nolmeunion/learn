# template 

���� ������ �� �Ű� �ͼ����� �κе� ������ ���� �� �𸣴� �κе� ����. 
������ �����ϰ� ���� ������ �����ϱ� ����� �ñ�� ���θ� ��ĥ �Ѵ�. 

## ���� 

C++ Templates. the Complete Guide. å�� Visual C++�� STL ������ ���ַ� ����. 
C++11, 14, 17 ���� �߰��ǰų� ����� ������ ���쵵�� �Ѵ�. 

�ſ� �����ϰ� �����ǵ��� �Ѵ�. C++ ǥ���� ���������� ����� ������ ���� ����� �Ѵ�. 

## �غ� 

const�� ���� ���� �ٲٱ� 
- �׻� const�� �տ� �δ� �͸� ����� �Դ�. 
- const char* const �� ���� �� ����ϵ��� �Ѵ�. 
- char* const�� ������ �Ѵ�. 

https://dydtjr1128.github.io/cpp/2020/01/08/Cpp-const.html

Ÿ���� �������� ���� const�� type�� ���� �Ӽ�, type ���Ŀ��� ������ ��� ����Ǵ� �Ӽ� 
type�� �����̰�, const�� Ư�� Ÿ���� ��/������ ���� decorator ����(�߰� �Ӽ�)�̴�. 

## chap 2. �Լ� ���ø�

���� 2���� �Լ� ���ø��� ���󰣴�. 

Ÿ�� �߷��� �ſ� �߿��� ���� ����̴�. decltype���� �߰��� ��ȯŸ�� �߷��� 
������ ���ؼ��� �ſ� ���� ����̴�. ��� �������� ��ȯ�� ���� �ڵ� ������
���α׷��ӿ��� ������ ������ �ȴ�.  ������ ��� �� �ϳ�. 

### overloading (�ߺ�����) ��Ģ

�Ϲ� �Լ��� �� ������ �Ϲ� �Լ� ���.
������ template�� Ÿ�� ��꿡 ���� ������ template�� ���. 
�Ϲ� �Լ��� ������ max('a', 42.7)�� ���� Ÿ���� �ٸ� ��� ������ ���� 

### STL�� max ���� 

visual c++�� stl �������� max �Լ��� ���캻��. 

#### initializer_list 

���̺귯���� �����Ϸ� ���� Ÿ�� ������ ��ȯ�� �ִ�. 
{1, 2, 3}�� ���� ������ std::initializer_list<int>()�� ��ȯ�Ѵ�. 

https://en.cppreference.com/w/cpp/utility/initializer_list

cppreference�� �׻� ��Ȯ�� ���ǿ� ��Ȯ�� ���ø� �����Ѵ�. 

Initializer lists may be implemented as a pair of pointers or 
pointer and length. Copying a std::initializer_list does not copy the underlying objects.

visual c++�� ������ �� ���� �����Ѵ�. _Elem* _First�� _Elem* _Last�̴�. 

C++ 14���Ŀ��� ���� �迭�� a temporary array of type const T[N] �� ����Ǿ���. 

in which each element is copy-initialized (except that narrowing conversions are invalid) 
from the corresponding element of the original initializer list.

���� �����ȴٰ� �����µ� �޸𸮴� ���� ��� ������? 


#### max�� ���� 

constexpr �Լ��̴�. 

noexcept(_Left < _Right)�� constexpr�� �����ϴ� �� Ȯ���ϴ� �����̴�. 

Because the noexcept operator always returns true for a constant expression, 
it can be used to check if a particular invocation of a constexpr function takes 
the constant expression branch.






