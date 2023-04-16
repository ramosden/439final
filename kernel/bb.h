#ifndef _bb_h_
#define _bb_h_

#include "semaphore.h"
#include "stdint.h"
#include "shared.h"

template <typename T>
class BoundedBuffer {
    uint32_t size;
    T* data;
    uint32_t head = 0;
    uint32_t tail = 0;
    Semaphore n_full{0};
    Semaphore n_empty;
    Semaphore lock{1};

public:
    Atomic<uint32_t> ref_count{0};

    BoundedBuffer(uint32_t N): size(N), data(new T[N]), n_empty(N) {
    }

    ~BoundedBuffer() {
        delete []data;
    }

    BoundedBuffer(const BoundedBuffer&) = delete;

    void put(T t) {
        n_empty.down();
        lock.down();
        data[tail] = t;
        tail = (tail + 1) % size;
        lock.up();
        n_full.up();
    }

    T get() {
        n_full.down();
        lock.down();
        auto v = data[head];
        head = (head + 1) % size;
        lock.up();
        n_empty.up();
        return v;
    }
        
};


template <typename Out, typename Work>
Shared<BoundedBuffer<Out>> stream(uint32_t N, Work work) {
    auto f = Shared<BoundedBuffer<Out>>::make(N);

    thread([work, f]{
        work(f);
    });

    return f;
}

#endif
