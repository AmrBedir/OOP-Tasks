#ifndef COMPAREKMAPTERMS_H
#define COMPAREkMAPTERMS_H

#include "setKmap.h"


//This class is using for compare iputs results and provide
// minmizing terms in order to filter them and get results
class   CompareKmapTerms : public setKmap 
{

protected:
		int	temp, temp1, temp2, temp3; //temprature variables
		int resultTerms;

	vector<char> minimize (vector<int> &ones, vector<int> &dCare);
	void compare (vector < vector< int >> &terms); // comparelify
	void saveValue(vector<int> &tempSave, vector<vector<int>> &saver, vector<bool> &hascompare, vector<vector<int>> &terms);
	void addOther (vector<vector<int>> &saver,vector<bool> &hascompare, int &saverCount, vector<vector<int>> &terms);
	void unRepeat (vector<vector<int> > &terms);
	vector<char> posToTerm(vector<vector<int>> &terms); //converte position to its terms
		
};//end kmap

/***
	The main function of the program that implement K-map by:
	1- prompting for k-map type by its variable's number
	2- prompting for one's position by getPos function
	3- prompting for don't care position by getPos function
	4- Minimizing and getting results
*/

/***
* minimize is the function that do minimizing process by:
* 1- Save ones and don't care positions with its coordinates 
*    in (vector) terms with "setTerms" function
* 2- comparelify terms with "compare" Function
* 3- Represent comparelification as alphapetical terms with posToTerm
* 4- Filter unfull and unempty kmaps to getting essential 
*    terms and remove others
*/

vector<char> CompareKmapTerms :: minimize (vector<int> &ones, vector<int> &dCare)
	{
		vector<vector<int> >terms; //for saving one's coordinates
		vector<char>result;        //Minimizing results before filter
		
		termCount = 0;
		setTerms (ones, terms);		//save one's with its coordintates in (vector) terms
		setTerms(dCare, terms);     //save don't care with its coordinates in (vector) terms
		compare(terms);				//compare ones
		unRepeat(terms);
		result = posToTerm(terms);  //converte result to terms of variables
		
		return result;            //return result
	}//end minimize


/*
* compare function (compare)
* compare each two terms with each other and save 
* compare result in (saver) with "setValue" function
* Add unsiplified terms to saver with "addOther" function
*/
	void CompareKmapTerms ::compare (vector < vector< int >> &terms)
{

	vector<int>tempSave;
	vector<vector<int> >saver;    //save similarty
	vector<bool>hascompare;

	//comparelify loop
	for( temp3 = 0; temp3 < type && terms.size() > 1; temp3++)
	{//times while
	
	//hasSave = false;
	saverCount = 0; //default case
	
	//initializing has comparelified with false
	hascompare.clear();
	hascompare.resize(terms.size(), false);
	
	//do essential minimizations
	for( temp = 0; temp < terms.size() -1 ; temp++)
		{//for 1
			for ( temp1 = temp + 1; temp1 < terms.size(); temp1 ++ )
			{//for 2
				tempSave.clear(); //clear temp Save
				////////element's loop/////////////////
				for (temp2 = 0; temp2 < type; temp2++)
				{//for 3
					
					//searching for identical coordinate and save its arrangement in tempSave
					// temp and temp1 cover terms
					//temp2 cover coordinates
					if( ( terms[temp][temp2] == terms[temp1][temp2] )  ) //search for mathcing element
					{
						//save identical
						tempSave.push_back(temp2);
					}

				}//end for 3
			if(tempSave.size () == type -1  )
				saveValue(tempSave,saver, hascompare, terms);
		
			}//end for 2
		}//end for 1
		
		//add remain terms that hasn't comparelified with other
		addOther(saver,hascompare,saverCount, terms);
		
		//clear terms before comparelified
			terms.clear();
		//assuming terms after comparelified
			terms = saver;
			
		saver.clear(); //clear saver to receive new data

	}//end comparelify loop
}//end compare

	void CompareKmapTerms ::unRepeat(vector<vector<int>> &terms)
	{
		for(int temp = 0; temp < terms.size(); temp ++)
			for(int temp1 = temp + 1 ; temp1 < terms.size(); temp1++)
			{
				if(terms[temp] == terms[temp1])        //checking for repeating terms
					{
						terms.erase(terms.begin() + temp); //remove repeating terms
						temp1--;
				    }
			}
	}//end unrepeat

/*
*save Value function
* set don't care arrangements after getting identicals arrangements
* converte identical coordinates from its arrangement to its values 
*/
void CompareKmapTerms :: saveValue(vector<int> &tempSave, vector<vector<int>> &saver, vector<bool> &hascompare, vector<vector<int>> &terms)
{
			if(tempSave.size () == type -1  )
			{
				
				saver.push_back(vector<int> () ); //initializing terms
				
				/*set don't care arrangements after getting identicals arrangements*/

				for(temp2 = 0; temp2 < terms[temp].size(); temp2++)
				{
					//don't care locates after matching coordinates
					if(temp2 == tempSave.size() )
						tempSave.push_back(-1);
					
					//don't care locates between matching coordinates
					else if(temp2 != tempSave [temp2]) 
						tempSave.insert(tempSave.begin()+temp2,-1);
				}//end adding don't care
				
				/*converte identical coordinates from its arrangement to its values*/
				for(temp2 = 0; temp2 < tempSave.size(); temp2++)
					{//saver for
						if(	tempSave[temp2] == -1)				
						    saver[saverCount].push_back(-1);
						else
							saver[saverCount].push_back(terms[temp][temp2]);
					}//end saver for

				hascompare[temp] = hascompare[temp1] = true;   //assuming them as comparelified
				saverCount++; //increase saving comparelified terms

			}//end if condition		
}//end save values

//add Un comparelified terms to terms
void CompareKmapTerms :: addOther (vector<vector<int>> &saver,vector<bool> &hascompare, int &saverCount, vector<vector<int>> &terms)
{
	//add single element
		for(temp2 = 0; temp2 <terms.size(); temp2++)
				{
					if(hascompare[temp2] == false )
					{
						saver.push_back( vector<int> () );

						for(int temp4 = 0; temp4 < terms[temp2].size(); temp4++)
						{
							saver[saverCount].push_back(terms[temp2][temp4]);
						}
						saverCount++;
					}
				}
}//end add other


//represent comparelification as alphapetical terms
vector<char> CompareKmapTerms :: posToTerm(vector<vector<int>> &term)
{
	vector<char>result; //for returinging
	int  smallLetter = false; //representing with small letters
	int digit,          //for pushing back
		dashCount = 0;  //dash cound
	bool isFull = true, //for checking full maps
		isEmpty = false;        //checking empty maps

	resultTerms = 0;
	//terms loop
	for(temp = 0; temp < term.size(); temp++)
	{
		//minterms loop
		for(temp1 = 0; temp1<term[temp].size(); temp1++)
		{//minterms loop

			//more than 9 k-map type
			if(smallLetter == false && temp - dashCount  > 9)
				smallLetter = true; //start represent with small letter
				
			
			digit = temp1 + 65;
				if (smallLetter) digit + 22; //97 - 65 - 10
				                             // 97 a ascii, 65 A ascii, 10 numerical a
			//dashed minterms
			if(term[temp][temp1] == 0)
			{
				result.push_back(digit); //add minterm
				result.push_back(39);    //add dash
				dashCount ++;            //increase dash count
			}

			//undashed minterms
			if(term[temp][temp1] == 1)
			{
				result.push_back(digit); //add minterm
			}
		}//end minterms loop
		
		//add + for seperating between terms
		if(temp < term.size() -1)
			result.push_back('+');

		resultTerms++;
	}//end terms loop

	//no function case
	if(ones.size() == 0)
	{
		result.push_back('0');
		isEmpty = true;
	}
	//checking full map 
	for(int temp = 0; temp < term.size() && isEmpty == false; temp++)
	{
		isFull = true;   //default case
		for(int temp1= 0; temp1 < term[temp].size(); temp1++)
		{
			if(term[temp][temp1] != -1)
				isFull = false;
		}
	}
		
	//empty maps
	 if (isEmpty)
			{
			result.clear();
			result.push_back('0');
		}

	//full-map case
		else if(isFull)
		{
			result.clear();
			result.push_back('1');
		}
		
	return result;
}//end get Result


#endif