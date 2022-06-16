#include <string>
#include <iostream>
#include <vector>
#include <queue>


using namespace std;

namespace ariel
{
    class OrgChart
    {
        
        private:
            class Node
            {
                public:
                    // my name as the root of the values below me
                    string name;
                    // the values that below me (childrens)
                    vector<Node*> under_me;
                    Node(string&);  //constructor

                    //pointers to next node
                    Node *nextLevel;
                    Node *nextReverse;
                    Node *nextPreOrder;
            };
            Node* root;
            
            

        public:
            class iterator            // open class iterator inside Orgchart
            {
                private:
                    Node * cur;
                    int flag;
                    void Level();
                    void Reverse() ;
                    void Pre();
                    void preDFS(Node*, queue<Node*>&);  //preorder based recursion
                
                public:     //define operators
                    Node* getCur(); //getter for the cur
                    iterator(Node*, int);    // constructor
                    iterator & operator++();    //iterator++
                    iterator operator++(int);     //++iterator
                    string operator*();
                    bool operator!=(const iterator&);
                    bool operator==(const iterator&);
                    string * operator->();  //operator on variable type class

            };

            // orgchart functions
            OrgChart();            // constructor
            
            iterator begin();   //start level order
            iterator end();     //retrun itertor empty in order tokmow when to finish

            OrgChart add_root(string);   //get node and put it in the root
            
            OrgChart add_sub(string, string);    //get person/class
            
            bool findEmployeeDFS(Node*, string&, string&);  //find employee by his name
            
            
            iterator begin_level_order();        //return iterator in level order
            iterator end_level_order();        
            
            iterator begin_reverse_order();      //return iterator in reverse level order
            iterator end_reverse_order();
            
            iterator begin_preorder();        //return iterator in preorder
            iterator end_preorder();

            iterator reverse_order();

            friend ostream & operator <<(ostream& stream, OrgChart& chart);     //operator output
            Node* getRoot();

    };
}
