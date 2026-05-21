#include "memory.h"
#include <cstdint>
#include <cstdio>
#include <string>

struct s_personaje
{
  std::string name;
  int vida; 
  float position[3];

  s_personaje() 
  {
    printf("PERSONAJE:: Default Constructor\n");
    name = " ";
    vida = 0;
    position[0] = 0.0f;
    position[1] = 0.0f;
    position[2] = 0.0f;
  }

  s_personaje(std::string _name, int _vida, float (&_position)[3])
  {
    //printf("PERSONAJE:: Constructor\n");
    name = std::move(_name);
    vida = _vida;
    position[0] = _position[0];
    position[1] = _position[1];
    position[2] = _position[2];
  }
  
  s_personaje(std::string &&_name, int &&_vida, float (&&_position)[3])
  {
    //printf("PERSONAJE:: Move Constructor\n");
    name = std::move(_name);
    vida = std::move(_vida);
    position[0] = std::move(_position[0]);
    position[1] = std::move(_position[1]);
    position[2] = std::move(_position[2]);   
  }
  
  ~s_personaje() {
    //printf("PERSONAJE:: Destructor \n");
  }

};
typedef s_personaje Personaje; 

void transverseList(Memory::Containers::flat_list<uint32_t> &list)
{
  Memory::Containers::list_node<uint32_t> node = list.get_root();
  printf("position in vector of next in:  %d value:  %d \n",node.next, node.value);
  do
  {
    uint32_t new_index = node.next;
    node = list.retrieve_node(new_index);

    printf("position in vector of next in:  %d value:  %d \t",node.next, node.value);
    printf("has next %b\n", node.has_next());
  }
  while (node.has_next());

}

void transverseList(Memory::Containers::flat_list<Personaje> &list)
{
  Memory::Containers::list_node<Personaje> node = list.get_root();

  printf("nombre:  %s, vida: %d,  posición {%f, %f, %f} \n",node.value.name.c_str(), node.value.vida, node.value.position[0], node.value.position[1], node.value.position[2]);
  printf("current index: %d next: %d prev: %d has_next: %b has_prev: %b\n ---------------- \n",0, node.next, node.previous, node.has_next(), node.has_previous());
  do
  { 
    uint32_t new_index = node.next;
    node = list.retrieve_node(new_index);

    printf("nombre:  %s, vida: %d,  posición {%f, %f, %f} \n",node.value.name.c_str(), node.value.vida, node.value.position[0], node.value.position[1], node.value.position[2]);
    printf("current index: %d next: %d prev: %d has_next: %b has_prev: %b\n ---------------- \n",new_index, node.next, node.previous, node.has_next(), node.has_previous());
  }
  while (node.has_next());
}


#define MAX_REPS 10
int main (int argc, char *argv[]) {

  Memory::Containers::flat_list<Personaje> deafultList {};
 
  { 
    for(int i = 0; i < MAX_REPS; ++i)
    {

      //float position[3] = {0.0,1.0,1.1};
      //Personaje pablo {"pablo", 10, position};
      //deafultList.add(pablo);
      deafultList.add({"pablo", 10, {0.0,1.0,1.1}});
    }
 
    printf("root index: %d top index: %d\n", deafultList.i_root, deafultList.i_top);
    transverseList(deafultList);

    printf("REMOVED 1 NODE \n------------------\n");
    deafultList.remove(5);
    transverseList(deafultList);
    printf("root index: %d top index: %d\n", deafultList.i_root, deafultList.i_top);

    printf("REMOVED 1 NODE \n------------------\n");
    deafultList.remove(9);
    transverseList(deafultList);
    printf("root index: %d top index: %d\n", deafultList.i_root, deafultList.i_top);

    deafultList.remove_top();
    transverseList(deafultList);
    printf("root index: %d top index: %d\n", deafultList.i_root, deafultList.i_top);

    deafultList.remove(0);
    transverseList(deafultList);
    printf("root index: %d top index: %d\n", deafultList.i_root, deafultList.i_top);
  }



  /*
  float position[3] = {0.0,1.0,1.1};
  Memory::Containers::vector<Personaje> defaultVector {};

  //Personaje nuevo_pers {"paco", 100, position};
  //defaultVector.push_back(nuevo_pers);
  //defaultVector.push_back({"pedro", 100, position});
  defaultVector.emplace_back("pilar", 20, position);
  */ 
  return 0;
}
