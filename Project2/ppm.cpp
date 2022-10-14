#include <fstream>
 
using namespace std;

int main1() {
    constexpr auto width = 80u, height = 80u;

    ofstream ofs("first.txt", ios_base::out | ios_base::binary);

    ofs << "P6" << endl << width << ' ' << height << endl << "255" << endl;
 
    for (auto j = 0u; j < height; ++j)
        for (auto i = 0u; i < width; ++i)
            ofs <<  (i % 256)        // red
		<<  (j % 256)        // green
		<<  ((i + j) % 256); // red, green, blue

    ofs.close();
    return EXIT_SUCCESS;
}
