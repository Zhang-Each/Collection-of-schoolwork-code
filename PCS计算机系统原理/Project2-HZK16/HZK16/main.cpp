#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<vector>
#include<iostream>
#include<stdlib.h>
using namespace std;

#define font 3
vector<string> change2binary(unsigned char x[]);
string binary(int m);

int main(void)
{

	FILE* fp = NULL;
	int i, j, k, offset;
	int flag;
	unsigned char buffer[32];
	unsigned char word[5];
	unsigned char key[8] = {
		0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01
	};

	printf("可以修改宏定义中的font值来更换字体，默认宋体为1，楷体为2，黑体为3:\n");

	if (font == 1)
		fp = fopen("hzk16", "rb");
	else if (font == 2)
		fp = fopen("hzk16k", "rb");
	else if (font == 3)
		fp = fopen("hzk16h", "rb");


	printf("Input the Hanzi:\n");
	for (;;) {
		fgets((char*)word, 3, stdin);
		if (*word == '\n')
			break;
		offset = (94 * (unsigned int)(word[0] - 0xa0 - 1) + (word[1] - 0xa0 - 1)) * 32;
		fseek(fp, offset, SEEK_SET);
		fread(buffer, 1, 32, fp);

		//正常显示
		printf("------------------------正常显示------------------------\n");
		for (k = 0; k < 16; k++) {
			for (j = 0; j < 2; j++) {
				for (i = 0; i < 8; i++) {
					flag = buffer[k * 2 + j] & key[i];
					if (!flag) {
						printf("☆");
					}
					else {
						printf("★");
					}
				}
			}
			printf("\n");
		}

		//倒立显示
		printf("------------------------反转字体------------------------\n");
		for (k = 15; k >= 0; k--) {
			for (j = 1; j >=0 ; j--) {
				for (i = 7; i >= 0; i--) {
					flag = buffer[k * 2 + j] & key[i];
					if (!flag) {
						printf("☆");
					}
					else {
						printf("★");
					}
				}
			}
			printf("\n");
		}

		//倒立显示
		printf("------------------------倒立字体------------------------\n");
		for (k = 15; k >= 0; k--) {
			for (j = 0; j < 2; j++) {
				for (i = 0; i < 8; i++) {
					flag = buffer[k * 2 + j] & key[i];
					if (!flag) {
						printf("☆");
					}
					else {
						printf("★");
					}
				}
			}
			printf("\n");
		}

		//斜体显示
		printf("------------------------斜体显示------------------------\n");
		for (k = 0; k < 16; k++) {
			for (i = 0; i < 16 - k; i++) {
				printf("☆");
			}
			for (j = 0; j < 2; j++) {
				for (i = 0; i < 8; i++) {
					flag = buffer[k * 2 + j] & key[i];
					if (!flag) {
						printf("☆");
					}
					else {
						printf("★");
					}
				}
			}
			for (i = 0; i < k; i++) {
				printf("☆");
			}
			printf("\n");
		}
	

		//change to binary
		vector<string> word = change2binary(buffer);
		printf("------------------------二进制字符表示------------------------\n");
		for (i = 0; i < 16; i++) {
			cout << word[2 * i] << word[2 * i + 1] << endl;
		}

		printf("------------------------文件显示------------------------\n");
		FILE *fp2 = fopen("result.txt", "w");
		for (k = 0; k < 16; k++) {
			for (j = 0; j < 2; j++) {
				for (i = 0; i < 8; i++) {
					flag = buffer[k * 2 + j] & key[i];
					if (!flag) {
						fwrite(" ", sizeof(" "), 1, fp2);
					}
					else {
						fwrite("1", sizeof("0"), 1, fp2);
					}
				}
			}
			fwrite("\n", sizeof("\n"), 1, fp2);
		}
		printf("请在文件result中查看文件输出的结果！\n");
		fclose(fp2);

		//放大显示
		printf("------------------------放大显示------------------------\n");
		for (k = 0; k < 16; k++) {
			for (j = 0; j < 2; j++) {
				for (i = 0; i < 8; i++) {
					flag = buffer[k * 2 + j] & key[i];
					if (!flag) {
						printf("☆☆");
					}
					else {
						printf("★★");
					}
				}
			}
			printf("\n");
			for (j = 0; j < 2; j++) {
				for (i = 0; i < 8; i++) {
					flag = buffer[k * 2 + j] & key[i];
					if (!flag) {
						printf("☆☆");
					}
					else {
						printf("★★");
					}
				}
			}
			printf("\n");
		}
		//system("color 24");
		printf("------------------------彩色显示------------------------\n");
		for (k = 0; k < 16; k++) {
			for (j = 0; j < 2; j++) {
				for (i = 0; i < 8; i++) {
					flag = buffer[k * 2 + j] & key[i];
					if (!flag) {
						printf("☆");
					}
					else {
						printf("★");
					}
				}
			}
			printf("\n");
		}
		//system("color F0");
		//print the unsigned char code of a word
		printf("uchar code key[32] = \n");
		for (k = 0; k < 32; k++) {
			printf("0x%02X,", buffer[k]);
			if (k % 2 == 1) {
				printf("\n");
			}
		}
		printf("};\n");
	}

	fclose(fp);
	system("pause");
	return 0;

}

vector<string> change2binary(unsigned char x[])
{
	vector<string> result;
	int i, j;
	for (i = 0; i < 16; i++) {
		int a, b;
		a = x[2 * i];
		b = x[2 * i + 1];
		result.push_back(binary(a));
		result.push_back(binary(b));
	}

	return result;
}

string binary(int m)
{
	string result = "";
	vector<int> bin;
	while (m != 0) {
		bin.push_back(m % 2);
		m = m / 2;
	}
	for (int i = 0; i < 8 - bin.size(); i++) {
		result += '0';
	}
	for (int i = bin.size()-1; i >= 0; i--) {
		if (bin[i] == 1) {
			result += '1';
		}
		else
			result += '0';
	}
	return result;
}