#include "ARB.h"
#define reference_type 1201 //�ѦҦ�q1-1200
void  ARB(vector<int> references, vector<int> dirtys, int frames_num) {
	int interval = 30;
	vector<int> frames;
	frames.reserve(frames_num);
	vector<bool> frames_pages_dirty(frames_num, false);
	vector<int> frames_reference_time(frames_num, 0);//�i�Jframe���ɶ�
	vector<int> reference_history(reference_type,0x0000);//�̪�X�����ѦҬ���
	vector<int> reference_bit(reference_type, 0);//�o���O�_���Ѧ�
	int page_fault = 0, write_back = 0, interval_interrupt=0;
	for (int i = 0; i < references.size(); i++) {
		reference_bit[references[i]] = 1;
		if (find(frames.begin(), frames.end(), references[i]) != frames.end()) {//�bframe�����
			if (dirtys[i]) {
				vector<int>::iterator it = find(frames.begin(), frames.end(), references[i]);//��X�ؼ�page�bfram��address
				int el_distance = distance(frames.begin(), it);//�Ѧҭ����{�b��m�����frame
				frames_pages_dirty[el_distance] = dirtys[i];
			}
		}
		else {
			if (frames.size() < frames_num) {
				frames.push_back(references[i]);
				vector<int>::iterator it = find(frames.begin(), frames.end(), references[i]);//��X�ؼ�page�bfram��address
				int el_distance = distance(frames.begin(), it);//�Ѧҭ����{�b��m�����frame
				frames_reference_time[el_distance] = i;//�i�Jframe���ɶ�
				frames_pages_dirty[el_distance] = dirtys[i];
			}
			else {
				int replace_value = reference_history[frames[0]];
				int replace_index = 0;//��l�Ȭ�frame���Ĥ@�Ӧ�m
				int early_reference_time = frames_reference_time[0];
				for (int j = 1; j < frames_num; j++) {
					if (reference_history[frames[j]] < replace_value) {//�D��Reference�̤p��
						replace_index = j;
						early_reference_time = frames_reference_time[j];
					}
					else if (reference_history[j]== replace_value){//�p�GReference�@�ˡA�h��FIFO
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
	cout << "ARB Frame�ƶq:" << frames_num << "  page fault:" << page_fault << "  write back:" << write_back << "  interval interrupt:" << interval_interrupt << "  cost:" << page_fault + write_back+ interval_interrupt << endl;

}