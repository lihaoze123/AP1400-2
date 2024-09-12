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

    SharedPtr& operator=(const SharedPtr& shared_ptr) {
        if (this != &shared_ptr) {
            _p = shared_ptr.get();
            _use = &shared_ptr.use_count();
            ++ (*_use);
        }
        return *this;
    }

    ~SharedPtr() {
        if (_use != nullptr && -- (*_use) == 0) {
            delete _p;
            delete _use;
        }

        _p = nullptr;
        _use = new size_t{0};
    }

    T& operator*() const { return *_p; }
    T* operator->() const { return &this->operator*(); }

    T* get() const {
        return _p;
    }

    size_t& use_count() const {
        return *_use;
    }
    
    void reset(T* ptr = nullptr) {
        this->~SharedPtr();
        _p = ptr;
        _use = new size_t{ptr != nullptr};
    }

    operator bool() const { return _p == nullptr; }
};

template <typename T>
SharedPtr<T> make_shared(T&& t) {
    return SharedPtr<T>{new T{t}};
}

#endif //SHARED_PTR
