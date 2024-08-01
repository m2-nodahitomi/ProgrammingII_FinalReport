#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <ios>
using namespace std;

struct Goods {
	string name;
	int price;
	int num;
};

static bool cmp_pri(const Goods& a, const Goods& b) {
	return a.price > b.price;
}

static bool cmp_num(const Goods& a, const Goods& b) {
	return a.num < b.num;
}

int main() {
	//�v���O�����̐���
	cout << "���̃v���O�����́A�����Ƃ��Ċ�ƂȂ���z�Ƃ���ȏォ�ȉ������߂�ƁA" << endl;
	cout << "�����̒��Ŋ�ƂȂ���z�ɋ߂����v���z�ɂȂ�悤�ɃO�b�Y�̍w���������߂܂��B" << endl; 
	cout << "�� ���l����͂���Ƃ��͔��p�œ��͂��Ă��������B" << endl;
	cout << "�� ���͂��I������� Enter �������Ă��������B" << endl;
	cout << endl;


	//�����̓���
	//��̋��z
	int yosan;
	while (true) {
		cout << "��ƂȂ���z����͂��Ă��������B" << endl;
		cin >> yosan;
		if (cin.fail() || yosan <= 0) {
			cout << "���̓G���[���������܂����B" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (yosan > 0)break;
	}
	cout << endl;

	//��ȏォ�ȉ���
	cout << "��ƂȂ���z�u�ȏ�v���u�ȉ��v�����͂��Ă��������B" << endl;
	string more_or_less;
	while (cin >> more_or_less) {
		if (more_or_less == "�ȏ�" || more_or_less == "�ȉ�")break;
		cout << "���̓G���[���������܂����B" << endl;
		cout << "��ƂȂ���z�u�ȏ�v���u�ȉ��v�����͂��Ă��������B" << endl;
	}
	cout << endl;

	//���������
	int postage;
	while (true) {
		cout << "��������͂��Ă��������B" << endl;
		cout << "�� �������܂߂Ȃ��ꍇ�́u0�v����͂��Ă��������B" << endl;
		cin >> postage;
		if (cin.fail() || postage < 0) {
			cout << "���̓G���[���������܂����B" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (postage >= 0)break;
	}
	cout << endl;


	//�����������i�������
	cout << "�w���������O�b�Y�̏����u���� ���z �w�����v�̗l�ɔ��p�X�y�[�X�ŋ�؂��ē��͂��Ă��������B" << endl;
	cout << "���͂��I������Ƃ��� Ctrl+z ����͂��Ă��������B" << endl;
	cout << "�� �w���������߂������i�� '�w����' �̗��Ɂu0�v����͂��Ă��������B" << endl;
	cout << "�� ���̂͐��m�łȂ��Ƃ����܂��܂��񂪁A�������͓̂��͂��Ȃ��ł��������B" << endl;
	cout << "�� ��F�u�A�N�X�^ 1500 1�v,�u�����_���ʃo�b�` 550 0�v" << endl;
	string goodsdata;
	ofstream outfile("datafile.dat", ios_base::out);
	while (cin >> goodsdata) {
		outfile << goodsdata << endl;
	}
	outfile.close();
	cout << endl;


	//�v�Z����
	int total = postage;
	ifstream infile("datafile.dat");
	string NAME;
	int PRICE;
	int NUM;
	vector<Goods>vec;
	vec.emplace_back();
	int x = 0;

	//vec�ɏ��i�������Ă���
	while (infile >> NAME >> PRICE >> NUM) {
		vec.emplace_back();
		vec[x].name = NAME;
		vec[x].price = PRICE;
		vec[x].num = NUM;
		x += 1;
	}
	vec.pop_back();
	infile.close();
	size_t s1 = vec.size();

	//vec���������Ȃ����ɕ��ׂ�
	sort(vec.begin(), vec.end(), cmp_num);

	//vec_ran�ɍw�����v�Z������̂�����
	int ran = 0;
	for (int i = 0; i < s1; ++i) {
		if (vec[i].num == 0)ran += 1;
	}
	vector<Goods>vec_ran(ran);
	for (int j = 0; j < s1; ++j) {
		if (vec[j].num == 0 && vec[j].price > 0) {
			vec_ran[j].name = vec[j].name;
			vec_ran[j].price = vec[j].price;
			vec_ran[j].num = vec[j].num;
		}
		total += (vec[j].price * vec[j].num);
	}
	size_t s2 = vec_ran.size();

	//vec_ran��l�i���������ɕ��ׂ�
	sort(vec_ran.begin(), vec_ran.end(), cmp_pri);

	//�v�Z	
	vector<int>counter(yosan / vec_ran[s2 - 1].price);
	counter[0] = 0;
	auto it = counter.begin();
	int kari = 0;
	int yobi = 0;
	//�ȏ�̏ꍇ
	if (more_or_less == "�ȏ�") {
		if (total < yosan) {
			for (int p = 0; ++p;) {
				if (total >= yosan)continue;
				for (int q = 0; q < s2; ++q) {
					if (total >= yosan)continue;
					vec_ran[q].num += 1;
					total += vec_ran[q].price;
					*it = q;
					yobi = q;
				}
			}
			//�����̂Ȃ��ō��v���z���ŏ��ɂȂ�悤�ɒ���
			for (int r = 0; r < (s2 - yobi); ++r) {
				if ((total - yosan) < vec_ran[s2 - 1].price)break;
				total -= vec_ran[*(it + r)].price;
				vec_ran[*(it + r)].num -= 1;
				for (int s = 0; ++s;) {
					if (total >= yosan)continue;
					for (int t = 0; t < s2; ++t) {
						if (total >= yosan)continue;
						vec_ran[t].num += 1;
						total += vec_ran[t].price;
						*(it + r + 1) = t;
					}

				}
			}
			cout << "�����ɂ���";
		}
		else {
			cout << "�w���������܂��Ă���O�b�Y�̍��v���z���\�Z�𒴂��Ă��܂��B" << endl;
		}
	}
	//�ȉ��̏ꍇ
	else if (more_or_less == "�ȉ�") {
		if (total <= yosan) {
			for (int p = 0; ++p;) {
				if (total <= yosan && (yosan - total) < vec_ran[0].price)continue;
				for (int q = 0; q < s2; ++q) {
					if (total < yosan && (yosan - vec_ran[q].price) < total)continue;
					vec_ran[q].num += 1;
					total += vec_ran[q].price;
					*it = q;
					yobi = q;
				}
			}
			//�����̂Ȃ��ō��v���z���ő�ɂȂ�悤�ɒ���
			for (int r = 0; r < (s2 - yobi); ++r) {
				if (total <= yosan && (yosan - vec_ran[s2 - 1].price) < total)break;
				for (int s = 0; ++s;) {
					if (total <= yosan && (yosan - total) < vec_ran[*(it + r)].price)continue;
					for (int t = *(it + r); r < s2; ++t) {
						kari = t + 1;
						if (total < yosan && (yosan - vec_ran[kari].price) < total)continue;
						vec_ran[kari].num += 1;
						total += vec_ran[kari].price;
						*(it + r + 1) = kari;
					}
				}
			}
			cout << "�����ɂ���";
		}
		else {
			cout << "�w���������܂��Ă���O�b�Y�̍��v���z���\�Z�𒴂��Ă��܂��B" << endl;
		}
	}

	//���߂�����vec�ɓ���Ȃ���
	for (int k = 0; k < s2; ++k) {
		for (int l = 0; l < s2; ++l) {
			if (vec_ran[k].name == vec[l].name)vec[l].num = vec_ran[k].num;
		}
	}


	//���ʂ��o��
	cout << "�e�O�b�Y�̌��A���v���z�͈ȉ��̂悤�ɂȂ�܂��B" << endl;
	for (size_t m = 0; m < s1; ++m) {
		cout << left << setw(16) << vec[m].name << "  ";
		cout << right << setw(6) << vec[m].price << "�~  ";
		cout << right << setw(3) << vec[m].num << "��" << endl;
	}
	cout << "���v���z�� " << total << "�~ �ł��B" << endl;
}
