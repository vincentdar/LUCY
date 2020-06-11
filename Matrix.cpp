//#include "Matrix.h"
//
//Matrix::Matrix()
//{
//	for (int i = 0; i < 5; i++)
//	{
//		for (int j = 0; j < 8; j++)
//		{
//			MATRIX[i][j] = nullptr;
//		}
//	}
//}
//
//void Matrix::AddUnit(BaseUnit* b)
//{
//	if (MATRIX[b->GetPosition().y][b->GetPosition().x] == nullptr)
//	{
//		MATRIX[b->GetPosition().y][b->GetPosition().x] = b;
//	}
//	else
//	{
//		LUCY::Logger::PrintLn("Cannot Add Unit");
//	}
//
//}
//
//void Matrix::DeleteUnit(int row, int col)
//{
//	if (MATRIX[row][col] != nullptr)
//	{
//		delete MATRIX[row][col];
//	}
//	MATRIX[row][col] = NULL;
//}
//
//void Matrix::Update()
//{
//	for (int i = 0; i < 5; i++)
//	{
//		for (int j = 0; j < 8; j++)
//		{
//			MATRIX[i][j]->Update();
//		}
//	}
//}
//
//BaseUnit* Matrix::at(int row, int col)
//{
//	return MATRIX[row][col];
//}
