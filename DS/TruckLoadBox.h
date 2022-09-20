#pragma once
#include <iostream>
#include <random>        
#include <functional>    
#include <memory>        
#include <memory>
#include <vector>
#include <optional>
#include <span>
#include <compare>

namespace TruckLoadBox 
{
    class Truckload;
    class Box;
    using SharedBox = std::shared_ptr<Box>;
   
    inline auto randomSharedBox();
    inline auto createUniformPseudoRandomNumberGenerator(double max);
    inline auto randomSharedBox();
    std::ostream& operator<<(std::ostream& stream, const Box& box);
    class Box
    {
    public:
        Box() = default;
        Box(double length, double width, double height)
            : m_length{ length }, m_width{ width }, m_height{ height } {};

        double volume() const
        {
            return m_length * m_width * m_height;
        }

        double getLength() const { return m_length; }
        double getWidth() const { return m_width; }
        double getHeight() const { return m_height; }

        int compare(const Box& box) const
        {
            if (volume() < box.volume()) return -1;
            if (volume() == box.volume()) return 0;
            return +1;
        }
        std::partial_ordering operator<=>(const Box& aBox) const;
        std::partial_ordering operator<=>(double value) const;
        bool operator==(const Box& aBox) const = default;
        Box& operator+=(const Box& aBox);     
        Box operator+(const Box& aBox) const; 

        /*
        std::partial_ordering operator<=>(const Box& box) {
            return volume() <=> box.volume();
        }
        std::partial_ordering operator<=>(double v) {
            return volume() <=> v;
        }
        */

        bool operator== (const Box& box) {
            return m_length == box.m_length && m_width == box.m_width && m_height == box.m_height;
        } 

        void listBox() const
        {
            std::cout << *this;
            //std::cout << std::format("Box({:.1f},{:.1f},{:.1f})", m_length, m_width, m_height);
        }

    private:
        double m_length{ 1.0 };
        double m_width{ 1.0 };
        double m_height{ 1.0 };
    };

    class Truckload
    {
    public:
        Truckload() = default;            

        Truckload(SharedBox box);         
        Truckload(std::vector<SharedBox>& boxes);
        Truckload(const Truckload& src);  

        ~Truckload();                     

        SharedBox getFirstBox();          
        SharedBox getNextBox();           
        void addBox(SharedBox box);       
        bool removeBox(SharedBox box);    
        void listBoxes() const;           

    private:
        class Package
        {
        public:
            SharedBox m_box;      
            std::shared_ptr<Package> m_next{ nullptr };

            Package(SharedBox box) : m_box{ box }, m_next{ nullptr } {} 
            ~Package() { }                          
        };

        std::shared_ptr<Package> m_head{ nullptr};               
        std::shared_ptr<Package> m_tail{ nullptr };               
        std::shared_ptr<Package> m_current{ nullptr };            
    };

    std::ostream& operator<<(std::ostream& stream, const Box& box)
    {
        stream << std::format("Box({:.1f},{:.1f},{:.1f})", box.getLength(), box.getWidth(), box.getHeight());
        return stream;
    }

    Box& Box::operator+=(const Box& aBox)
    {
        
        m_length = std::max(m_length, aBox.m_length);
        m_width = std::max(m_width, aBox.m_width);
        m_height += aBox.m_height;
        return *this;
    }

    Box Box::operator+(const Box& aBox) const
    {
        Box copy{ *this };
        copy += aBox;
        return copy;
    }

    std::partial_ordering Box::operator<=>(const Box& aBox) const
    {
        return volume() <=> aBox.volume();
    }

    std::partial_ordering Box::operator<=>(double value) const
    {
        return volume() <=> value;
    }

    
    inline auto createUniformPseudoRandomNumberGenerator(double max)
    {
        std::random_device seeder;      
        std::default_random_engine generator{ seeder() };    
        std::uniform_real_distribution distribution{ 0.0, max }; 
        return std::bind(distribution, generator);        
    }

    inline Box randomBox()
    {
        const int dimLimit{ 100 };        
        static auto random{ createUniformPseudoRandomNumberGenerator(dimLimit) };
        return Box{ random(), random(), random() };
    }

    inline auto randomSharedBox()
    {
        return std::make_shared<Box>(randomBox());  
    }
    
    Truckload::Truckload(SharedBox box)
    {
        m_head = m_tail = std::make_shared<Package> ( box );
    }


    Truckload::Truckload(std::vector<SharedBox>& boxes)
    {
        for (const auto& box : boxes)
        {
            addBox(box);
        }
    }


    Truckload::Truckload(const Truckload& src)
    {
        for (std::shared_ptr<Package> package ( src.m_head ); package; package = package->m_next)
        {
            addBox(package->m_box);
        }
    }


    Truckload::~Truckload()
    {
        
    }

    void Truckload::listBoxes() const
    {
        const size_t boxesPerLine{ 4 };
        size_t count{};
        std::shared_ptr<Package> package = m_head;

        while (package)
        {
            std::cout << ' ';
            package->m_box->listBox();
            if (!(++count % boxesPerLine)) std::cout << std::endl;
            package = package->m_next;
        }
        if (count % boxesPerLine) std::cout << std::endl;
    }


    SharedBox Truckload::getFirstBox()
    {
        
        m_current = m_head;
        return m_current ? m_current->m_box : nullptr;
    }

    SharedBox Truckload::getNextBox()
    {
        if (!m_current)                                 
            return getFirstBox();                         

        m_current = m_current->m_next;                 

        return m_current ? m_current->m_box : nullptr;   
    }

    void Truckload::addBox(SharedBox box)
    {
       auto package  = std::make_shared<Package>(box) ;

        if (m_tail)                      
            m_tail->m_next = package;    
        else                             
            m_head = package;             

        m_tail = package;                
    }

    bool Truckload::removeBox(SharedBox boxToRemove)
    {
        std::shared_ptr<Package> previous{ nullptr };     
        std::shared_ptr<Package> current{ m_head };
        while (current)
        {
            if (current->m_box == boxToRemove) 
            {
                
                if (previous) previous->m_next = current->m_next;
                if (current == m_head) m_head = current->m_next;
                if (current == m_tail) m_tail = previous;
                if (current == m_current) m_current = current->m_next;

                current->m_next.reset(); 
                return true;                   
            }
            
            previous = current;              
            current = current->m_next;       
        }

        return false;     
    }

    void Run()
    {
        Truckload load1;        
        size_t boxCount{ 12 };
        for (size_t i{}; i < boxCount; ++i)
            load1.addBox(randomSharedBox());

        std::cout << "The first list:\n";
        load1.listBoxes();

        
        Truckload copy{ load1 };
        std::cout << "The copied truckload:\n";
        copy.listBoxes();

        
        SharedBox largestBox{ load1.getFirstBox() };

        SharedBox nextBox{ load1.getNextBox() };
        while (nextBox)
        {
            if (nextBox->compare(*largestBox) > 0)
                largestBox = nextBox;
            nextBox = load1.getNextBox();
        }

        std::cout << "\nThe largest box in the first list is ";
        largestBox->listBox();
        std::cout << std::endl;
        load1.removeBox(largestBox);
        std::cout << "\nAfter deleting the largest box, the list contains:\n";
        load1.listBoxes();

        const size_t nBoxes{ 20 };            
        std::vector<SharedBox> boxes;        

        for (size_t i{}; i < nBoxes; ++i)
            boxes.push_back(randomSharedBox());

        Truckload load2{ boxes };
        std::cout << "\nThe second list:\n";
        load2.listBoxes();

        auto smallestBox{ load2.getFirstBox() };
        for (auto box{ load2.getNextBox() }; box; box = load2.getNextBox())
            if (box->compare(*smallestBox) < 0)
                smallestBox = box;

        std::cout << "\nThe smallest box in the second list is ";
        smallestBox->listBox();
        std::cout << std::endl;

        const double limit{ 99 };       
        auto random{ createUniformPseudoRandomNumberGenerator(limit) };

        boxCount =  20 ; 
        boxes.clear();

        
        for (size_t i{}; i < boxCount; ++i)
            boxes.push_back(std::make_shared<Box>(Box{ random(), random(), random() }));

        size_t first{};            
        size_t second{ 1 };        
        double minVolume{ (*boxes[first] + *boxes[second]).volume() };

        for (size_t i{}; i < boxCount - 1; ++i)
        {
            for (size_t j{ i + 1 }; j < boxCount; j++)
            {
                if (*boxes[i] + *boxes[j] < minVolume)
                {
                    first = i;
                    second = j;
                    minVolume = (*boxes[i] + *boxes[j]).volume();
                }
            }
        }

        std::cout << "The two boxes that sum to the smallest volume are "<< *boxes[first] << " and " << *boxes[second] << '\n';
        std::cout << std::format("The volume of the first box is {:.1f}\n",boxes[first]->volume());
        std::cout << std::format("The volume of the second box is {:.1f}\n",boxes[second]->volume());
        std::cout << "The sum of these boxes is " << (*boxes[first] + *boxes[second]) << '\n';
        std::cout << std::format("The volume of the sum is {:.1f}", minVolume) << std::endl;

        Box sum{ 0, 0, 0 };            
        for (const auto& box : boxes)  
            sum += *box;

        std::cout << "The sum of " << boxCount << " random boxes is " << sum << std::endl;
    }
}