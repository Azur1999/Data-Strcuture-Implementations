#ifndef STACK_ARRAY_HPP
#define STACK_ARRAY_HPP
#include <iostream>
#include <string>

template <typename T>
class stack
{
private:
   T* elem;
   int num;
   int size;
   void realloc ();
public:
  ~stack ();
   stack ();
   stack (int);

   stack (stack&&);
   stack (const stack&);

   stack& operator=(stack&&);
   stack& operator=(const stack&);
  
   stack& push (const T&);
   stack& pop  ();

   int  length () { return num;      }
   bool empty  () { return num == 0; }
   T&   top    () ;

   friend std::ostream& operator<<(std::ostream& out, const stack<T>& temp)
   {
      out << std::endl;
    for(auto i=temp.num-1; i>=0; --i)
      out << temp.elem[i] << std::endl;
    return out;
   }
};

template <typename T>
stack<T>::stack(int vel)
{
  size = vel;
  num  = 0;
  elem = new T[size];
}

template <typename T>
T& stack<T>::top()
{
  if(num==0) std::cout << "Stack is empty" << std::endl;
  return elem[num-1]; 
}

template <typename T>
stack<T>& stack<T>::pop()
{
  if(num == 0) 
    std::cout << std::string("Stack is empty") << std::endl;
  else 
    --num;
  return *this;
}

template <typename T>
stack<T>& stack<T>::push(const T& el)
{
  if(num==size) realloc();
  if(num==0)
  {
    elem[0] = el;
  }
  else
  {
    elem[num] = el;
  }
  ++num;
  return *this;
}

template <typename T>
stack<T>& stack<T>::operator=(const stack<T>& other)
{
  delete [] elem;
  num  = other.num;
  size = other.size;
  elem = new T[size];
  for(auto i=0; i<other.num; ++i)
    elem[i] = other.elem[i];
  return *this;
}

template <typename T>
stack<T>& stack<T>::operator=(stack<T>&& other)
{
  delete [] elem;
  num = other.num;
  size = other.size;
  elem = other.elem;
  other.elem = nullptr;
  other.size = 0;
  other.num  = 0;
  return *this;
}

template <typename T>
stack<T>::stack(const stack<T>& other)
{
  size = other.size;
  num  = other.num;
  elem = new T[size];
  for(auto i = 0; i<num; ++i)
    elem[i] = other.elem[i]; 
}

template <typename T>
stack<T>::stack(stack<T>&& other)
{
  num  = other.num;
  size = other.size;
  elem = other.elem;
}

template <typename T>
stack<T>::stack()
{
  num = 0;
  size = 10;
  elem = new T[size];
}

template <typename T>
void stack<T>::realloc()
{
  T * temp = new T[size*2];
  for(auto i=0; i<size; ++i)
    temp[i] = elem [i];
  
  delete [] elem;
  elem = temp;
  size = size*2;
  temp = nullptr;
}

template <typename T>
stack<T>::~stack()
{
  delete [] elem;
  elem = nullptr;
  num  = 0;
  size = 0;
}
#endif 
