#ifndef _threads_h_
#define _threads_h_

#include "debug.h"

namespace gheith {

    extern void entry();
    extern uint32_t* get_stack();

    struct PostSwitchWork {
        virtual void doit() = 0;
    };

    struct TCB {
        constexpr static int HOW_MANY_BYTES = 8 * 1024;
        constexpr static int HOW_MANY_LONGS = HOW_MANY_BYTES / sizeof(uint32_t);

        uint32_t saved_esp;
        TCB* next;
        PostSwitchWork* psw = nullptr;
        volatile bool no_preempt = false;
        uint32_t *the_stack = nullptr;

        virtual void do_work() {
            Debug::panic("should never be called");
        }

        static TCB* current();

        virtual ~TCB() {
            if (the_stack != nullptr) {
                delete []the_stack;
                the_stack = nullptr;
            }
        }
    };


    template <typename Work>
    struct TCBWithWork: public TCB {
        Work work;

        ~TCBWithWork() override {
        }

        TCBWithWork(Work work): work(work) {
            no_preempt = false;
            the_stack = get_stack();
            auto bottom = &the_stack[HOW_MANY_LONGS - 1];
            if ((uint32_t(bottom) % 8) != 0) {
                bottom -= 1;
            }
            bottom[0] = uint32_t(entry);
            bottom[-5] = getFlags() | 0x200;
            saved_esp = uint32_t(&bottom[-5]);
        }

        void do_work() override {
            work();
        }
    };



    bool block(PostSwitchWork* psw);
    void schedule(TCB* tcb);



}

extern void threadsInit();

extern void stop();
extern void yield();


template <typename T>
void thread(T work) {
    using namespace gheith;
    auto tcb = new TCBWithWork(work);
    schedule(tcb);  // maniuplates the ready queue
}



#endif
