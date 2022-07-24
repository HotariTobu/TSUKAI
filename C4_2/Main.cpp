#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
	if (argc < 2) {
		return -1;
	}

	for (int index = 1; index < argc; index++) {
		ifstream is(argv[index]);
		ofstream os(string(argv[index]).append("_c4_2.txt"));

		if (is.fail()) {
			return -1;
		}

		while (!is.eof()) {
			int v;
			is >> v;
			switch (v) {
			case 1:
				os << 1 << endl << 1 << endl;
				break;

			case 2:
				os << 1 << endl << 0 << endl;
				break;

			case 3:
				os << 0 << endl << 1 << endl;
				break;

			case 4:
				os << 0 << endl << 0 << endl;
				break;
			}
		}

		is.close();
		os.close();
	}

	return 0;
}