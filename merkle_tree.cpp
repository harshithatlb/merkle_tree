#include <iostream>
#include <vector>
#include <stdint.h>
#include <openssl/sha.h>
#include <string.h>
/* a binary merkle tree, left and right pointers are children 
 * has a pointer to its level node called sibling
   leaf nodes have only left_sha
   other levels have both left_sha, right_sha populated
   Shows the functions required in Merkle tree
   TODO: update, find differences
 */

struct Merkle_node {
    Merkle_node* left;
    Merkle_node* right;
    Merkle_node* sibling;
    unsigned char left_sha[20];
    unsigned char right_sha[20];
};

Merkle_node* addLeaves(std::vector<std::string>input){
    Merkle_node* root;
    
    Merkle_node* prev = NULL;
    for(int i =0; i<input.size(); i++){
        
        Merkle_node* leaf = new Merkle_node();
        if(i ==0) root = leaf;
        leaf->left = NULL;
        leaf->right = NULL;
        leaf->sibling =NULL;

        ::SHA1(reinterpret_cast<const unsigned char*>(input[i].data()), 20, leaf->left_sha);
        
        if( prev!=NULL)
            prev->sibling = leaf;
        prev = leaf;
    }
    return root;
}

void traverse_leaves(Merkle_node* node){
    Merkle_node* current = node;
    while(current!= NULL){
        std::cout<<"\n" ;
        for(int i =0;i<20;i++)
            printf("%x",current->left_sha[i]); 
            current = current->sibling;
    }
}

void compute(Merkle_node* node, unsigned char arr[]){
    if(node->left ==NULL && node->right== NULL)
        arr = node->left_sha;   

}
/*
Merkle_node* build_levels(Merkle_node* leaves){
    Merkle_node* prev = NULL;
    Merkle_node* current;
    int first_time = 1;
    while(leaves->sibling!=NULL) 
    {   
        Merkle_node* node = new Merkle_node();
        if(first_time == 1){ 
            current = node;
            first_time = 0;
        }
        node->sibling = NULL;
        node->left = leaves;
        if(leaves->sibling!=NULL)
            node->right = leaves->sibling;
        compute(leaves, node->left_sha);
        if(leaves->sibling!=NULL)
            compute(leaves->sibling, node->right_sha);
        if(prev!=NULL)
            prev->sibling = node;
        prev = node;
        if(leaves->sibling!=NULL)
            leaves = leaves->sibling->sibling;
        else leaves = leaves->sibling;
    }
    return current;
    
}
*/
void traverse_build1(Merkle_node* node){
 Merkle_node* current = node;
    while(current!= NULL){
        std::cout<<"\n" ;
        std::cout<<"left sha";
        
        for(int i =0;i<20;i++)
            printf("%x",current->left->left_sha[i]);
        std::cout<<"\n right sha";
        for(int i =0;i<20;i++)
            printf("%x",current->right->left_sha[i]);
    
        current = current->sibling;
    }
    
   
}

void traversal(Merkle_node* node)
{   
    while(node!=NULL)
    {
        Merkle_node* current = node;
        while(current->sibling !=NULL){
            std::cout<<"left_sha:"<<current->left_sha<<"right_sha:"<<current->right_sha;
            current = current->sibling;
        }
        node = node->left;
    }
}

int main(){
    std::vector<std::string>input_data;
    Merkle_node* node;
    std::string data = "input data";
    for(int i =0;i<10; i++)
          input_data.push_back(std::to_string(i));
      
    node = addLeaves(input_data);   
    traverse_leaves(node);
    build_levels(node);
    //traverse_build1(node);
}

