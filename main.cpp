#include <iostream> 
#include <iomanip> 
#include <fstream> 
#include <string> 
#include <vector> 
#include <sstream> 
#include <stdlib.h> 
#include <new> 
#include <list> 
#include <algorithm> 
#include <time.h>

using namespace std; 
// BASIC BLOCK TO HOLD PROCESSED DATA
struct BID_MOMENT {
	// THIS HOLDS BID NUMBER i.e. BID ONE WITH K ITEMS
	int bid;
	// AMOUNT FOR k ITEMS
	int amount;
	// THIS HOLDS BID NUMBER i.e. BID ONE WITH K ITEMS
	int rank;
	// COST DISTRIBUTION PER ITEM
	int Cst_Dstr;
	// STORES LIST OF ITEMS IN BID
	vector <int> items;
	// USED TO POPULATE TREE
	vector < BID_MOMENT > NODE;
	// OVERLOADED OPERATORS USED FOR SORTING FUNCTION FOUND IN ALGORITHM
	bool operator<(const BID_MOMENT& val) const {
		return ( (items[0] <= val.items[0]) && (amount > val.amount) && (Cst_Dstr > val.Cst_Dstr) );
	}
	bool operator>(const BID_MOMENT& val) const {
		return ( (amount > val.amount) && (Cst_Dstr > val.Cst_Dstr) );
	}
	bool operator==(const BID_MOMENT& val) const {
		return ( (items[0] == val.items[0]) && (amount > val.amount) );
	}
};
// MAIN FUNCTION
int main() 
{
	// OPEN input.txt FILE
	ifstream inFile;
	ofstream outFile;
	// READ FROM input.txt FILE, AND WRITE TO MENDOZA.txt FILE
	inFile.open("input.txt", inFile.in);
	outFile.open("Mendoza_Cunningham_Bell.txt", outFile.out);
	// USED TO MONITOR INSTANCES
	int instances = 0, num_inst = 0;
	// READ INPUT FILE
	inFile >> instances;
	float total_time = 0;
cout << "Bird" << endl;
	// READ FILE AND PROCESS INSTANCES
	while (num_inst < instances)
	{
		// ITEMS FOR SALE = n, NUMBER OF BIDS = m
		// OFFERING PRICE = k, ITEMS IN BID = l
		int n = 0, m = 0;
		
		int Worst_Case_Sum = 0;
		// LIST TO CONTAIN NUMBER OF BIDS
		vector < BID_MOMENT > bid;
		// GOING TO USE TO DISPLAY IN CORRECT ORDER LATER ON
		vector < BID_MOMENT > bid_copy;
		inFile >> n >> m;
		// STORES ONE LINE AT A TIME OF input.txt FILE
		string line;
		getline(inFile, line);
		// USED AS COUNTER FOR bid[]
		int tmp = 0;
		// READS THE FILE LINE BY LINE
		for (int i = 0; i < m; i++)
		{	
			getline(inFile, line);
			int value;
			// USED TO HOLD DATA READ
			vector<int> tmpData;
			stringstream linestream(line);
			while (linestream >> value)
			{	//somehome ignore the first value;
				tmpData.push_back(value);
			}
			BID_MOMENT tmpBid;
			tmpBid.amount = tmpData[0];
			tmpData.erase( tmpData.begin() );
			tmpBid.items = tmpData;
			// SORTS EACH BID ELEMENTS IN INCREASING ORDER
			sort( tmpBid.items.begin(), tmpBid.items.end() );
			//STORES BIDDING ELEMENTS
			bid.push_back( tmpBid );
			// ASSIGNS RANK TO BID...ORDER OF BIDDER
			bid[tmp].rank = (tmp + 1);
			// ASSIGNS WORTH TO THE BID RELATIVE TO NUMBER
			// OF ITEMS TO THE MONEY OFFERED
			bid[tmp].Cst_Dstr = ( bid[tmp].amount / bid[tmp].items.size() );
			// ADD MONEY INCASE ITS ALL THE SAME SIZE, ITEM SIZE OF ONE
			Worst_Case_Sum += bid[i].amount;
			tmp++;
		}
		// INSTANCE DISCARDED IF SIZE OF ITEMS IS GREATER THAN ONE
		bool discard = true;
		int Most_money_single_item = 0;
		// INSTANCE REJECTED IF ONLY ONE ITEM EXISTS
		bool many_items = false;
		// TWO TYPES OF INSTANCE RANKS
		int RNK = 0, RNK_ = 0;
		// VERIFIES EACH BIDDER ONLY WANTS ONE ITEM
		int item_size_Count = 0;
		// IDENTIFIES MULTIPLE BIDDERS WANT THE SAME ITEM
		bool same_found = false;
		// LOOKS FOR AN ITEM REPEATING
		for( int i = 0; i < m - 1; i++ )
		{	for( int j = i + 1; j < m; j++ )
			{	if( bid[i].items[0] == bid[j].items[0] )
				{  same_found = true; i = j = m;  } } }		
		// LOOK FOR "one-bid per one-item" WORST CASE
		for( int i = 0; i < int( bid.size() ); i++ )
		{       // MORE THAN ONE ITEM PER LINE
			if( bid[i].items.size() >= 2 || n >= 2)
			{  discard = false; i = (bid.size() - 1); }
			// THRE EXIST ONLY ONE ITEM PER LINE
			if( bid[i].items.size() == 1 )
			{ ++item_size_Count; }
			// IDENTIFIES MOST MONEY AND LOCATION OF SINGLE ITEM AND MANY BIDS
			if( Most_money_single_item < bid[i].amount && n == 1 )
			{
				Most_money_single_item = bid[i].amount;
				Worst_Case_Sum = Most_money_single_item;
				RNK = i;
			}//IDENTIFIES MOST MONEY GIVEN A BIDDER WHO WANTS LOTS OF ITEMS
			else if( (Most_money_single_item < bid[i].amount) && (n >= 2) && (bid[i].items.size() == 1))
			{  Most_money_single_item = bid[i].amount;  RNK_ = i;  }
		}
		// ONLY ONE ITEM TO PROCESS POSSIBLE MULTIPLE BIDS
		if( n == 1 )
		{ Worst_Case_Sum = Most_money_single_item; }
		// THERE EXISTS MANY ITEMS
		if( n >= 2 )
		{ many_items = true; Worst_Case_Sum = Most_money_single_item; }		
		// INITIATE CLOCK
		clock_t Begin_to_End;
		Begin_to_End = clock();
		// IF BIDDERS WANT MANY ITEMS AND MANY ITEMS EXIST AND 
		// SEVERAL BIDDERS WANT THE SAME ITEM
		if( discard == true && many_items == false && same_found == false )
		{	// SORT EACH BIDDERS WANTS IN INCREASING ORDER
			sort( bid.begin(), bid.end() );
			// DISPLAY RESULTS
			total_time += ((float)(clock() - Begin_to_End)/ CLOCKS_PER_SEC);
			// DISPLAYS TIME
			outFile << ((float)(clock() - Begin_to_End)/ CLOCKS_PER_SEC * 1000) << endl;
			if( n >= 2 && (item_size_Count == int( bid.size() ) ) )
			{	// THERE IS MORE THAN ONE ITEM
				Worst_Case_Sum = 0;
				// ADD UP MONEY
				for( int i = 0; i < int( bid.size() ); i++ )
				{  Worst_Case_Sum += bid[i].amount;  }
				outFile << bid.size() << " " << Worst_Case_Sum << endl;
				// DISPLAY 
				for( int i = 0; i < int( bid.size() ); i++ )
				{	// USED TO BE -->outFile << bid[i].rank << " ";<--
					// AND CHANGED TO LINE BELOW
					outFile << bid[i].rank << endl;
				}
			}//DISPLAYS NUMBER BIDS AND SUM OF MONEY
			if( n == 1 )
			{	outFile << RNK << " " << bid[ RNK ].amount << endl;
				// THERE IS ONE ITEM AND RNK IS ITS LOCATION
				// WITH MOST MONEY
				outFile << bid[ RNK ].rank << " ";
			}	outFile << endl << endl;
		}
		else {	// GOING TO USE TO DISPLAY IN CORRECT ORDER LATER ON
			bid_copy = bid;
			// SORTS INCREASING ORDER
			sort( bid.begin(), bid.end() );
			// USED TO CREATE TREE
			vector< BID_MOMENT > tree;
			int first_element = 0;
			first_element = bid[0].items[0];
			// COUNTS NUMBER ELEMENTS ON THE FIRST ROW
			// PUSHED UNTO THE VECTOR
			int Cnt_On_Frst_Lvl = 0;
			// INITIAL BRANCH
			if( bid.size() <= 3000 )
			{	for( int i = 0; i < int(bid.size()); i++ )
				{	// BELOW CREATES INITIAL BRANCH
					// ALLOWS TO PUCH IN HORIZONTALLY
					tree.push_back( bid[i] );
					// STORES AMOUNT ON FIRST LEVEL
					tree[ Cnt_On_Frst_Lvl ].amount = bid[i].amount;
					// RANK REPRESENTS POSITION OF ORDER READ FROM input.txt FILE
					tree[ Cnt_On_Frst_Lvl ].rank = bid[i].rank;
					// TRACKS NUMBER OF NODES ON FIRST LEVEL
					Cnt_On_Frst_Lvl++; } }
			else
			{	for( int i = 0; i < int(bid.size()); i++ )
				{	//BELOW CREATES INITIAL BRANCH
					if( first_element == bid[i].items[0] )
					{	//ALLOWS TO PUCH IN HORIZONTALLY
						tree.push_back( bid[i] );
						//STORES AMOUNT ON FIRST LEVEL
						tree[ Cnt_On_Frst_Lvl ].amount = bid[i].amount;
						//RANK REPRESENTS POSITION OF ORDER READ FROM input.txt FILE
						tree[ Cnt_On_Frst_Lvl ].rank = bid[i].rank;
						// TRACKS NUMBER OF NODES ON FIRST LEVEL
						Cnt_On_Frst_Lvl++;
					} } }
			// USED TO START AT NEXT LOCATION FOR COMPARISON...THIS IS TO KNOW
			// WHERE THE NEXT NUMBER STARTS THAT IS DIFFERENT THEN THE FIRST
			// ROW IN THE TREE
			int K = 0, L = 0, J = 0, I = 0;
			bool can_buy = true; int most_money = 0; int when = 0;
			// BEGINS COLLISIONS
			for( int i = 0; i < int( tree.size() ); i++ )
			{	// START AFTER THE SORTED EVENT OF SAME VALUES IN SAME LEVEL
				for( int j = 0; j < int( bid.size() ); j++ )
				{	for( int k = 0; k < int( tree[i].items.size() ); k++ )
					{	for( int l = 0; l < int( bid[j].items.size() ); l++ )
						{ // LOOKS FOR A MATCH IF THE SAME DO NOT ADD
							if( tree[i].items[k] == bid[j].items[l] )
							{	// SAME ITEM BY MULTIPLE ITEM
								can_buy = false;
								// THERE IS NO NEED TO KEEP LOOKING
								// TERMINATE for LOOPS
								k = tree[i].items.size();
								l = bid[j].items.size();
							}	I = i; J = j; K = k; L = l;
						}
					}// CHECK DOWN THE TREE NODE FOR A MATCH
					for( int depth = 0; depth < int( tree[i].NODE.size() ); depth++)
					{	int count = tree[i].NODE[depth].items.size();
						int DPTH = int( tree[i].NODE.size() );
						int SD = int( bid[j].items.size() ); int cnt = 0;
						// LOOK THROUGH CORRESPONDING BRANCH FOR MATCHING NUMBER BID
						for(int side = 0; side < int( bid[j].items.size() ); side++ )
						{ // CHECK INDIVIDUAL ELEMENTS
							while(cnt < count)
							{	if( tree[i].NODE[depth].items[cnt++] == bid[j].items[ side ] )
								{	// NO NEED TO CONTINUE LOOKING DOWN THIS PATH STOP
									// AND MOVE OVER TO NEXT BRANCH
									can_buy = false;  count = 0;
									side = SD;  depth = DPTH;
								} } cnt = 0; }
					}
					if( can_buy == true )
					{	// ALLOWS TO PUSH IN VERTICALLY
						tree[I].NODE.push_back( bid[J] );
						// KEEPS TRACK OF MONEY ON TOP NODE
						tree[I].amount += bid[J].amount;
					}// RESET can_buy
					can_buy = true;
				}
			}// LOOK FOR THE MOST MOENY
			for( int i = 0; i < int(tree.size()); i++ )
			{	// LOOK FOR THE MOST MONEY
				if( most_money < tree[i].amount )
				{  most_money = tree[i].amount;  when = i; }
			}// DISPLAY TIME, # BIDS AND AMOUNT, WHEN TO BID
			total_time += ((float)(clock() - Begin_to_End)/ CLOCKS_PER_SEC);
			outFile << ((float)(clock() - Begin_to_End)/ CLOCKS_PER_SEC /* * 1000 */) << endl;
			// BELOW NUMBER OF BIDS AND AMOUNT OF MONEY
			// REASON WHY PLUS ONE IS BECAUSE DISPLAYING HANGING NODES FROM TREE
			// NOT INCLUDING PARENT NODE
			outFile << tree[ when ].NODE.size() + 1 << " " << tree[ when ].amount << endl;
			// THE RANK DISPLAYS WHEN TO PLACE A BID
			// SORTS TO DISPLAY IN CORRESPONDING ORDER
			//sort( tree[when].items.begin(), tree[when].items.end() );
			vector<int> in_order;		
			in_order.push_back( tree[when].rank );
			for( int i = 0; i < int( tree[when].NODE.size()); i++ )
			{  in_order.push_back( tree[when].NODE[i].rank );  }
			sort( in_order.begin(), in_order.end() );
			if( tree[when].NODE.size() > 0 )
			{	for( int i = 0; i < int( in_order.size() ); i++ )
				{ // THIS WILL PRING OUT THE PARENT NODE IN ITS CORRESPONDING PLACE
					// AS IT READS FROM THE INPUT FILE
					outFile << in_order[i] << " ";
				} }
			else { outFile << tree[when].rank << " "; }		
			outFile << endl << endl;
		}// COUNTS NUMBER OF INSTANCES
		num_inst++;
	}
	outFile << "***TOTAL RUN TIME***\n\t " << total_time << endl;
	outFile << "***THAT'S FREAKY FAST***" << endl;
	// CLOSE BOTH INPUT AND OUTPUT FILES
	inFile.close(); outFile.close();
	// END OF PROGRAM
	return 0;
}
