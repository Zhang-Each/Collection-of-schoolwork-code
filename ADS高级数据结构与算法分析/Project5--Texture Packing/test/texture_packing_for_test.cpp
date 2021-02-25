#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <fstream>

using namespace std;

class rectangle { /* The rectangles need to be packed onto the texture. */
public:
    int height, width;
    rectangle():height(0),width(0){}
    rectangle(int h, int w):height(h), width(w){} /* Default constructor. */
};

clock_t start_time, end_time;

bool cmp(const rectangle& a, const rectangle& b); /* The way we compare two rectangles. */

int main()
{
    int total_width, total_height, num, i, j;
    string filename;
    cout << "Please input the file you want to test:";
    cin >> filename;
    filename += ".txt";
    ifstream fin(filename.c_str());
    if(!fin) {
        cout << "Error" << endl;
        return 1;
    }
    fin >> total_width >> num;
    total_height = 0; /*Initialize the total height to zero. */
    vector<rectangle> rectangles; /* To store all the rectangles. */
    for(i = 0; i < num; ++i) {
        int h, w;
        fin >> h >> w;
        rectangles.emplace_back(h, w);
    }
    fin.close();
    start_time = clock();
    sort(rectangles.begin(), rectangles.end(), cmp); /* To sort all the rectangles as the way we describe in cmp(). */
    vector<pair<int, int>> blocks;
    for(i = 0; i < num; i++) {
        for(j = 0; j < blocks.size(); j++) {
            if(rectangles[i].width + blocks[j].second <= total_width) { /* We find a suitable block to pack this rectangle.*/
                blocks[j].second += rectangles[i].width; /* Ignoring the height, just cover current block. */
                break;
            }
        }
        if(j == blocks.size()) { /* We don't' find a suitable block to pack this rectangle.*/
            blocks.emplace_back(rectangles[i].height, rectangles[i].width); /* Append a new block to the blocks. */
            total_height += rectangles[i].height; /* Add the height of the new block to the total height. */
        }
    }
    cout << "Total height: " << total_height << "." << endl;
    end_time = clock();
    cout << "Total time: " << (double)(end_time - start_time) * 1000 / CLOCKS_PER_SEC << "ms." << endl;
    return 0;
}

bool cmp(const rectangle& a, const rectangle& b) /* First, compare the height of a and b, then come to the width. */
{
    if(a.height > b.height) return true;
    else if(a.height < b.height) return false;
    else return a.width > b.width;
}