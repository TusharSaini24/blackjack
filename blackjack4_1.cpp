#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include"blackjack_record.cpp"

using namespace std;

//class CARDS;

enum Suit
{
	HEART,SPADE,DIAMOND,CLUB
};

enum Person 
{
	player,dealer,foldeddealer
};


// This class represent the all the properties that a card possess
class CARDS
{
	private :
	    int face;
		Suit suit;
	public :
	    int Get_Rank(int face );
		void Display_Face(int face );
		void Display_Suit(Suit suit);
		int Set_Face(int face);
		Suit Set_Suit(Suit suit);
		int Get_Face()
		{
			return face;
		}
		Suit Get_Suit()
		{
			return suit;
		}
		
};
// to calculate the rank of the cards 
int CARDS :: Get_Rank(int face )
{
	if(face > 10)
	{
		return 10;
	}
	return face;
}
// display the face value of the cards

void CARDS :: Display_Face(int face)
{
	if(face == 1)
	{
		cout<<"ACE";
	}
	else if(face == 11)
	{
		cout<<"JACk";
	}
	else if(face == 12)
	{
		cout<<"QUEEN";
	}
	else if(face ==13)
	{
		cout<<"KING";
	}
	else
	{
	    cout<<face;	
	}
}
// displaying the suit value of the cards
void CARDS :: Display_Suit(Suit suit)
{
	if(suit == HEART)
	{
		cout<<"HEART";
	}
	else if(suit == SPADE)
	{
		cout<<"SPADE";
	}
	else if(suit == DIAMOND)
	{
		cout<<"DIAMOND";
	}
	else if(suit == CLUB)
	{
		cout<<"CLUB";
	}
}
int CARDS :: Set_Face(int face)
{
	this->face = face;
	return this->face;
}
Suit CARDS :: Set_Suit(Suit suit)
{
	this->suit = suit;
	return this->suit;
}

// now preparing and shuffling of deck 

class DECK                 
{
	private :
		CARDS cards[52];
		int top_index;
	public :
	    
	    void PrepareDeck();
		int Get_Top_Index()
		{
			return top_index;
		}
		int Set_Top_Index(int top)
		{
			top_index = top;
			return top_index;
		}
		int Get_Card_Face_Value(int top)
		{
			return cards[top].Get_Face();
		}
		Suit Get_Card_Suit_Value(int top)
		{
			return cards[top].Get_Suit();
		}
};


void DECK::PrepareDeck()
{
	int deck_index=0;
	// prepare deck to cards
	for(int face=1;face<=13;face++)
	{
		cards[deck_index].Set_Face(face);
		cards[deck_index].Set_Suit(HEART);
		deck_index++;
		cards[deck_index].Set_Face(face);
		cards[deck_index].Set_Suit(CLUB);
		deck_index++;
		cards[deck_index].Set_Face(face);
		cards[deck_index].Set_Suit(SPADE);
		deck_index++;
		cards[deck_index].Set_Face(face);
		cards[deck_index].Set_Suit(DIAMOND);
		deck_index++;
	}
	srand(time(NULL));
	
	int swap_index,temp_face;
	Suit temp_suit;
	// shuffling the cards 
	for(int index=1;index<=1000;index++)
	{
		swap_index=rand()%52;
		temp_face=cards[0].Get_Face();
		cards[0].Set_Face(cards[swap_index].Get_Face());
		cards[swap_index].Set_Face(temp_face);
		
		temp_suit=cards[0].Get_Suit();
		cards[0].Set_Suit(cards[swap_index].Get_Suit());
		cards[swap_index].Set_Suit(temp_suit);
	}
	top_index =0;
}

// PLAYER class represent the all the properities of player and DEALER class represent properties of dealer as both dealer and player have all most same properties 
// so DEALER class  is child of PLAYER class

class PLAYER
{
	protected :
	    int player_index;
		int playercardface[12];
		Suit playercardsuit[12];
		
		DECK deckobject;
	public :
		int Get_Player_Index()
		{
			return player_index;
		}
		int Set_Player_Index( int player_index )
		{
			this->player_index = player_index;
			return this->player_index;
		}
	    void Call_Prepare_Deck()
		{
			deckobject.PrepareDeck();
		}
		/*int Get_Player_Card_Face()
		{
			return playercardface;
		}
		Suit Set_Player_Card_Suit( Suit playercardsuit)
		{
			this->playercardsuit = playercardsuit;
			return this->playercardsuit;
		}
		Suit Get_Player_Card_Suit()
		{
			return playercardsuit;
		}
		int Set_Player_Card_Face( int playercardface)
		{
			this->playercardface = playercardface;
			return this->playercardface;
		}*/
};


class DEALER : public  PLAYER
{
	private :
	   int dealer_index;
	   int dealercardface[12];
	   Suit dealercardsuit[12];
	   
	   CARDS card;
	public :
	   void Pick_Cards( Person picking_card_for );
	   int Calculate_Rank_of_Cards( Person calculating_rank_for );
	   void Display_Cards( Person display_card_for );
	   int Get_Dealer_Index()
	   {
		   return dealer_index;
	   }
	   int Set_Dealer_Index( int dealerindex)
	   {
		   dealer_index = dealerindex;
		   return dealer_index;
	   }
};

void DEALER :: Pick_Cards( Person picking_card_for )
{
	// picking card for player
	if(picking_card_for == player)
	{
		player_index++;
		playercardface[player_index]=deckobject.Get_Card_Face_Value( deckobject.Get_Top_Index());
		playercardsuit[player_index]=deckobject.Get_Card_Suit_Value( deckobject.Get_Top_Index());
		deckobject.Set_Top_Index( deckobject.Get_Top_Index()+1);
	}
	// picking card for dealer
	else if(picking_card_for == dealer)
	{
		dealer_index++;
		dealercardface[dealer_index]=deckobject.Get_Card_Face_Value( deckobject.Get_Top_Index());
		dealercardsuit[dealer_index]=deckobject.Get_Card_Suit_Value( deckobject.Get_Top_Index());
		deckobject.Set_Top_Index( deckobject.Get_Top_Index()+1);
	}
}

int DEALER :: Calculate_Rank_of_Cards( Person calculating_rank_for )
{
	int total = 0;
	// calculating rank for player cards
	if(calculating_rank_for == player)
	{
		
		bool ace_found = false;
		for( int index = 0; index <= player_index; index++ )
		{
			total += card.Get_Rank( playercardface[index] );
			if( playercardface[index] == 1 )
			{
				ace_found = true;
			}
		}
		if( ace_found && total + 10 <= 21 )
		{
			total += 10;
		}
	}
	// calculating rank for dealer unfolded cards
	else if(calculating_rank_for == dealer)
	{
			bool ace_found = false;
		for(int index=0;index<=dealer_index;index++)
		{
			total=total+card.Get_Rank(dealercardface[index]);
			if(card.Get_Rank(dealercardface[index])==1)
			{
				ace_found=true;
			}
		}
		if(ace_found&&total+10<=21)
		{
			total+=10;
		}
	}
	// calculating rank for dealer folded cards
	else
	{
		bool ace_found = false;
		for(int index=0;index<=dealer_index;index++)
		{
			if(index!=0)
			{
				total=total+card.Get_Rank(dealercardface[index]);
				if(card.Get_Rank(dealercardface[index])==1)
				{
					ace_found=true;
				}
			}
		}
		if(ace_found&&total+10<=21)
		{
			total+=10;
		}
	}
	return total;
}

void DEALER::Display_Cards( Person display_card_for )
{
	// displaying card for players
	if(display_card_for == player)
	{
		for(int index=0;index<=player_index;index++)
		{
			cout<<"[";
			card.Display_Face(playercardface[index]);
			cout<<"  of  ";
			card.Display_Suit(playercardsuit[index]);
			cout<<"]"<<"\t";
		}
		cout<<"\t{Total Rank :"<<Calculate_Rank_of_Cards(player)<<"}"<<endl;
	}
	// displaying unfolded card of dealer
	else if (display_card_for == dealer)
	{
		for(int index=0;index<=dealer_index;index++)
		{
			cout<<"[";
			card.Display_Face(dealercardface[index]);
			cout<<"  of  ";
			card.Display_Suit(dealercardsuit[index]);
			cout<<"]"<<"\t";
		}
		cout<<"\t{Total Rank :"<<Calculate_Rank_of_Cards(dealer)<<"}"<<endl;
	}
	// displaying folded card of dealer
	else 
	{
		for(int index=0;index<=dealer_index;index++)
		{
			cout<<"[";
			if(index==0)
			{
				cout<<"FOLDED";
			}
			else
			{
				card.Display_Face(dealercardface[index]);
				cout<<"  of  ";
				card.Display_Suit(dealercardsuit[index]);
			}
			cout<<"]\t";
		}
		cout<<"\t{Total Rank :"<<Calculate_Rank_of_Cards(foldeddealer)<<"}"<<endl;
	}
}

class STARTGAME
{
	private :
	    DEALER dealerobject;
	public :
	    STARTGAME()
		{
			fstream file;
			file.open("BLACKJACK_RECORD.txt",ios::app |ios::binary);
			file.close();
		}
	    void StartGame(double &amount , double bet , int &result );
};

void STARTGAME ::StartGame(double &amount , double bet , int &result )
{
	//top_index=0;
	
	dealerobject.Set_Dealer_Index(-1);
	dealerobject.Set_Player_Index(-1);
	// preparing deck
	dealerobject.Call_Prepare_Deck();
	// picking cards for players and dealers
	dealerobject.Pick_Cards(player);
	dealerobject.Pick_Cards(dealer);
	dealerobject.Pick_Cards(player);
	dealerobject.Pick_Cards(dealer);
	// displaying picked cards 
	dealerobject.Display_Cards(player);
	dealerobject.Display_Cards(foldeddealer);
	// if blackjack arise for player 
	if(dealerobject.Calculate_Rank_of_Cards(player)==21)
	{
		cout<<"\n BLACKJACK !!!";
		dealerobject.Display_Cards(dealer);
		int dealer_total=dealerobject.Calculate_Rank_of_Cards(dealer);
		while(dealer_total<=16)
		{
			dealerobject.Pick_Cards(dealer);
			dealerobject.Display_Cards(dealer);
			dealer_total=dealerobject.Calculate_Rank_of_Cards(dealer);
		}
		// if blackjack arise of dealer too 
		if(dealer_total==21)
		{
			cout<<"\n TIE"<<endl;
			result = 0;
		}
		else 
		{
			cout<<"Player WON !!!"<<endl;
			amount+=1.5*bet;
			result = 1;
		}
		
	}
	else 
	{
		int choice ;
		bool running = true;
		while(running)
		{
			cout<<"\n Press 1 to hit ";
			cout<<"\n Press 2 to stand ";
			cout<<"\n Press 3 to EXIT"<<endl;
			cout<<"\n Enter the choice :";
			cin>>choice;
			cout<<endl;
			if(choice == 1)
			{
				dealerobject.Pick_Cards(player);
				dealerobject.Display_Cards(player);
				int player_total=dealerobject.Calculate_Rank_of_Cards(player);
				if(player_total>21)
				{
					cout<<"\n Player BUSTED !!! :"<<endl;
					amount-=bet;
					running = false;
					result = -1;
				}
				else
				{
					dealerobject.Display_Cards(foldeddealer);
				}
			}
			else if(choice == 2)
			{
				dealerobject.Display_Cards(dealer);
				int dealer_total=dealerobject.Calculate_Rank_of_Cards(dealer);
				while(dealer_total<=16)
				{
					dealerobject.Pick_Cards(dealer);
					dealerobject.Display_Cards(dealer);
					dealer_total=dealerobject.Calculate_Rank_of_Cards(dealer);
				}
				int player_total = dealerobject.Calculate_Rank_of_Cards(player);
				if(dealer_total==player_total)
				{
					cout<<"\n TIE !!!"<<endl;
					result = 0;
				}
				else if(dealer_total>player_total&&dealer_total<=21)
				{
					cout<<"\n DEALER WON !!! "<<endl;
					amount-=bet;
					running = false;
					result =  -1;
				}
				else
				{
					cout<<"\n Player WON !!!"<<endl;
					amount+=bet;
					result = 1;
				}
				running = false ;
				
			}
			else 
			{
				cout<<"\n Invalid choice !!!!"<<endl;
			}
			
		}
	}
}
// RECORDING_DETAILS class for saving game history 
class RECORDING_DETAILS
{
	private :
	    BLACKJACKRECORD  br;
	public :
	
	    void Adding_Records( char playername[] , double &amount);
		void Viewing_Records(char playername[] , double amount);
		bool CheckinWhetherPlayerNameAlreadyExistOrNot(char pname[] , double &amount);
};
// recording the gaming detail into files 
void RECORDING_DETAILS :: Adding_Records( char playername[] , double &amount)
{
	fstream file;
	file.open("BLACKJACK_RECORD.txt",ios::in | ios::out | ios::binary );
	
	time_t now=time(0);
	tm *ltm=localtime(&now);
	
	STARTGAME bj; 
	int choice,bet,result;   
	
	br.Set_Player_Name(playername);	
	
	br.Set_Year(1900+ltm->tm_year);
	br.Set_Month(1+ltm->tm_mon);
	br.Set_Date(ltm->tm_mday);
	br.Set_Day( ltm->tm_wday);
	int t[2];
	t[0]=ltm->tm_hour;
	t[1]=ltm->tm_min;
    br.Set_Time(t);
	bool running = true;
	while(running)
	{
		cout<<"\n Enter the bet amount :";
		cin>>bet;
		cout<<endl;

		if(bet>0&&bet<=amount)
		{
		   br.Set_Bet(bet);
		   bj.StartGame(amount,bet,result);
		   br.Set_AmountLeft(amount);
		   br.Set_Result(result);
		   file.seekg(0,ios::end);
		   file.write((char*)&br,sizeof(br));
		   
		   running=false;
		}
		else if(amount == 0)
		{
			cout<<"\n Amount left is zero !!! \n";
			break;
		}
		else 
		{
			cout<<"\n Invalid BET !!!"<<endl;
		}
	}
	file.close();
}
// displaying the games played  history
void RECORDING_DETAILS :: Viewing_Records(char playername[] , double amount)
{
	fstream file;
	file.open("BLACKJACK_RECORD.txt",ios::in | ios::out | ios::binary );
	file.seekg(0,ios::end);
	cout.width(60);
	cout<<"\n\n Player Name :"<<playername<<endl;
	cout<<endl;
	cout.width(10);
	cout<<"Bet";
	cout.width(15);
	cout<<"Amountleft";
	cout.width(10);
	cout<<"Result";
	cout.width(8);
	cout<<"Time";
	cout.width(8);
	cout<<"Day";
	cout.width(9);
	cout<<"Date";
	cout<<endl;
	
	if(!(file.tellg()==0)&&CheckinWhetherPlayerNameAlreadyExistOrNot(playername,amount))
	{
		file.seekg(0);
		while(file.read((char*)&br,sizeof(br)))
		{
			if(strcmp(playername,br.Get_Player_Name())==0)
			{
				br.Display_Record();
			}
		}
	}
	else
	{
		cout<<"\n No record for this user name !!! \n";
	}
	file.close();
}
// If the name already exist then player can continue his last game 
bool RECORDING_DETAILS :: CheckinWhetherPlayerNameAlreadyExistOrNot(char pname[] , double &amount)
{
	fstream file;
	bool check=false;
	file.open("BLACKJACK_RECORD.txt",ios::in | ios::out | ios::binary );
	file.seekg(0);
	while(file.read((char *)&br,sizeof(br)))
	{
		if(strcmp(pname,br.Get_Player_Name()) == 0)
		{
			amount=br.Get_AmountLeft();
			check = true;
		}
	}
	file.close();
	if(check)
	{
		return check;
	}
	return false;
}
int main()
{
	RECORDING_DETAILS rd;
	char playername[50];
    double amount=2500 ;
	bool running = true ;
	int choice;
	cout<<"\n Enter your name : ";
	cin.getline(playername,50);

	int check = rd.CheckinWhetherPlayerNameAlreadyExistOrNot(playername,amount);
	
	if(check)
	{
		cout.width(50);
		cout<<"\n Welcome Back Sir !!!\n";
		if(amount <=0)
		{
			amount = 2500;
		}
	}
	else
	{
		cout.width(60);
		cout<<"\n Welcome Sir !!! Start Your First game !!!\n";
	}
	
	while(running)
	{
		cout<<"\n Press 1 to start game ";
		cout<<"\n Press 2 to show amount Left ";
		cout<<"\n Press 3 to watch history of the previous days games";
		cout<<"\n Press 4 to EXIT "<<endl;
	    cout<<"\n Enter the choice :";	
		cin>>choice;
		cout<<endl;
		switch(choice)
		{
			case 1 :
		    rd.Adding_Records(playername , amount);
			break;
			case 2 :
			cout<<"\n Amount Left :";
			cout<<amount<<endl;
			break;
			case 3 :
			rd.Viewing_Records(playername, amount);
	        break;
			case 4 :
			cout<<"\n See you soon !!!\n";
			running=false ;
			break;
			default :
			cout<<"\n Invalid choice , Please enter the correct choice "<<endl;
			break;
		}
		
	}
	
	return 0;
}