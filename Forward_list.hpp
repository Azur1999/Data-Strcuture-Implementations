#include<iostream>
#include<initializer_list>
#include<functional>
#include<iterator>
#include<utility>

template<typename T>
    class Cvor{
      public:
      Cvor* naredni=nullptr;
      T vrijednost_cvora;
      Cvor(T e,Cvor<T>* n=nullptr):vrijednost_cvora{e},naredni{n}{}
    };
template<typename T>
class Forward_list{
  private:
    int size_=0;
    Cvor<T>* glava_{nullptr};
    Cvor<T>* rep_{nullptr};

  public:

    Forward_list();//
    Forward_list(const Forward_list&);//
    Forward_list& operator=( const Forward_list&);
    Forward_list& operator=(Forward_list&&);
    Forward_list(Forward_list&&);//
    ~Forward_list();
    Forward_list(const std::initializer_list<T>& );//


    void pop_back();
    void pop_front();
    bool empty()const;//
    void print()const;
    void clear();
    void copyall(const Forward_list&);

    class Iterator;
    Iterator begin();//
    Iterator end();//
    void add(const T&);//
    Iterator& find(Iterator)const;
    void remove(Iterator);

      friend class Forward_list<T>::Iterator;
    template<typename U>
    Iterator find_if(U predicate); 
};








template<typename T> 
Forward_list<T>::Forward_list( const std::initializer_list<T>& a):size_{0}{
auto it=a.begin();
while(it!=a.end()){
add(*it);
++it;
}
}


template<typename T>
Forward_list<T>::Forward_list():size_{0} {
}



template<typename T>
Forward_list<T>::Forward_list(const Forward_list& druga):size_{0}{
 for(auto tmp=druga.glava_;tmp!=nullptr;tmp=tmp->naredni){//Forward_list<int> a{1,2,3}; 
  add(tmp->vrijednost_cvora);
 }
}





template<typename T>
Forward_list<T>::Forward_list(Forward_list&& druga):size_{druga.size_},
  glava_{druga.glava_},rep_{druga.rep_}{
    druga.size_=0;
    druga.glava_=nullptr;
    druga.rep_=nullptr;

}



template<typename T>
Forward_list<T>& Forward_list<T>::operator=(const Forward_list& druga){
  if(this!=&druga){   
  clear();
  for(Cvor<T>* tmp=druga.glava_;tmp!=nullptr;tmp=tmp->naredni)
   add(tmp->vrijednost_cvora);
  }
}



template<typename T>
Forward_list<T>& Forward_list<T>::operator=(Forward_list&& druga){
clear();
size_=druga.size_;
glava_=druga.glava_;
rep_=druga.rep_;
druga.rep_=nullptr;
druga.glava_=nullptr;
druga.size_=0;

}



template<typename T>
Forward_list<T>::~Forward_list(){
clear();
}





template<typename T>
void Forward_list<T>::pop_back(){
  if(empty())
    return;

  if(size_==1){
     Cvor<T>*  tmp=glava_;
     glava_=nullptr;
     rep_=nullptr;
     delete tmp;
     --size_;
  }

  else{
  
    for(Cvor<T>* tmp=glava_;tmp!=nullptr;tmp=tmp->naredni){
       if(tmp->naredni_==rep_){
           delete rep_;
           tmp->naredni=nullptr;
           rep_=tmp;
           --size_;
        }
    }
}
}


template<typename T>
void Forward_list<T>::pop_front(){
  if(empty())
    return;
Cvor<T>* tmp=glava_;
glava_=glava_->naredni;
delete tmp;
--size_;

}




template<typename T>
bool Forward_list<T>::empty()const{
 return glava_==nullptr;
}




template<typename T>
void Forward_list<T>::print()const{
for(Cvor<T>* tmp=glava_;tmp!=nullptr;tmp=tmp->naredni)
  std::cout<<tmp->vrijednost_cvora<<' ';
std::cout  << std::endl;
}



template<typename T>
void Forward_list<T>::clear(){
Cvor<T> *tmp=glava_;
while(glava_){
tmp=tmp->naredni;
delete glava_;
glava_=tmp;
}
size_=0;
glava_=nullptr;
rep_=nullptr;
}

template<typename T>
class Forward_list<T>::Iterator
:public std::iterator<std::forward_iterator_tag, T>
{
  private:
  Cvor<T>* ptr_=nullptr;
  public:
  friend class Forward_list;
 Iterator() = default;
  Iterator(const Iterator& it) : ptr_{it.ptr_} {}
  Iterator(Iterator&& it) : ptr_{it.ptr_} { it.ptr_ = nullptr; }
  Cvor<T>* cvor() const { return ptr_; }
  Iterator& operator=(const Iterator& it) {
    if (this != &it) {
      ptr_ = it.ptr_;
    }
    return *this;
  }
  Iterator& operator=(Iterator&& it) {
    ptr_ = it.ptr_;
    it.ptr_ = nullptr;
    return *this;
  }
  ~Iterator() { ptr_ = nullptr; }
  Iterator(Cvor<T>* ptr) : ptr_{ptr} {}
  Iterator(T& element) : ptr_{&element} {}
  Iterator& operator++();
  Iterator operator++(T);
  bool operator==(const Iterator& it) const;
  bool operator!=(const Iterator& it) const;
  T& operator*() const;

};


template<typename T>
template<typename U>
typename Forward_list<T>::Iterator Forward_list<T>::find_if(U predicate){
auto it=begin();
while(it!=end()){
if(predicate(*it)){
  return it;
}
++it;
}
return end();
}



template<typename T>
void Forward_list<T>::add(const T& toAdd){
auto it=find_if([&toAdd](T element){return toAdd<element;});
Cvor<T>* tmp=new Cvor<T>{toAdd};
if(empty())
  glava_=rep_=new Cvor<T>{toAdd};
else if(it==begin()){
   
    std::cout << 1 << std::endl;
   tmp->naredni=glava_;
   glava_=tmp;
    std::cout << 1 << std::endl;
}
else if(it==end()){
 std::cout << 2 << std::endl;
  rep_->naredni=tmp;
  rep_=tmp;
  std::cout << 2 << std::endl;
}
else{
  Cvor<T>* pom=glava_;
  Cvor<T>* prethodni=nullptr;;
  while(pom!=it.ptr_){
     prethodni=pom;
     pom=pom->naredni;
  }

  tmp->naredni=it.ptr_;
  prethodni->naredni=tmp;
  std::cout << 3 << std::endl;
}
++size_;
 
}




template<typename T>
void Forward_list<T>::remove(typename Forward_list<T>::Iterator pozicija){
if(empty())
return ;

}




template<typename T>
typename Forward_list<T>::Iterator Forward_list<T>::begin(){
return Iterator{glava_};
}


template<typename T>
typename Forward_list<T>::Iterator Forward_list<T>::end(){
rep_->naredni=nullptr;
return Iterator{rep_->naredni};
}



//Iteratori
template<typename T>
bool Forward_list<T>::Iterator::operator!=(const Iterator& drugi)const{
return ptr_!=drugi.ptr_;

}

template<typename T>
bool Forward_list<T>::Iterator::operator==(const Iterator& drugi)const{

return ptr_==drugi.ptr_;

}


template<typename T>
T& Forward_list<T>::Iterator::operator*()const{
   return ptr_->vrijednost_cvora;
}



template<typename T>
typename Forward_list<T>::Iterator& Forward_list<T>::Iterator::operator++(){ 
  if(ptr_)
    ptr_=ptr_->naredni;
  return *this;
}



template<typename T>
typename Forward_list<T>::Iterator Forward_list<T>::Iterator::operator++(T){
  auto oldThis=*this;
  ++(*this);
  return oldThis;
}



