#include "FIFO.h"
#define reference_type 1201 //參考串從1-1200
void  FIFO(vector<int> references, vector<int> dirtys,int frames_num) {
	queue<int> frames;
	bool inQ[reference_type] = {false};
	bool pages_dirty[reference_type] = {false};
	int  page_fault = 0, write_back=0;
	for (int i = 0; i < references.size(); i++) {
		if (inQ[references[i]]) {
			if (dirtys[i]) {
				pages_dirty[references[i]] = dirtys[i];
			}
		}
		else {
			if(frames.size() < frames_num) {
				frames.push(references[i]);
				inQ[references[i]] = true;
				pages_dirty[references[i]] = dirtys[i];
			}
			else {
				if (pages_dirty[frames.front()]) {
					write_back++;
				}
				inQ[frames.front()] = false;
				pages_dirty[frames.front()] = false;
				frames.pop();
				frames.push(references[i]);
				inQ[references[i]] = true;
				pages_dirty[references[i]] = dirtys[i];
			}
			page_fault++;
		}
	}
	//cost:總interrupt數量 
	cout << "FIFO Frame數量:"<<frames_num << "  page fault:" << page_fault << "  write back:" << write_back <<"  cost:"<<page_fault+ write_back <<endl;
}