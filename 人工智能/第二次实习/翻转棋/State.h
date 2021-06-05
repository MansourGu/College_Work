#pragma once

#include "types.h"
#include "othello.h"

class State {
public:
	player Player;//�������
	player Opponent;
	board Board;
	int nMoves;//��һ�����߷�����, = Moves.size()
	std::vector<position> Moves;//��һ�����߷�
	position _p;//��һ�����ӵ�

	State(player p, player o, board b)
		:Player(p), Opponent(o), Board(b) {
		Moves = GetLegalMoves(&Board, &Player);
		nMoves = Moves.size();
	}

	State(const State& s) {
		Player = s.Player;
		Opponent = s.Opponent;
		Board = s.Board;
		nMoves = s.nMoves;
		Moves = s.Moves;
	}
	void clean() {
		Moves.swap(std::vector<position>());//vector<position>().swap(Moves);
	}
	bool is_terminated() { 
		return Moves.empty()/* && GetLegalMoves(&Board, &Opponent).empty()*/; 
	}
	
	//bool is_no_legal_moves() { return Moves.empty(); }

	position apply_random_action(board* b) {
		srand(time(NULL));
		int Choice = rand() % nMoves;
		PerformMove(b, &Moves[Choice], &Player);
		position ret = Moves[Choice];
		swap(Choice, --nMoves);
		return ret;
	}

	void swap(int a, int b) {
		position tmp = Moves[a];
		Moves[a] = Moves[b];
		Moves[b] = tmp;
	}

	float evaluate() {
		CountPiecesOfPlayer(&Board, &Player);
		CountPiecesOfPlayer(&Board, &Opponent);
		player winner;
		/*if (Player.Pieces == Opponent.Pieces) return 0.5;
		else*/ if (Player.Pieces > Opponent.Pieces) winner = Player;
		else winner = Opponent;
		return (float)(winner.AIPlayer ? 1 : 0);
	}
};