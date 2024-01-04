#include "OPT.h"
void  OPT(vector<int> references,vector<int> dirtys, int frames_num) {
	vector<int> frames;
	frames.reserve(frames_num);
	vector<bool> pages_dirty(frames_num, false);
	int  page_fault = 0, write_back = 0;
	vector<int> nextsame_references;//癘魁じ竚
	nextsame_references.resize(frames_num);
	for (int i = 0; i < references.size(); i++) {
		if (find(frames.begin(), frames.end(), references[i])  != frames.end()) {//frameΤт
			vector<int>::iterator it = find(frames.begin(), frames.end(), references[i]);//тヘ夹pageframaddress	
			int el_distance = distance(frames.begin(), it);//把σ瞷竚frame
			vector<int>::iterator ref_it = find(references.begin()+i+1, references.end(), references[i]);
			int ref_distance = distance(references.begin(), ref_it);
			nextsame_references[el_distance] = ref_distance;
			if (dirtys[i]) {
				pages_dirty[el_distance] = dirtys[i];
			}
		}
		else {//frame⊿Τт
			if (frames.size() < frames_num) {
				frames.push_back(references[i]);
				vector<int>::iterator it = find(frames.begin(), frames.end(), references[i]);
				int el_distance = distance(frames.begin(), it);//穝pageframe竚
				pages_dirty[el_distance] = dirtys[i];
				vector<int>::iterator ref_it = find(references.begin() + i + 1, references.end(), references[i]);
				int ref_distance = distance(references.begin(), ref_it);//тpage把σ竚
				nextsame_references[el_distance] = ref_distance;
			}
			else {
				int far = -1;
				int replace_index = 0;
				for (int j = 0; j < frames_num; j++) {
					if (far < nextsame_references[j]) {
						far = nextsame_references[j];
						replace_index = j;
					}			
				}
				frames[replace_index] = references[i];
				vector<int>::iterator ref_it = find(references.begin() + i + 1, references.end(), references[i]);
				int ref_distance = distance(references.begin(), ref_it);
				nextsame_references[replace_index] = ref_distance;
				if (pages_dirty[replace_index]) {
					write_back++;
				}
				pages_dirty[replace_index] = dirtys[i];
			}
			page_fault++;
		}
	}
	//cost:羆interrupt计秖 
	cout << "OPT Frame计秖:" << frames_num << "  page fault:" << page_fault << "  write back:" << write_back << "  cost:" << page_fault + write_back << endl;
}