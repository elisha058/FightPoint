#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX_HEALTH 10
#define _CRT_SECURE_NO_WARNINGS
#define RESET "\033[0m"
#define MAGENTA "\033[0;35m"
#define CYAN    "\033[0;36m"
#define LIGHTGREEN "\033[1;32m"
#define LIGHTRED "\033[1;31m"
#define LIGHTYELLOW "\033[1;33m"
//structure to represent a player in the game
typedef struct {
	int defense[2];
	int health;
} Player;

//structure to represent the game state
typedef struct {
	Player player1;
	Player player2;
	int turn;
} Game;
//// Function prototypes
int generate_random_number(int min, int max);
void initialize_game(Game* game);
void print_game(Game* game);
int player_turn(int turn);
int get_place_choice();
int get_choice();
int change_self_defense(Player* P);
int change_opponent_defense(Player* P);
int Attack();
int check_attack(int attack, Player* Opponent);
int get_dominant_defense(Player* P);
int Is_game_over(Game* game);
int display_winner(Game* game);
void Print_guide();
// start of creating functions
void initialize_game(Game* game) //initialize the game
{
	game->player1 = (Player){ {generate_random_number(1, 9), generate_random_number(1, 9)}, MAX_HEALTH };
	game->player2 = (Player){ {generate_random_number(1, 9), generate_random_number(1, 9)}, MAX_HEALTH };
	game->turn = generate_random_number(1, 2);//make the first turn randomised each game to make it more interesting
}
int generate_random_number(int min, int max)//generate a random number between min and max 
{

	return rand() % (max - min + 1) + min;
}
void print_game(Game* game)//display the game state
{
	printf(LIGHTRED "Player 1: \n");
	printf("Defense:   %d    %d\n", game->player1.defense[0], game->player1.defense[1]);
	printf("Health:      %d\n"RESET, game->player1.health);

	printf(CYAN "Player 2: \n");
	printf("Defense:   %d    %d\n", game->player2.defense[0], game->player2.defense[1]);
	printf("Health:      %d\n"RESET, game->player2.health);
}
int player_turn(int turn)//display the turn of the player
{
	if (turn == 1)
	{
		printf(LIGHTRED"******Player 1's turn******\n"RESET);
		return 1;
	}
	else
	{
		printf(CYAN"******Player 2's turn******\n"RESET);
		return 1;
	}
}
int get_place_choice()//get the choice of which defense to change
{
	int choice;
	printf("Enter 1. change defense place [1] \n      2. change defense place [2]\n");
	scanf_s("%d", &choice);
	return choice;
}
int get_choice()//get the choice of what to do in the turn
{
	int choice;
	printf("Enter The one of the options: \n 1. attack \n 2. defend \n 3. change opponent cards\n");
	scanf_s("%d", &choice);
	return choice;
}
int change_self_defense(Player* P)//change the player's defense
{
	int choice = get_place_choice();
	if (choice == 1)
	{
		printf("You picked to change the first defense\n");
		P->defense[0] = generate_random_number(1, 9);
		printf("Your new defense is: %d\n", P->defense[0]);
		return 1;
	}
	else if (choice == 2)
	{
		printf("You picked to change the second defense\n");
		P->defense[1] = generate_random_number(1, 9);
		printf("Your new defense is: %d\n", P->defense[1]);
		return 1;
	}
	else {
		printf("Invalid choice please a correct spot\n ");
		change_self_defense(P);
	}
	return 0;
}
int change_opponent_defense(Player* P)//change the opponent's defense 
{
	int choice = get_place_choice();
	if (choice == 1)
	{
		printf("You picked to change the first defense\n");
		P->defense[0] = generate_random_number(1, 9);
		printf("The new opponent defense is: %d\n", P->defense[0]);
		return 1;
	}
	else if (choice == 2)
	{
		printf("You picked to change the second defense\n");
		P->defense[1] = generate_random_number(1, 9);
		printf("The new opponent defense is: %d\n", P->defense[1]);
		return 1;
	}
	else {
		printf("Invalid choice\n  ");
		change_opponent_defense(P);
	}
	return 0;
}
int Attack()//generate a random attack value between 1 and 9
{
	int attack = generate_random_number(1, 9);
	printf("Attack value: %d\n", attack);
	return attack;
}
int check_attack(int attack, Player* Opponent)//check if the attack was successful
{
	int dominant_defense = get_dominant_defense(Opponent);
	if (attack > dominant_defense)
	{
		printf("Attack was successful\n");
		Opponent->health -= attack - dominant_defense;
		printf("Ouch That hurts!!\n");
		return 1;
	}
	else
	{
		printf("Attack was blocked\n");
		return 0;
	}
}
int get_dominant_defense(Player* P)//get the dominant defense of the player
{
	if (P->defense[0] > P->defense[1])
	{
		return P->defense[0];
	}
	else
	{
		return P->defense[1];
	}
}
int Is_game_over(Game* game)//check if the game is over
{
	//check if the health of one of the players is less than or equal to 0 
	if (game->player1.health <= 0)
	{
		return 1;
	}
	else if (game->player2.health <= 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int display_winner(Game* game)//display the winner of the game
{
	//check which player health is greater than 0
	if (game->player1.health > 0)
	{
		printf(LIGHTYELLOW"******Player 1 wins GG in the Chat!!!******\n"RESET);
		return 1;
	}
	else if (game->player2.health > 0)
	{
		printf(LIGHTYELLOW"******Player 2 wins GG in the Chat!!!******\n"RESET);
		return 1;
	}
	return 0;
}
void Print_guide()
{
	//מדריך למשחק
	printf(LIGHTGREEN"Welcome to the game\n");
	printf("In this game, you will play against your friend in a duel\n");
	printf("You will have 10 health points and the opponent will have 10 health points\n");
	printf("You can attack oppo or defend yourself\n");
	printf("You can also manipulate your defense or the opponent's defense for the better or worse\n");
	printf("The game will end when one of the players has lost his health points\n"RESET);
}
int main()
{
	Game game;
	srand(time(NULL)); // Seed the random number generator
	int choice;

	printf(MAGENTA"Welcome to the game 'Fight Point'\n");
	printf("please pick!\n"RESET);
	printf("pick 1.Open Guide and understand the game / pick 2 .Start the game!!\n");
	scanf_s("%d", &choice);
	if (choice == 1)
	{
		Print_guide();
		printf("Would like to Start the Game?\n");
		printf("pick 1. Yes / pick 2. No\n");
		scanf_s("%d", &choice);
		if (choice == 1)
		{
			printf("Let's start the game\n");
		}
		else if (choice == 2)
		{
			printf("Goodbye:(\n");
			return 0;
		}
		else
		{
			printf("Invalid choice Returning to Main Menu!\n");
			main();
		}
	}
	else if (choice == 2)
	{
		printf("Let's start the game\n");
	}
	else
	{
		printf("Invalid choice Please Enter a Valid choice\n");
		main();
	}

	initialize_game(&game);
	print_game(&game);
	while (!Is_game_over(&game))
	{
		if (game.turn == 1)
		{
			player_turn(game.turn);
			choice = get_choice();
			if (choice == 1) // the player choose to attack
			{
				int attack = Attack();
				check_attack(attack, &game.player2);
				print_game(&game);
				game.turn = 2;
			}
			else if (choice == 2)// the player choose to change his defense
			{
				change_self_defense(&game.player1);
				print_game(&game);
				game.turn = 2;

			}
			else if (choice == 3) // the player choose to manipulate the opponent's defense
			{
				change_opponent_defense(&game.player2);
				print_game(&game);
				game.turn = 2;
			}
			else
			{
				printf("Invalid choice Please Enter a Valid choice to make your turn!\n");//dealing with invalid input
			}
		}
		else if (game.turn == 2)
		{
			player_turn(game.turn);
			int choice = get_choice();
			if (choice == 1)
			{
				int attack = Attack();
				check_attack(attack, &game.player1);
				print_game(&game);
				game.turn = 1;
			}
			else if (choice == 2)
			{
				change_self_defense(&game.player2);
				print_game(&game);

				game.turn = 1;

			}
			else if (choice == 3)
			{
				change_opponent_defense(&game.player1);
				print_game(&game);
				game.turn = 1;
			}
			else
			{
				printf("Invalid choice Please Enter a Valid choice this time!\n");//dealing with invalid input
			}
		}

	}
	display_winner(&game);
	return 0;
}

