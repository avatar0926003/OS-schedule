// AOS_HW1.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#include <iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include <fstream>
#include <string>
#include "FIFO.h"
#include "OPT.h"
#include "ARB.h"
#include "LDF.h"

#define references_maxnum 300000

using namespace std;
int main()
{
	cout << "讀檔模式請輸入1" << endl<< "程式產生檔案模式請輸入2" << endl;
	cout << "請輸入";
	int answer;
	while (cin >> answer) {
		if (answer == 1) {
			cout << "您選擇讀檔模式" << endl;
			break;
		}
		else if (answer == 2) {
			cout << "您選擇程式產生檔案模式" << endl;
			break;
		}
		else{
			cout << "請重新輸入" << endl;
		}
	}
	cout << "處理中..." << endl;
	vector<int> references1;
	references1.reserve(references_maxnum);
	vector<int> dirtys1;
	dirtys1.reserve(references_maxnum);
	vector<int> references2;
	references2.reserve(references_maxnum);
	vector<int> dirtys2;
	dirtys2.reserve(references_maxnum);
	vector<int> references3;
	references3.reserve(references_maxnum);
	vector<int> dirtys3;
	dirtys3.reserve(references_maxnum);
	if (answer == 1) {
		ifstream myFile;
		myFile.open("references1.txt");
		int page,dirty;
		while (myFile >> page >> dirty) {
			references1.push_back(page);
			dirtys1.push_back(dirty);
		}
		myFile.close();
		myFile.open("references2.txt");
		while (myFile >> page >> dirty) {
			references2.push_back(page);
			dirtys2.push_back(dirty);
		}
		myFile.close();
		myFile.open("references3.txt");
		while (myFile >> page >> dirty) {
			references3.push_back(page);
			dirtys3.push_back(dirty);
		}
		myFile.close();
	}
	else {
		//字串1
		srand(time(NULL));
		for (int page_cnt = 0; page_cnt < references_maxnum;) {
			int each_continous = 1 + rand() % 20;
			
			if (each_continous + page_cnt > references_maxnum) {
				each_continous = references_maxnum - page_cnt;
			}
			page_cnt += each_continous;//計算總共多少參考數量
			int head = 1 + rand() % 1200;
			for (int i = 0; i < each_continous; i++, head++) {
				references1.push_back(1 + head % 1200);
				dirtys1.push_back(rand() % 2);
			}
		}
		//ofstream newFile;
		//newFile.open("references1.txt");
		//for (int i = 0; i < references1.size(); i++) {
		//	newFile << references1[i] <<" "<< dirtys1[i]<<endl;
		//}
		//cout << "references1 ok" << endl;
		//newFile.close();
		////字串2
		for (int page_cnt = 0; page_cnt < references_maxnum;) {
			int each_continous = references_maxnum / (120 + rand() % 181);
			if (each_continous + page_cnt > references_maxnum) {
				each_continous = references_maxnum - page_cnt;
			}
			page_cnt += each_continous;//計算總共多少參考數量
			int cycle_length = 20+ rand() % 30;//範圍
			int head = rand() % 1200;
			for (int i = 0; i < each_continous; i++) {
				references2.push_back(1 + (head + rand() % cycle_length) % 1200);
				dirtys2.push_back(rand() % 2);
			}
		}
		//newFile.open("references2.txt");
		//for (int i = 0; i < references2.size(); i++) {
		//	newFile << references2[i] << " " << dirtys2[i] << endl;
		//}
		//cout << "references2 ok" << endl;
		//newFile.close();
		for (int page_cnt = 0; page_cnt < references_maxnum;) {
			int each_continous = references_maxnum / (120 + rand() % 181);
			if (each_continous + page_cnt > references_maxnum) {
				each_continous = references_maxnum - page_cnt;
			}
			page_cnt += each_continous;//計算總共多少參考數量
			int cycle_length = 151 + rand() % 30;//範圍
			int head = rand() % 1200;
			int k = 0;
			for (int i = 0; i < each_continous; i++,k++) {
				references3.push_back(1+(head+k%cycle_length) % 1200);
				dirtys3.push_back(rand() % 2);
			}
		}
		//newFile.open("references3.txt");
		//for (int i = 0; i < references3.size(); i++) {
		//	newFile << references3[i] << " " << dirtys3[i] << endl;
		//}
		//cout << "references3 ok" << endl;
		//newFile.close();
	}
	cout << "開始執行頁面替換..." << endl;
	cout << "參考1" << endl;
	for (int i = 1;i<=5; i++) {
		FIFO(references1,dirtys1,30*i);
		OPT (references1,dirtys1,30*i);
		ARB (references1,dirtys1,30*i);
		LDF (references1,dirtys1,30*i);
	}	
	cout << "參考2" << endl;
	for (int i = 1; i <= 5; i++) {
		FIFO(references2, dirtys2, 30 * i);
		OPT (references2, dirtys2, 30 * i);
		ARB (references2, dirtys2, 30 * i);
		LDF (references2, dirtys2, 30 * i);
	}
	cout << "參考3" << endl;
	for (int i = 1; i <= 5; i++) {
		FIFO(references3, dirtys3, 30 * i);
		OPT(references3, dirtys3, 30 * i);
		ARB(references3, dirtys3, 30 * i);
		LDF(references3, dirtys3, 30 * i);
	}
}

