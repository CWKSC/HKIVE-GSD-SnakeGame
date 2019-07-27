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

	// 初始化動作 //
	SnakeGame() {
		gameBoard.init();
		snake.init();
		snake.snakeBody.push_front({ 1, 0 });
		snake.snakeBody.push_front({ 2, 0 });
		gameBoard.addSnakeToBoard(snake);
		FoodControl::generateFood(gameBoard, foodList);
	}

	// 畫面列印 //
	void Draw() {
		system("cls"); //清空畫面

		gameBoard.printBoard(); //打印 board
		std::cout << '\n';
		std::cout << "Control the snake (a,s,d,w): \n";
		std::cout << '\n';
		std::cout << '\n';
		snake.print_Mark_Step_Size(); // 打印 mark, step, size
		std::cout << '\n';
		snake.printStomach(); // 打印 stomach
		std::cout << '\n';

		// 測試用，檢測可用空間
		//gameBoard.printAvailableSpace();

		// 把光標移動到適當輸入的位置 //
#define InputPositionIndex  GameBoardMaxY + 3
		gotoxy(sizeof("Control the snake(a,s,d,w) : ") - 1, InputPositionIndex);
	}

	// 獲取輸入 //
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

	// 邊界檢測 //
	bool outBoundary(Point movePoint) {
		return movePoint.x < 0 || 
			   movePoint.y < 0 ||
			   movePoint.x >= GameBoardMaxX ||
			   movePoint.y >= GameBoardMaxY;
	}

	// 邏輯處理層 //
	void Logic(Point movePoint) {

		// 邊界檢測 //
		if (outBoundary(movePoint)) GameOver();
		
		// 新位置是否食物 //
		if (FoodControl::isItFoodOnBoard(gameBoard, movePoint)) {

			Food food = (Food)gameBoard.board[movePoint.x][movePoint.y];
			
			// 胃是否空 //
			if (snake.stomach.empty()) {
				snake.stomach.push(food);
				snake.mark += 3;
			}
			else {
				// 胃不是空的情況 //

				Food stomachTopFood = snake.stomach.top();

				// 配對引號食物 //
				if (snake.matchPairOfQuotes(stomachTopFood, food)) {
					snake.stomach.pop();
					snake.mark += 5;
				}
				// 配對括弧食物 //
				else if (snake.matchPairOfbrackets(stomachTopFood, food)) {
					snake.stomach.pop();
					snake.mark += 8;
				}
				// 沒有食物被配對 //
				else {
					snake.stomach.push(food);
					snake.mark += 3;
				}
			}

			// 食物被吃掉，在 foodList 中移除
			FoodControl::removeFormFoodList(foodList, movePoint);
		}

		// 胃的大小大於五，到達上限死亡 //
		if (snake.stomach.size() > 5) {
			GameOver();
		}

		// 檢查該位置是否蛇的身體，是否吃到自己 //
		if (snake.isItEatSelf(movePoint)) {
			GameOver();
		}
		
	}

	// 後續處理，有關數據的更新 //
	void Updata(Point movePoint) {

		// 新位置是否食物 //
		if (FoodControl::isItFoodOnBoard(gameBoard, movePoint)) {
			snake.moveTo_AndGrowUp(movePoint); // 長大
		}
		else {
			// 在 board 移除蛇的尾巴，並移動 //
			gameBoard.removeToBoard(snake.snakeBody.back());
			snake.moveTo(movePoint);
		}

		// 把整條蛇加載到 board 
		gameBoard.addSnakeToBoard(snake);

		// 生成食物 //
		if (FoodControl::isItTimeToGenerateFood(snake.step)) { // 是否一個時刻去生成食物
			FoodControl::generateFood(gameBoard, foodList); // 生成食物
		}

		// 把 foodList 加載到 board 
		gameBoard.addFoodListToBoard(foodList);
	}

	// 遊戲結束 //
	void GameOver() {
		gotoxy(0, GameBoardMaxY + 5); //移動光標到適當位置
		std::cout << "--- Game Over ---\n";
		snake.print_Mark_Step_Size();  // 打印 mark, step, size
		gotoxy(sizeof("--- Game Over ---"), GameBoardMaxY + 5);
		system("pause");
		exit(0);
	}

};


