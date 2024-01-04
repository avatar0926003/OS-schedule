#include "ARB.h"
#define reference_type 1201 //把σ﹃眖1-1200
void  ARB(vector<int> references, vector<int> dirtys, int frames_num) {
	int interval = 30;
	vector<int> frames;
	frames.reserve(frames_num);
	vector<bool> frames_pages_dirty(frames_num, false);
	vector<int> frames_reference_time(frames_num, 0);//秈frame丁
	vector<int> reference_history(reference_type,0x0000);//程碭Ω把σ魁
	vector<int> reference_bit(reference_type, 0);//硂Ω琌Τ把σ
	int page_fault = 0, write_back = 0, interval_interrupt=0;
	for (int i = 0; i < references.size(); i++) {
		reference_bit[references[i]] = 1;
		if (find(frames.begin(), frames.end(), references[i]) != frames.end()) {//frameΤт
			if (dirtys[i]) {
				vector<int>::iterator it = find(frames.begin(), frames.end(), references[i]);//тヘ夹pageframaddress
				int el_distance = distance(frames.begin(), it);//把σ瞷竚frame
				frames_pages_dirty[el_distance] = dirtys[i];
			}
		}
		else {
			if (frames.size() < frames_num) {
				frames.push_back(references[i]);
				vector<int>::iterator it = find(frames.begin(), frames.end(), references[i]);//тヘ夹pageframaddress
				int el_distance = distance(frames.begin(), it);//把σ瞷竚frame
				frames_reference_time[el_distance] = i;//秈frame丁
				frames_pages_dirty[el_distance] = dirtys[i];
			}
			else {
				int replace_value = reference_history[frames[0]];
				int replace_index = 0;//﹍frame材竚
				int early_reference_time = frames_reference_time[0];
				for (int j = 1; j < frames_num; j++) {
					if (reference_history[frames[j]] < replace_value) {//珼匡Reference程
						replace_index = j;
						early_reference_time = frames_reference_time[j];
					}
					else if (reference_history[j]== replace_value){//狦Reference妓玥ノFIFO
						if (frames_reference_time[j] < early_reference_time) {
							replace_index = j;
							early_reference_time = frames_reference_time[j];
						}
					}
				}
				if (frames_pages_dirty[replace_index]) {
					write_back++;
				}
				frames_reference_time[replace_index] = i;
				frames_pages_dirty[replace_index] = dirtys[i];
				frames[replace_index] = references[i];	
			}
			page_fault++;
		}
		if(i%interval==0){
			interval_interrupt++;
			for (int j = 1; j < reference_type; j++) {
				reference_history[j] = reference_history[j] >> 1;
				reference_history[j] |= 0x007f;
				if (reference_bit[j] == 1)
				{
					reference_history[j] |= 0x0080;
				}			
				reference_bit[j] = 0;
			}
		}
	}
	cout << "ARB Frame计秖:" << frames_num << "  page fault:" << page_fault << "  write back:" << write_back << "  interval interrupt:" << interval_interrupt << "  cost:" << page_fault + write_back+ interval_interrupt << endl;

}