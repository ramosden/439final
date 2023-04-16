#include "debug.h"
#include "smp.h"
#include "debug.h"
#include "config.h"
#include "machine.h"
#include "threads.h"
#include "queue.h"

extern "C" void context_switch(uint32_t*, uint32_t*);

namespace gheith {
    Queue<TCB, InterruptSafeLock> ready_queue{};
    Queue<TCB, InterruptSafeLock> zombies{};

    TCB * volatile * active;
    // cannot delete stack immedatly once a thread is stopped becasue there is a risk interrupts are disables if interrupts dont wnta to maniuplates the heap with interrupts disables bc not o(1)
    // if coming from semaphre down stop thread and as a result trying t ofree stack while in middle of semaphore down
        // might recursivly calling blocking lock
        // mysterious time outs


    // called when safe to delete the thread
    void kill_the_zombies() {
        if (Interrupts::isDisabled()) return; // if interrupts are disables nothing will happen
        //Debug::printf("here");
            // no paratheses alwasy returning true and never killing any zombies
            // if its null its false if its not null its true 
            // isdisables a pointer to a function it is always true
        // deletes everything in the zombie queue
        auto t = zombies.remove();

        while (t != nullptr) {
            delete t;
            t = zombies.remove();
        }

    }


    
    uint32_t* get_stack() {

        // ASSERT(!Interrupts::isDisabled()); violated by 074

    // how do we get a stack: go to heap and allopcate the stack
    // beacsue the zombie quue have a stack that it will free 
    // in order to run faster
    // traverse the zombie queue and find a thread with a stcak steal and use it
    // when destrctir runs its deletes it so save time when destructor is called
        // repeats until finds a stack int he zombie queue if not goes to heap and allocates the stack
        while (true) {
            auto t = zombies.remove();
            if (t == nullptr) {
                return new uint32_t[TCB::HOW_MANY_LONGS];
            }
            auto s = t->the_stack;  // tcb doesnt delete
            t->the_stack = nullptr; // delete tcb
            delete t;
            if (s != nullptr) { // if stack is null
                return s;
            }
        }
    }

    // prints information and call within gdb
    void dump_rq() {
        ready_queue.foreach([](TCB* tcb) {
            Debug::printf("the_stack:%x saved_esp:%x\n", tcb->the_stack, tcb->saved_esp);
        });
    }

    // need to find out current tcb with interrupts disables
    TCB* TCB::current() {
        auto was = Interrupts::disable();
        auto me = active[SMP::me()];
        Interrupts::restore(was);
        return me;
    }

    // adding things to ready queue and checks invariants
        // never schedule something that is null
    void schedule(TCB* tcb) {
        ASSERT(tcb != nullptr);
        ASSERT(!tcb->no_preempt);
        //ASSERT(!Interrupts::isDisabled());
        ready_queue.add(tcb);
    }

// after cintext switch
    void post_switch() {
        // Why is this safe?
        // who am i ?
        // no_preemt flag is true --> cheap interrupts diables
            // never get preempted so never get interrupted
        auto me = active[SMP::me()];
        ASSERT(me->no_preempt);
        //me->psw->show();
        if (me->psw != nullptr) {
            me->psw->doit();
            me->psw = nullptr;
        }
        me->no_preempt = false;
    }

    // 
    void entry() {
        post_switch();
        kill_the_zombies();
        TCB::current()->do_work();
        Interrupts::restore(false);
        stop();
    }

    // 
    bool block(PostSwitchWork* psw) {
        auto me = TCB::current();
        // psw->show();
        ASSERT(me != nullptr);
        ASSERT(!me->no_preempt);
        // could call yeild while im the middle block
        me->no_preempt = true;

        auto next = ready_queue.remove();
        if (next == nullptr) {
             me->no_preempt = false;
             return false;

        }

        ASSERT(me != next);
        // after you swict hhere is the work i want you to do
        next->psw = psw;
        // about to make switch but make sure preemt is true bc not want any interrutps
        // pit is checking falg on active thread
        next->no_preempt = true;
        active[SMP::me()] = next;
        me->no_preempt = false;

        context_switch(&me->saved_esp, &next->saved_esp);
        // pass poitner to yhe post switch work and does all the after swict hstuff
        post_switch();
        return true;
    }

    struct PostYieldWork: public PostSwitchWork {

        TCB* me;

        PostYieldWork(TCB* me): me(me) {}

        //
        void doit() override {
            ready_queue.add(me);
            // this might go awway
        }

    };

    struct PostStopWork: public PostSwitchWork {
        TCB* me;

        PostStopWork(TCB* me): me(me) {}

        void doit() override {
            // put on zombie queue instead of ready queue
            gheith::zombies.add(me);
        }

    };
}

void threadsInit() {
    using namespace gheith;
    active = new TCB*[kConfig.totalProcs];
    for (uint32_t i=0; i<kConfig.totalProcs; i++) {
        active[i] = new TCB();

        thread([]{
            while(true){
                auto t = zombies.remove();
                while(t != nullptr){
                    delete t;
                    t = zombies.remove();
                }
                yield();
            }
        });
    }

}



// allocate varible (PostYieldWork pyw{TCB::current()};)
// yield function calls block (block(&pyw);)
// when will the block return ?
    // 1. ready wueue is empty then blokc returns
        // do nothing with post yield work,yield just returns... no risk
        // it is okay to pop stack from and let the varible live
    // 2. actually find something in ready queu
    // thread a creat py work put it on stack frmae switch to b calls post  yield work
    // still exists still running so no way pop stack froma 
    // not running so no way to pop stack frame avrible continue live
    // post yirld work adds to ready ueue again
        // call for yeild block will return and contunie to run 
        // pop stack frame
        // pyw instacne sitting on stack ill cease to exists
            // side effect of adding thread to live on ready queue
                // pyw to go away
    // last thing i do is add tcb to queeue
    // varibel is guarnet==tee to exist after 
// here is the postswitch work and give a  pointer to the block 

void yield() {
    using namespace gheith;
    PostYieldWork pyw{TCB::current()};  // allocating a stack vairbale
    // yeild is not a safe space for heap operations becasue an interrupt can happen
    //
    block(&pyw);    // every thread is helping the thread bewfore it do its work
    // taking its address and poassing it into a fucntion
    // stack maniultaion
    // very time a poitner stack varibale sleaks outside the blokc to which its allocted we ahve to ask does it liove long enough and if it doesnt we have seriously allocation issues

    // why it is okay ?
        // every time postyieldwork is called have to convice myself that it is safe
        // before adding to the ready queue it has no hope for running so when added to the ready queue its only thing is to be added to the ready queue
        // anything after that is risky
            // the tcb will be added the ready queue and some other core might pick it up and it might return from the function and the vairble will disseaper from the stack

}

// 
void stop() {
    using namespace gheith;
    auto me = TCB::current();
    ASSERT(!Interrupts::isDisabled());
    ASSERT(!me->no_preempt);
    // create a post stop work
        // adds to zombie queue instead of read =y queue
    PostStopWork psw{TCB::current()};
    while (true) {
        kill_the_zombies(); // kill zombies
        // pls blokc me
        // once im switched out of add me to zombie queue
        block(&psw);    // if rq is empty it return
    }

    // the threads that stoping becomes an idle thread until it finds a nother thread to run
    // not as bad as whiletrueyield every thread will contnue to exists
    // only threead that are going to stop that cannot find anything int he ready queue will act as an idle thread until they find something
    // wokr sor p3 but not p4
        // if we have a test that relies on refence counting and once something is caputures and it will never be deleted becasue it will pkay the idle threa
        //thread caputures, gets a copy of ref counted poitner etst case sits there witing for it to go awa ythe shared poitner 
        /// thread using it never actually deleted becasue it sits as an idle thread indeifnitly
        //
        // indtroducing idle or reaper threads will fix it 
}
// any post switch impelemtation \// allow thread to run and contiue to use object irself
// t to be used after the function exists