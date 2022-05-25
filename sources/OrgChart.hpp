#include <string>
#include <iostream>
#include <vector>

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
                    // the values that below me
                    vector<Node> under_me;
            };
            Node * root;
            

        public:
            class iterator            // open class iterator inside Orgchart
            {
                public:     //define operators
                    Node * cur;
                    iterator(OrgChart * cur);    // constructor
                    iterator & operator++();    //iterator++
                    iterator & operator++(int);     //++iterator
                    string operator*();
                    bool operator!=(iterator comp);
                    string * operator->();  //operator on variable type class

            };

            // iterator functions
            OrgChart();            // constructor
            
            iterator begin();
            iterator end();

            OrgChart & add_root(string root);   //get node and put it in the root
            OrgChart & add_sub(string f, string c);    //get person/class
            
            iterator begin_level_order();        //return iterator in level order
            iterator end_level_order();        
            
            iterator begin_reverse_order();      //return iterator in reverse level order
            iterator end_reverse_order();
            
            iterator begin_preorder();        //return iterator in preorder
            iterator end_preorder();

            iterator reverse_order();

            friend ostream & operator <<(ostream & stream, OrgChart const & chart);     //operator output

    };
}
