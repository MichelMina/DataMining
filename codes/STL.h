#ifndef STL_H_INCLUDED
#define STL_H_INCLUDED
#include "Class.h"
#include <stdlib.h>
class Node
{
    private:
        customer *data;
        Node *next;
    public:
        /*Nodes constructors*/
        Node(){next=nullptr;}
        Node(customer *X)
        {
            data=X;
            next=nullptr;
        }
		~Node() {
			delete data;
		}
        /*Data setters and getters*/
        void set_Data(customer *X)
        {data = X;}
        customer* get_Data()
        {return data;}
        /*next setters and getters*/
        void set_next(Node * X){next=X;}
        Node* get_next(){return next;}

};

class List
{
    private:
        Node * head;
        Node * tail;
        int counter;
    public:
        /*Constructors*/
        List(){head=nullptr;tail=head;counter=0;}
        /*Checks if the list is empty*/
        bool isEmpty()
        {
            if (head==nullptr)
                return true;
            return false;
        }
        /*front manipulation*/
        void add_Front(customer *item)
        {
            if (isEmpty())
            {
                head = new Node(item);
                tail = head;
            }
            else{
            Node * nw= new Node(item);
            nw ->set_next(head);
            head=nw;
            }
			counter++;
        }
        void pop_Front()
        {
            if (isEmpty())
                return;
            if (head==tail)
            {
                Node* temp=head;
                head = nullptr;
                tail = nullptr;
                delete temp;
                counter--;
                return;
            }
            Node * temphead=head;
            head=head->get_next();
            delete temphead;
            counter--;
        }
        /*End Manipulation*/
        void add_End(customer *X)
        {
            if(isEmpty()){
                add_Front(X);
				return;
			}
            else
            {
                Node * temp=new Node(X);
                tail->set_next(temp);
                tail=temp;
                counter++;
            }
        }
        /*Remove end is not implemented because we dont need it*/
        /*TODO >> add remove at index*/
        /*Search is not implemented*/
        /*Remove item with a specific value not implemented*/

        /*freeing the whole list*/
        void Clear()
        {
            while (!isEmpty())
                pop_Front();
        }

        /*Destructor*/
        ~List(){Clear();}

        /*Extras*/
        int get_Size(){return counter;}
        customer* get_Front(){return head->get_Data();}
        customer* get_End(){return tail->get_Data();}


        /*copy operator*/
        List& operator=(const List& rhs)
        {
            Clear();
            Node* temp = rhs.head;
            while (temp) {
                add_End(temp->get_Data());
                temp = temp->get_next();
            }
            return *this;
        }

		Node* getHead() {
			return head;
		}
		Node* getTail() {
			return tail;
		}

};



#endif // STL_H_INCLUDED
