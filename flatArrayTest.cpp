#include "memory.h"
#include <cstdint>
#include <cstdio>

void transverseList(Memory::Containers::flat_list<uint32_t> &list)
{
  Memory::Containers::list_node<uint32_t> &node = list.get_root();
  printf("position in vector of next in:  %d value:  %d \n",node.next, node.value);
  do
  { 
    node = list.retrieve_node(node.next);

    printf("position in vector of next in:  %d value:  %d \t",node.next, node.value);
    printf("has next %b\n", node.has_next());
  }
  while (node.has_next());

}


int main (int argc, char *argv[]) {

  Memory::Containers::flat_list<uint32_t> deafultList {};
  
  deafultList.add(3);
  deafultList.add(5);
  deafultList.add(7);
  deafultList.add(9);

  transverseList(deafultList);

  return 0;
}
