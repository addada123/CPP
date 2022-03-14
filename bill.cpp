#include <iostream>
#include <fstream>

class shopping
{
    private:
        int pcode;
        float price;
        float discount;
        std::string pname;

    public:
        void menu();
        void administrator();
        void buyer();
        void add();
        void edit();
        void remove();
        void list();
        void receipt();

};

void shopping :: menu()
{
    int choice;
    std::string email;
    std::string password;

    std::cout<<"Hello\n";
    std::cout<<"1)Administration\n";
    std::cout<<"2)Buyer\n";
    std::cout<<"3)Exit\n";

    std::cin>>choice;

    switch (choice)
    {
    case 1:
        std::cout<<"Login\n";
        std::cout<<"Email; \n";
        std::cin>>email;
        std::cout<<"Password \n";
        std::cin>>password;
        if(email=="hi@gmail.com" && password=="hi"){
            administrator();
        }
        else{
            std::cout<<"invalid";
        }
    case 2:
    {
        buyer();
    }
    case 3:
    {
        exit(0);
    }
    }

}