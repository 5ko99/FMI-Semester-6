// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Бойчо Златанов
// ФН: 82092
// Специалност: КН
// Курс: 2
// Административна група: 4
// Ден, в който се явявате на контролното: 24.04.2021
// Начален час на контролното: <09:30>
// Кой компилатор използвате: <Visual Studio Code mingw-64>
//


#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include<cstdlib>
#include<cstime>

class intBuffer{

	public:
	intBuffer();
	intBuffer(const size_t&);
	intBuffer(const intBuffer&);
	intBuffer(const size_t&, const intBuffer&);
	~intBuffer();

	intBuffer& operator = (const intBuffer&);
    int& at(std::size_t);
    const int& at(std::size_t) const;

    int & operator[](std::size_t);
    const int& operator [](std::size_t) const;

    std::size_t size() const;

    void copy_from(const intBuffer& other, std::size_t count);

	bool operator== count(intBuffer& other);
	bool operator<(const intBuffer& other);



   private:
   void delete_content();
   std::size_t arr_size;
   int*int_array;
   

};


	intBuffer::IntBuffer() :  arr_size{0}
	{
		int_array = nullptr;
	}

	intBuffer::intBuffer(const intBuffer &other): arr_size{other.arr_size}}
	{
			this->int_array = new int [this->size];
			for(int i = 0; i < other.size;++i)
			{
				this ->int_array[i] = other.int_array[i];
			}

	}

	intBuffer::intBuffer(const std::size_t&size)
	{
		try{
			this->int_array = new int[size];
		   }
		  catch(std::bad_alloc &e)
	      { 
	 	    throw new std::bad_alloc();
	      }
	
	}
	
	intBuffer::~intBuffer()
	{
		delete_content();
	}

	intBuffer::intBuffer(const size_t &size, const intBuffer &other):arr_size{size}
	{
		try{
			this->int_array = new int[size];
			int min_sum = std::min(size, other.arr_size);
			for(int i = 0; i< min_sum; ++i)
			{
				this->int_array[i] = other.int_array[i];
			}
		}
		catch (std::bad_alloc &e)
		{
			throw new std::bad_alloc();
		}
	}



	intBuffer& intBuffer::operator = (const intBuffer& other)
	{
		if(this!= &other)
		{
			delete_content();
			this->arr_size = other.arr_size;
			this -> int_array = new[this->size];
			for(int i=0;i<other.arr_size;++i)
			{
				this->int_array[i] = other.int_array[i];
			}
		}
		return *this;
	}

    int& intBuffer::at(std::size_t& index)
	{  
		if(index>=this->index)
		{
			throw std::out_of_range("Invalid index ! ");
		}
		return this->int_array[index];

	}

    const int& intBuffer::at(std::size_t index) const
	{
		
		if(index>=this->arr_size || index < 0)
		{
			throw std::out_of_range("Invalid index ! ");
		}
		return this->int_array[index];
	}

   
    int & intBuffer::operator[](std::size_t index)
	{
		assert ( 0 <= index && index < this->arr_size);
		return this->int_array[index];
	}

    const int& intBuffer::operator [](std::size_t index) const
	{
		assert( 0 <= index && index < this->arr_size);
		return this->int_array[index];
	}
    std::size_t intBuffer::size() const
	{
      return this->arr_size;
	}


    void copy_from(const intBuffer& other, std::size_t count)
	{
		if(std::max(this->arr_size, other.arr_size)<count)
		{
			throw std::out_of_range("Count too large, not enough elemenets ! ");
		}
		for(int i=0; i < count; ++i)
		{
			this->int_array[i] = other.int_array[i];
		}
	}

	bool intBuffer::operator== (intBuffer& other)
	{
		if(this-> arr_size != other.arr_size)
		{
			return false;
		}
		for(int i=0; i<this->arr_size;++i)
		{
			if(this->int_array[i] != other.int_array[i])
			{
				return false;
			}
		}
	}
	bool intBuffer::operator< (const intBuffer& other)
	{
		int equal_counter = 0;
	if(this->arr_size == 0)
	{
		if(other.arr_size > 0)
		{
			return true;
		}
		return false;

	}
	for(int i=0; i<this->arr_size && i<other.arr_size;++i)
	{
		if(this->int_array[i]> other.int_array[i])
		{
			return false;
		}
		else if(this-> int_array[i] == other.int_array[i])
		{
			++equal_counter;
		}
	}
	if(equal_counter == std::min(this->arr_size, other.arr_size))
	{
		return false;
	}
	return true;
	}




class Set
	{
     public:
     
	 Set();
	 void insert(int );
	 bool contains(int)const;
	 std::size_t size() const;


      private:
	  void resize();
	  void add_value(const int&);
	  intBuffer elements; //sorted in asc ord, each el is unique
      int number_of_elems;

	};
  void Set::resize()
  {
	  intBuffer set_buffer = intBuffer(this->elements.size()*2);
	  for(int i=0; i<this->elements.size();++i)
	  {
		  set_buffer[i] = elements[i];
	  }
	  this->elements = set_buffer;
  }

  void add_value(const int&value)
  {
	  elements[number_of_elems] = value;
	  ++number_of_elems;
	  for(int i=0; i< number_of_elems -1 ; ++i)
	  {
		  for(int j = i+1; j < number_of_elems; ++j)
		  {
			  if(elements[i] > elements[j])
			  {
				  std::swap(elements[i], elements[j]);
			  }
		  }
	  }
  }
     Set::Set()
	 {
		 elements = intBuffer(2);
		 number_of_elems = 0;
	 }

	 void Set::insert(int value)
	 {
       if(contains(value))
	   {
		   return;
	   }
	   else if(this->number_of_elems == elements.size())
	   {
		   try{
        resize();
	   }
	   catch(const std::bad_alloc& e)
	   {
		   throw new std::bad_alloc();
		  
	   }
	 }
	   add_value(value);
	 }

	 bool Set::contains(int value)const
	 {
       int left = 0;
	    int right = number_of_elems;
	    int mid = (left + right)/2;

	   while(left <= right)
	   {
		   if(elements[mid] == value)
		   {
			   return true;
		   }
		   else if(elements[mid] > value)
		   {
			   right = mid - 1;
		   }
		   else{
			   left = mid + 1 ;
		   }

	   }
	   return false;

	 }
	 std::size_t Set::size() const
	 {
		 return this->
	 }

void generate_random(Set& curr_set)
{

	std::sran(std::time(0));
	while(curr_set.size()<number_to_add)
	{


	int random_variable = std::rand();
    curr_set.insert(rand_to_add);
		}
		return;
}

int main()
{

	std::size_t N; 
	std::cin>>N;
	Set generated;
	generate_random(generated, N);

	Set G;
	int k;

	std::cout<<std::endl<<"Please input your desired numbers:" <<std::endl;
	while(G.size()<generated.size())
	{
		std::cin>>k;
		if(generated.contains(k))
		{
			G.insert(k);
			std::cout<<"The number k is part of the generated sequence !" <<std::endl;
		}
		std::cout<<"The number k is NOT part of the generated sequence !" <<std::endl;
	}
  std::cout<<"Congrats !  You have guessed all random numbers ! "<<std::endl;




	return 0;
}