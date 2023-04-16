#ifndef _future_h_
#define _future_h_

#include "semaphore.h"
#include "shared.h"

template <typename T>
class Future {
    volatile T value{};
    Semaphore sem{0};
public:
    Atomic<uint32_t> ref_count{0};

    Future() {
    }

    // Can't copy a future
    Future(const Future&) = delete;
    
    void set(T v) {
        value = v;
        sem.up();
    }
    T get() {
        sem.down();
        sem.up();
        return value;
    }
};

template <typename Out, typename T>
Shared<Future<Out>> future(T work) {
    auto f = Shared<Future<Out>>::make();
    thread([work, f]{
        f->set(work());
    });
    return f;
}

#endif

