#pragma once

#include <conio.h>

#include "GameBoard.h"
#include "Snake.h"
#include "FoodList.h"
#include "FoodControl.h"

#include "gotoxy.h"

class SnakeGame {
public:
	GameBoard gameBoard;
	Snake snake;
	FoodList foodList;

	// ��l�ưʧ@ //
	SnakeGame() {
		gameBoard.init();
		snake.init();
		snake.snakeBody.push_front({ 1, 0 });
		snake.snakeBody.push_front({ 2, 0 });
		gameBoard.addSnakeToBoard(snake);
		FoodControl::generateFood(gameBoard, foodList);
	}

	// �e���C�L //
	void Draw() {
		system("cls"); //�M�ŵe��

		gameBoard.printBoard(); //���L board
		std::cout << '\n';
		std::cout << "Control the snake (a,s,d,w): \n";
		std::cout << '\n';
		std::cout << '\n';
		snake.print_Mark_Step_Size(); // ���L mark, step, size
		std::cout << '\n';
		snake.printStomach(); // ���L stomach
		std::cout << '\n';

		// ���եΡA�˴��i�ΪŶ�
		//gameBoard.printAvailableSpace();

		// ����в��ʨ�A���J����m //
#define InputPositionIndex  GameBoardMaxY + 3
		gotoxy(sizeof("Control the snake(a,s,d,w) : ") - 1, InputPositionIndex);
	}

	// �����J //
	Point Input() {
		Point movePoint = snake.snakeBody.front();;

		for (;;) { 

			switch (_getch())
			{
			case 'w': movePoint.y -= 1; break;
			case 's': movePoint.y += 1; break;
			case 'a': movePoint.x -= 1; break;
			case 'd': movePoint.x += 1; break;
			default: continue;  // back to front
			}

			break; //leave
		}

		return movePoint;
	}

	// ����˴� //
	bool outBoundary(Point movePoint) {
		return movePoint.x < 0 || 
			   movePoint.y < 0 ||
			   movePoint.x >= GameBoardMaxX ||
			   movePoint.y >= GameBoardMaxY;
	}

	// �޿�B�z�h //
	void Logic(Point movePoint) {

		// ����˴� //
		if (outBoundary(movePoint)) GameOver();
		
		// �s��m�O�_���� //
		if (FoodControl::isItFoodOnBoard(gameBoard, movePoint)) {

			Food food = (Food)gameBoard.board[movePoint.x][movePoint.y];
			
			// �G�O�_�� //
			if (snake.stomach.empty()) {
				snake.stomach.push(food);
				snake.mark += 3;
			}
			else {
				// �G���O�Ū����p //

				Food stomachTopFood = snake.stomach.top();

				// �t��޸����� //
				if (snake.matchPairOfQuotes(stomachTopFood, food)) {
					snake.stomach.pop();
					snake.mark += 5;
				}
				// �t��A������ //
				else if (snake.matchPairOfbrackets(stomachTopFood, food)) {
					snake.stomach.pop();
					snake.mark += 8;
				}
				// �S�������Q�t�� //
				else {
					snake.stomach.push(food);
					snake.mark += 3;
				}
			}

			// �����Q�Y���A�b foodList ������
			FoodControl::removeFormFoodList(foodList, movePoint);
		}

		// �G���j�p�j�󤭡A��F�W�����` //
		if (snake.stomach.size() > 5) {
			GameOver();
		}

		// �ˬd�Ӧ�m�O�_�D������A�O�_�Y��ۤv //
		if (snake.isItEatSelf(movePoint)) {
			GameOver();
		}
		
	}

	// ����B�z�A�����ƾڪ���s //
	void Updata(Point movePoint) {

		// �s��m�O�_���� //
		if (FoodControl::isItFoodOnBoard(gameBoard, movePoint)) {
			snake.moveTo_AndGrowUp(movePoint); // ���j
		}
		else {
			// �b board �����D�����ڡA�ò��� //
			gameBoard.removeToBoard(snake.snakeBody.back());
			snake.moveTo(movePoint);
		}

		// �����D�[���� board 
		gameBoard.addSnakeToBoard(snake);

		// �ͦ����� //
		if (FoodControl::isItTimeToGenerateFood(snake.step)) { // �O�_�@�Ӯɨ�h�ͦ�����
			FoodControl::generateFood(gameBoard, foodList); // �ͦ�����
		}

		// �� foodList �[���� board 
		gameBoard.addFoodListToBoard(foodList);
	}

	// �C������ //
	void GameOver() {
		gotoxy(0, GameBoardMaxY + 5); //���ʥ��Ш�A���m
		std::cout << "--- Game Over ---\n";
		snake.print_Mark_Step_Size();  // ���L mark, step, size
		gotoxy(sizeof("--- Game Over ---"), GameBoardMaxY + 5);
		system("pause");
		exit(0);
	}

};


