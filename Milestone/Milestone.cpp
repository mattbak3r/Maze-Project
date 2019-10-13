#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>

using namespace std;

/*
	Matthew T Baker
	CST-201
	October 13, 2019
	Dominga Gardner
*/

class DirectionTaken
{
public:
	bool Left;
	bool Up;
	bool Right;
	bool Down;

	DirectionTaken()
	{
		Left = false;
		Up = false;
		Right = false;
		Down = false;
	}
};

class Heap_Path
{
public:
	int moveNumber;
	int movePosition;

	Heap_Path()
	{
		moveNumber = 0;
		movePosition = 0;
	}
};

void Heapify(Heap_Path arr[], int size, int index)
{
	int max = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	if (left < size && arr[left].movePosition > arr[max].movePosition)
	{
		max = left;
	}
	if (right < size && arr[right].movePosition > arr[max].movePosition)
	{
		max = right;
	}
	if (max != index)
	{
		swap(arr[index], arr[max]);
		Heapify(arr, size, max);
	}
}

void ConvertToHeap(Heap_Path arr[], int index)
{
	int i = (index / 2) - 1;
	for (int x = i; x >= 0; x--)
	{
		Heapify(arr, index, i);
	}
}

class GamePiece
{
public:
	int square[3][3] =
	{
		{0,0,0},
		{0,0,0},
		{0,0,0}
	};
	GamePiece* next;
	GamePiece* prev;
	
	GamePiece()
	{
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				square[x][y] = 0;
			}
		}
		next = 0;
		prev = 0;
	}
	GamePiece(int x, GamePiece* pointer = 0, GamePiece* p_pointer = 0)
	{
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				square[x][y] = x;
			}
		}
		prev = next;
		next = pointer;
		prev = p_pointer;
	}	
	void Passable()		//Sets square to passable values
	{
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				square[x][y] = 1;
			}
		}
	}
};

class GameBoard
{
public:
	GamePiece* head;
	GamePiece* tail;

	GameBoard()
	{
		head = tail = NULL;
	}

	void Add_Piece()
	{
		GamePiece* temp = new GamePiece();
		temp->next = NULL;
		
		if (head == NULL)
		{
			head = temp;
			tail = temp;
		}
		else
		{
			tail->prev = tail;
			tail->next = temp;
			tail = tail->next;
		}
	}
	bool isPassable(GamePiece* gp)
	{
		

		if (gp->square[0][0] == 1)
		{
			//cout << "P - ";
			return true;
		}
		else
		{
			//cout << "XX - ";
			return false;
		}
	}
	void Passable(int num)		//Sets square to passable values
	{
		GamePiece* temp = head;

		for (int x = 0; x < num; x++)
		{
			temp = temp->next;
		}
		temp->Passable();
	}
	void Player(int val)
	{
		GamePiece* node = head;
		if (val == 0)
		{
			node->square[1][1] = 5;
		}
		else if (val > 0)
		{
			for (int i = 0; i < val; i++)
			{
				node = node->next;
			}
			node->square[1][1] = 5;
		}
	}
	void End(int val)
	{
		GamePiece* node = head;
		if (val == 1)
		{
			node->square[1][1] = 20;
		}
		else
		{
			for (int i = 0; i < val; i++)
			{
				node = node->next;
			}
			node->square[1][1] = 20;
		}
	}
	void Print_To_Text()
	{
		GamePiece* temp = head;
		fstream file("display_maze.txt");

		file << "Display of Maze!\n";
		file << "\t  0     1     2     3     4     5     6     7     8     9    10\n";
		
		if (file.is_open())
		{
			while (temp != NULL)
			{
				for (int i = 0; i < 11; i++)
				{
					GamePiece* one = temp;
					GamePiece* two = one->next;
					GamePiece* three = two->next;
					GamePiece* four = three->next;
					GamePiece* five = four->next;
					GamePiece* six = five->next;
					GamePiece* seven = six->next;
					GamePiece* eight = seven->next;
					GamePiece* nine = eight->next;
					GamePiece* ten = nine->next;
					GamePiece* elev = ten->next;
					
					for (int x = 0; x < 3; x++)
					{
						if (x == 1)
						{
							file << i << "\t";
						}
						if (x != 1)
						{
							file << "\t";
						}

						for (int y = 0; y < 3; y++)
						{
							file << Translate(one, x, y) << " ";
						}
						for (int y = 0; y < 3; y++)
						{
							file << Translate(two, x, y) << " ";
						}
						for (int y = 0; y < 3; y++)
						{
							file << Translate(three, x, y) << " ";
						}
						for (int y = 0; y < 3; y++)
						{
							file << Translate(four, x, y) << " ";
						}
						for (int y = 0; y < 3; y++)
						{
							file << Translate(five, x, y) << " ";
						}
						for (int y = 0; y < 3; y++)
						{
							file << Translate(six, x, y) << " ";
						}
						for (int y = 0; y < 3; y++)
						{
							file << Translate(seven, x, y) << " ";
						}
						for (int y = 0; y < 3; y++)
						{
							file << Translate(eight, x, y) << " ";
						}
						for (int y = 0; y < 3; y++)
						{
							file << Translate(nine, x, y) << " ";
						}
						for (int y = 0; y < 3; y++)
						{
							file << Translate(ten, x, y) << " ";
						}
						for (int y = 0; y < 3; y++)
						{
							file << Translate(elev, x, y) << " ";
						}
						file << "\n";
					}
					temp = elev->next;
				}
			}
		}
	}
	char Translate(GamePiece* gp, int x, int y)
	{
		char c = 'i';
		int val = gp->square[x][y];

		if (val == 0)
			c = '#';
		else if (val == 5)
			c = 'P';
		else if (val == 20)
			c = 'E';
		else if (val == 1)
			c = '.';

		return c;
	}
	void Print()
	{
		GamePiece* node = head;
		char block = 'i';

		while (node != NULL)
		{
			for (int x = 0; x < 3; x++)
			{
				for (int y = 0; y < 3; y++)
				{
					if (node->square[x][y] == 0)
						block = '#';
					else if (node->square[x][y] == 5)
						block = 'P';
					else if (node->square[x][y] == 20)
						block = 'E';
					else if (node->square[x][y] == 1)
						block = '.';
					std::cout << block << " ";
				}
				std::cout << "\n";
			}
			node = node->next;
		}
	}
	void Print(int x)
	{
		GamePiece* temp = Find_POS(x);
		for (int i = 0; i < 3; i++)
		{
			cout << temp->square[1][i] << " ";
		}
		cout << "POS " << x << "\n";
	}
	// *** UNDER CONSTRUCTION / CURRENTLY 'PREV' IS NOT WORKING *** //
	GamePiece* Move_UP(GamePiece* pos)		//advance pos back 11 places
	{
		for (int x = 0; x < 11; x++)
		{
			pos->prev;
		}
		return pos;
	}
	GamePiece* Move_RIGHT(GamePiece* pos)		//advance pos forward 1 place
	{
		pos = pos->next;
		return pos;
	}
	GamePiece* Move_DOWN(GamePiece* pos)		//advance pos forward 11 places
	{
		for (int x = 0; x < 11; x++)
		{
			pos = pos->next;
		}
		return pos;
	}
	// *** UNDER CONSTRUCTION / CURRENTLY 'PREV' IS NOT WORKING *** //
	GamePiece* Move_LEFT(GamePiece* pos)		//advance pos back 1 place
	{
		pos = pos->prev;
		return pos;
	}
	GamePiece* Shortcut(GamePiece* pos)
	{
		for (int x = 0; x < 96; x++)
		{
			pos = pos->next;
		}
		return pos;
	}
	bool FindUsingQueues(int start, int end)
	{
		// Up = -9 places in list
		// Right = +1 places in list
		// Down = +9 places in list
		// Left = -1 places in list

		queue<GamePiece*> path;
		queue<int> solution;
		GamePiece* temp = new GamePiece();

		temp = Find_POS(start);
		//temp = Shortcut(temp);
		int path_value = start;
		int last_move = 0;		// 1 = Down; 2 = Right; 3 = Left; 4 = Up;
		path.push(temp);
		DirectionTaken path_taken[125];
		solution.push(path_value);

		do
		{
			if (path.back()->square[1][1] == 20)
			{
				cout << "Solution found...\n";
				while (!solution.empty())
				{
					cout << solution.front() << " -> ";
					solution.pop();
				}
				cout << "\n";
				return true;
			}
			else if ((isPassable(Find_POS(path_value + 1))) && (path_taken[path_value].Right == false) && (last_move != 3))
			{
				//cout << "\t \t \t \t";
				//cout << "::" << temp->next->square[1][1] << "::";
				temp = Move_RIGHT(path.back());
				path_taken[path_value].Right = true;
				path_value += 1;
				solution.push(path_value);
				path.pop();
				path.push(temp);
				last_move = 2;
				//cout << "(LM Check)Advancing RIGHT to POS.." << path_value << endl;
			}
			else if ((isPassable(Find_POS(path_value + 11))) && (path_taken[path_value].Down == false) && (last_move != 4))
			{
				//cout << "\t \t \t";
				//cout << "::" << temp->next->next->next->next->next->next->next->next->next->next->next->square[1][1] << "::";
				temp = Move_DOWN(path.back());
				path_taken[path_value].Down = true;
				path_value += 11;
				solution.push(path_value);
				path.pop();
				path.push(temp);
				last_move = 1;
				//cout << "(LM Check)Advancing DOWN to POS.." << path_value << endl;
			}
			else if ((isPassable(Find_POS(path_value - 1))) && (path_taken[path_value].Left == false) && (last_move != 2))
			{
				//cout << "\t \t \t";
				//cout << "::" << temp->prev->square[1][1] << "::";
				temp = Find_POS(path_value - 1);
				//temp = Move_LEFT(path.back());
				path_taken[path_value].Left = true;
				path_value -= 1;
				solution.push(path_value);
				path.pop();
				path.push(temp);
				last_move = 3;
				//cout << "(LM Check)Advancing LEFT to POS.." << path_value << endl;
			}
			else if ((isPassable(Find_POS(path_value - 11))) && (path_taken[path_value].Up == false) && (last_move != 1))
			{
				//cout << "\t \t";
				//cout << "::" << temp->prev->prev->prev->prev->prev->prev->prev->prev->prev->prev->prev->square[1][1] << "::";
				temp = Find_POS(path_value - 11);
				//temp = Move_UP(path.back());
				path_taken[path_value].Up = true;
				path_value = path_value - 11;
				solution.push(path_value);
				path.pop();
				path.push(temp);
				last_move = 4;
				//cout << "(LM Check)Advancing UP to POS.." << path_value << endl;
			}
			else if ((isPassable(Find_POS(path_value + 11))) && (path_taken[path_value].Down == false))
			{

				temp = Move_DOWN(path.back());
				path_taken[path_value].Down = true;
				path_value += 11;
				solution.push(path_value);
				path.pop();
				path.push(temp);
				last_move = 1;
				//cout << "Advancing DOWN to POS.." << path_value << endl;
			}
			else if ((isPassable(Find_POS(path_value + 1))) && (path_taken[path_value].Right == false))
			{
				temp = Move_RIGHT(path.back());
				path_taken[path_value].Right = true;
				path_value += 1;
				solution.push(path_value);
				path.pop();
				path.push(temp);
				last_move = 2;
				//cout << "Advancing RIGHT to POS.." << path_value << endl;
			}
			else if ((isPassable(Find_POS(path_value - 1))) && (path_taken[path_value].Left == false))
			{
				temp = Find_POS(path_value - 1);
				//temp = Move_LEFT(path.back());
				path_taken[path_value].Left = true;
				path_value -= 1;
				solution.push(path_value);
				path.pop();
				path.push(temp);
				last_move = 3;
				//cout << "Advancing LEFT to POS.." << path_value << endl;
			}
			else if ((isPassable(Find_POS(path_value - 11))) && (path_taken[path_value].Up == false))
			{
				temp = Find_POS(path_value - 11);
				//temp = Move_UP(path.back());
				path_taken[path_value].Up = true;
				path_value = path_value - 11;
				solution.push(path_value);
				path.pop();
				path.push(temp);
				last_move = 4;
				//cout << "Advancing UP to POS.." << path_value << endl;
			}
			else
			{
				cout << "Pop last place of queue, no direction available" << endl;
				path.pop();
			}
		} while (!path.empty());
		return false;
	}
	bool Find_Path(GamePiece* player, int start, int end)
	{
		// Up = -9 places in list
		// Right = +1 places in list
		// Down = +9 places in list
		// Left = -1 places in list

		stack<GamePiece*> path;
		GamePiece* temp = player;
		DirectionTaken path_taken[125];
		int path_value = start;
		int last_move = 0;			// 1 = Down; 2 = Right; 3 = Left; 4 = Up;
		//temp = Shortcut(temp);
		path.push(temp);
		
		do
		{
			if (path.top()->square[1][1] == 20)
			{
				cout << "Solution found...\n";
				while (!path.empty())
				{
					cout << path.top() << " <- ";
					path.pop();
				}
				cout << "\n";
				return true;
			}
			else if ((isPassable(Find_POS(path_value + 1))) && (path_taken[path_value].Right == false) && (last_move != 3))
			{
				temp = Move_RIGHT(path.top());
				path_taken[path_value].Right = true;
				path_value += 1;
				//path.pop();
				path.push(temp);
				last_move = 2;
				//cout << "(LM Check)Advancing RIGHT to POS.." << path_value << endl;
			}
			else if ((isPassable(Find_POS(path_value + 11))) && (path_taken[path_value].Down == false) && (last_move != 4))
			{
				temp = Move_DOWN(path.top());
				path_taken[path_value].Down = true;
				path_value += 11;
				//path.pop();
				path.push(temp);
				last_move = 1;
				//cout << "(LM Check)Advancing DOWN to POS.." << path_value << endl;
			}
			else if ((isPassable(Find_POS(path_value - 1))) && (path_taken[path_value].Left == false) && (last_move != 2))
			{
				temp = Find_POS(path_value - 1);
				//temp = Move_LEFT(path.top());
				path_taken[path_value].Left = true;
				path_value -= 1;
				//path.pop();
				path.push(temp);
				last_move = 3;
				//cout << "(LM Check)Advancing LEFT to POS.." << path_value << endl;
			}
			else if ((isPassable(Find_POS(path_value - 11))) && (path_taken[path_value].Up == false) && (last_move != 1))
			{
				temp = Find_POS(path_value - 11);
				//temp = Move_UP(path.top());
				path_taken[path_value].Up = true;
				path_value = path_value - 11;
				//path.pop();
				path.push(temp);
				last_move = 4;
				//cout << "(LM Check)Advancing UP to POS.." << path_value << endl;
			}
			else if ((isPassable(Find_POS(path_value + 11))) && (path_taken[path_value].Down == false))
			{
				temp = Move_DOWN(path.top());
				path_taken[path_value].Down = true;
				path_value += 11;
				//path.pop();
				path.push(temp);
				last_move = 1;
				//cout << "Advancing DOWN to POS.." << path_value << endl;
			}
			else if ((isPassable(Find_POS(path_value + 1))) && (path_taken[path_value].Right == false))
			{
				temp = Move_RIGHT(path.top());
				path_taken[path_value].Right = true;
				path_value += 1;
				//path.pop();
				path.push(temp);
				last_move = 2;
				//cout << "Advancing RIGHT to POS.." << path_value << endl;
			}
			else if ((isPassable(Find_POS(path_value - 1))) && (path_taken[path_value].Left == false))
			{
				temp = Find_POS(path_value - 1);
				//temp = Move_LEFT(path.top());
				path_taken[path_value].Left = true;
				path_value -= 1;
				//path.pop();
				path.push(temp);
				last_move = 3;
				//cout << "Advancing LEFT to POS.." << path_value << endl;
			}
			else if ((isPassable(Find_POS(path_value - 11))) && (path_taken[path_value].Up == false))
			{
				temp = Find_POS(path_value - 11);
				//temp = Move_UP(path.top());
				path_taken[path_value].Up = true;
				path_value = path_value - 11;
				//path.pop();
				path.push(temp);
				last_move = 4;
				//cout << "Advancing UP to POS.." << path_value << endl;
			}
			else
			{
				cout << "Pop top of stack, no direction available" << endl;
				path.pop();
			}
		} while (!path.empty());
		return false;
	}
	GamePiece* Find_POS(int val)
	{
		if (val < 0)
		{
			return NULL;
		}
		GamePiece* temp = head;
		for (int x = 0; x < val; x++)
		{
			temp = temp->next;
		}
		return temp;
	}
	bool FindUsingHeap(int start, int end)
	{
		// Up = -9 places in list
		// Right = +1 places in list
		// Down = +9 places in list
		// Left = -1 places in list

		Heap_Path hp[125];
		int moveNumber = 1;
		int path_value = start;
		hp[moveNumber - 1].movePosition = path_value;
		hp[moveNumber - 1].moveNumber = moveNumber;

		int last_move = 0;		// 1 = Down; 2 = Right; 3 = Left; 4 = Up;
		DirectionTaken path_taken[125];
		bool solvable = false;
		do
		{
			if (Find_POS(hp[moveNumber - 1].movePosition)->square[1][1] == 20)
			{
				cout << "Solution found...\n";
				solvable = true;
				cout << "Start at position: " << start << endl;
				for (int x = 1; x < moveNumber; x++)
				{
					cout << "Move " << x << " to " << hp[x].movePosition << endl;
				}
				cout << "\n";
				int n = sizeof(hp) / sizeof(hp[0]);
				ConvertToHeap(hp, n);
				cout << "After conversion to Heap: " << endl;
				for (int x = 1; x < moveNumber; x++)
				{
					cout << "Move " << x << " to " << hp[x].movePosition << endl;
				}
				return true;
			}
			else if ((isPassable(Find_POS(path_value + 1))) && (path_taken[path_value].Right == false) && (last_move != 3))
			{
				path_taken[path_value].Right = true;
				path_value += 1;
				hp[moveNumber].movePosition = path_value;
				last_move = 2;
				moveNumber++;
				hp[moveNumber].moveNumber = moveNumber;
			}
			else if ((isPassable(Find_POS(path_value + 11))) && (path_taken[path_value].Down == false) && (last_move != 4))
			{
				path_taken[path_value].Down = true;
				path_value += 11;
				hp[moveNumber].movePosition = path_value;
				last_move = 1;
				moveNumber++;
				hp[moveNumber].moveNumber = moveNumber;
			}
			else if ((isPassable(Find_POS(path_value - 1))) && (path_taken[path_value].Left == false) && (last_move != 2))
			{
				path_taken[path_value].Left = true;
				path_value -= 1;
				hp[moveNumber].movePosition = path_value;
				last_move = 3;
				moveNumber++;
				hp[moveNumber].moveNumber = moveNumber;
			}
			else if ((isPassable(Find_POS(path_value - 11))) && (path_taken[path_value].Up == false) && (last_move != 1))
			{
				path_taken[path_value].Up = true;
				path_value = path_value - 11;
				hp[moveNumber].movePosition = path_value;
				last_move = 4;
				moveNumber++;
				hp[moveNumber].moveNumber = moveNumber;
			}
			else if ((isPassable(Find_POS(path_value + 11))) && (path_taken[path_value].Down == false))
			{
				path_taken[path_value].Down = true;
				path_value += 11;
				hp[moveNumber].movePosition = path_value;
				last_move = 1;
				moveNumber++;
				hp[moveNumber].moveNumber = moveNumber;
			}
			else if ((isPassable(Find_POS(path_value + 1))) && (path_taken[path_value].Right == false))
			{
				path_taken[path_value].Right = true;
				path_value += 1;
				hp[moveNumber].movePosition = path_value;
				last_move = 2;
				moveNumber++;
				hp[moveNumber].moveNumber = moveNumber;
			}
			else if ((isPassable(Find_POS(path_value - 1))) && (path_taken[path_value].Left == false))
			{
				path_taken[path_value].Left = true;
				path_value -= 1;
				hp[moveNumber].movePosition = path_value;
				last_move = 3;
				moveNumber++;
				hp[moveNumber].moveNumber = moveNumber;
			}
			else if ((isPassable(Find_POS(path_value - 11))) && (path_taken[path_value].Up == false))
			{
				path_taken[path_value].Up = true;
				path_value = path_value - 11;
				hp[moveNumber].movePosition = path_value;
				last_move = 4;
				moveNumber++;
				hp[moveNumber].moveNumber = moveNumber;
			}
			else
			{
				cout << "No direction available" << endl;
				solvable = true;
			}
		} while (!solvable);
		return false;
	}
	bool FindUsingBFS(int start, int end, int last)
	{
		// Up = -9 places in list
		// Right = +1 places in list
		// Down = +9 places in list
		// Left = -1 places in list

		queue<GamePiece*> path;
		queue<int> solution;
		GamePiece* temp = new GamePiece();

		temp = Find_POS(start);
		//temp = Shortcut(temp);
		int path_value = start;
		int last_move = last;		// 1 = Down; 2 = Right; 3 = Left; 4 = Up;
		path.push(temp);
		DirectionTaken path_taken[125];
		solution.push(path_value);

		do
		{
			if (path.back()->square[1][1] == 20)
			{
				cout << "\nSolution found...\n";
				return true;
			}
			else
			{
				path.pop();
				if (isPassable(Find_POS(start + 1)) && (path_taken[path_value].Right == false) && (last_move != 3))
				{
					cout << start << " to " << start + 1 << "\n";
					FindUsingBFS(start + 1, end, 2);
				}
				if (isPassable(Find_POS(start - 1)) && (path_taken[path_value].Left == false) && (last_move != 2))
				{
					cout << start << " to " << start - 1 << "\n";
					FindUsingBFS(start - 1, end, 3);
				}
				if (isPassable(Find_POS(start + 11)) && (path_taken[path_value].Down == false) && (last_move != 4))
				{
					cout << start << " to " << start + 11 << "\n";
					FindUsingBFS(start + 11, end, 1);
				}
				if (isPassable(Find_POS(start - 11)) && (path_taken[path_value].Up == false) && (last_move != 1))
				{
					cout << start << " to " << start - 11 << "\n";
					FindUsingBFS(start - 11, end, 4);
				}
			}
		} while (!path.empty());
		return false;
	}
	bool FindUsingDFS(int start, int end, int last)
	{
		// Up = -9 places in list
		// Right = +1 places in list
		// Down = +9 places in list
		// Left = -1 places in list

		stack<GamePiece*> path;
		queue<int> solution;
		GamePiece* temp = new GamePiece();

		temp = Find_POS(start);
		//temp = Shortcut(temp);
		int path_value = start;
		int last_move = last;		// 1 = Down; 2 = Right; 3 = Left; 4 = Up;
		path.push(temp);
		DirectionTaken path_taken[125];
		solution.push(path_value);

		do
		{
			if (path.top()->square[1][1] == 20)
			{
				cout << "\nSolution found...\n";
				return true;
			}
			else
			{
				path.pop();
				if (isPassable(Find_POS(start + 1)) && (path_taken[path_value].Right == false) && (last_move != 3))
				{
					cout << start << " to " << start + 1 << "\n";
					FindUsingDFS(start + 1, end, 2);
				}
				if (isPassable(Find_POS(start - 1)) && (path_taken[path_value].Left == false) && (last_move != 2))
				{
					cout << start << " to " << start - 1 << "\n";
					FindUsingDFS(start - 1, end, 3);
				}
				if (isPassable(Find_POS(start + 11)) && (path_taken[path_value].Down == false) && (last_move != 4))
				{
					cout << start << " to " << start + 11 << "\n";
					FindUsingDFS(start + 11, end, 1);
				}
				if (isPassable(Find_POS(start - 11)) && (path_taken[path_value].Up == false) && (last_move != 1))
				{
					cout << start << " to " << start - 11 << "\n";
					FindUsingDFS(start - 11, end, 4);
				}
			}
		} while (!path.empty());
		return false;
	}
};
int main()
{
	GameBoard gb;
	for (int x = 0; x < 121; x++)
	{
		gb.Add_Piece();
	}

	cout << "Game initialized...\n";

	//Gets all passing blocks from txt file
	ifstream passing_blocks;
	passing_blocks.open("passable_blocks_file_v2.txt");
	int i;
	while (passing_blocks >> i)
	{
		gb.Passable(i);
	}
	passing_blocks.close();

	//Reads input_file.txt to determine player POS and end POS
	ifstream maze_detail;
	maze_detail.open("input_file.txt");
	int c, d, e, f, g, h;
	while (maze_detail >> c >> d >> e >> f >> g >> h)
	{
		gb.Player(c);
		gb.End(d);
	}
	maze_detail.close();
	
	cout << "\nPrinting Linked List Values\n";
	gb.Print_To_Text();

	GamePiece* plyr = gb.Find_POS(c);
	GamePiece* _end = gb.Find_POS(d);
	cout << c << " = starting POS\n";

	cout << "Finding path using QUEUES...\n";
	gb.FindUsingQueues(c, d);

	cout << "Finding path using STACK...\n";
	gb.Find_Path(plyr, c, d); 
	
	cout << "Finding path using HEAP...\n";
	gb.FindUsingHeap(c, d);

	cout << "Finding path using BFS...\n";
	gb.FindUsingBFS(c, d, NULL);

	cout << "Finding path using DFS...\n";
	gb.FindUsingDFS(c, d, NULL);
	return 0;
}
