#include "admin.h"

void Admin::add_data()
{
	ofstream out("sdm_dat.csv", ios_base::app);
	if (out.is_open())
	{
        Student student;
		vector<string> temp;
		cin.ignore();
		adds(5,5);
		cout << "ENTER STUDENT'S DETAILS-" << endl;
		adds(5);
		cout << "------------------------\n"<< endl;
		adds(5,1);
		cout << "STUDENT ID.: ";
		getline(cin, student.id);
		if (file.find(student.id) != file.end())
		{
			adds(5, 1);
			cout << "ID " << student.id << " ALREADY EXISTS." << endl;
			return;
		}
		temp.push_back(student.id);
		adds(5,1);

		cout << "NAME: ";
		getline(cin, student.name);
		temp.push_back(student.name);
		adds(5,1);

		cout << "COURSE: ";
		getline(cin, student.course);
		temp.push_back(student.course);
		adds(5,1);

		cout << "DEPARTMENT: ";
		getline(cin, student.dep);
		temp.push_back(student.dep);
		adds(5,1);

		do{
			cout << "GENDER[M/F/Other]: ";
			cin >> student.gender;
			adds(5,1);
		}while(student.gender!="M" && student.gender!="F" && student.gender!="Other" && student.gender!="m" && student.gender!="f" && student.gender!="other");
		temp.push_back(student.gender);

		cout << "AGE: ";
		cin >> student.age;
		cin.ignore();
		temp.push_back(student.age);
		adds(5,1);

		cout << "PHONE No.: ";
		cin >> student.ph_no;
		temp.push_back(student.ph_no);

		out << student.id << "," << student.name << "," << student.course << "," << student.dep << "," << student.gender << "," << student.age << "," << student.ph_no << endl;
		out.close();
		file.insert({temp[0], temp});
	}
	else
	{
		cout << "Can't open file" << endl;
		exit(1);
	}
}

void Admin::delete_data()
{
	string str;
	adds(5, 5);
	cin.ignore();
	cout << "ENTER THE STUDENT ID TO DELETE : ";
	getline(cin, str);
	if (file.find(str) == file.end())
	{
		adds(5, 1);
		cout << "NO RECORD FOR STUDENT ID \"" << str << "\" EXISTS.\n"
			<< endl;
		return;
	}
	if (file.erase(str))
	{
		write_dat();
		adds(5, 1);
		cout << "STUDENT ID \"" << str << "\" RECORDS DELETED SUCCESSFULLY.\n"
			<< endl;
		return;
	}
	adds(5, 1);
	cout << "FACING SOME UNKNOWN PROBLEM, PLEASE TRY AGAIN.\n"
		<< endl;
}

void Admin::update_data()
{
	string id,val;
	vector<string> temp;
	char ch;
	adds(5,5);
	cin.ignore();
	cout<<"ENTER THE STUDENT ID TO UPDATE: ";
	getline(cin,id);
	if(file.find(id)==file.end())
	{
		adds(5,1);
		cout<<"NO RECORD FOR STUDENT ID \""<<id<<"\" EXISTS.\n"<<endl;
		return;
	}
	temp=file.at(id);
	do{
		system("clear");
		print_label(4);
		adds(8,3);
		cout<<"|| UPDATING STUDENT ID \""<<id<<"\" RECORDS. ||"<<endl;
		adds(0, 3);
		cout << "ID";
		adds(5);
		cout << "NAME";
		adds(5);
		cout << "COURSE";
		adds(3);
		cout << "DEPARTMENT";
		adds(3);
		cout << "GENDER";
		adds(2);
		cout << "  AGE";
		adds(2);
		cout << " PH_No." << endl;
		for (int i = 0; i < tot + 12; i++)
			cout << "-";
		cout << "\n"
			 << endl;
			print(temp);
		for (int i = 0; i < tot + 12; i++)
			cout << "-";
		cout << "\n"
			 << endl;

		adds(5,3);
		cout<<"UPDATE =>";
		adds(1);cout<<"1. NAME";
		adds(1);cout<<"2. COURSE";
		adds(1);cout<<"3. DEPARTMENT";
		adds(1);cout<<"4. GENDER";
			adds(1);cout<<"5. AGE";
		adds(1);cout<<"6. PHONE No.";
		adds(5,2);
		cout<<"RETURN =>";
		adds(1);cout << "7. UPDATE & RETURN";adds(1);cout << "8. ABORT ALL CHANGES & RETURN"<<endl;
		adds(5,2);
		cout<<"ENTER YOUR CHOICE: ";
		cin>>choice;
		cin.ignore();
		adds(5,2);
		if(choice>='1' && choice<='6')
			cout<<"ENTER NEW VALUE FOR- "<<endl;
		adds(5,1);
		switch(choice)
		{
			case '1':
				cout<<"NAME: ";
				getline(cin,val);
				temp[1]=val;
				break;
			case '2':
				cout<<"COURSE: ";
				getline(cin,val);
				temp[2]=val;
				break;
			
			case '3':
				cout<<"DEPARTMENT: ";
				getline(cin,val);
				temp[3]=val;
				break;
			
			case '4':
				do{
					cout<<"GENDER(M/F/Other): ";
					getline(cin,val);
				}while(val!="M" && val!="m" && val!="F" && val!="f" && val!="Other" && val!="other");
				temp[4]=val;
				break;

			case '5':
				cout<<"AGE: ";
				cin>>val;
				cin.ignore();
				temp[5]=val;
				break;
			
			case '6':
				cout<<"PHONE No.: ";
				cin>>val;
				cin.ignore();
				temp[6]=val;
				break;

			case '7':
				break;

			case '8':
				adds(5,1);
				cout<<"ALL CHANGES ABORTED. RECORDS OF \""<<id<<"\" NOT EFFECTED."<<endl;
				return;
			
			default:
				cout<<"INVALID CHOICE FROM GIVEN OPTIONS."<<endl;
		}
			if(choice=='7')
				break;
			val.clear();
			adds(5,1);
			cout<<"UPDATE MORE VALUES?(Y/N): ";
			cin>>ch;
			cin.ignore();
	}while(ch=='Y' || ch=='y');
	file.at(id)=temp;
	write_dat();
	adds(5,1);
	cout<<"\""<<id<<"\" RECORDS UPDATED SUCCESSFULLY."<<endl;
}

void Admin::load_dat()
{
	in.open("sdm_dat.csv", ios::binary | ios::in);
	if (!in.is_open())
	{
		out.open("sdm_dat.csv");
		if (out.is_open())
		{
			out.close();
			return;
		}
		cout << "SOME PROBLEM OCCURED WHILE OPENING THE DATAFILE." << endl;
		exit(1);
	}
	string str;
	while (getline(in, str))
	{
		vector<string> line;
		line = split(str);
		file.insert({line[0], line});
		//		for(auto it:file[line[0]])
		//			cout<<it<<" ";
		//		cout<<endl;
		//	print(line);
		//	print(file[line[0]]);
	}
	in.close();
}

void Admin::write_dat()
{
	ofstream tmp;
	tmp.open(".tmp_dat.csv", ios::binary | ios::out);
	for (auto it : file)
	{
		vector<string> line = it.second;
		string last = line.back();
		for (auto str : line)
		{
			if(str == last)
				tmp << str << endl;
			else
				tmp << str << ",";
		}
	}
	tmp.close();
	remove("sdm_dat.csv");
	rename(".tmp_dat.csv", "sdm_dat.csv");
}

void Admin::view_data()
{
	if(file.empty())
	{
		adds(5, 5);
		cout << "NO RECORDS TO SHOW, DATAFILE IS EMPTY.\n"
			<< endl;
		return;
	}
	//	string str, s = "            ";
	adds(0, 5);
	cout << "ID";
	adds(5);
	cout << "NAME";
	adds(5);
	cout << "COURSE";
	adds(3);
	cout << "DEPARTMENT";
	adds(3);
	cout << "GENDER";
	adds(2);
	cout << "  AGE";
	adds(2);
	cout << " PH_No." << endl;
	for (int i = 0; i < tot + 12; i++) cout << "-";
	cout << "\n"<< endl;
	for (auto it : file)
		print(it.second);
	for (int i = 0; i < tot + 12; i++) cout << "-";
	cout << "\n"<< endl;
}

void Admin::print(vector<string> &line)
{
	for (int i = 0; i < line.size(); i++)
	{
		cout << line[i];
		int n = abs(int(sp[i] - line[i].size()));
		for (int j = 0; j < n; j++)
			cout << " ";
	}
	cout << "\n"
		<< endl;
}

vector<string> Admin::split(string str)
{
	string s;
	vector<string> temp;
	for (int i = 0; i < str.length(); i++)
	{
		if(str[i] != ',')
			s.push_back(str[i]);
		else
		{
			temp.push_back(s);
			s.clear();
		}
	}
	temp.push_back(s);
	return temp;
}

void Admin::menu()
{
	char ch;
	do
	{
		system("clear");
		print_label(0);
		adds(s2, 2);
		cout << "1. ADD STUDENT RECORD\n\n";
		adds(s2);
		cout << "2. VIEW RECORDS\n\n";
		adds(s2);
		cout << "3. DELETE STUDENT RECORD\n\n";
		adds(s2);
		cout << "4. UPDATE RECORD\n\n";
		adds(s2);
		cout << "5. EXIT\n\n"
			<< endl;
		adds(s2);
		cout << "ENTER YOUR CHOICE: ";
		cin >> choice;

		switch (choice)
		{
			case '1':
				do
				{
					system("clear");
					print_label(1);
					add_data();
					adds(5, 2);
					cout << "ADD MORE RECORDS?(Y/N): ";
					cin >> ch;
				} while (ch != 'n' && ch != 'N');
				//			load_dat();
				break;
			case '2':
				system("clear");
				print_label(2);
				view_data();
				break;
			case '3':
				system("clear");
				print_label(3);
				delete_data();
				break;
			case '4':
				system("clear");
				print_label(4);
				adds(5, 1);
				update_data();
				break;
			case '5':
				break;
			default:
				adds(s2, 1);
				cout << "INVALID CHOICE. " << endl;
		}
		if(choice == '5')
			break;
		//		cin.ignore();
		adds(5, 1);
		cout << "RETURN TO MAIN MENU?(Y/N) : ";
		cin >> ch;
	} while (ch != 'n' && ch != 'N');
}

Admin::Admin()
{
	load_dat();
	tot = 0;
	for (auto it : sp) tot += it;
	menu();
}

// Admin::~Admin()
//{
//	adds(5,1);
//	cout<<"ADMIN LOGGING OUT. "<<endl;
//}

void Admin::adds(int t, int n)
{
	t = t * 4;
	for (int i = 0; i < n; i++)
		cout << "\n";
	for (int i = 0; i < t; i++)
		cout << " ";
}
