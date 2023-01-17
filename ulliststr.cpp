
#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
// NEW CODE START HERE
std::string* ULListStr::getValAtLoc(size_t loc) const {
    if (loc >= size_) {
        return nullptr;
    }
    Item* temp = head_;
    while (temp != nullptr) {
        if (temp->last - temp->first - 1 < loc) {
            loc -= (temp->last - temp->first);
            temp = temp->next;
        }
        else {
            return temp->val + temp->first + loc;
        }
    }
}

void ULListStr::push_back(const std::string& val) {
    size_ += 1;
    if (size_ == 1) {
        head_ = new Item();
        tail_ = head_;
        head_->first = 0;
        head_->last = 1;
        head_->val[head_->first] = val;
    }
    else{
        if (tail_->last >= 10) {
            Item* temp = new Item();
            temp->val[0] = val;
            temp->first = 0;
            temp->last = 1;
            tail_->next = temp;
            temp->prev = tail_;
            tail_ = temp;
        }
        else {
            tail_->val[tail_->last] = val;
            tail_->last += 1;
        }
    }
}
void ULListStr::pop_back() {
    tail_->last -= 1;
    size_ -= 1;
    if (size_ == 0) {
        delete head_;
        head_ = tail_ = nullptr;
    }
    else {
        if (tail_->last == tail_->first) {
            tail_ = tail_->prev;
            delete tail_->next;
            tail_->next = nullptr;
        }
    }
}
void ULListStr::push_front(const std::string& val) {
    size_ += 1;
    if (size_ == 1) {
        head_ = tail_ = new Item();
        head_->first = 9;
        head_->last = 10;
        head_->val[head_->first] = val;
    }
    else {
        if (head_->first == 0) {
            Item* temp = new Item;
            temp->val[9] = val;
            temp->first = 9;
            temp->last = 10;
            temp->next = head_;
            head_->prev = temp;
            head_ = temp;
        }
        else {
            head_->val[head_->first - 1] = val;
            head_->first -= 1;
        }
    }
}
void ULListStr::pop_front() {
    head_->first += 1;
    size_ -= 1;
    if (size_ == 0) {
        delete head_;
        head_ = tail_ = nullptr;
    }
    else {
        if (head_->last == head_->first) {
            head_ = head_->next;
            delete head_->prev;
            head_->prev = nullptr;
        }
    }

}

std::string const& ULListStr::back() const {
    return get(size_ - 1);
}
std::string const& ULListStr::front() const {
    return get(0);
}

