template <class T>  
class EntityFactory
{
public:
     T* create();
     T* create(T copy);
};