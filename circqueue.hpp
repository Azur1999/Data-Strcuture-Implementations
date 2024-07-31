#include<iostream>
#include<algorithm>
#include<utility>

template<typename T>
class Circqueue {
  private:
   int size_=0;
   int capacity_=50;
   T* p_=nullptr;
   int prvi_=-1;
   int zadnji_=-1;
   void realloc();
  public:
  Circqueue(int k):capacity_{k},p_{new T[capacity_]}{}
  Circqueue(){}

  Circqueue(const Circqueue&);
  Circqueue(Circqueue&&);
  Circqueue& operator=(const Circqueue&);
  Circqueue& operator=(Circqueue&&);
  ~Circqueue();

   T operator[](int a)const{

     return p_[a];
   }
   T pop();
   T front();
   const T& front()const;
   T back();
   const T& back()const;
   template<typename U>
   void push(U &&);
   
   bool empty()const{
    return size_==0;
   }
   int capacity()const{
    return capacity_;
   }
   int size()const{
    return size_;
   }



};



//konstruktori
template<typename T>
Circqueue<T>::Circqueue(const Circqueue& d):size_{d.size_},capacity_{d.capacity_},prvi_{d.prvi_},zadnji_{d.zadnji_}{
  p_=new T[capacity_];
  for(auto i=0; i<size_;++i)
  {
    p_[i] = d.p_[i];
  }
}
template<typename T>
Circqueue<T>::Circqueue(Circqueue&& d):size_{d.size_},capacity_{d.capacity_},prvi_{d.prvi_},zadnji_{d.zadnji_}{
p_=d.p_;
d.p_=nullptr;
d.size_=0;
d.zadnji_=-1;
d.prvi_=-1;
d.capacity_=0;

}

template<typename T>
Circqueue<T>& Circqueue<T>::operator=(const Circqueue& d){
if(this!=&d){
delete []p_;
size_=d.size_;
capacity_=d.capacity_;
prvi_=d.prvi_;
zadnji_=d.zadnji_;
p_=new T[capacity_];
std::copy(d.p_,d.p_+size_,p_);

}
return *this;

}


template<typename T>
Circqueue<T>& Circqueue<T>::operator=(Circqueue&& d){

delete []p_;
size_=d.size_;
capacity_=d.capacity_;
prvi_=d.prvi_;
zadnji_=d.zadnji_;
p_=d.p_;

d.p_=nullptr;
d.size_=0;
d.zadnji_=-1;
d.prvi_=-1;
d.capacity_=0;

}


template<typename T>
Circqueue<T>::~Circqueue(){
delete []p_;
}





//metodi
template<typename T>
T Circqueue<T>::pop(){
if(empty())
  throw std::string{"Prazan red"};
T toReturn;
if(prvi_==zadnji_){
toReturn=p_[prvi_];
prvi_=zadnji_=-1;
size_=0;
}
else{
toReturn=p_[prvi_++];
--size_;
}
return toReturn;
}


template<typename T>
T Circqueue<T>::front(){
  if(empty())
    throw std::string{"Prazan red"};
 return p_[prvi_];

}


template<typename T>
const T& Circqueue<T>::front()const{

  if(empty())
    throw std::string{"Prazan red"};
return p_[prvi_];


}


template<typename T>
T Circqueue<T>::back(){
  if(empty())
    throw std::string{"Prazan red"};
return p_[zadnji_];

}


template<typename T>
const T& Circqueue<T>::back()const{

if(empty())
throw std::string{"Prazan red"};
return p_[zadnji_];

}
template<typename T>
void Circqueue<T>::realloc(){
capacity_=capacity_*2;
T* pom=new T[capacity_];
int i=0;
while(i<capacity_){
if(prvi_==0){
  pom[i]=p_[i];
  ++i;
  if(i==size_)break;
}
else{

  if(prvi_!=size_){
   pom[i++]=p_[prvi_++];
  }
  else{
  prvi_=0;
    pom[i++]=p_[prvi_++];
    if(prvi_==zadnji_)break;
  }
}
}
prvi_=0;
zadnji_=size_-1;
delete []p_;
p_=pom;
pom=nullptr;
}





template<typename T>
template<typename U>
void Circqueue<T>::push(U&& elem){
if((size_==capacity_))
  realloc();
if(size_==0)
prvi_=zadnji_=0;
else
zadnji_=(zadnji_+1)%capacity_;

p_[zadnji_]=std::forward<U>(elem);
++size_;

}


