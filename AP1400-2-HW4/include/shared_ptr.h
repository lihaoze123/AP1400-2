#ifndef SHARED_PTR
#define SHARED_PTR

template <typename T>
class SharedPtr {
private:
    T* _p = nullptr;

public:
    SharedPtr() = default;
    SharedPtr(T* _p) : _p(_p) {}

    T* get() {
        return _p;
    }
};

template <typename T>
SharedPtr<T> make_shared(T&& t) {
    return SharedPtr<T>{new T{t}};
}

#endif //SHARED_PTR
