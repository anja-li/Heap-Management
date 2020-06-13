#include<iostream>
#include<stdio.h>
#include<array>
#include<string.h>
using namespace std;

struct node_free*head_free;
int heap[20000]; //heap  defined of space 20000

struct node_free{
    int starting_address;
    int free_space;
    struct node_free *next;
    //Free list
};


struct node_allocate{
    int starting_address;
    int allocated_space;
    int ending_address;
    string p_name;
    struct node_allocate *next;
    //allocated list 
};

struct node_free* createfree(int sa,int fs){
    struct node_free* new1;
    new1=(struct node_free*)malloc(sizeof(struct node_free));
    new1->starting_address=sa;
    new1->free_space=fs;
    new1->next=nullptr;
    return new1;
  

}
struct node_allocate*create(int sa,int as,string name){
    struct node_allocate *new1;
    new1= new node_allocate();
    new1->starting_address=sa;
    new1->allocated_space=as;
    new1->p_name=name;
    new1->ending_address=sa+as;
    new1->next=nullptr;
    return new1;
}

struct node_free *search(struct node_free**headf1,int size)
{
    struct node_free*temp=*headf1;
    struct node_free*prev;
     while (temp->free_space<size && temp!=NULL)
    {
        //cout<<"entered while0";

        prev=temp;
        temp=temp->next;
       // cout<<"kaha attak raha h";
    }

    return temp;
    }

struct node_free* updatefreelist(struct node_free**hf,struct node_free*temp,int size)   
{
    struct node_free*t;
    t=*hf;
    struct node_free*w=t;
    struct node_free*emp=temp;
  //  cout<<t->starting_address<<"--"<<t->next<<"tt"<<t->free_space<<endl;
     
     if ((*hf)->starting_address==temp->starting_address &&(*hf)->free_space==size)
     {
         (*hf)=(*hf)->next;
         free(temp);
     }
     
     while (t->starting_address!=emp->starting_address)
     {
       //  cout<<"w";
        w=t;
        t=t->next;
       // cout<<"t";
     }
     if (t->free_space==size)
     {
        w->next=t->next;
        free(t);
     }
     else
     {
        t->starting_address+=size;
        t->free_space-=size;

     } 
     return *hf;
            
} 

void updateallocatedlist(struct node_allocate**h,struct node_allocate*temp1)
{

    struct node_allocate*new_node=temp1;  
    struct node_allocate*current;
       if (*h == NULL || (*h)->starting_address >= new_node->starting_address)  
    {  
        new_node->next = *h;  
        *h = new_node;  
    }  
    else
    {  
        current = *h;  
       // cout<<"else"<<endl;
        while (current->next!=NULL &&  current->next->starting_address < new_node->starting_address)  
        { // cout<<"in while"<<endl;
            current = current->next;  
        }  
       // cout<<"out of while"<<endl;
        new_node->next = current->next;  
        current->next = new_node;  
    }  
}


struct node_allocate* allocate(struct node_free*headf1,struct node_allocate* heada1,int size,string name)
{
   
    struct node_free*temp;
    struct node_allocate*temp1;
    struct node_allocate*p=heada1;
 
     if (headf1==NULL)
   {
       //cout<<"head defined!"<<endl;
       struct node_free*a=nullptr;
       a=createfree(0,20000);
       headf1=a;
       
   }
 
   temp=search(&headf1,size);
   if (temp==NULL)
   {
       cout<<"NO BLOCK FOUND"<<endl;
       return NULL;
   }
   else
   {
      
       temp1=create(temp->starting_address,size,name);
       head_free=updatefreelist(&headf1,temp,size);
      // cout<<"after free update"<<endl;
     //  cout<<headf1->starting_address<<"--"<<headf1->free_space<<endl;
       updateallocatedlist(&heada1,temp1);
      // cout<<heada1->starting_address;
       return heada1;
   }
      
    
}
struct node_allocate *searchallocate(struct node_allocate**heada1,int size,string name)
{
    struct node_allocate*temp2=*heada1;
    struct node_allocate*prev2;
     while (temp2->allocated_space!=size && temp2!=NULL && temp2->p_name!=name)
    {
        //cout<<"entered while0";
        prev2=temp2;
        temp2=temp2->next;
        // cout<<"kaha attak raha h";
    }
    return temp2;
    }
struct node_free*add(struct node_free**h,struct node_free*p)
{ // cout<<"in add"<<endl;  
    struct node_free*new_node=p;  
    struct node_free*current;
    
     if (*h == NULL || (*h)->starting_address >= new_node->starting_address)  
    {  
      //  cout<<"if"<<endl;
      //  cout<<new_node->free_space<<endl;
        new_node->next = *h;  
        *h = new_node; 
       // cout<<(*h)->free_space<<endl; 
    }  
    else
    {  
        current = *h;  
      //  cout<<"else"<<endl;
        while (current->next!=NULL &&  current->next->starting_address < new_node->starting_address)  
        { // cout<<"in while"<<endl;
            current = current->next;  
        }  
      //  cout<<"out of while"<<endl;
        new_node->next = current->next;  
        current->next = new_node;  
    }  
    struct node_free*curr=*h;
    return curr;

}    
struct node_allocate*removeallocate(struct node_allocate**heada1,struct node_allocate*temp3)
{   struct node_allocate*temp2=*heada1;
    struct node_allocate*prev2;
   // cout<<"in remove"<<endl;
    if ((*heada1)->starting_address==temp3->starting_address&&(*heada1)->allocated_space==temp3->allocated_space)
    {
        /* code */
       // cout<<"in remove if"<<endl;
        (*heada1)=(*heada1)->next;
        //cout<<(*heada1)->starting_address<<endl;
        free(temp3);
    }
    else
    {
        /* code */
    
    
     while (temp2->allocated_space!=temp3->allocated_space  && temp2->p_name!=temp3->p_name)
     {
      //  cout<<"entered while0";
        prev2=temp2;
        temp2=temp2->next;
       //  cout<<"kaha attak raha h";
     }
     prev2->next=temp2->next;
     cout<<prev2->next->allocated_space<<endl;
     free(temp2);
    }
    struct node_allocate*t=*heada1;
  //  cout<<t->allocated_space<<endl;
    return t;


}
struct node_allocate*deallocate(struct node_allocate*heada1,struct node_free*headf1,int size,string name)
{
  
    struct node_allocate*temp3;
  //  cout<<"in deallocate"<<endl;
    temp3=searchallocate(&heada1,size,name);
  //  cout<<temp3->starting_address<<"----"<<temp3->ending_address<<endl;
    if (temp3==NULL)
    {
        cout<<"Not found"<<endl;
    }
    else
    {
        struct node_free *p=createfree(temp3->starting_address,temp3->allocated_space);
    //    cout<<p->free_space<<endl;
        head_free=add(&headf1,p);
      //  cout<<head_free->starting_address<<"---"<<head_free->free_space<<endl;
        heada1=removeallocate(&heada1,temp3);
       // cout<<"after remove allocate"<<endl;
       // cout<<heada1->allocated_space<<endl;

        
    }
    return heada1;
    
  
}

void printlistallocated(struct node_allocate*b)
{ 
   // cout<<"entering print allocated!"<<endl;
    struct node_allocate*list1;
    list1=b;
    while(list1!=NULL)
    {
      //cout<<"entered while"<<endl;
      cout<<"SA:"<<list1->starting_address<<"Space:"<<list1->allocated_space<<"Ending Address:"<<list1->ending_address<<"Name:"<<list1->p_name<<"--->";
      list1=list1->next;
    }
    cout<<endl;
}
void printlistfree(struct node_free*headf1)
{ 
    struct node_free *list;
    list=headf1;
    
    while(list!=NULL)
    {
      cout<<"SA:"<<list->starting_address<<"Space:"<<list->free_space<<"--->";
      list=list->next;
    }
    cout<<endl;
}


struct node_free *searchbestfit(struct node_free **headf1,int size)
{ //  cout<<"in search best fit"<<endl;
	struct node_free *temp=*headf1;
    int ssize;
    struct node_free *short_size=NULL;
    cout<<temp->free_space<<endl;
    while(temp!=NULL){
        if(short_size==NULL){
           // cout<<"in if"<<endl;
            if(temp->free_space>=size){
             //   cout<<"comparing size"<<endl;
                short_size=temp;
                ssize=temp->free_space;
            }
        }
        else{
          //  cout<<"entered in else"<<endl;
            if(temp->free_space<ssize&&temp->free_space>=size){
                short_size=temp;
                ssize=temp->free_space;
            }                 

        }
        temp=temp->next;
    }
    temp=short_size;
  //  cout<<temp->starting_address<<endl;
    return temp;
}
	
//best fit
struct node_allocate *bestfit(struct node_free*headf1,struct node_allocate*heada1,int size,string name)
{
    struct node_allocate *temp1;
    struct node_free *temp=searchbestfit(&headf1,size);
    if(temp==NULL){
        cout<<"\nNo Block Found"<<endl;
        return NULL;
    }
    else{
    	temp1=create(temp->starting_address,size,name);
    	head_free=updatefreelist(&headf1,temp,size);
      // cout<<"after free update"<<endl;
      // cout<<headf1->starting_address<<"--"<<headf1->free_space<<endl;
       updateallocatedlist(&heada1,temp1);
      // cout<<heada1->starting_address;
       return heada1;
        
    }
}


int main()
{
    int choice;
    int size;
    string name;
    struct node_free *headf1=NULL;
    struct node_allocate *heada1=NULL; 
    struct node_allocate *b=nullptr;
    while(1){
        cout<<"MENU:"<<endl;
        cout<<"1.First Fit"<<endl;
        cout<<"2.DEAllocate"<<endl;
        cout<<"3.Best Fit"<<endl;
        cout<<"4.Exit"<<endl;
        cout<<"ENTER YOUR CHOICE:";
        cin>>choice;

        switch(choice){
         
         case 1:
             
                cout<<"Enter the size of the process:"<<endl;
                cin>>size;
                cout<<"Enter the name of the process:"<<endl;;
                cin>>name;
                heada1=allocate(headf1,heada1,size,name);
               // cout<<"after allocate"<<endl;
              //  cout<<head_free->free_space<<endl;
                headf1=head_free;
                cout<<"ALLOCATED LIST:";
                printlistallocated(heada1);
                cout<<endl;
                cout<<endl;
                cout<<endl;
                cout<<endl;
                cout<<"FREE LIST:"<<endl;
                cout<<endl;
                printlistfree(headf1);
                break;
         case 2:
            
              cout<<"ENTER THE PROCESS NAME"<<endl;
              cin>>name;
              cout<<"Enter the size of the process:"<<endl;
              cin>>size;
              deallocate(heada1,headf1,size,name);
              headf1=head_free;
              cout<<"ALLOCATED LIST:";
              printlistallocated(heada1);
              cout<<endl;
              cout<<endl;
              cout<<endl;
              cout<<endl;
                cout<<"FREE LIST:"<<endl;
              printlistfree(headf1);
              break;
         case 3:
              
                cout<<"Enter the size of the process:"<<endl;
                cin>>size;
                cout<<"Enter the name of the process:"<<endl;;
                cin>>name;
                heada1=bestfit(headf1,heada1,size,name);
                headf1=head_free;
                printlistallocated(heada1);
                printlistfree(headf1);
               // allocate(size,name);
               // printlistallocated();
                break;
          case 4:
                 exit(0);
                 break;
      

        }
    }
}

