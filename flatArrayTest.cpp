#include "memory.h"
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <string>

#define MAX_REPS 10
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
  if (list.is_empty()) {return;}
  Memory::Containers::list_node<Personaje> node = list.get_root();

  printf("nombre:  %s, vida: %d,  posición {%f, %f, %f} \n",node.value.name.c_str(), node.value.vida, node.value.position[0], node.value.position[1], node.value.position[2]);
  printf("current index: %d next: %d prev: %d has_next: %b has_prev: %b\n ---------------- \n",list.i_root, node.next, node.previous, node.has_next(), node.has_previous());
  do
  { 
    uint32_t new_index = node.next;
    node = list.retrieve_node(new_index);

    printf("nombre:  %s, vida: %d,  posición {%f, %f, %f} \n",node.value.name.c_str(), node.value.vida, node.value.position[0], node.value.position[1], node.value.position[2]);
    printf("current index: %d next: %d prev: %d has_next: %b has_prev: %b\n ---------------- \n",new_index, node.next, node.previous, node.has_next(), node.has_previous());
  }
  while (node.has_next());
}

void test1()
{

  Memory::Containers::flat_list<Personaje> deafultList {};
 
  { 
    for(int i = 0; i < MAX_REPS; ++i)
    {
      deafultList.add({"pablo", 10, {0.0,1.0,1.1}});
    }
 
    printf("root index: %d top index: %d\n", deafultList.i_root, deafultList.i_top);
    transverseList(deafultList);

    deafultList.remove(5);
    printf("REMOVED 5 NODE \n------------------\n");
    transverseList(deafultList);
    printf("root index: %d top index: %d\n", deafultList.i_root, deafultList.i_top);

    deafultList.remove(9);
    printf("REMOVED 9 NODE \n------------------\n");
    transverseList(deafultList);
    printf("root index: %d top index: %d\n", deafultList.i_root, deafultList.i_top);

    deafultList.remove_top();
    printf("REMOVED 8 NODE \n------------------\n");
    transverseList(deafultList);
    printf("root index: %d top index: %d\n", deafultList.i_root, deafultList.i_top);
  
    deafultList.add({"luisa", 2, {1.0,2.2, 10.0}}); 
    printf("ADDED A NODE \n------------------\n");
    transverseList(deafultList);
    printf("root index: %d top index: %d\n", deafultList.i_root, deafultList.i_top);

    deafultList.remove(2);
    printf("REMOVED 2 NODE \n------------------\n");
    transverseList(deafultList);
    printf("root index: %d top index: %d\n", deafultList.i_root, deafultList.i_top);

    deafultList.remove(1);
    printf("REMOVED 1 NODE \n------------------\n");
    transverseList(deafultList);
    printf("root index: %d top index: %d\n", deafultList.i_root, deafultList.i_top);

    deafultList.add({"paco", 33, {1.0,2.2, 10.0}}); 
    printf("ADDED A NODE \n------------------\n");
    transverseList(deafultList);
    printf("root index: %d top index: %d\n", deafultList.i_root, deafultList.i_top);

    Personaje pepa {"pepa", 100, {1.1, 23.3, 102}};
    //deafultList.add({"pepa", 100, {1.1, 23.3, 102}});
    deafultList.add(pepa);
    transverseList(deafultList);
    printf("root index: %d top index: %d\n", deafultList.i_root, deafultList.i_top);

    pepa.name = "martina";

    transverseList(deafultList);
  }

  deafultList.remove(0);
  transverseList(deafultList);
  printf("root index: %d top index: %d\n", deafultList.i_root, deafultList.i_top);

  deafultList.clear();
  printf("\nCLEAR\n_____________________________________________\n\n");
  deafultList.add({"pablo", 10, {0.0,1.0,1.1}});
  deafultList.add({"pablo", 10, {0.0,1.0,1.1}});
  deafultList.add({"pablo", 10, {0.0,1.0,1.1}});
  transverseList(deafultList);
  printf("root index: %d top index: %d\n", deafultList.i_root, deafultList.i_top);
  
  deafultList.clear();
  transverseList(deafultList);
}

void test2()
{
  Memory::Containers::flat_list<Personaje> defaultlist {};

  for (int i = 0; i < MAX_REPS; ++i)
  {
    defaultlist.add({"a", 10, {1,1,1}});
  }

  transverseList(defaultlist);

  for (int i = 0; i < MAX_REPS; ++i)
  {
    defaultlist.remove_top();
  }
  printf("\n ---------------------------- \n");
  for (int i = 0; i < MAX_REPS/2; ++i)
  {
    defaultlist.add({"b", 1, {2,2,2}});
  }
  transverseList(defaultlist);
}


int main (int argc, char *argv[]) {

  //test1();
  test2();

  return 0;
}
