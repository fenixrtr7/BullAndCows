// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

#include "Count.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
// #include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();
	
	const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
	FFileHelper::LoadFileToStringArray(Words, *WordListPath);

	Isograms = GetValidWords(Words);
	SetupGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
	/*if game is over then do ClearScreen() and Setup_Game() the game
	 else Checking PlayerGuess*/
	if (bGameOver)
	{
		ClearScreen();
		SetupGame();
	}
	else // Checking PlayerGuess
	{
		ProcessGuess(PlayerInput);
	}
}

void UBullCowCartridge::SetupGame()
{
	// Welcoming the Player
	PrintLine(TEXT("Welcome to bull cows!"));

	HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
	Lives = HiddenWord.Len();
	bGameOver = false;

	PrintLine(TEXT("The Hidden Wors is: %s"), *HiddenWord);
	
	PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
	PrintLine(TEXT("You have %i lives"), Lives);
	PrintLine(TEXT("Type in your guess and \npress enter to continue...")); // Prompt player for guess

	// const TCHAR HW[] = TEXT("plums");
	// PrintLine(TEXT("Character 1 of the hidden word is: %c"), HiddenWord[0]); // print "c"
	// PrintLine(TEXT("The 4th character of HW is: %c"), HW[3]); // print "m"
}

void UBullCowCartridge::EndGame()
{
	bGameOver = true;
	PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
	if (Guess == HiddenWord)
	{
		PrintLine(TEXT("You have won!"));
		EndGame();
		return;
	}

	if (Guess.Len() != HiddenWord.Len())
	{
		PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
		PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining."), Lives);
		return;
	}

	// Check if Isogram
	if (!IsIsogram(Guess))
	{
		PrintLine(TEXT("No repeating letters, guess again!"));
		return;
	}

	// Remove Life
	Lives--;
	PrintLine(TEXT("You have lost a live. You have %i lives"), Lives);

	if (Lives <= 0)
	{
		ClearScreen();
		PrintLine(TEXT("Game Over"));
		PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
		EndGame();
		return;
	}

	// Show the player Bulls and Cow
	FBullCowCount Score = GetBullCows(Guess);

	PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);
	PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
	for(int32 Index = 0; Index < Word.Len();Index++)
	{
		for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
		{
			if(Word[Index] == Word[Comparison])
			{
				return false;
			}
		}
	}
	return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
	TArray<FString> ProviValidWords;
	
	for (FString TempWord : WordList)
	{
		if((TempWord.Len() >= 4) && ( TempWord.Len() <= 8) && (IsIsogram(TempWord)))
		{
			ProviValidWords.Emplace(TempWord);	
		}
	}
	return ProviValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
	// for every index Guess is same as index Hidden, BullCount ++
	// if not a bull was it a cow? if yes CowCount ++
	FBullCowCount Count;

	for(int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
	{
		if(Guess[GuessIndex] == HiddenWord[GuessIndex])
		{
			Count.Bulls++;
			continue;
		}

		for(int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
		{
			if(Guess[GuessIndex] == HiddenWord[HiddenIndex])
			{
				Count.Cows++;
				break;
			}
		}
	}
	return Count;
}
