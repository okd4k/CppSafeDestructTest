### Description of the thread-safe observer implementation

The **observer** is a design pattern in which an object, called the subject,
maintains a list of its dependents, called observers, and notifies them
automatically of any state changes, usually by called one their
methods. ([https://en.wikipedia.org/wiki/Observer_pattern](https://en.wikipedia.org/wiki/Observer_pattern))

Normal implementations of the observer design pattern in C++ is easily
implemented: define an observer base class, with a virtual **update()** function 
for the subject to notify the state changes to it. ```/src/Observer_unsafe.h``` is a 
pretty straightforward implementation. It works fine when running normally, but 
it can come to problems when some objects get released. For example, if the 
Observable_unsafe object is destructed before some Observer_safe objects get 
released, then after that when the Observer_safe destructor function is called, 
it can result in a core dump, since the protected variable *subject_* is pointing 
to a piece of memory that is already released.


In order to design a thread-safe observer that can work well in any circumstances, 
smart pointer is introduced. Shared_ptr has the ability to know the exact time
to destruct an object according to the reference count, and weak_ptr can be 
used to trace the shared_ptr object without adding a reference count, and 
can upgrade to a shared_ptr if the object is still alive and nullptr when the object
has already been released. And the upgrade operation of the weak_ptr is thread 
safe and has good performance since it utilizes atomic operations.

As seen implemented in ```/src/Observer.h``` and ```/src/Observer.cc```, the Observer
inherited std::enable_shared_from_this template class, so that shared_ptr of *this*
without adding an extra reference count can be obtained within the class. The 
Observable class maintains a vector of the weak_ptr objects of the Observers. When
notify is needed, it iterates the vector, and tries to upgrade every weak_ptr object
to a shared_ptr object. If it succeeds, it means the observer is still alive, and
further operation is safe. Otherwise, the observer is dead, and it should be removed 
from the observer vector. When the Observable gets released before the Observers,
the problem shown before will not happen, since the Obserable does not need the 
Observer to unregister, it does not need to do operations on *subject_*. When the 
Observer gets released first, the Obserable can also work fine since the smart pointers
help to keep tracing the Observer status. 