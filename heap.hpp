#pragma once
#include <algorithm>
#include <iostream>


template <typename T>
class Heap {
  private:
    int size_;
    int capacity_;
    T* heap_;
   void swap(T*,T*);
   void doubleCapacity();    
    int parent(int index) const {
        return (index - 1) / 2;
    }

    int leftChild(int index) const{
        return 2 * index + 1;
    }

    int rightChild(int index) const{
        return 2 * index + 2;
    }
  
    void top_down(int,int);
    void bottom_up(int);

  public:
  Heap();
  Heap(const Heap&);
  Heap(Heap&&);
  Heap& operator=(const Heap&);
  Heap& operator=(Heap&&);
  ~Heap(); 


  int size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    int capacity() const {
        return capacity_;
    }

    void deleteAll();

    const T& max()const;
    const T& min()const;
    template<typename U>
    void insert(U&&);
    T remove_max();
    T remove_min();


 friend std::ostream& operator<<(std::ostream& os, const Heap& heap) {
    os << "[";
    for (int i = 0; i < heap.size_; i++) {
      if (i < heap.size_ - 1)
        os << heap.heap_[i] << ",";
      else
        os << heap.heap_[i] << "]" << std::endl;
    }
    return os;
  }
};
//konstruktori

template<typename T>
  Heap<T>::Heap() : capacity_{10}, size_{0}, heap_{new T[capacity_]} {}

template<typename T>
Heap<T>::Heap(const Heap& d):size_{d.size_},capacity_{d.capacity_},heap_{new T[d.capacity_]}{
  std::copy(d.heap_,d.heap_+size_,heap_);

}



template<typename T>
Heap<T>::Heap(Heap&& d):size_{d.size_},capacity_{d.capacity_},heap_{d.heap_}{
d.heap_=nullptr;
d.size_=0;
d.capacity_=0;
}

template<typename T>
Heap<T>& Heap<T>::operator=(const Heap& d){
if(&d!=this){
   delete []heap_;
   size_=d.size_;
   capacity_=d.capacity_;
   heap_=new T[capacity_];
   std::copy(d.heap_,d.heap_+size_,heap_);
}
return *this;

}

template<typename T>
Heap<T>& Heap<T>::operator=(Heap&& d){
delete []heap_;
size_=d.size_;
capacity_=d.capacity_;
heap_=d.heap_;
d.heap_=nullptr;
d.size_=0;
d.capacity_=0;
return *this;

}

template<typename T>
Heap<T>::~Heap(){
delete []heap_;
}


//priavte metodi
template<typename T>
 void Heap<T>::doubleCapacity(){
        int newCapacity = 2 * capacity_;
        T *temp = new T[newCapacity];
        std::copy(heap_, heap_ + capacity_, temp);
        delete[] heap_;
        heap_ = temp;
        capacity_ = newCapacity;
    }

    template<typename T>
    void Heap<T>::swap(T *a, T *b)
    {
        T temp = *a;
        *a = *b;
        *b = temp;
    }


//public metodi
 template<typename T>
 void Heap<T>::deleteAll() {
        if(!heap_) {
            return;
        }

        delete[] heap_;
        heap_ = nullptr;
        capacity_ = 0;
        size_ = 0;
    }

template<typename T>
const T& Heap<T>::max() const
    {
        if (empty())
        {
            throw std::out_of_range("Heap is empty");
        }
        return heap_[0];
    }


   
    template<typename T>
    const T& Heap<T>::min()const{

        if (empty())
        {
            throw std::out_of_range("Heap is empty");
        }

    }

template<typename T>
void Heap<T>::bottom_up(int i){

  while ((i != 0) && heap_[parent(i)] < heap_[i]){
      swap(&heap_[parent(i)], &heap_[i]);
       i = parent(i);
 }

}

  template<typename T>
  template<typename U>
  void Heap<T>::insert(U && elem){

    if (size() == capacity())  doubleCapacity();
       
        heap_[size_++] = std::forward<U>(elem);
        bottom_up(size() - 1);
  }






template<typename T>
void Heap<T>::top_down(int k,int n){

while(2*k<=n){

 int j=2*k;
 if(j<n && heap_[j]<heap_[j+1])    ++j;
 if(!(heap_[k]<heap_[j])) break;
 
 swap(heap_[k],heap_[j]);
 k=j;

}
}

template<typename T>
T Heap<T>::remove_max(){
swap(heap_[0],heap_[size_]);
top_down(0,size_-1);
return heap_[size_--];

}


