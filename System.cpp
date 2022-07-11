#include<bits/stdc++.h>
using namespace std;

struct Node{
    string fooditem;
    int quantity;
    float price;
    int data;
    Node* prev;
    Node* next;
};

Node* headC = NULL ;
Node* tailC = NULL ;
Node* headA = NULL ;
Node* tailA = NULL ;
Node* headS;
Node* newnode;


void adminMenu(){
    cout<<"\n      1.View total sales"<<endl;
    cout<<"\n      2.Add new items in the order menu"<<endl;
    cout<<"\n      3.Delete items from the order menu"<<endl;
    cout<<"\n      4.Display order menu"<<endl;
    cout<<"\n      5.View total sales"<<endl;
    cout<<"      Enter your choice"<<endl;
}


void customerMenu(){
    cout<<"\n      1.Place your order"<<endl;
    cout<<"\n      2.View your ordered items"<<endl;
    cout<<"\n      3.Delete items from the order"<<endl;
    cout<<"\n      4.Display final bill"<<endl;
    cout<<"\n      5.Back to main menu"<<endl;
    cout<<"      Enter your choice"<<endl;
}

Node* createAdmin(Node* head,int data ,string fooditem,float price ){
    newnode = new Node();

    newnode->data = data;
    newnode->price = price;
    newnode->quantity= 0;
    newnode->fooditem = fooditem;
    newnode->next = NULL;
    newnode->prev = NULL;

    Node* temp = head;

    if(temp== NULL){
        headA = tailA = newnode;

    }
    else{
        while(temp->next!=NULL){
            temp=temp->next;

        temp->next=newnode;
        newnode->prev = tailA;
        tailA = newnode;

        }
    }

    return headA;

}


Node* createcustomer(Node* head,int data,int quantity){
    newnode = new Node();
    Node* temp1 = headA;
    int flag =0;
    while(temp1!=NULL){
        if(temp1->data==data){
            flag=1;
            break;
        }
        temp1=temp1->next;
    }
    if(flag==1){
        newnode->data =data;
        newnode->price = quantity*(temp1->price);
        newnode->quantity = quantity;
        newnode->fooditem = temp1->fooditem;
        newnode->next =NULL;
        newnode->prev = NULL;

        Node* temp = head;
        if(temp==NULL){
            headC = tailC = newnode;
        }
        else{
            while(temp->next!=NULL){
                temp=temp->next;
            }
            temp->next = newnode;
            newnode->prev = tailC;
            tailC = newnode;
        }


    }
    else{
        printf("\n\t\t\t\t\t\t\tThis item is not present in the menu!\n");
    }
    return headC;
}

void displayList(Node* head){
    Node* temp1 =head;
    if(temp1==NULL){
        printf("\n\t\t\t\t\t\t\t\tList is empty!!\n\n");
    }
    else{
        printf("\n");
        while(temp1!=NULL){
            if(temp1->quantity==0){
                 printf("\t\t\t\t\t\t\t%d\t%s\t%0.2f\n",temp1->data,temp1->fooditem,temp1->price);
            }
            else{
                printf("\t\t\t\t\t\t\t%d\t%s\t%d\t%0.2f\n",temp1->data,temp1->fooditem,temp1->quantity,temp1->price);
            }
            temp1=temp1->next;
        }
        printf("\n");
    }
}


Node* totalSales(int data,int quantity){
    newnode = new Node();
    int flag =0 ;
    Node* temp1 = headA;
    while(temp1->data!=data){
        temp1 = temp1->next;
    }

    newnode->data = data;
    newnode->price = quantity*(temp1->price) ;
    newnode->quantity = quantity;
    newnode->fooditem = temp1->fooditem;
    newnode->next = NULL;
    newnode->prev = NULL;

    Node* temp = headS;
    if(temp==NULL){
        headS = newnode;
    }
    else{
        while(temp->next!=NULL){
            if(temp->data==data){
                flag=1;
                break;
            }
            temp=temp->next;
        }
        if(flag==1){
            temp->quantity += newnode->quantity;
            temp->price += newnode->price;
        }
        else{
            temp->next=newnode;
        }
    }
    return headS;
}

void calculateTotalSales(){
    Node* temp= headC;
    while(temp!=NULL){
        headS = totalSales(temp->data,temp->quantity);
        temp=temp->next;
    }
}


Node* Delete(int data,Node* head,Node* tail){
      if(head=NULL){
         printf("\n\t\t\t\t\t\t\tList is empty\n");
      }
      else{
        Node* temp;
        if(data == head->data){
            temp = head;
            head = head->next;
            if(head != NULL){
                head->prev = NULL;
            }
            delete(temp);
        }
        else if(data == tail->data){
            temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            delete(temp);
        }
        else{
            temp = head;
            while(data!=temp->data){
                temp=temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            delete(temp);
        }
      }
      return head;
} 


int deleteAdmin(){
     printf("\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ");
    int n;
    cin>>n;

    Node* temp = headA;
    while(temp!=NULL){
        if(temp->data == n){
            headA = Delete(n,headA,tailA);
            return 1 ;
        }
        temp=temp->next;
    }
    return 0;
}

int deleteCustomer(){
    printf("\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ");
    int n;
    cin>>n;

    Node* temp = headC;
    while(temp!=NULL){
        if(temp->data == n){
            headC = Delete(n,headC,tailC);
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void displaybill(){
    displayList(headC);
    Node* temp = headC;
    float totalPrice = 0;
    while(temp!=NULL){
        totalPrice += temp->price;
        temp = temp->next;
    }
    printf("\t\t\t\t\t\t\tTotal price: %0.02f\n",totalPrice);
}

Node* DeleteList(Node* head){
    if(head==NULL){
        return NULL;
    }
    else{
        Node* temp = head;
        while(temp->next!=0){
            temp = temp->next;
            delete(temp->prev);
        }
        delete(temp);
        head = NULL;
    }
    return head;
}

void admin_login(){
     printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    ADMIN SECTION\n");
    printf("\t\t\t\t\t   ----------------------------------------------\n");
    while(1){
        adminMenu();
        int option;
        cin>>option;

        if(option==5){
            break;
        }
        switch (option){
            case 1:
            displayList(headS);
            break;
            case 2:
            printf("\n\t\t\t\t\t\t\tEnter serial no. of the food item: ");
            int n;
            int flag =0;
            char name[50];
            float price;
            cin>>n;
            Node* temp = headA;
            while(temp!=NULL){
                if(temp->data == n){
                    printf("\n\t\t\t\t\t\tFood item with given serial number already exists!!\n\n");
                     flag=1;
                     break;               
                }
                temp=temp->next;
            }

            if(flag==1)
                break;
            printf("\t\t\t\t\t\t\tEnter food item name: ");
                cin>>name;
                printf("\t\t\t\t\t\t\tEnter price: ");
                cin>>price;
                headA = createAdmin(headA, n, name, price);
                printf("\n\t\t\t\t\t\t\tNew food item added to the list!!\n\n");
                break;
            
            case 3:
            if(deleteAdmin()){
                printf("\n\t\t\t\t\t\t### Updated list of food items menu ###\n");
                displayList(headA);
            }
            else
                printf("\n\t\t\t\t\t\tFood item with given serial number doesn't exist!\n\n");
                 break;
            case 4:
                printf("\n\t\t\t\t\t\t\t   ### Order menu ###\n");
                displayList(headA);
                break;
            
            default:
             printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
                break;

        }

    }

}

void customer_login(){
    int flag=0,j=1;
    string ch;
    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    CUSTOMER SECTION\n");
    printf("\t\t\t\t\t   ----------------------------------------------\n");
    while(1){
        customerMenu();

        int option;
        cin>>option;
        if(option==5){
            break;
        }
        switch (option){
           case 1:
                displayList(headA);
                printf("\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ");
                int n;
                cin>>n;
                printf("\t\t\t\t\t\tEnter quantity: ");
                int quantity;
                cin>>quantity;
                headC = createcustomer(headC, n, quantity);
                break;
            case 2:
                printf("\n\t\t\t\t\t\t\t  ### List of ordered items ###\n");
                displayList(headC);
                break;
            case 3:
                if(deleteCustomer())
                {
                    printf("\n\t\t\t\t\t\t### Updated list of your ordered food items ###\n");
                    displayList(headC);
                }
                else
                    printf("\n\t\t\t\t\t\tFood item with given serial number doesn't exist!!\n");
                break;
            case 4:
                calculateTotalSales();
                printf("\n\t\t\t\t\t\t\t  ### Final Bill ###\n");
                displaybill();
                headC = DeleteList(headC);
                printf("\n\t\t\t\t\t\tPress any key to return to main menu:\n\t\t\t\t\t\t");
                fflush(stdin);
                ch=fgetc(stdin);
                flag=1;
                break;

            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
                break;
        }
        if(flag==1)
            break; 
        }
    }








void mainMenu() {

    printf("\n                                 --------------------------------------------------------------------------\n");
    printf("                                                     WELCOME TO RESTAURANT MANAGEMENT SYSTEM\n");
    printf("                                 -------------------------------------------------------------------------------\n\n\n");
    printf("\t\t\t\t\t\t\t1. ADMIN SECTION--> \n");
    printf("\t\t\t\t\t\t\t2. CUSTOMER SECTION--> \n");
    printf("\t\t\t\t\t\t\t3. EXIT--> \n\n");
    printf("\t\t\t\t\t\t\tEnter Your Choice --->");
}








int main(){

    headA = createAdmin(headA,1,"Hot and Sour Soup",100);
    headA = createAdmin(headA,2,"Manchow Soup",200);
    headA = createAdmin(headA,3,"Manchurian Noodles",150);
    headA = createAdmin(headA,4,"Fried Rice",180);
    headA = createAdmin(headA,5,"Hakka Noodles",80);

    while(1)
    {
        mainMenu();
        int choice;
        scanf("%d",&choice);

        if(choice==3)
        {
            printf("\n\n\t\t\t\t\t\t\t**********Thank you!!**********\n");
            break;
        }

        switch (choice)
        {
            case 1:
                admin_login();
                break;
            case 2:
                customer_login();
                break;
            case 3:
                break;

            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
                break;
        }
    }







}























