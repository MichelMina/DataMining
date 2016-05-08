#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED
#include <ctime>
#include <string>
#include <cstdlib>
#define Male 0
#define Female 1
#define _18To25 1
#define _26To40 2
#define _41To60 3
#define Above60 4
#define Cairo 0
#define Giza 1
#define Alex 2
#define Other 3
#define Cash 0
#define CreditCard 1
#define DebitCard 2
#define Paypal 3
#define Poor 0
#define Average 1
#define Good 2
#define Excellent 3
#define TVs 1
#define Computers 2
#define Mobiles 3
#define HomeAppliance 4
#define gadgets 5


using namespace std;

class customer
{
    private:
        char agecategory, interrest, User_Rating;
        char Location,Gender, Payment_method;
		long long IDs;
    public:
		customer() {
			agecategory = 0;
			interrest = 0;
			User_Rating = 0;
			Location = 0;
			Gender = 0;
			Payment_method = 0;
			IDs = 0;
		}
		customer(string ID, string genderr, string counteryy, string payment, string interestt) {
        	agecategory = -1;
			interrest = atoi(interestt.c_str());
			IDs = atoi(ID.c_str());
        	User_Rating = -1;
			Location = atoi(counteryy.c_str());
			Gender = atoi(genderr.c_str());
			Payment_method = atoi(payment.c_str());
        }
        customer(string ID,string agecat,string genderr, string counteryy, string payment, string rating, string interestt)
        {
            IDs=atoi(ID.c_str());
            agecategory = atoi(agecat.c_str());
            Gender=atoi(genderr.c_str());
            Location = atoi(counteryy.c_str());
            Payment_method = atoi(payment.c_str());
            User_Rating = atoi(rating.c_str());
            interrest= atoi(interestt.c_str());
            /*TODO append file*/
        }
        bool random_customer()
        {
        	agecategory = (rand()%4)+1;
			Gender=rand()%2;
			Location = rand()%4;
			Payment_method = rand()%4;
			User_Rating = rand()%6;
			interrest= (rand()%5)+1;

			return true;

        }

		void set_age(char a) { agecategory = a; };
		void set_interrest(char in) { interrest = in; };
		void set_ID(long long I) { IDs = I; };
		void set_gender(char g) { Gender = g; };
		void set_location(char loc) { Location = loc; };
		void set_payment_method(char P) { Payment_method = P; };
		void set_user_rating(char UR) { User_Rating = UR; };

        char get_age(){return agecategory;}
        char get_interrest(){return interrest;}
        long long get_ID(){return IDs;}
        char get_gender(){return Gender;}
        char get_Location(){return  Location;}
        char get_payment_method(){return Payment_method;}
        char get_user_rating(){return User_Rating;}


};


#endif // CLASS_H_INCLUDED
