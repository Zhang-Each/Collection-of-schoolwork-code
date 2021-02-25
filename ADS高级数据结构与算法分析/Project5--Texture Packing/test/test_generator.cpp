#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand((int)time(nullptr));
    string filename;
    cout << "Please input a filename:"; /* The filename is defined by yourself. */
    cin >> filename;
    filename += ".txt";
    int MaxWidth, num, i;
    cout << "Please input the max width of the texture:";
    cin >> MaxWidth; /* Choose the max width you want to test. */
    cout << "Please input the number of the rectangles:";
    cin >> num;
    ofstream fout(filename);
    fout << MaxWidth << " " << num << endl;
    for(i = 0; i < num; i++) {
        int h, w;
        h = rand() % (3 * MaxWidth / 2) + 1; /* Constrain the rectangles that the width must be smaller than
                                                MaxWidth and the height must be smaller than MaxWidth * 1.5. */
        w = rand() % MaxWidth + 1;
        if(h < w) swap(h, w);
        fout << h << " " << w << endl;
    }
    cout << "Succeeded.";
    return 0;
}
