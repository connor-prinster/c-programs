#include "FirstWordInfo.h"

///////////////////////////////////////////
//  STANDARD CONSTRUCTOR AND DESTRUCTOR  //
///////////////////////////////////////////
FirstWordInfo::FirstWordInfo()			 //
{										 //
}										 //
FirstWordInfo::~FirstWordInfo()			 //
{										 //
}										 //
///////////////////////////////////////////


//==================================================================================//
//-----------------------------------------------------------//
//          Typical toString Function for Debugging          //
//-----------------------------------------------------------//
std::string FirstWordInfo::toString()
{
	return "placementstring";
}

//---------------------------------------------------------------------//
//          Custom Constructor Created by A Word and a Number          //
//---------------------------------------------------------------------//
FirstWordInfo::FirstWordInfo(std::string s, int c)
{
	word = s;
	count = c;
}

//--------------------------------------------------------------------------//
//          Based on the First Word, Adjust Second Word to Meet it          //
//--------------------------------------------------------------------------//
void FirstWordInfo::updateSecondWord(std::string w)
{
	bool wordAlreadyExists = false;	//bool to check if the word already exists
	int idxFound = 0;	//making sure the index in the for loop is in scope of function
	for (int i = 0; i < secondWordList.size(); i++)
	{
		if (secondWordList[i].word == w) wordAlreadyExists = true; //if word is found, set bool true
		idxFound = i;	//set idxFound to the index where the word was found
	}
	if (!wordAlreadyExists)
	{
		secondWordList.push_back(SecondWordInfo(word, 0));	//since the word doesn't exist, make a spot for the word
	}
	else
	{
		secondWordList[idxFound].increment();	//at the index where the same word was found, increment the word count
	}
}
//==================================================================================//
