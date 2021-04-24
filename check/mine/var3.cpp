#include <iostream>
#include <cassert>
#include <cstdlib>

class IntBuffer {
   int* data = 0;
   std::size_t allocated = 0;

   int* clone(int* buffer, std::size_t size) const
   {
      int* copy = new int[size];

      for (size_t i = 0; i < size; ++i)
         copy[i] = buffer[i];

      return copy;
   }

   int compare(int* arr1, int* arr2, size_t size) const
   {
      for (size_t i = 0; i < size; i++)
      {
         if (arr1[i] < arr2[i])
            return -1;
         else if (arr1[i] > arr2[i])
            return 0;
      }
      return 0;
   }

public:
   IntBuffer(std::size_t size)
   {
      data = new int[size];
      allocated = size;
   }

   IntBuffer(std::size_t size, const IntBuffer& other)
   {
      data = new int[size];
      allocated = size;
      copy_from(other, std::min(size, other.size()));
   }

   ~IntBuffer()
   {
      delete[] data;
   }

   IntBuffer(const IntBuffer& other)
   {
      data = clone(other.data, other.size());
      allocated = allocated;
   }

   IntBuffer& operator=(const IntBuffer& other)
   {
      if (this != &other)
      {
         int* copy = clone(other.data, other.size());
         delete[] data;
         data = copy;
         allocated = other.size();
      }

      return *this;
   }

   int& at(std::size_t index)
   {
      if (index >= size())
         throw std::out_of_range("index out of range");
      return data[index];
   }

   const int& at(std::size_t index) const
   {
      if (index >= size())
         throw std::out_of_range("index out of range");
      return data[index];
   }

   int& operator[](std::size_t index)
   {
      assert(index < size());
      return data[index];
   }

   const int& operator[](std::size_t index) const
   {
      assert(index < size());
      return data[index];
   }

   std::size_t size() const
   {
      return allocated;
   }

   void copy_from(const IntBuffer& other, std::size_t count)
   {
      if (size() < count || other.size() < count)
         throw std::out_of_range("count is greater than the size of the buffer");

      for (std::size_t i = 0; i < count; ++i)
         (*this)[i] = other[i];
   }

   bool operator==(const IntBuffer& other) const
   {
      return size() == other.size() && compare(data, other.data, size()) == 0;
   }

   bool operator<(const IntBuffer& other) const
   {
      std::size_t limit = std::min(size(), other.size());
      int comp = compare(data, other.data, limit);
      return comp < 0 || comp == 0 && size() < other.size();
   }
};

class Set {
   IntBuffer elements;
   std::size_t elements_count;

public:
   Set()
      : elements(2), elements_count(0)
   {}

   void insert(int value)
   {
      if (contains(value))
         return;

      if (elements_count >= elements.size())
         elements = IntBuffer(elements.size() * 2, elements);
      
      std::size_t insert_at = 0;      
      while (insert_at < elements_count && elements[insert_at] <= value)
         ++insert_at;

      for (std::size_t i = elements_count; i > insert_at; --i)
         elements[i] = elements[i - 1];

      elements[insert_at] = value;

      ++elements_count;
   }

   bool contains(int value) const
   {
      std::size_t left = 0;
      std::size_t right = elements_count;
      
      while (left < right)
      {
         std::size_t middle = left + (right - left) / 2;

         if (value == elements[middle])
            return true;
         else if (value < elements[middle])
            right = middle;
         else
            left = middle + 1;
      }

      return false;
   }

   std::size_t size() const
   {
      return elements_count;
   }

   std::size_t max_size() const
   {
      return elements.size();
   }

   friend std::ostream& operator<<(std::ostream& out, const Set& s)
   {
      if (s.size() == 0)
      {
         out << "{empty}";
      }
      else
      {
         out << '{' << s.elements[0];

         for (size_t i = 1; i < s.size(); ++i)
            out << ", " << s.elements[i];

         out << '}';
      }

      return out;
   }

};


int main()
{
   std::size_t N = 5;
   //std::cout << "Enter N: ";
   //std::cin >> N;

   Set generated;
   for (std::size_t i = 0; i < N; ++i)
      generated.insert(std::rand());

   std::cout << "Generated:" << generated;

   Set guessed;
   int n;

   while (guessed.size() < generated.size()) {
      std::cout << "\nGuessed:" << guessed;
      std::cout << "\nEnter a number: ";
      std::cin >> n;
      
      if (generated.contains(n))
      {
         std::cout << "Correct!\n";
         guessed.insert(n);
      }
   }
}