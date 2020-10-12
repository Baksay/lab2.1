#include <iostream>
#include <malloc.h>
const int defaultSize = 10;

class Vector{
private:
    int size;
    int maxsize;
    int* data;

public:
    // constructors
    Vector(){
        data = (int*)malloc(defaultSize*sizeof(int));
        maxsize = defaultSize;
        size = 0;
    }
    explicit Vector(int n){
        if(n<1)
            throw std::invalid_argument("Size must be >0");
        data = (int*)malloc(n*sizeof(int));
        maxsize = n;
        size = 0;
    }

    //destructor
    ~Vector(){
        // free the data
        if(data)
            free(data);
    }

    //copy constructor
    Vector(const Vector &v2){
        size = v2.size;
        maxsize = v2.maxsize;
        data = (int*)malloc(maxsize*sizeof(int));
        for (int i=0;i<size;i++)
            data[i] = v2.data[i];
    }

    void add(int elem){
        if(size >= maxsize){
            int* old_data = data;
            maxsize+=defaultSize;
            data = (int*)malloc(maxsize*sizeof(int));
            for(int i=0;i<size;i++)
                data[i]=old_data[i];
            free(old_data);
        }
        data[size] = elem;
        size++;
    }

    int getSize() const{
        return size;
    }

    void replace(int new_elem, int idx){
        if(idx>=size)
            throw std::invalid_argument("Index must be lower than size of array");
        data[idx] = new_elem;
    }

    int find(int elem){
        for(int i=0;i<size;i++)
            if(elem == data[i])
                return i;
        return -1;
    }

    int& operator[](int idx){
        if(idx>=size)
            throw std::invalid_argument("Index must be lower than size of array");
        return data[idx];
    }

    const int& operator[](int idx) const {
        return data[idx];
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& obj);
};

std::ostream& operator<<(std::ostream& os, const Vector& obj)
{
    for(int i=0;i<obj.size;i++)
        os << obj.data[i] << " ";
    return os;
}

int main() {
    // default constructor
    Vector a;

    //add element to the end
    a.add(1);

    //constructor with size of vector
    Vector b(2);
    b.add(1);
    b.add(2);
    b.add(3);

    //get size of vector
    std::cout << "Size of vector b: "<< b.getSize() << std::endl;

    //copy constructor
    Vector c(b);
    c.add(5);

    //replace element in vector
    c.replace(9,1);

    // << overloading
    std::cout << "Elements of vector C:  " << c << std::endl;

    // [] overloading
    std::cout << "Elements #0,1,2 of vector b:  " << b[0] << " " << b[1] << " " << b[2] << " " << std::endl;

    // find
    std::cout << "Searching 9 in vector c: " <<c.find(9) << std::endl;
    std::cout << "Searching 2 in vector c: " <<c.find(2) << std::endl;

    /*
    a.~Vector();
    b.~Vector();
    c.~Vector();
    */

    return 0;
}
