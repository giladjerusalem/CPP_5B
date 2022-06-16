#include <string>
#include <iostream>
#include "OrgChart.hpp"
#include <stack>
#include <queue>

using namespace std;

namespace ariel{

    //initilize node constructor with Null references to other nodes with employy's name
    OrgChart::Node::Node(string& b):nextLevel(NULL),nextPreOrder(NULL),nextReverse(NULL)    // initial list
    ,under_me({}),name(b){
    }

    //orgchart constructor initilize, with no root(yet)
    OrgChart::OrgChart():root(NULL)
    {
    }

    //add root to orgchart - str empty is guarded.
    //if its adding employee - root node is added, else - only name is changed.
    OrgChart OrgChart::add_root(string str)
    {
        if(str.empty()){
            throw invalid_argument("input cant be empty");
        }
        if(this-> root != NULL){       //if boss exist - replace
            this->root->name = str;
        }
        else{
            this->root = new Node{str};
        }
        
        return *this;
    }


    OrgChart OrgChart::add_sub(string f, string c)
    {
        
        //name guard - make sure input for both father and child is not empty string
        if(f.empty() || c.empty()){
            throw invalid_argument("cant add sub with empty strings");
        }

        //if there is no boss yet - we cant search for any employee
        if(this->root == nullptr){
            throw invalid_argument("no boss was found");
        }

        //run employee search function, if not found f - cant add new child
        if(!findEmployeeDFS(this->root,f,c)){
            throw invalid_argument("no superiour employee was found to add subordinate to it");
        }
        return *this;
    }

    //dfs search for employee
    bool OrgChart::findEmployeeDFS(Node* employee, string& f, string& c){   //& for reference - i dont want to copy 
        
        //stopping condition  - employee found
        if(employee->name == f){
            employee->under_me.push_back(new Node(c));
            return true;
        }

        //for each through all epmployee's children
        for(Node* n : employee->under_me){
            bool dfs = this->findEmployeeDFS(n,f,c); //recursive search
            if(dfs){    //if true
                return true;
            }
        }
        //if not employee found - return false
        return false;
    }  

    OrgChart::iterator OrgChart::begin()
    {
        return iterator(this->root,1);
    }
    OrgChart::iterator OrgChart::end()
    {
        return iterator(this->root,0);
    }
    OrgChart::iterator OrgChart::begin_level_order()
    {
        return iterator(this->root,1);
    }
    OrgChart::iterator OrgChart::begin_preorder()
    {
        return iterator(this->root,3);
    }
    OrgChart::iterator OrgChart::begin_reverse_order()
    {
        return iterator(this->root,2);
    }
    OrgChart::iterator OrgChart::end_level_order()
    {
        return iterator(this->root,0);
    }
    OrgChart::iterator OrgChart::end_preorder()
    {
        return iterator(this->root,0);
    }
    OrgChart::iterator OrgChart::reverse_order()
    {
        return iterator(this->root,0);
    }

    OrgChart::Node* OrgChart::getRoot(){
        return this->root;
    }




    OrgChart::iterator::iterator(Node* _cur, int _flag):cur(_cur),flag(_flag)   //normal constructor
    {
         //0 - empty iterator
        //1 - level order
        //2 - reverse order
        //3 - preorder
        
        if(this->cur == NULL){
            throw invalid_argument("no boss");
        }
        if(flag == 0){
            this->cur = NULL;
        }
        else if(flag == 1){
            this->Level();
        }
        else if(flag == 2){
            this->Reverse();
        }
        else{
            this->Pre();
        }

    }

    OrgChart::Node* OrgChart::iterator::getCur(){
        return this->cur;
    }

    void OrgChart::iterator::Level()  //level order  //print by level from left to right
    {   
        Node* cur = this->cur;
        if (cur == NULL)
        {
            //if there is no boss - you cant create level order
            throw runtime_error("root cant be null");
        }
        queue<Node *> q;
        q.push(cur);
        Node *tmp = NULL;   //for storing junction
        while (!q.empty())
        {
            //while you can - add children to the end of the queue, and in loop we will access then one by one
            tmp = q.front();
            q.pop();
            for (Node *child : tmp->under_me)
            {
                q.push(child);
            }
            if(!q.empty()){     //put next level as front of the q
                tmp->nextLevel = q.front();
            }             
        }
    }

    void OrgChart::iterator::Reverse()  //reverse level order
    {
        Node* cur = this->cur;
        if (cur == NULL)
        {
            throw runtime_error("root cant be null");
        }
        queue<Node*> q;
        Node *tmp = NULL;
        q.push(cur);  
        while (!q.empty())
        {
            tmp = q.front();
            q.pop();
            //this time we need to go from the last child, to the first
            for (int i = (int)tmp->under_me.size() - 1; i >= 0; i--)    //for --
            {
                q.push(tmp->under_me.at((size_t)i));
            }
            if(!q.empty()){
                
                //move on to the next employee
                tmp->nextReverse = q.front();
            }
            
        }
      
        if(tmp != NULL){
            tmp->nextReverse =NULL;
        }
        

        //now we need to reverse the order, that is because the nodes are linked in the reverse order
        //from 1->2->3->4, to 4->3->2->1
        tmp = cur;
        Node* prev = NULL;
        Node* tempNext = NULL;
        while(tmp != NULL){
            tempNext = tmp->nextReverse;
            tmp->nextReverse = prev;
            prev = tmp;
            tmp = tempNext;
        }
        this->cur = prev;   //cur become last

    }

    //preorder ordering used with recursion
    void OrgChart::iterator::Pre()
    {
        Node* cur = this->cur;
        if (cur == NULL)
        {
            throw runtime_error("root cant be null");
        }

        queue<Node*> q;
        Node* tmp = NULL;
        q.push(cur);
        //start
        this->preDFS(cur,q);    //return ordered in q

        while (!q.empty()){
            tmp = q.front();
            q.pop();
            if(!q.empty()){
                tmp->nextPreOrder = q.front();  //enter next node to q
            }
     
        }

    }

    //recursive function to add children
    void OrgChart::iterator::preDFS(Node* cur, queue<Node*>&q){
        if(cur == NULL){
            return;
        }

        for (Node* child : cur->under_me)
        {
            q.push(child);
            preDFS(child,q);
        } 
    }

    OrgChart::iterator & OrgChart::iterator::operator++()
    {
        //sort increment by eralier used flag (iter++)
        if (this->flag == 1)
        {
            this->cur = this->cur->nextLevel;
        }
        else if (this->flag == 2)
        {
            this->cur = this->cur->nextReverse;
        }
        else if (this->flag == 3)
        {
            this->cur = this->cur->nextPreOrder;
        }
        return *this;
    }

    OrgChart::iterator OrgChart::iterator::operator++(int)
    {
        //(++iter)
        iterator tmp = *this;
        (*this)++;
        return tmp; //return original
    }
    string OrgChart::iterator::operator*()
    {
        return this->cur->name;
    }
    bool OrgChart::iterator::operator!=(const OrgChart::iterator& iterat)
    {
        return !(*this==iterat);
    }
    bool OrgChart::iterator::operator==(const OrgChart::iterator& iterat)
    {
        return this->cur == iterat.cur;
    }
    string * OrgChart::iterator::operator->()
    {
        return (&(this->cur)->name);
    }

    std::ostream & operator<<(std::ostream & stream, OrgChart & chart)
    {
        
        if (chart.root == NULL)
        {
            throw std::out_of_range("OrgChart is empty");
        }

        OrgChart::iterator iter = chart.begin_level_order();    //return itertator
        while(iter.getCur() != NULL){   //while on iterator
            if(iter.getCur()->under_me.empty()){    //if no children
                ++iter;
                continue;
            }
            cout << "worker name -> " << iter.getCur()->name << ", worker's children: ";
            //else print children
            for(OrgChart::Node* o : iter.getCur()->under_me){   //print children
                cout << o->name << ", ";
            }
            cout << "\n";
            ++iter;
        }
        return stream;
    }
}