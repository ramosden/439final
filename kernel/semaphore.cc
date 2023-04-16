#include "semaphore.h"
#include "threads.h"

struct PostDownWork: public gheith::PostSwitchWork {

    Semaphore* const sem;
    gheith::TCB* const me;

    PostDownWork(Semaphore* sem, gheith::TCB* me): sem(sem), me(me) {}

    void doit() override {
        auto was = sem->spin.lock();
        if (sem->count == 0) {
            sem->waiting.add(me);
            sem->spin.unlock(was);
        } else {
            sem->spin.unlock(was);
            gheith::schedule(me);
        }
    }
    
};

void Semaphore::down() {
    // double checking to prevent for holding the lock for a long time
    auto was = spin.lock();
    auto me = gheith::TCB::current();
    // ASSERT((count > 0) || !was); 021 violates this invariant :-(
    while (count == 0) {
        // loop while the count is 0
        // race condition is gone
        // intorudce a lock but release it before block is called
            //
        spin.unlock(was);
        ASSERT(me != nullptr);
        PostDownWork pdw{this, me};
        gheith::block(&pdw);
        spin.lock();
    }
    count -= 1;
    spin.unlock(was);
}

void Semaphore::up() {
    gheith::TCB* wakeup = nullptr;
    auto was = spin.lock();
    count += 1;
    wakeup = waiting.remove();
    spin.unlock(was);
    
    if (wakeup != nullptr) {
        gheith::schedule(wakeup);
    }
}
