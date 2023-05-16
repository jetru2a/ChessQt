#pragma once
#include "Piece.hpp"
#include "Pawn.hpp"




#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

TEST(Board, createBoard) {
	gameLogic::Board board("8/8/8/4k3/8/8/8/4K3 w KQkq - 0 1");
	for (int i = 0; i < 64; i++) {
		if (i == 28)
			EXPECT_EQ(board.getPieceInfo(i % 8, i / 8), "bKing");
		else if(i == 60)
			EXPECT_EQ(board.getPieceInfo(i % 8, i / 8), "wKing");
		else
			EXPECT_EQ(board.getPieceInfo(i % 8, i / 8), "");
	}
}

TEST(Board, legalMovement) {
	gameLogic::Board board("rnbqkbnr/pppppppp/8/8/7b/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	EXPECT_EQ(board.moveIsLegal(4, 6, 4, 6), false);
	EXPECT_EQ(board.moveIsLegal(4, 6, 4, 7), false);
	EXPECT_EQ(board.moveIsLegal(5, 6, 5, 4,true), false);
	EXPECT_EQ(board.moveIsLegal(4, 6, 4, 5, false), true);
	EXPECT_EQ(board.moveIsLegal(4,6,4,4),true);
	EXPECT_EQ(board.moveIsLegal(4, 6, 4, 4), true);

}
	
TEST(Board, movement) {
	gameLogic::Board board("rnbq1bnr/pppp1ppp/8/R7/3n2k1/3P4/PPP1PPP1/RNBQKBNR w KQkq - 0 1");
	board.confirmedMove(52,36);
	EXPECT_EQ(board.isCheck(38), true);
	board.confirmedMove(35, 45);
	EXPECT_EQ(board.isCheck(38), false);
	EXPECT_EQ(board.isCheck(60), true);
	EXPECT_EQ(board.getPieceInfo(60 % 8, 60 / 8), "wKingC");
	board.confirmedMove(59, 45);
	EXPECT_EQ(board.isMate(), true);
}

TEST(Board, kingAndPawn) {
	gameLogic::Board board("k7/7P/8/8/8/8/8/K7 b KQkq - 0 1");
	board.confirmedMove(0, 1);
	board.confirmedMove(15, 7);
	EXPECT_EQ(board.isCheck(1), true);
}

TEST(Board, selectable) {
	gameLogic::Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	EXPECT_EQ(board.pieceSelectable(0,0), false);
	EXPECT_EQ(board.pieceSelectable(4,4), false);
	EXPECT_EQ(board.pieceSelectable(7,7), true);
}

TEST(Pieces, showPiece) {
	gameLogic::Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	for (int i = 0; i < 16; i++)
		EXPECT_EQ(board.getPieceInfo(i%8, i/8)[0], 'b');
	for (int i = 48; i < 64; i++)
		EXPECT_EQ(board.getPieceInfo(i%8, i/8)[0], 'w');

}
TEST(Pawn, movement) {
	gameLogic::Pawn pawn("black");
	EXPECT_EQ(pawn.canMove(1, 1, true), 9);
	EXPECT_EQ(pawn.canMove(0, 2, false), 8);
	EXPECT_EQ(pawn.canMove(0, 2, true), 0);
}

#endif
