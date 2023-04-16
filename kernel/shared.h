#ifndef _shared_h_
#define _shared_h_

#include "debug.h"

template <typename T>
class Shared {
    T* ptr;

public:
    
    // here is a fresh raw poitner: now wrap it
    // find the counter and add one to it
    // explicit: can change the parameter type
    // pointer to T to a shared poitner
    // if need to do a cnoversion eed to call contructor itslef
    explicit Shared(T* it) : ptr(it) {
        if(ptr != nullptr) {
            ptr->ref_count.add_fetch(1);
        }
    }

    // constructor that calls a null shared poitner
    // intilize pointer to show that is pointing to nothing
    // no counter 
    // Shared<Thing> a{};
    //
    // default constructor poitns to null
    Shared(): ptr(nullptr) {

    }

    // copy constructor
    // constructing a brand new b by copying an a
    // copilers defualt behavior is to copy the bits, must update the count
    // return value returns a copy of the value to the outside world
    //
    // Shared<Thing> b { a };
    // Shared<Thing> c = b;
    // f(b);    // when you pass values into fucntions you copy the pointer and update the reference counter
    // return c;
    //
    Shared(const Shared& rhs): ptr(rhs.ptr) {
        if(ptr != nullptr) {
            ptr->ref_count.add_fetch(1);
        }
    }

    // 
    // 
    // Shared<Thing> d = g();
    //
    // like a copy constructor but immediatly after you copy this object it will go awway
    // reduce adds adn subtracts by optimize
    // if a function is returing or casted to an R value reference(&&) i will never use this value again
    Shared(Shared&& rhs): ptr(rhs.ptr) {
    // if not null dec
        // if(ptr != nullptr){
        //     ptr->ref_count.add_fetch(-1);
        // }
        rhs.ptr = nullptr;
    }


    // destrcutor is called when a shared poitner goes out of scope
    // leave a fucntion, blokc, R value, etc
    // reduce the ref count by 1 and if its 0 THEN we delete
    // worry about reace conditions
    ~Shared() {
        if(ptr != nullptr){
            if(ptr->ref_count.add_fetch(-1) == 0) {
                delete ptr;
            }
        }

    }

    // d->m();
    T* operator -> () const {
        return ptr;
    }


// assignment operatior
// assign value from a raw pointer to a shared poitner
    // d = nullptr;
    // d = new Thing{};
    /*
        assign  vlaue of raw poutner into shraed pointer
        alr head a pointer chnage what it needs to poitn to
        ptr is d , t* rhs is null ptr
        ptr is a raw poitner aka d
    */
    Shared<T>& operator=(T* rhs) {
        if(ptr != rhs){
            if(ptr != nullptr){
                if(ptr->ref_count.add_fetch(-1) == 0) {
                    delete ptr;
                }
            }

            ptr = rhs;
            if(ptr != nullptr) {
                ptr->ref_count.add_fetch(1);
            }
        }

        return *this;
    }


// share between pointers
    // d = a;
    // d = Thing{};
    Shared<T>& operator=(const Shared<T>& rhs) {
        if(ptr != rhs.ptr){
            auto dummy = ptr;
            ptr = rhs.ptr;
            ptr-> ref_count.add_fetch(1);
            
            if(dummy -> ref_count.add_fetch(-1) == 0){
                delete dummy;
            }
        }

        // if(ptr != nullptr) {        
        //     ptr->ref_count.add_fetch(-1); //delete
        // }
        // ptr = rhs.ptr;
        // if(ptr != nullptr){
        //     rhs.ptr->ref_count.add_fetch(1);
        // }
        return *this;
    }


// assign from R value to L value
// function that will run will copmute the value whic wil eventually call the move
    // d = g();
    Shared<T>& operator=(Shared<T>&& rhs) {
        //if(ptr != rhs.ptr){
            auto currptr = ptr;
            ptr = rhs.ptr;
            rhs.ptr = currptr;
        //}

        return *this;
    }

    // compare two shared poitner for equituy
    // poitning to the same thing
    bool operator==(const Shared<T>& rhs) const {
        if(ptr == rhs.ptr) {
            return true;
        }
        return false;
    }
    

// 
    bool operator!=(const Shared<T>& rhs) const {
        if(ptr != rhs.ptr) {
            return true;
        }
        return false;
    }


// copmaring to raw pointers
    bool operator==(T* rhs) {
        if(ptr == rhs) {
            return true;
        }
        return false;
    }

    bool operator!=(T* rhs) {
        if(ptr != rhs) {
            return true;
        }
        return false;
    }


// takes a number of argements becasue it deosnt know what arguements for the contstucor takes
// creates a shared poitner and wrap a new instacne of that
    // e = Shared<Thing>::make(1,2,3);
    template <typename... Args>
    static Shared<T> make(Args... args) {
        return Shared<T>{new T(args...)};   // making a shared abject lovally but returning a wrapped copy
    }

};

#endif

// copy constrctors a is barnd new
// just putting apoitner in it and need ONLY to add a refernce to b
// auto a = b;
// auto a = f();


// a is not brand new and REPLACING it with another value
// a might be poitning to something so need to add one to the reference count to b
// and subtract one from a because we are losing a refernce

// a = b;
// a = f();

// destrutor is automatically called for an object going out of scope
// ex: a function is created and it is finsihed (went out of the ending curly brace) ??