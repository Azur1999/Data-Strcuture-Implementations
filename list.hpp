#pragma once
#include<iostream>

#include<initializer_list>
template<typename T>
class Cvor{
  public:
    T vrijednost;
    Cvor<T> *naredni=nullptr;
    Cvor<T> *prethodni=nullptr;
    Cvor(T e,Cvor<T>* p=nullptr,Cvor<T> *n=nullptr):vrijednost{e},prethodni{p},naredni{n}{}
};

template<typename T>
class mojaLista {
  private:
    size_t size_=0;
    Cvor<T> *head{nullptr};
    Cvor<T> *tail{nullptr};
  public:
   class Iterator;
   mojaLista();//done
   mojaLista(const mojaLista&);//done
   mojaLista(const std::initializer_list<T>&);
   mojaLista(mojaLista&&);//done
   mojaLista& operator=(const mojaLista&);
   mojaLista& operator=(mojaLista&&);
   ~mojaLista();

   size_t size()const{
   return size_;
   }
   bool operator==(const mojaLista&)const;//done
   bool operator!=(const mojaLista&)const;//done
   void push_back(const T&);//done
   void push_front(const T&);//done
   void erase(Iterator);
   void pop_back();//done
   void pop_front();//done
   T& front();//done
   T& back();//done
   const T& front()const;//done
   const T& back()const;//done
   bool empty()const;//done
   Iterator begin();//done
   Iterator end();//done
   void insert(Iterator,T);
   Iterator find(const T&);
   void clear();//done
   void print()const;//done
};

template <typename T>
class mojaLista<T>::Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  public:
  Iterator() = default;
  Iterator(const Iterator& other) : trenutni_{other.trenutni_}{};
  Iterator(Cvor<T>* prethodni, Cvor<T>* trenutni) : prethodni_{prethodni}, trenutni_{trenutni} {}
  ~Iterator(){};

  Cvor<T>* cvor()const{
    return trenutni_;
  }
  // increment pref
  Iterator& operator++() {
    prethodni_ = trenutni_;
    if (trenutni_) trenutni_ = trenutni_->naredni;
    return *this;
  }
  // increment post
  Iterator operator++(int) {
    auto oldThis = *this;
    ++(*this);
    return oldThis;
  }
  // decrement pref
  Iterator& operator--(){
    trenutni_ = prethodni_;
    if(prethodni_) prethodni_ = prethodni_->naredni;
    return *this;
  }
  // decrement post
  Iterator operator--(int){
    auto oldThis = *this;
    --(*this);
    return oldThis;
  }
  T& operator*() { return trenutni_->vrijednost; }
  const T& operator*() const { return trenutni_->value; }
  bool operator==(const Iterator& other) const { return trenutni_ == other.trenutni_; }
  bool operator!=(const Iterator& other) const { return !operator==(other); }
  friend class mojaLista;

  private:
  Cvor<T>* trenutni_ = nullptr;
  Cvor<T>* prethodni_ = nullptr;
};





//Konstruktori operatori
template<typename T>
mojaLista<T>::mojaLista(){
}
template<typename T>
mojaLista<T>::mojaLista(const mojaLista& other):size_{other.size_}{
 if (!other.empty()) {
    head= tail = new Cvor<T>(other.head->vrijednost);
    Cvor<T>* temp = other.head->naredni;
    while (temp) {
      Cvor<T>* novi= new Cvor<T>(temp->vrijednost);
      tail->naredni = novi;
      novi->prethodni = tail;
      tail = novi;
      temp = temp->naredni;
    }
  }
}

template<typename T>
mojaLista<T>::mojaLista(mojaLista&& other):size_{other.size_},
head{other.head},tail{other.tail}{
other.tail=nullptr;
other.size_=0;
other.head=nullptr;
}


template<typename T>
mojaLista<T>::mojaLista(const std::initializer_list<T>& l){
  for(T elem:l)
    push_back(elem);
}

template<typename T>
mojaLista<T>& mojaLista<T>::operator=(const mojaLista& other){
clear();
for(auto tmp=other.head;tmp!=nullptr;tmp=tmp->naredni)
  push_back(tmp->vrijednost);

return *this;
}

template<typename T>
mojaLista<T>& mojaLista<T>::operator=(mojaLista&& other){
clear();
size_=other.size_;
head=other.head;
tail=other.tail;
other.tail=nullptr;
other.head=nullptr;
other.size_=0;
return *this;
}

template<typename T>
mojaLista<T>::~mojaLista(){
clear();
}



//metodi
template<typename T>
T& mojaLista<T>::front(){

return head->vrijednost;
}

template<typename T>
const T& mojaLista<T>::front()const{
return head->vrijednost;
}

template<typename T>
T& mojaLista<T>::back(){

return tail->vrijednost;
}


template<typename T>
const T& mojaLista<T>::back()const{
return tail->vrijednost;
}

template<typename T>
bool mojaLista<T>::empty()const{
return size_==0; 
}


template <typename T> void mojaLista<T>::print() const {
  Cvor<T> *tmp = head;
  while (tmp) {
    std::cout << tmp->vrijednost << " ";
    tmp = tmp->naredni;
  }

  std::cout << std::endl;
}
template<typename T>
bool mojaLista<T>::operator==(const mojaLista& other)const{

return !operator!=(other);
}


template<typename T>
bool mojaLista<T>::operator!=(const mojaLista& other)const{
if(size_==other.size_){
Cvor<T> *tmp=head;
Cvor<T>* tmp2=other.head;
while(tmp!=nullptr&&tmp2!=nullptr){
  if(tmp->vrijednost!=tmp2->vrijednost)
    return true;
  tmp=tmp->naredni;
  tmp2=tmp2->naredni;
}
return false;
}
else
return true;

}

template<typename T>
typename mojaLista<T>::Iterator mojaLista<T>::begin(){

return Iterator(nullptr,head);
}


template<typename T>
typename mojaLista<T>::Iterator mojaLista<T>::end(){
return Iterator(tail,nullptr);
}

template<typename T>
void mojaLista<T>::pop_front(){
if(empty())
  return;
if(size_==1){
delete head;
head=nullptr;
tail=nullptr;
--size_;
}
else{
Cvor<T>* tmp=head->naredni;
delete head;
head=tmp;
head->prethodni=nullptr;
size_--;
}

}

template<typename T>
void mojaLista<T>::pop_back(){
if(empty())
  return;
if(size_==1){
delete head;
head=nullptr;
tail=nullptr;
--size_;
}
else{
  Cvor<T>* tmp=tail->prethodni;
  delete tail;
  tail=tmp;
  tail->naredni=nullptr;
  --size_;
}
}


template<typename T>
void mojaLista<T>::push_back(const T& elem){
Cvor<T> *tmp=new Cvor<T>{elem};
if(empty()){
head=tail=tmp;
}
else{
  tail->naredni=tmp;
  tmp->prethodni=tail;
  
}
tail=tmp;
++size_;
}


template<typename T>
void mojaLista<T>::push_front(const T& elem){
  Cvor<T> *novi_cvor=new Cvor<T>(elem);
  if(empty())
    head=tail=novi_cvor;
  else{

  novi_cvor->naredni=head;
  head->prethodni=novi_cvor;


  }
head=novi_cvor;
++size_;
}
 template<typename T>
 void mojaLista<T>::clear(){
  Cvor<T> *tmp = head;
  while (head) {
    tmp = tmp->naredni;
    delete head;
    head = tmp;
  }
  size_=0;
  head = nullptr;
  tail = nullptr;  
 }

template<typename T>
typename mojaLista<T>::Iterator mojaLista<T>::find(const T& elem){
auto it=begin();
while(it!=end()){
if(*it==elem)
  return it;
   ++it;
}
return end();
}



template<typename T>
void mojaLista<T>::erase(Iterator pos){
  if(empty()) return ;
  else if(size_==1){
    head = nullptr;
    tail = nullptr;
    delete pos.trenutni_;
  }
  else if(pos == begin()){
    head = head->naredni;
    head->prethodni = nullptr;
    delete pos.trenutni_;
  }
  else if(pos.trenutni_ == tail){
    tail = tail->prethodni;
    tail->naredni = nullptr;
    delete pos.trenutni_;
  }
  else {
    pos.trenutni_->prethodni->naredni = pos.trenutni_->naredni;
    pos.trenutni_->naredni->prethodni = pos.trenutni_->prethodni;
  }
  --size_;

}

template<typename T>
void mojaLista<T>::insert(Iterator pos,T element){

  Cvor<T>* novi_cvor=new Cvor<T>{element};
     if (pos == end()) {
    return;
  }
    if(pos==begin()){
       
    novi_cvor->naredni=head;
    head=novi_cvor;
    pos.trenutni_->prethodni=head;
    head->prethodni=nullptr;

    }
    else{
  pos.trenutni_->prethodni->naredni=novi_cvor;
  novi_cvor->prethodni=pos.trenutni_->prethodni;
  novi_cvor->naredni=pos.trenutni_;
  pos.trenutni_->prethodni=novi_cvor;
    }
  ++size_;
  




}



