#include "factory.hpp"

template <class T, class I>
Factory<T,I>* Factory<T,I>::factory =nullptr;

template <class T, class I>
Factory<T,I>::Factory(){

}
// template <class T, class I>
// Factory<T,I>::~Factory(){
//     destroy();
// }

template <class T, class I>
void Factory<T,I>::destroy(){
    for(T* elemnt: elements){
        delete elemnt;
    }
    elements.clear();
    delete factory;
    factory = nullptr;
}


template <class T, class I>
T* Factory<T,I>::findById(const I& id) const{ 
    for(T* element : this->elements){
        if(*element == id){
            return element;
        }
    }
    return nullptr;
}


template <class T, class I> 
Factory<T,I>* Factory<T,I>::getInstance() {
    if(!factory){
        factory = new Factory<T,I>();
    }
    return factory;
}

template <class T, class I> 
T* Factory<T,I>::create(const I& id, const std::string& s){
    if(!id)throw std::invalid_argument("ID should not be null!");
    T* element = findById(id);
    if(element){
        throw std::invalid_argument(T::getClassName() + " with id: " + element->getIdToString() + " already exists!");
    }
    this->elements.push_back(new T(id, s));
    return this->elements.back();
}

template <class T, class I> 
void Factory<T,I>::remove(const I& id, const bool user_confirmation){
    if(!id)throw std::invalid_argument("ID should not be null!");
    for(unsigned i=0; i<this->elements.size();i++){
        if(*(this->elements[i]) == id){
            if((!this->elements[i]->needConfirmToDelete()) || (this->elements[i]->needConfirmToDelete() && user_confirmation)){
                elements[i]->prepareForDelete();
                delete elements[i];
                this->elements.erase(this->elements.begin()+i);
                return;
            }else{
                throw std::invalid_argument("Are you sure you want to delete "+T::getClassName() +" with id: " + this->elements[i]->getIdToString());
            }
        }
    }
    throw std::invalid_argument(T::getClassName() + " not found!");
}

template <class T, class I> 
const T* Factory<T,I>::getById(const I& id) const{
    if(!id)throw std::invalid_argument("ID should not be null!");
    T* element = this->findById(id);
    if(!element){
        throw std::invalid_argument(T::getClassName() + " does not exist!");
    }
    return element;
}

template <class T, class I> 
T* Factory<T,I>::getById(const I& id){
    if(!id) throw std::invalid_argument("ID should not be null!");
    T* element = this->findById(id);
    if(!element){
        throw std::invalid_argument(T::getClassName() + " does not exist!");
    }
    return element;
}

template <class T, class I>
const size_t Factory<T,I>::getNumberOfElements() const{
    return this->elements.size();
}

template <class T, class I>
std::ostream& operator<<(std::ostream& out, const Factory<T,I>& f) {
    for(T* element : f.elements){
        out<<*element<<"\n";
    }
    return out;
}

template <class T, class I>
const std::vector<T*> Factory<T,I>::getElements() const{
    return this->elements;
}

template class Factory<Person, unsigned>;
template class Factory<Vehicle,const char*>;
