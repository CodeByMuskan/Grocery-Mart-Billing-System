#include<iostream>
using namespace std;
const int size=8;
void registerCustomer(string &name, int &id, string &type, string &payment){
    cout<<"Enter Customer Name: ";
    cin>>name;
    cout<<"Enter Customer ID: ";
    cin>>id;
    cout<<"Enter Customer Type (Regular/Member): ";
    cin>>type;
    cout<<"Enter Payment Method (Cash/Card): ";
    cin>>payment;
}

int menu(){
    int choice;
    cout<<"===== MAIN MENU ====="<<endl;
    cout<<"1. View Grocery Items"<<endl;
    cout<<"2. Add Items to Cart"<<endl;
    cout<<"3. Calculate Bill"<<endl;
    cout<<"4. View Customer Details"<<endl;
    cout<<"5. Exit"<<endl;
    cout<<"Enter choice: ";
    cin>>choice;
    return choice;
}

void displayGrocery(string items[], float price[]){
    cout<<"========== GROCERY ITEMS =========="<<endl;
    for(int i=0; i<size; i++){
        cout<<i+1<<". "<<items[i]<<" - Rs. "<<price[i]<<endl;
    }
}

void addToCart(float price[], float &bill){
	cout<<"========== Add To Cart =========="<<endl;
    int item, quantity;
    cout<<"Enter Item Number: ";
    cin>>item;
    cout<<"Enter Quantity: ";
    cin>>quantity;
    if(item>=1 && item<=size){
        bill+=price[item-1]*quantity;
        cout<<"Item Added Successfully!"<<endl;
    }
    else{
        cout<<"Invalid Item Number!"<<endl;
    }
}

float calculateGross(float bill){
    return bill;
}

float calculateTax(float price[], float bill){
    float tax=0;
    for(int i=0; i<size; i++){
        if(i<7){
            tax+=price[i]*0.05; 
        } else{
            tax+=price[i]*0.10; 
        }
    }
    return tax;
}

float membershipDiscount(float bill, string type){
    if(type=="Member" || type=="member"){
        return bill*0.07;
    }
}

float billDiscount(float bill){
    if(bill>=10000){
        return bill*0.10;
    }
    else if(bill>=5000){
        return bill*0.05;
    }
}

float cardCharges(float bill, string payment){
    if(payment=="Card" || payment=="card"){
        return bill*0.02;
    }
    return 0;
}

float calculateLoyalty(float bill){
    return bill/100;
}

float redeemPoints(float totalPoints){
    int choice;
    cout<<"Press 1 to redeem loyalty points"<<endl;
    cout<<"Press 2 to continue: ";
    cin>>choice;
    if(choice==1){
        return totalPoints; 
    }
    return 0;
}

void showCustomer(string name, int id, string type, string payment){
    cout<<"Customer Name: "<<name<<endl;
    cout<<"Customer Type: "<<type<<endl;
    cout<<"Payment Method: "<<payment<<endl;
}

void showFinalBill(float gross, float tax, float memDis, float billDis, float card, float loyaltyUsed){
    float total=gross+tax+card-memDis-billDis-loyaltyUsed;
    cout<<"---------------------------------------"<<endl;
    cout<<"Total Payable Amount: Rs. "<<total<<endl;
    cout<<"Thank You For Shopping "<<endl;
    cout<<"---------------------------------------"<<endl;
}

int main(){
    string name, type, payment;
    int id;
    float existingLP;    
    registerCustomer(name, id, type, payment);
    string items[size]={"Rice 1 KG","Sugar 1 KG","Cooking Oil 1 Litre","Milk Pack","Tea Pack","Flour 5 KG","Eggs Dozen","Detergent"};
    float price[size]={350,180,580,220,450,950,320,600};
    float bill=0;
    int choice;
    do {
        choice=menu();
        switch(choice){
            case 1:
                displayGrocery(items, price);
                break;
            case 2:
                addToCart(price, bill);
                break;
            case 3:{
                float gross=calculateGross(bill);
                float tax=calculateTax(price, bill);
                float memDis=membershipDiscount(bill, type);
                float billDis=billDiscount(bill);
                float card=cardCharges(bill, payment);
                float currentLP=calculateLoyalty(bill);
                cout<<"Generated Loyalty Points: "<<currentLP<<endl;
                cout<<"Enter Your Existing Loyalty Points (Enter 0 if new): ";
                cin>>existingLP;
                float totalLP=currentLP+existingLP;
                cout<<"Loyalty Points after Purchase: "<<totalLP<<endl;
                float redeemValue=redeemPoints(totalLP);
                showFinalBill(gross, tax, memDis, billDis, card, redeemValue);
                break;
            }
            case 4:
                showCustomer(name, id, type, payment);
                break;
            case 5:
                cout<<"Program Ended!";
                break;
            default:
                cout<<"Invalid Choice!";
        }
    } while(choice!=5);
    return 0;
}
