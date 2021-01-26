#ifndef KANGAROON_UTIL_SINGLETON_H_
#define KANGAROON_UTIL_SINGLETON_H_

#include <pthread.h>
namespace zoo {
namespace kangaroo {

template <typename T>
class Singleton {
   public:
    static T* getInstance() { pthread_once(&once_control, &Singleton::init); return value_;}
    static void destroy() {
        if (nullptr != value_) {
            delete value_;
        }
    }

   private:
    Singleton();
    ~Singleton();
    static void init() {
        value_ = new T();
        ::atexit(destroy);
    }
    static T* value_;
    static pthread_once_t once_control;
};

template <typename T>
pthread_once_t Singleton<T>::once_control = PTHREAD_ONCE_INIT;

template <typename T>
T* Singleton<T>::value_ = nullptr;

}  // namespace kangaroo
}  // namespace zoo
#endif