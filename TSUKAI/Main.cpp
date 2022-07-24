#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
	for (int i = 0; i < argc; i++) {
		cout << "argv[" << i << "] = " << argv[i] << endl;
	}

	if (argc < 2) {
		cout << "args : Text File Path" << endl;
		system("pause");
		return -1;
	}

	for (int index = 1; index < argc; index++) {
		ifstream is(argv[index]);

		if (is.fail()) {
			cout << "Failed file open" << endl;
			system("pause");
			return -1;
		}

		cout << endl;

		vector<int> arr;

		cout << "File Data Begin" << endl;
		while (!is.eof()) {
			int v;
			is >> v;
			cout << "\t" << v << endl;
			arr.push_back(v);
		}
		cout << "File Data End" << endl;

		is.close();

		int size = arr.size();

		cout << endl;

		ofstream os(string(argv[index]).append("_report.txt"));

		cout << "Frequency Search Begin" << endl;
		os << "単純頻度分析の開始" << endl;

		double toprf = 0;
		int topvalue = 0;
		vector<int> copy = arr;
		while (!copy.empty()) {
			int copykey = copy.front();
			int copycount = 0;

			while (true) {
				auto result = find(copy.begin(), copy.end(), copykey);
				if (result == copy.end()) {
					break;
				}
				else {
					copy.erase(result);
					copycount++;
				}
			}

			double rf = copycount;
			rf /= size;

			if (toprf < rf) {
				toprf = rf;
				topvalue = copykey;
			}

			cout << "\tpair = (" << copykey << ", " << copycount << ")" << endl;
			os << "\t" << copykey << " : " << rf << endl;
		}
		cout << "result = " << topvalue << endl;

		cout << "Frequency Search End" << endl;
		os << "単純頻度分析の終了" << endl;

		cout << endl;
		os << endl;

		system("pause");

		cout << endl;
		os << endl;

		cout << "Interval Search Begin" << endl;
		os << "単純等間隔分析の開始" << endl;

		double maxave = 0;
		int interval = 0;
		for (int i = 2; i < size; i++) {
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (i == 11) {
				break;
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			cout << "\ti = " << i << endl;
			os << "\t" << i << "個の間隔" << endl;

			double averf = 0;

			for (int j = 0; j < i; j++) {
				cout << "\t\tj = " << j << endl;
				//os << "\t\t" << j << "列目" << endl;

				vector<int> poarr;
				for (int l = j; l < size; l += i) {
					cout << "\t\t\tl = " << l << endl;
					poarr.push_back(arr[l]);
				}

				cout << endl;

				int posize = poarr.size();
				int max = 0;
				int var;

				while (!poarr.empty()) {
					int key = poarr.front();
					int count = 0;

					while (true) {
						auto result = find(poarr.begin(), poarr.end(), key);
						if (result == poarr.end()) {
							break;
						}
						else {
							poarr.erase(result);
							count++;
						}
					}

					if (max < count) {
						max = count;
						var = key;
					}

					cout << "\t\t\tpair[" << j << "] = (" << key << ", " << count << ")" << endl;
					//os << "\t\t\t" << key << " : " << ((double)count / posize) << endl;
				}

				double rf = max;
				rf /= posize;

				cout << "\t\tpair[" << j << "] = (" << var << ", " << rf << ")" << endl;
				os << "\t\t" << j << "列目で" << var << "になる確率は" << (rf * 100) << "％" << endl;
				averf += rf;

				cout << endl;
				//os << endl;
			}

			averf /= i;

			if (maxave < averf) {
				maxave = averf;
				interval = i;
			}

			cout << "\tave = " << averf << endl;
			os << "\t" << i << "個の間隔でのスコアは" << averf << endl;

			cout << endl;
			os << endl;
		}
		cout << "result = " << interval << endl;

		cout << "Interval Search End" << endl;
		os << "単純等間隔分析の終了" << endl;

		cout << endl;
		os << endl;

		system("pause");

		cout << endl;
		os << endl;

		cout << "Array Search Begin" << endl;
		os << "類似配列分析の開始" << endl;

		double maxrf = 0;
		int *temp = &interval;
		int tempi;
		for (int i = 2; i < size; i++) {
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (i == 9) {
				break;
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			cout << "\ti = " << i << endl;
			os << "\t" << i << "個の配列" << endl;

			vector<int *> temps;

			for (int j = 0; j < size - i; j++) {
				cout << "\t\t[" << j << "] : ";

				int *potemp = new int[i];
				for (int l = 0; l < i; l++) {
					potemp[l] = arr[j + l];

					cout << potemp[l];
				}

				temps.push_back(potemp);

				cout << endl;
			}

			cout << endl;

			int tempssize = temps.size();
			int max = 0;
			int *var = &max;

			while (!temps.empty()) {
				int *pi = temps.front();
				int count = 0;

				while (true) {
					auto result = temps.begin();
					for (; result != temps.end(); result++) {
						bool match = true;
						for (int j = 0; j < i; j++) {
							if (pi[j] != (*result)[j]) {
								match = false;
							}
						}

						if (match) {
							break;
						}
					}
					if (result == temps.end()) {
						break;
					}
					else {
						temps.erase(result);
						count++;
					}
				}

				if (max < count) {
					max = count;
					var = pi;
				}

				cout << "\t\t(";
				os << "\t\t";
				for (int j = 0; j < i; j++) {
					cout << pi[j];
					os << pi[j];
				}
				cout << ", " << count << ")" << endl;
				os << " : " << ((double)count / tempssize) << endl;
			}

			double rf = max;
			rf /= tempssize;

			cout << "\tpair[" << i << "] = (";
			os << "\t" << i << "個の配列で";
			for (int j = 0; j < i; j++) {
				cout << var[j];
				os << var[j];
			}
			cout << ", " << rf << ")" << endl;
			os << "になる確率は" << (rf * 100) << "％" << endl;

			if (maxrf < rf) {
				maxrf = rf;
				temp = var;
				tempi = i;
			}

			cout << endl;
			os << endl;
		}
		cout << "result = ";
		for (int i = 0; i < tempi; i++) {
			cout << temp[i];
		}
		cout << endl;

		cout << "Array Search End" << endl;
		os << "類似配列分析の終了" << endl;

		cout << endl;
		os << endl;

		system("pause");

		os.close();

		system("cls");
	}

	return 0;
}