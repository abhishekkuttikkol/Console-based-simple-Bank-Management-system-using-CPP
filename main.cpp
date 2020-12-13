#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
#include<iomanip>
#include<string>
#include<cstring>
#include<cstdlib>  
#include<sstream>
#include<time.h>				//time

using namespace std;

void temp_file_clear();	
void copy_content(string a,string b); 	
void number_system_put(int n1);
int number_system_get();	
string yearadd(string date1,int year) ;	
void user_menu(int);
void clrscr();
int display_all();
void delay();

void clrscr()
{
    cout << string( 100, '\n' );
}
    
class user 
{
	public:
	
	char fname[10],lname[10];
	string phone;
	string dob;

		user()
		{
			phone = '\0';
			dob = '\0';
		}
		~user()
		{}	
};

class Account : public user
{
	int accountNumber ;
	int passcode ;
	int balance;
	string type;
	public:
	Account()
	{
		accountNumber = 0;
		balance = 0;
		passcode = 0;
	}
	~Account(){}				//destroy the object
	
	void CurrentBalance(int);	//balance chack
	void createAccount(); 		//function for openning new account
	void showDetails(); 		//function for showing account details
	void searchDetails(int);	//function to search details of perticular user
	void delete_details();		//function for deleting record
	void update_details(int); 	//function for updating record
	void login_user(int,int);	//login function
	void add(int,int);          //Add Money
	void deduct(int,int);	 	//Deduct Money
	void viewTr(int); 			//view all transections 
	void fund_tr(int); 			//For tranfering fund between tow users
	
	
};

void Account :: login_user(int user, int pass)
{	
	int flag = 0;

	
	ifstream file_read("cus_details.txt" ,ios::in);
	while(!file_read.eof())
	{
		file_read >> fname;
		file_read >>lname;
		file_read >>phone;
		file_read >>dob;
		file_read >>type;
		file_read >>accountNumber;
		file_read >>passcode;
		file_read >>balance;
		if(file_read.eof())
		{
			break;
		}
		if(user == accountNumber && pass == passcode)
		{
			cout<<"\n Login sucessful !"<<endl;
			system("cls");
			user_menu(user);
			flag = 1;
		}
	}
	if(flag == 0 )
	{
		cout<<"\n User name & Passcode Not matched !"<<endl;
		delay();
	}
	file_read.close();
}

void Account :: createAccount()
{
	
	cout << "\n\tEnter your First name :";
	cin >>fname;
	cin.clear();

	cout << "\n\tEnter Last name :";
	cin >>lname;
	cin.clear();

	string temp_phone;
	cout << "\n\tEnter phone number :";
	cin >>temp_phone;
	cin.clear();
	if(temp_phone.length()==10)
	{
		phone = temp_phone;
		
	}
	else
	{
	
		while(temp_phone.length() != 10)
		{
			cout<<"phone number must be 10 digit\n";
			cout<<"\n input phone number:";
			cin >> temp_phone;
			phone = temp_phone;	
		}
	}

	
	
	cout << "\n\tEnter Date of Birth :";
	cin >>dob;
	cin.ignore();
	
	char atype ='\0';
	cout <<"\n\tSelect Account Type(Savings S/Other O) :";
	cin >>atype;
	if(tolower(atype) == 's' )
	{
		type = "SAVINGS";
	}
	else
	{
		type = "OTHER";
	}
	accountNumber = number_system_get();
	
	cout << "\n\t Your Account Number :"<<accountNumber;

	cout << "\n\t Enter 4 digit Passcode ::";
	cin >> passcode;
	
	cout <<"\n\t Enter Primary Balance :";
	cin >>balance;

	ofstream file("cus_details.txt",ios::out | ios :: app);
	file << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
	
	number_system_put(accountNumber);
	file.close();
}

void Account::viewTr(int user_no)
{
	
	int number,amount,flag = 0;
	string date,status;
	
	ifstream tr_file_read("transec.txt" ,ios::in);
	//cin.clear();
	cout<<"\n\t"<<"AccountNumber"<<" | "<<"Date"
	<<" | "<<"Amount"<<" | "<<"CR / DR "<<endl;
	
	while(tr_file_read)
	{
		tr_file_read >>number;
		tr_file_read >>date;
		tr_file_read >>amount;
		tr_file_read >>status;	
	if(tr_file_read.eof())
	{
		break;
	}

	if(user_no == number)
	{
		cout<<"\t"<<number<<" | "<<date<<" | "<<amount
				<<" | "<<status<<" | "<<endl ;
		flag  = 1;
	}
	
	
	}
	getch();
	cin.clear();
	cin.ignore();
	system("cls");
	if(flag != 1)
	{
		cout << "\n\tNo record found";	
		system("cls");
	}
	tr_file_read.close();
}

void Account::fund_tr(int user_no)
{
	int user2_no ,amt =0,flag = 0;
	char ans;
	
	cout <<"\nEnter Friends Account Number: ";
	cin >> user2_no;
	
	cout <<"\nEnter Amount : ";
	cin >> amt;
	
	string a = "cus_details.txt";
	string b = "temp.txt";
	char tr_date[9];
	
	Account();//constructor call to empty variables
	ifstream file_read("cus_details.txt" ,ios::in);
	ofstream file_temp("temp.txt",ios::out |ios::app);
	ofstream tr_write("transec.txt",ios::out | ios::app);
	while(!file_read.eof())
	{
		
	file_read >> fname;
	file_read >>lname;
	file_read >>phone;
	file_read >>dob;
	file_read >>type;
	file_read >>accountNumber;
	file_read >>passcode;
	file_read >>balance;
	
	if(file_read.eof())
	{
		break;
	}
	
	if(user2_no == accountNumber)
	{
		cout << "\nAccount Holder's name :"<<fname<< " "<<lname<<endl;
		cout<<"enter(Y/N): ";
		cin >>ans;
		
		if(ans == 'n')
		{
			flag = 1;
			break;
		}
		
		
			balance = balance + amt;
			_strdate(tr_date);

			file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
				<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
			
			tr_write<<accountNumber<<" "<<tr_date<<" "<<amt<<" "<<"CR"<<endl; 
			

	}	
	else
	{
			file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
			<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
	}
	
	}
	
	if(flag == 1)
	{
		cout <<"\n NO Account Found";
	}
	file_temp.close();
	file_read.close();
	copy_content(b,a);
	cout<<"\n\t Done ! Amount Added\n";
	temp_file_clear();
	
	//now time for deducting amount from main user
	deduct(user_no,amt);
	cout << "\n Money Successfully Transferd !";
	system("cls");	
}

void Account :: CurrentBalance(int user_no)
{
	Account();
	ifstream file_read("cus_details.txt" ,ios::in);
	while(file_read)
	{
		
	file_read >> fname;
	file_read >>lname;
	file_read >>phone;
	file_read >>dob;
	file_read >>type;
	file_read >>accountNumber;
	file_read >>passcode;
	file_read >>balance;

	if(file_read.eof())
	{
		break;
	}

	if(user_no == accountNumber)
	{
		
		cout<<"\n\tCurrent Balance           :"<<balance<<"/-RS.";
		cout<<"\n\n\n";
		getch();
		cin.clear();
		cin.ignore();
		system("cls");
	}
	
	
	}
	
	file_read.close();
}
void Account :: searchDetails(int user_no) 
{
	int ch;
	int flag = 0;
	Account();
	ifstream file_read("cus_details.txt" ,ios::in);
	while(file_read)
	{
		file_read >> fname;
		file_read >>lname;
		file_read >>phone;
		file_read >>dob;
		file_read >>type;
		file_read >>accountNumber;
		file_read >>passcode;
		file_read >>balance;

		if(file_read.eof())
		{
			break;
		}

		if(user_no == accountNumber)
		{
			cout<<"\n\tAccount Number is :"<<accountNumber;
			cout<<"\n\tName              :"<<fname<<" "<<lname;
			cout<<"\n\tPhone             :"<<phone;
			cout<<"\n\tDate of birth     :"<<dob;
			cout<<"\n\tAccount Type      :"<<type;
			cout<<"\n\tBalance           :"<<balance<<"/-RS.";
			cout<<"\n\n\n";
			flag  = 1;
			cout<<"\n\tPress Enter To continue...!";
			getch();
			cin.clear();
		 	cin.ignore();
		 	system("cls"); 
		}
	
	
	}
	if(flag != 1)
	{
		system("cls");
		cout << "\n\tNo record found";
		delay();
		
	}
	file_read.close();
	
}
void Account ::delete_details()
{
	char ch[10];
	char buff;
	int flag = 0;
	string a = "cus_details.txt";
	string b = "temp.txt";
	
	Account();
	ifstream file_read("cus_details.txt" ,ios::in);
	ofstream file_temp("temp.txt",ios::out |ios::app);
	cout <<"\n\tEnter name:";
	cin >>ch;
	cin.clear();
	
	while(!file_read.eof())
	{
		file_read >> fname;
		file_read >>lname;
		file_read >>phone;
		file_read >>dob;
		file_read >>type;
		file_read >>accountNumber;
		file_read >>balance;
	
		if(file_read.eof())
		{
			break;
		}
		if(strcmp(fname,ch) == 0)
		{
			cout <<fname<<" "<<lname<<"\t"<<dob<<"\t"<<phone<<"\t"<<type<<"\t"<<accountNumber<<"\t"<<balance<<endl;
			flag  = 1;
			break;
		}
		else{
			file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
			break;
		}
	
	}
	if(flag != 1)
	{
		cout << "\n\tNo record found";
		
	}
	file_temp.close();
	file_read.close();
	copy_content(b,a);
	
	cout<<"\n\t Done Account Is Removed !\n";
	temp_file_clear();
	getch();
	cin.clear();
	cin.ignore();
	system("cls");
	
}

void Account :: add(int user_no,int amt)
{
	string a = "cus_details.txt";
	string b = "temp.txt";
	char tr_date[9];
	
	Account();
	ifstream file_read("cus_details.txt" ,ios::in);
	ofstream file_temp("temp.txt",ios::out |ios::app);
	ofstream tr_write("transec.txt",ios::out | ios::app);
	while(!file_read.eof())
	{
		
	file_read >> fname;
	file_read >>lname;
	file_read >>phone;
	file_read >>dob;
	file_read >>type;
	file_read >>accountNumber;
	file_read >>passcode;
	file_read >>balance;
	
	if(file_read.eof())
	{
		break;
	}
	
	if(user_no == accountNumber)
	{
			balance = balance + amt;
			_strdate(tr_date);

			file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
				<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
			
			tr_write<<accountNumber<<" "<<tr_date<<" "<<amt<<" "<<"CR"<<endl; 

	}	
	else
	{
			file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
			<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
	}
	
	}
	
	file_temp.close();
	file_read.close();
	copy_content(b,a);
	cout<<"\n\t Done ! Amount Added\n";
	temp_file_clear();
	system("cls");
	
}
void Account :: deduct(int user_no,int amt)
{
	string a = "cus_details.txt";
	string b = "temp.txt";
	char tr_date[9];
	
	int flag = 0;
	Account();
	ifstream file_read("cus_details.txt" ,ios::in);
	ofstream file_temp("temp.txt",ios::out |ios::app);
	ofstream tr_write("transec.txt",ios::out | ios::app);
	while(!file_read.eof())
	{
		
	file_read >> fname;
	file_read >>lname;
	file_read >>phone;
	file_read >>dob;
	file_read >>type;
	file_read >>accountNumber;
	file_read >>passcode;
	file_read >>balance;
	
	if(file_read.eof())
	{
		break;
	}
	
	if(user_no == accountNumber)
	{
			if(balance != 0 && balance > amt)
			{
			
				balance = balance - amt;
				_strdate(tr_date); 

				file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
					<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
					
				tr_write<<accountNumber<<" "<<tr_date<<" "<<amt<<" "<<"DR"<<endl; 

				flag = 1;
			}
			else
			{
				
				cout<<"\nyour transection can not be completed balance is Zero or Less than withdrawal amount\n! ";
				file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
				<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
				system("cls");
			}
	}
		
	else
	{
			file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
			<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
	}
	
}
	
	file_temp.close();
	file_read.close();
	copy_content(b,a);
	if(flag == 1)
	{
		cout<<"\n\t Done ! Amount Deducted\n";
		getch();
		cin.clear();
		cin.ignore();
		system("cls");
		
	}
	
	temp_file_clear();
	
}

void Account ::update_details(int user_no)
{
	int ch;
	char buff;	
	int flag = 0;
	string a = "cus_details.txt";
	string b = "temp.txt";
	
	Account();
	ifstream file_read("cus_details.txt" ,ios::in);
	ofstream file_temp("temp.txt",ios::out |ios::app);
	
	while(!file_read.eof())
	{
		
	file_read >> fname;
	file_read >>lname;
	file_read >>phone;
	file_read >>dob;
	file_read >>type;
	file_read >>accountNumber;
	file_read >>passcode;
	file_read >>balance;
	
	if(file_read.eof())
	{
		break;
	}
	
	if(user_no == accountNumber)
	{
			cout <<"\n\tAccount Number is : "<<accountNumber;
			cout <<"\n\tFill up Details with new records :\n"<<endl;
			
			cout<<"\n\n\t New First name:";
			
			cin >>fname;
			cin.clear();
				
			cout <<"\n\t New Last name:";
			cin >> lname;
			cin.clear();
			
			cout <<"\n\t New  phone:";
			cin >> phone;
			cin.clear();
			
			cout <<"\n\t New Dob";
			cin >> dob;
			cin.clear();
			
			cout <<"\n\t Current Account Type:"<<type;
			cout <<"\n\t Change Type (Saving S/Other O) otherwiese press (N) :"<<endl;;
			char ans; 
			cin >> ans;
			cin.clear();
				if(tolower(ans) == 'n')
				{
				cout <<"\n\tOk !account type is not changed!\n "<<endl;
				}
				else if(tolower(ans) == 's')
				{
					type = "SAVING";
				}
				else
				{
					type = "OTHER";
				}
			file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
				<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
			flag  = 1;
	}	
	else
	{
			file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
			<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
	}
	
	}
	if(flag != 1)
	{
		cout << "\n\tNo record found"<<endl;
		system("cls");
		
	}
	file_temp.close();
	file_read.close();
	copy_content(b,a);
	
	cout<<"\n\t Done ! Details Updated .\n"<<endl;
	temp_file_clear();
	
}

void copy_content(string a,string b)
{
		char ch;
		int flag = 0;
	ifstream temp_read(a.c_str(),ios :: in);
	ofstream file_write(b.c_str(),ios::out);
	while(!temp_read.eof())
	{
		temp_read.get(ch);
		file_write.put(ch);
		flag = 1;
	}
	if(flag != 1)
	{
		cout <<"\n\tFile Error !";
	}
	
}

int number_system_get()
{
	int number;
	ifstream number_read("number.txt",ios::in);
	number_read >>number;
	return number;
}

void number_system_put(int n1)
{
	n1 = n1+1;
	ofstream number_write("number.txt",ios::out);	
	number_write <<n1;
}

void temp_file_clear()
{

	char ch;
	int flag = 0;
	ofstream temp_write("temp.txt",ios :: out);

	temp_write <<" ";
	temp_write.close();
	
}

string yearadd(string date1,int year)
{
	int add ;
	string date2;
	stringstream ss(date1.substr(6,4));
	 stringstream ss2(date1.substr(0,6));
	 stringstream ss3;
	 string s2; 
	 ss2 >> s2;
	 ss >> add;
	 add = add + year;
	 ss3 << add;
	 date2 = s2 + ss3.str();
	 
	 return date2;	 
}


void user_menu(int user_sesstion)
{
	int ch;
	int amount = 0;
	Account a;
	start:do{
		
		cout<<"\n\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2     		  |"<<endl;
		cout<<"\n\t 1.View Your Account.";
		cout<<"\n\t 2.Update Your Details.";
		cout<<"\n\t 3.Withdrawal.";
		cout<<"\n\t 4.Deposite Money.";
		cout<<"\n\t 5.Fund Transfer.";
		cout<<"\n\t 6.View Transfer Details";
		cout<<"\n\t 7.Close Account.";
		cout<<"\n\t 0.Exit";
			
		cout<<"\n\t Enter your Choice (1-7)::";
	if(cin >> ch)
	{
		
		
		switch (ch)
		{
			case 1:
				system("cls");
				a.searchDetails(user_sesstion);
				break;
				
			case 2:
				system("cls");
				a.update_details(user_sesstion);
				system("cls");
				break;
		
			case 3:
				system("cls");
				cout<<"\n\tEnter Amount to withdraw :";
				cin >> amount;
				
				a.deduct(user_sesstion,amount);
				break;
				
			case 4:
				system("cls");
				cout<<"\n\tEnter Amount to deposite :";
				cin >> amount;
				a.add(user_sesstion,amount);
				a.CurrentBalance(user_sesstion);
				break;
				
			case 5:
				system("cls");
				a.fund_tr(user_sesstion);
				break;
			
			case 6:
				system("cls");
				a.viewTr(user_sesstion);
				break;
				
			case 7:
				system("cls");
				a.delete_details();
				break;
				
			case 0:
					system("cls");
					break;
			
			default :
				system("cls");
				cout<<"\n\tWrong choice...! \n";
				delay();		
				break;
		}
	}
		else
		{
			cout<<"\n\t Invalid entry !";
			getch();
			cin.clear();
		 	cin.ignore();
			ch = 15;
		}
	

	}while(ch != 0);
	
}
int adminpanel()
{
	Account ad;
	int user_sesstion;
	int ch;
	start1:do
	{
		system("cls");
		cout<<"\n\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Admin Panel \xB2\xB2\xB2\xB2\xB2\xB2\xB2     		  |"<<endl;
		cout<<""<<endl;	
		cout<<"\n\t1.All account details. ";
		cout<<"\n\t2.Update account. ";
		cout<<"\n\t3.close an accouny. ";
		cout<<"\n\t0.Exit. ";
		cout<<"\n\tEnter your choice : ";
		cin>>ch;
		switch(ch)
		{
			case 1:
					system("cls");
					display_all();
					break;
					
			case 2:
					cout<<"\n\tEnter account number : ";
					cin>>user_sesstion;
					system("cls");
					ad.update_details(user_sesstion);
					break;
					
			case 3:
					system("cls");
					ad.delete_details();
					break;
			case 0:
					system("cls");
					break;
			default :
					system("cls");
					cout<<"\n\tInvalid Entry!..";
					delay();
					goto start1;
					break;
			
		}
	}while(ch!=0);
		
}

int display_all()
{
	string fname,lname,phone,dob,type,accountNumber,passcode,balance;
	Account();
	ifstream file_read("cus_details.txt" ,ios::in);
	cout<<"\n\t\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"===============================================================================\n";
	cout<<"A/c no.    	NAME 	          Type 	   Balance\n";
	cout<<"===============================================================================\n\n";
	while(file_read)
	{
	
		file_read >> fname;
		file_read >>lname;
		file_read >>phone;
		file_read >>dob;
		file_read >>type;
		file_read >>accountNumber;
		file_read >>passcode;
		file_read >>balance;

		if(file_read.eof())
		{
			break;
		}

	cout<<accountNumber<<setw(15)<<fname<<" "<<lname<<"\t"<<type<<"\t   "<<balance<<"\t\n\n";
	
	}
	
	cout<<"\nPress any key for exit..";
	getch();
	cin.clear();
	cin.ignore();
}

void animation1()               //welcome animation
{
clrscr();
for(int i=0;i<5;i++)
{
clrscr();

cout<<"\n\n\n\n\n";
cout<<"||            ||  ||=====   ||        ====      ====     ||\\  //||  ||======"<<endl;
cout<<" ||          ||   ||        ||      ==        ==    ==   || \\// ||  ||      "<<endl;
cout<<"  ||   ||   ||    ||====    ||      ==       ==      ==  ||     ||  ||====  "<<endl;
cout<<"   || |||| ||     ||        ||      ==        ==    ==   ||     ||  ||      "<<endl;
cout<<"    ||    ||      ||======  ||====    ====     =====     ||     ||  ||======"<<endl;
cout<<"\n\n\n \t\t\t\t\t\t  TO :- Bank Management System";
delay();
//for(long s=1; s<=20000000;s++);
clrscr();
cout<<"\n\n\n\n\n   \n\n\n\n\n";
cout<<"\n\n\n \t\t\t\t\t\t  TO :- Bank Management System";
for(long a=1; a<=20000000;a++);
}
}

int main()
{
	system("color 1f");
	animation1();
	int ch;
	int login_state = 0;
	int user;
	int pass;
	string userattempt;
	string passwordattempt;
	string username="admin";											//Admin Username
	string password="123";												//Admin Password
	Account a;
	do{
		system("cls");
		cout<<"\n\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Bank management System \xB2\xB2\xB2\xB2\xB2\xB2\xB2|"<<endl;
		cout<<""<<endl;
		
		cout <<"\n\t 1.Login To your Account.";
		cout <<"\n\t 2.Create An Account.";
		cout<<"\n\t 3.Admin panel.";
		cout <<"\n\t 0.Exit";
		
		cout<<"\n\n\tEnter your choice ::";
		if(cin >> ch )
		{
			switch (ch)
			{
				case 1:
					system("cls");
					cout << "\n\t Enter Account Number:";
					cin >>user;
					cout <<"\n\t Enter 4-digit password :";
					cin >>pass;
					system("cls");
					a.login_user(user,pass);
					break;
				case 2:
					system("cls");
					a.createAccount();
					break;
				
				case 3:
						system("cls");
						cout<<"\n\tEnter username for Admin : ";
						cin>>userattempt;
						if(username==userattempt)
						{
							cout<<"\n\tEnter password : ";
							cin>>passwordattempt;
							if(password==passwordattempt)
							{
									cout<<"Login successfully.";
									system("cls");
									adminpanel();
							}
							else
							{
									system("cls");
									cout<<"\n\tWrong Password...!";
									delay();
							}
						}
						else
						{
								system("cls");
								cout<<"\n\tInvalid Entry...!";
								delay();
						}
						break;
					}
		}
		else
		{
			system("cls");
			cout<<"\n\t Invalid entry ! Press Enter To continue";
			getch();
			cin.clear();
		 	cin.ignore();
			ch = 15 ;
		}
		

			
	}while(ch !=0);
	return 0;
}
void delay()
{
		for(int i=0;i<10000;i++)
			for(int j=0;j<10000;j++);
}

