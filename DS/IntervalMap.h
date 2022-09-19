//
// Created by Semih on 11.09.2022.
//

#ifndef CLION_INTERVALMAP_H
#define CLION_INTERVALMAP_H
#include <iostream>

#include <map>
#include <limits>
#include <iterator>
#include <optional>

template<typename K, typename V>
// TODO: add lessthancompareable
class interval_map {
    friend void IntervalMapTest();
    V m_valBegin;
    std::map<K,V> m_map;
public:
    interval_map(V const& val)
            : m_valBegin(val)
    {}

void assign( K const& keyBegin, K const& keyEnd, V const& val )
    {

        if (!(keyBegin< keyEnd))
            return;

        // insert end key
        auto end = m_map.upper_bound(keyEnd);
        auto prevVal = m_valBegin;
        if(end != m_map.begin())
            prevVal = std::prev(end)->second;
        end =  m_map.insert(end, std::make_pair(keyEnd, prevVal));

        // Remove values between begin and end
        auto begin = m_map.lower_bound(keyBegin);
        m_map.erase(begin, end);

        // insert begin value
        m_map.insert(end, std::make_pair(keyBegin, val));

        // clear leading begin values

        while(m_map.size()>0 && m_map.begin()->second == m_valBegin)
        {
                m_map.erase( m_map.begin());
        }

        begin = std::prev(end);
        while(m_map.size()> 0 && m_map.end()->second == begin->second)
        {
            if(begin != m_map.end())
                m_map.erase(begin);
            begin = std::prev(m_map.end());
        }

    }

    V const& operator[]( K const& key ) const {
        auto it=m_map.upper_bound(key);
        if(it==m_map.begin()) {
            return m_valBegin;
        } else {
            return (--it)->second;
        }
    }

    void print() {
        std::cout << "[" << INT_MIN << ':' << m_valBegin << "]";

        for (auto&&[key, val] : m_map)
            std::cout << "[" << key << ':' << val << "]";
        std::cout << '\n';
    }
};
template<typename K>
class KTest{
    K value;
public:
    KTest(){

    }
    KTest(const K& val){
        value = val;
    }
    KTest(const KTest& val){
        value = val.value;
    }
    KTest& operator=(const KTest& other){
        if(this!=other){
            this->value = other.value;
        }
        return *this;
    }
    friend bool operator <(const KTest &a, const KTest &b){
        return a.value<b.value;
    }
    bool operator ==(const KTest &b) = delete;
};

template<typename T>
class TTest{
public:
    T value;
    TTest(){

    }
    TTest(const T& val){
        value = val;
    }

    TTest(const TTest& val){
        value = val.value;
    }

    TTest& operator=(const TTest& other){
        if(this!=other){
            this->value = other.value;
        }
        return *this;
    }
    bool operator ==(const TTest &b)
    {
        return value == b.value;
    }
};


void IntervalMapTest()
{

    interval_map<int, char> map{ 'a' };
    map.print(); // [-2147483648:a]

    map.assign(3, 5, 'b');
    map.print(); // [-2147483648:a][3:b][5:a]

    map.assign(2, 3, 'c');
    map.print(); // [-2147483648:a][2:c][3:b][5:a]

    map.assign(2, 3, 'd');
    map.print(); // [-2147483648:a][2:d][3:b][5:a]

    map.assign(2, 4, 'e');
    map.print(); // [-2147483648:a][2:e][4:b][5:a]

    map.assign(4, 18, 'f');
    map.print(); // [-2147483648:a][2:e][4:f][18:a]

    map.assign(2, 8, 'g');
    map.print(); // [-2147483648:a][2:g][8:f][18:a]

    map.assign(0, 10, 'a');
    map.print(); // [-2147483648:a][10:f][18:a]

    map.assign(0, 20, 'a');
    map.print(); // [-2147483648:a]

    map.assign(0, 30, 'a');
    map.print(); // [-2147483648:a]

    map.assign(15, 16, 'k');
    map.print();

    map.assign(16, 17, 'G');
    map.print();

    map.assign(1, 2, 'G');
    map.print();
    map.assign(30, 36, 'h');
    map.print(); // [-2147483648:a]
    std::cout<<std::endl<<map[-3]<<std::endl;

    interval_map<int, int> mmap{ 0 };
    mmap.assign(5, 20, 0);
    mmap.print();
    mmap.assign(10, 30, 30);
    mmap.print();
    mmap.assign(12, 15, 15);
    mmap.print();
    mmap.assign(15, 20, 40);
    mmap.print();
    mmap.assign(17, 19, 41);
    mmap.print();

    mmap.assign(30, 40, 7);
    mmap.print();
    std::cout<<std::endl;
    std::cout<<mmap[-3]<<std::endl;
    std::cout<<mmap[5]<<std::endl;
    std::cout<<mmap[10]<<std::endl;
    std::cout<<mmap[15]<<std::endl;
    std::cout<<mmap[20]<<std::endl;
    std::cout<<mmap[25]<<std::endl;
    std::cout<<mmap[30]<<std::endl;
    std::cout<<mmap[35]<<std::endl;
    std::cout<<mmap[40]<<std::endl;
    std::cout<<mmap[45]<<std::endl;

    interval_map<int, int> mp{ 0 };
    mp.assign(5, 10, 1);
    mp.assign(10, 12, 3);
    mp.assign(10, 11, 2);
    mp.assign(15, 20, 2);
    mp.assign(20, 25, 0);
    mp.assign(25, 30, 0);
    mp.assign(26, 27, 0);



    mp.print();
    std::cout<<std::endl;
    std::cout<<mp[-3]<<std::endl;
    std::cout<<mp[5]<<std::endl;
    std::cout<<mp[10]<<std::endl;
    std::cout<<mp[14]<<std::endl;
    std::cout<<mp[15]<<std::endl;
    std::cout<<mp[20]<<std::endl;
    std::cout<<mp[25]<<std::endl;
    std::cout<<mp[30]<<std::endl;


}


// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.


#endif //CLION_INTERVALMAP_H
