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
	//プログラムの説明
	cout << "このプログラムは、条件として基準となる金額とそれ以上か以下かを定めると、" << endl;
	cout << "条件の中で基準となる金額に近い合計金額になるようにグッズの購入個数を求めます。" << endl; 
	cout << "※ 数値を入力するときは半角で入力してください。" << endl;
	cout << "※ 入力が終わったら Enter を押してください。" << endl;
	cout << endl;


	//条件の入力
	//基準の金額
	int yosan;
	while (true) {
		cout << "基準となる金額を入力してください。" << endl;
		cin >> yosan;
		if (cin.fail() || yosan <= 0) {
			cout << "入力エラーが発生しました。" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (yosan > 0)break;
	}
	cout << endl;

	//基準以上か以下か
	cout << "基準となる金額「以上」か「以下」か入力してください。" << endl;
	string more_or_less;
	while (cin >> more_or_less) {
		if (more_or_less == "以上" || more_or_less == "以下")break;
		cout << "入力エラーが発生しました。" << endl;
		cout << "基準となる金額「以上」か「以下」か入力してください。" << endl;
	}
	cout << endl;

	//送料を入力
	int postage;
	while (true) {
		cout << "送料を入力してください。" << endl;
		cout << "※ 送料を含めない場合は「0」を入力してください。" << endl;
		cin >> postage;
		if (cin.fail() || postage < 0) {
			cout << "入力エラーが発生しました。" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (postage >= 0)break;
	}
	cout << endl;


	//買いたい商品情報を入力
	cout << "購入したいグッズの情報を「名称 金額 購入個数」の様に半角スペースで区切って入力してください。" << endl;
	cout << "入力を終了するときは Ctrl+z を入力してください。" << endl;
	cout << "※ 購入個数を求めたい商品は '購入個数' の欄に「0」を入力してください。" << endl;
	cout << "※ 名称は正確でなくともかまいませんが、同じ名称は入力しないでください。" << endl;
	cout << "※ 例：「アクスタ 1500 1」,「ランダム缶バッチ 550 0」" << endl;
	string goodsdata;
	ofstream outfile("datafile.dat", ios_base::out);
	while (cin >> goodsdata) {
		outfile << goodsdata << endl;
	}
	outfile.close();
	cout << endl;


	//計算する
	int total = postage;
	ifstream infile("datafile.dat");
	string NAME;
	int PRICE;
	int NUM;
	vector<Goods>vec;
	vec.emplace_back();
	int x = 0;

	//vecに商品情報を入れていく
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

	//vecを個数が少ない順に並べる
	sort(vec.begin(), vec.end(), cmp_num);

	//vec_ranに購入個数計算するものを入れる
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

	//vec_ranを値段が高い順に並べる
	sort(vec_ran.begin(), vec_ran.end(), cmp_pri);

	//計算	
	vector<int>counter(yosan / vec_ran[s2 - 1].price);
	counter[0] = 0;
	auto it = counter.begin();
	int kari = 0;
	int yobi = 0;
	//以上の場合
	if (more_or_less == "以上") {
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
			//条件のなかで合計金額が最小になるように調整
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
			cout << "条件にあう";
		}
		else {
			cout << "購入個数が決まっているグッズの合計金額が予算を超えています。" << endl;
		}
	}
	//以下の場合
	else if (more_or_less == "以下") {
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
			//条件のなかで合計金額が最大になるように調整
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
			cout << "条件にあう";
		}
		else {
			cout << "購入個数が決まっているグッズの合計金額が予算を超えています。" << endl;
		}
	}

	//求めた個数をvecに入れなおす
	for (int k = 0; k < s2; ++k) {
		for (int l = 0; l < s2; ++l) {
			if (vec_ran[k].name == vec[l].name)vec[l].num = vec_ran[k].num;
		}
	}


	//結果を出力
	cout << "各グッズの個数、合計金額は以下のようになります。" << endl;
	for (size_t m = 0; m < s1; ++m) {
		cout << left << setw(16) << vec[m].name << "  ";
		cout << right << setw(6) << vec[m].price << "円  ";
		cout << right << setw(3) << vec[m].num << "個" << endl;
	}
	cout << "合計金額は " << total << "円 です。" << endl;
}
