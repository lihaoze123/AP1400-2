#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T>
class UniquePtr {
private:
    T* _p = nullptr;

public:
    UniquePtr() = default;
    UniquePtr(T* _p) : _p(_p) {}

    ~UniquePtr() {
        delete _p;
        _p = nullptr;
    }

    T* get() const { return _p; }
    T& operator*() const { return *_p; }
    T* operator->() const { return &this->operator*(); }

    void reset(T* ptr = nullptr) {
        delete _p;
        _p = ptr;
    }

    operator bool() const { return nullptr != _p; }
};

template <typename T>
UniquePtr<T> make_unique(T&& t) {
    return UniquePtr<T>{new T{t}};
}

#endif  // UNIQUE_PTR
