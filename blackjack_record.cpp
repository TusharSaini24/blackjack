#include<iostream>
#include<cstring>
#include<ctime>
using namespace std;
class BLACKJACKRECORD
{
	private :
		char player_name[50];
		int bet;
		double amountleft;
		int result;
		int year;
		int month;
		int date;
		int day;
		int time[2];
		
	public :
	    void Display_Record();
		char * Get_Player_Name();
		char * Set_Player_Name(char pn[] );
		int Get_Bet();
		int Set_Bet(int b);
		int Get_AmountLeft();
		int Set_AmountLeft( int al );
		int Get_Result();
		int Set_Result(int r );
		int Get_Year()
		{
			return year;
		}
		int Set_Year(int y)
		{
			year = y;
			return year;
		}
		int Get_Month()
		{
			return month;
		}
		int Set_Month(int m)
		{
			month = m;
			return month;
		}
		int Get_Date()
		{
			return date;
		}
		int Set_Date(int dt)
		{
			date = dt;
			return date;
		}
		int Get_Day()
		{
			return day;
		}
		int Set_Day(int d)
		{
			day = d;
			return day;
		}
		int * Get_Time()
		{
			return time;
		}
		int * Set_Time(int *t)
		{
			time[0]=t[0];
			time[1]=t[1];
			return time;
		}
};

void Days(int day)
{
	if(day == 1)
	{
		cout<<" Mon";
	}
	if(day == 2)
	{
		cout<<" Tue";
	}
	if(day == 3)
	{
		cout<<" Wed";
	}
	if(day == 4)
	{
		cout<<" Thur ";
	}
	if(day == 5)
	{
		cout<<" Fri ";
	}
	if(day == 6)
	{
		cout<<" Sat ";
	}
	else if(day == 7)
	{
		cout<<" Sun ";
	}
}

void BLACKJACKRECORD :: Display_Record()
{
	cout<<endl;
	
	cout.width(10);
	cout<<bet;
	cout.width(10);
	cout<<amountleft;
	cout.width(15);
	if(result==1)
	{
		cout<<" Won ";
	}
	else if(result==0)
	{
		cout<<" Tie ";
	}
	else
	{
		cout<<" Lose ";
	}
	cout.width(5);
	cout<<time[0]<<":"<<time[1];
	cout.width(7);
	Days(day);
	cout.width(7);
	cout<<date;
	cout<<"-"<<month;
	cout<<"-"<<year;
	cout<<endl;
}

char* BLACKJACKRECORD :: Get_Player_Name()
{
	return player_name;
}
char* BLACKJACKRECORD :: Set_Player_Name(char pn[])
{
	strcpy(player_name,pn);
	return player_name;
}
int BLACKJACKRECORD::Get_Bet()
{
	return bet;
}
int BLACKJACKRECORD::Set_Bet(int b)
{
	bet = b;
	return bet;
}
int BLACKJACKRECORD :: Get_AmountLeft()
{
	return amountleft;
}
int BLACKJACKRECORD :: Set_AmountLeft(int al)
{
	amountleft = al;
	return al;
}
int BLACKJACKRECORD :: Get_Result()
{
	return result;
}
int BLACKJACKRECORD :: Set_Result( int r )
{
	result = r;
	return result;
}
