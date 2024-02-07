#include<iostream>
#include <math.h>

using namespace std;


struct MyVector {
    unsigned size, capacity; // Размер массива и выделенный размер памяти 
    int* arr; // Указатель на первыый элемент массива в памяти  
};

unsigned pref_size(unsigned n) { // Функция преобразования размера под ближайшую степень двойки 

    int z = 0;
    int i = 0;
    while (n > z) {
        z = pow(2, i);
        i++;
    }
    return z;
}

void read(MyVector& vec, unsigned n) {
    vec.size = n;// Изменить размер 
    vec.capacity = pref_size(n);// Изменить размер зарезервированной памяти 
    vec.arr = new int[vec.capacity];// Выделить память 
    for (int i = 0; i < n; ++i) {
        cin >> vec.arr[i];
    }
}

void print(MyVector& vec) {
    for (int i = 0; i < vec.size; ++i) {
        cout << vec.arr[i] << " ";
    }
    cout << endl;
}

void del(MyVector& vec) { // Очищение памяти
    if (vec.arr != nullptr) {
        delete[] vec.arr;
        vec.capacity = 0;
        vec.size = 0;
    }
}
//
//int main() {
//   /* MyVector vec;
//    unsigned n; cin >> n;
//    read(vec, n);
//    print(vec);
//    del(vec);*/
//
//
//    return 0;
//}

//
//void myPlus(size_t& x, size_t& c, int a) {
//    x = x + a;
//    c = pref_size(x);
//}
//
//void myMinus(size_t& x, size_t& c, int a) {
//    x = x - a;
//    c = pref_size(x);
//}
//
//int main() {
//    size_t x = 0, c = 0, a;
//    int q;
//    std::cin >> q;
//    char cmd;
//    while (q--) {
//        std::cin >> cmd >> a;
//        if (cmd == '+') 
//        {
//            myPlus(x, c, a);
//        }
//        else if (cmd == '-')
//        { 
//            myMinus(x, c, a);
//        }
//        std::cout << x << ' ' << c << std::endl;
//    }
//}


void push_back(MyVector& vec, int x) {
    vec.size++;

    if (vec.capacity < vec.size) { // Что делать, если место еще есть 
        vec.capacity *= 2; // Изменить размер памяти 
        int* tmp_arr = new int[vec.capacity];// Выделить память под новый массив
        for (int i = 0; i < vec.size - 1; i++) {
            tmp_arr[i] = vec.arr[i];
        }   // Скопировать старый массив в новый 
            // Вставить нужный элемент в конец и очистить ненужную мамять
        delete[] vec.arr;
        vec.arr = tmp_arr;
        tmp_arr = nullptr;
    }
    vec.arr[vec.size - 1] = x;
}

int pop_back(MyVector& vec) { // Удалить последний элемент массива
    if (vec.size == 0) {
        return 0;
    }
    int result = vec.arr[vec.size - 1];
    vec.size--; // Удалить элемент
    if (vec.capacity >= vec.size * 2) { // Что делать если нужно изменить capasity
        vec.capacity /= 2;// Изменяем размер

        int* newarr = new int[vec.capacity];// Перекопируем
        for (int i = 0; i < vec.size; i++) {
            newarr[i] = vec.arr[i];
        }
        delete[] vec.arr;
        vec.arr = newarr;
        newarr = nullptr;

    }
    return result;
}
void print_size(MyVector& vec) {
    cout << vec.size << " " << vec.capacity << endl;
    }

void move(MyVector& dest, MyVector& src) {
    for (int i = 0; i < src.size; i++) {
        push_back(dest, src.arr[i]);
    }
    del(src);
}


int max(MyVector& vec) {
    
    int max = vec.arr[0];
    for (int i = 0; i < vec.size; i++) {
        if (vec.arr[i] > max) {
            max = vec.arr[i];
        }
    }
    return max;
}

int min(MyVector& vec) {
    int min = vec.arr[0];
    for (int i = 0; i < vec.size; i++) {
        if (min > vec.arr[i]) {
            min = vec.arr[i];
        }
    }

    return min;
}

long long sum(MyVector& vec) {
    long long sum = 0;
    for (int i = 0; i < vec.size; i++) {
        sum += vec.arr[i];
    }
    return sum;
}

long double mean(MyVector& vec) {
    long double srzn = static_cast<long double>(sum(vec)) / vec.size;
    return srzn;
}

size_t get_size(const MyVector& vec) {
    return vec.size;
}


void insert(MyVector& vec, int x, int k) {
    if (vec.capacity > vec.size) { // Что делать если размер выделенной памяти меньше, чем нужно 
            // Вставить элемент
            // Изменить размер
        for (int i = vec.size; i > k; i--) {
            vec.arr[i] = vec.arr[i - 1];
        }
        vec.arr[k] = x;
        vec.size++;
    }

    else {
        vec.capacity = vec.capacity * 2; // Изменить размер памяти 
        int* newarr = new int[vec.capacity];// Перекопируем
        for (int i = 0, j = 0; i < vec.size; i++,j++) {    
            if (i == k) {
                newarr[k] = x;
                j++;
            }
            newarr[j] = vec.arr[i];
        }
        vec.size++;
        delete[] vec.arr;
        vec.arr = newarr;
        newarr = nullptr;
    }
    return;
}

void erase(MyVector& vec, int k) { // Удалить элемент по индексу k 
    for (int i = k; i < vec.size - 1; i++) {
        vec.arr[i] = vec.arr[i + 1];
    }
    vec.size--;
   
    if (vec.capacity >= vec.size * 2) {
        vec.capacity /= 2;
        int* newarr = new int[vec.capacity];// Перекопируем
        for (int i = 0; i < vec.size; i++) {
            newarr[i] = vec.arr[i];
        }
        delete[] vec.arr;
        vec.arr = newarr;
        newarr = nullptr;
    }

}

int main() {
    MyVector vec1, vec2;
    long int vec1sz, vec2sz;
    cin >> vec1sz;
    read(vec1, vec1sz);
    cin >> vec2sz;
    read(vec2, vec2sz);
    move(vec1, vec2);
    print_size(vec1);
    print(vec1);
    print_size(vec2);
    }


//
//int main() {
//    int n, q, x, k; cin >> n;
//    char cmd;
//    MyVector vec;
//    read(vec, n);
//    cin >> q;
//    while (q--) {
//        cin >> cmd;
//        if (cmd == '+') {
//            cin >> k >> x;
//            if (k--) insert(vec, x, k);
//            else push_back(vec, x);
//        }
//        else if (cmd == '-') {
//            cin >> k;
//            if (k--) erase(vec, k);
//            else pop_back(vec);
//        }
//        else if (cmd == '?') {
//            print_size(vec);
//            cout << '\n';
//        }
//    }
//    print(vec);
//    del(vec);
//}
