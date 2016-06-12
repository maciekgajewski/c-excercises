template<typename T>
class MyUniquePtr
{
private:
	T* data;
public:
	MyUniquePtr();
	MyUniquePtr(T* ptr): data(ptr) {}; //
	
	MyUniquePtr(MyUniquePtr&&);
	
	// can't copy-construct from another implicitely, must cast as rvalue with std::move
	MyUniquePtr(const MyUniquePtr&) = delete;
	
	const T* get() const{return *data;};
	
	const T& operator*() const;
	const T* operator->() const; 
};
