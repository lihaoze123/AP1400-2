#ifndef SHARED_PTR
#define SHARED_PTR

#include <cstddef>

using std::size_t;

template <typename T>
class SharedPtr {
private:
    T* _p;
    size_t* _use;

public:
    SharedPtr() : _p(nullptr), _use(new size_t{0}) {}
    SharedPtr(T* _p) : _p(_p), _use(new size_t{1}) {}
    SharedPtr(const SharedPtr& shared_ptr) {
        _p = shared_ptr.get();
        _use = &shared_ptr.use_count();
        ++ (*_use);
    }

    ~SharedPtr() {
        if (_use != nullptr && -- (*_use) == 0) {
            delete _p;
            delete _use;
        }

        _p = nullptr;
        _use = new size_t{0};
    }

    T* get() const {
        return _p;
    }

    size_t& use_count() const {
        return *_use;
    }

    T& operator*() const { return *_p; }
    T* operator->() const { return &this->operator*(); }
};

template <typename T>
SharedPtr<T> make_shared(T&& t) {
    return SharedPtr<T>{new T{t}};
}

#endif //SHARED_PTR
