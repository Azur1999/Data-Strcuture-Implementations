#pragma once

#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename T> 
class MojVector {
public:
  MojVector():arr_{new T[capacity_]}{};
  MojVector(const std::initializer_list<T> &);
  MojVector(const MojVector &);
  MojVector &operator=(const MojVector &);
  MojVector(MojVector &&);
  MojVector &operator=(MojVector &&);
  ~MojVector();

  MojVector& push_back(T);
  T &at(size_t a) const;
  T &operator[](size_t) const;
  void clear();
  size_t size() const;
  bool empty() const;
  const T &back() const;
  const T &front() const;
  T &back();
  T &front();
  void resize(size_t);
  MojVector &pop_back();
  size_t capacity() const;
  bool operator==(const MojVector &) const;
  bool operator!=(const MojVector &) const;

  class Iterator;
  Iterator begin() const;
  Iterator end() const;
  Iterator find(const T &element) const;
  MojVector &insert(Iterator, T element);
  Iterator erase(Iterator pos);
  Iterator erase(Iterator beginIt, Iterator endIt);

private:
  size_t capacity_=1000;
  size_t size_=0;
  T *arr_=nullptr;
};

template <typename T>
std::ostream &operator<<(std::ostream & out, const MojVector<T> &v){
  for(size_t i=0;i<v.size();++i)
    out<<v[i]<<' ';
}

template <typename T>
class MojVector<T>::Iterator
    : public std::iterator<std::random_access_iterator_tag, T> {
public:
  Iterator(T *ptr);
  T &operator*() const;
  T *operator->() const;
  Iterator &operator++();
  Iterator operator++(int);
  Iterator &operator--();
  Iterator operator--(int);
  Iterator operator+(size_t index);
  Iterator operator-(size_t index);
  size_t operator-(Iterator other);

  bool operator==(const Iterator &it) const;
  bool operator!=(const Iterator &it) const;
  bool operator<(const Iterator &it) const ;

  ~Iterator(){}

private:
  T *ptr_;
};



//konstruktori,destruktor,op= x7
template<class T>
MojVector<T>::MojVector(const std::initializer_list<T>& a):size_{a.size()},arr_{new T[capacity_]}{
  std::copy(a.begin(),a.end(),arr_);
}

template<typename T>
MojVector<T>::MojVector(const MojVector& drugi):size_{drugi.size_},arr_{new T[capacity_]}{
  std::copy(drugi.arr_,drugi.arr_+size_,arr_);
}
 
template<typename T>
MojVector<T>& MojVector<T>::operator=(const MojVector& drugi){
  if(&drugi!=this){
   delete []arr_;
   size_=drugi.size_;
   arr_=new T[capacity_];
   std::copy(drugi.arr_,drugi.arr_+size_,arr_);
  }
  return *this;

}

template<typename U>
 MojVector<U>::~MojVector(){
  delete []arr_;
}

template<typename T>
MojVector<T>&  MojVector<T>::operator=(MojVector<T>&& drugi){
  delete []arr_;
  arr_=drugi.arr_;
  size_=std::move(drugi.size_);
  capacity_=std::move(capacity_);
  drugi.arr_=nullptr;
  drugi.size_=0;
  return *this;
}

template<typename T>
MojVector<T>::MojVector(MojVector&& drugi):size_{std::move(drugi.size_)},arr_{drugi.arr_}{ 
  drugi.size_=0;
  drugi.capacity_=0;
  drugi.arr_=nullptr;
}

//ostali metodi x15

template<typename T>
T& MojVector<T>::at(size_t a)const{
   if(a<size_)
     return arr_[a];
   else
     throw std::out_of_range{""};
}

template<typename T>
T& MojVector<T>::operator[](size_t a)const{
   return arr_[a];
}

template<typename T>
void MojVector<T>::clear(){
   size_=0; 
}

template<typename T> 
size_t MojVector<T>::size()const{
return size_;
}

template<typename T> 
size_t MojVector<T>::capacity()const{
return capacity_;
}

template<typename T>
bool MojVector<T>::empty() const{
return size_==0;
}

template<class T>
bool MojVector<T>::operator==(const MojVector& drugi)const{
  if(size_!=drugi.size_)
    return false;

   for(int i=0;i<size_;++i){
      if(operator[](i)!=drugi[i])
        return false;
   }
   return true;
}

template<class U>
bool MojVector<U>::operator!=(const MojVector& drugi)const{
  if(size_!=drugi.size_)
    return true;

   for(int i=0;i<size_;++i){
      if(this->operator[](i)!=drugi[i])
        return true;
   }
   return false;

}

template<typename T>
MojVector<T>& MojVector<T>::push_back(T a){
   if(size_==capacity_){
     capacity_*=10;
     auto tmp=new T[capacity_];
     std::copy(arr_,arr_+size_,tmp);
     delete []arr_;
      arr_=tmp;
      tmp=nullptr;
   }
  arr_[size_++]=a;
}


template<typename T>
T& MojVector<T>::back(){
  return arr_[size_-1];
}

template<typename T>
T& MojVector<T>::front(){
  return *arr_;
}


template<typename T>
const T& MojVector<T>::back()const{
return arr_[size_-1];
}

template<typename T>
const T& MojVector<T>::front()const{
  return *arr_;
}
 template<typename T> 
 MojVector<T>& MojVector<T>::pop_back(){
   if(size_>0)
   --size_;
   return *this;
 }

template<typename T>
void MojVector<T>::resize(size_t new_size){
  size_t pom=size_;
  if(new_size<capacity_)
  size_=new_size;

  if(size_>pom)
  for(;pom<size_;++pom)
    operator[](pom)=0; 
}
//klasa iterator metodi
template<typename T>
MojVector<T>::Iterator::Iterator(T *ptr):ptr_{ptr}{}



template<typename T>
 typename MojVector<T>::Iterator& MojVector<T>::Iterator::operator++(){
   ++ptr_;
   return *this;
}


template<typename T>
typename MojVector<T>::Iterator& MojVector<T>::Iterator::operator--(){
--ptr_;
return *this;
}


template<typename T>
 typename MojVector<T>::Iterator MojVector<T>::Iterator::operator++(int a){
  Iterator tmp=*this;
  ++ptr_;
  return tmp; 
}


template<typename T>
  typename MojVector<T>::Iterator MojVector<T>::Iterator::operator--(int a){

  Iterator tmp=*this;
  --ptr_;
  return tmp; 
}
//auto it=v.begin()+2; *it
template<typename T>
T& MojVector<T>::Iterator::operator*()const{  //*it1;
  return *ptr_;
}


template<typename T>
typename MojVector<T>::Iterator MojVector<T>::Iterator::operator+(size_t indeks){
return Iterator(ptr_+indeks);
}

template<typename T>
  typename MojVector<T>::Iterator MojVector<T>::Iterator::operator-(size_t indeks){
return Iterator(ptr_-indeks);
}

template<typename T>
size_t MojVector<T>::Iterator::operator-(Iterator other){//  int a=it1-it2;
   size_t pozicija; 
   return pozicija=(ptr_-other.ptr_)>=0?ptr_-other.ptr_:0;
}


template<class T>
T* MojVector<T>::Iterator::operator->()const{
    return ptr_;
}


template<typename T>
bool MojVector<T>::Iterator::operator==(const Iterator& drugi)const{
return ptr_==drugi.ptr_;
}

template<typename T>
bool MojVector<T>::Iterator::operator!=(const Iterator& drugi)const{
return ptr_!=drugi.ptr_;
}


template<typename T>
bool MojVector<T>::Iterator::operator<(const Iterator& drugi)const{
return ptr_<drugi.ptr_;
}

//metodi vektora sa iteratorima

template<typename T>
  typename MojVector<T>::Iterator MojVector<T>::begin()const{
  return Iterator{arr_};
}

template<typename T>
 typename MojVector<T>::Iterator MojVector<T>::end()const{
  return Iterator{arr_}+size_;
}


template<typename T>
 typename MojVector<T>::Iterator MojVector<T>::find(const T& element)const{
    auto it=this->begin();
    auto it2=it;
    while(it!=end()){
      it2=it;
      if(*it==element)
        return it2;
      ++it;
    }
    return end();
}


template<typename T>
MojVector<T>& MojVector<T>::insert(Iterator it,T element){ //v.insert(v.begin(),2);  {1,2,3,4}->{2,1,2,3,4}
  
  T tmp=*it;
   if(size_<capacity_){
    while(it!=end()){
      *it=element;//4->9 
      element=tmp;//el->4
      if((++it)!=end())
      tmp=*it; 
    }
    push_back(element);
    return *this;
   }
   else{
    T* pom=arr_;
    capacity_*=2;
    arr_=new T[capacity_];
    std::copy(pom,pom+size_,arr_);
    delete []pom; 
    
    while(it!=end()){
      *it=element;//4->9 
      element=tmp;//el->4
      if((++it)!=end())
      tmp=*it; 
    }
    push_back(element);
    return *this;
     
   }
  }


 template<typename T>
  typename MojVector<T>::Iterator MojVector<T>::erase(Iterator pos){
   T temp=*pos;
   int i=0;
   MojVector<T>::Iterator it=pos;//1 2 3 ->1 3 
   while(pos!=end()&&it!=end()){ 
    ++it;
    if(it!=end()){
     *pos=*it;//2,3
      *it=temp;
      ++pos;
      ++i; 
    }
   }
  pop_back(); 
   return i==0?end():end()-i;  
 }

  template<typename T>
  typename MojVector<T>::Iterator MojVector<T>::erase(Iterator BeginIt,Iterator endIt){
    while(BeginIt!=endIt){
    BeginIt=erase(BeginIt);
    --endIt;
    }
  return endIt;

  }





 





