#include "FIFO.h"
#include "math.h"
#define reference_type 1200 //參考串從1-1200
bool compare(int a,int b) {
	if (a > b)
		return true;
	else
		return false;
}
bool is_anti(int a, int b) {
	if (a < b)
		return true;
	else
		return false;
}
int findsmall(int a, int b) {
	if (a > b)
		return b;
	else
		return a;
}


void  LDF(vector<int> references, vector<int> dirtys, int frames_num) {
	bool pages_dirty[reference_type+1] = {false};
	bool inQ[reference_type+1] = {false};
	vector<int> frames;
	int  page_fault = 0, write_back = 0;
	for (int i = 0; i < references.size(); i++) {
		if (inQ[references[i]]) {
			if (dirtys[i]) {
				pages_dirty[references[i]] = dirtys[i];
			}
		}
		else {
			if (frames.size() < frames_num) {
				frames.push_back(references[i]);
				inQ[references[i]] = true;
				pages_dirty[references[i]] = dirtys[i];
			}
			else {
				int replace_distance =-1;
				int replaceindex = -1;
				int current_distance;
				int anti;
				for (int j = 0;j< frames.size(); j++) {
					if (compare(references[i],frames[j])) {
						int min1 =references[i] - frames[j];//逆時針
						int min2 = reference_type - min1;//順時針
						current_distance = findsmall(min1, min2);//找出距離
						anti = is_anti(min1, min2);
					}
					else {
						int min1 = reference_type- frames[j]+references[i];//逆時針
						int min2 = reference_type - min1;//順時針
						current_distance = findsmall(min1, min2);//找出距離
						anti = is_anti(min1, min2);
					}
					if (replace_distance < current_distance) {
						replace_distance = current_distance;
						replaceindex = j;
					}
					else if (replace_distance == current_distance) {
						if (anti){
							replace_distance = current_distance;
							replaceindex = j;							
						}
					}
				}						
				if (pages_dirty[frames[replaceindex]]) {
					write_back++;
				}
				inQ[frames[replaceindex]] = false;
				pages_dirty[frames[replaceindex]] = false;

				frames[replaceindex] = references[i];
				inQ[references[i]] = true;
				pages_dirty[references[i]] = dirtys[i];			
			}
			page_fault++;
		}
	}
	//cost:總interrupt數量 
	cout << "LDF Frame數量:" << frames_num << "  page fault:" << page_fault << "  write back:" << write_back << "  cost:" << page_fault + write_back << endl;
}