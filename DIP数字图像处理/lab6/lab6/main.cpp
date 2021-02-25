#include<iostream>
#include<math.h>
#include<stdio.h>
using namespace std;

#pragma pack(1)
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef unsigned short WORD;

typedef struct tagBITMAPFILEHEADER
{
	WORD  bfType;
	DWORD bfSize;
	WORD  bfReserved1;
	WORD  bfReserved2;
	DWORD bfOffset;
}BMPFILEHEADER; //14 bytes in total

typedef struct tagBITMAPINFOHEADER
{
	DWORD biSize;
	long  biWidth;
	long  biHeight;
	WORD  biPlanes;
	WORD  biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	long  biXPelsPerMeter;
	long  biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
}BMPINFOHEADER; //40 Bytes in total

typedef struct tagRGBQUAD
{
	BYTE rgbBlue;
	BYTE rgbRed;
	BYTE rgbGreen;
	BYTE rgbReserved;
}RGBQUAD;

int LineByte;
//double sigmod = 300;
void PrintBMP(BMPFILEHEADER *, BMPINFOHEADER *);
double Guassian_s(int a, int b);
double Guassian_r(int i, int j, int k, int l, BYTE *data);
int conv(BYTE *data, int i, int j);

int main()
{
	FILE *fp1, *fp2;
	BYTE *buf1, *buf2;
	BMPFILEHEADER head;
	BMPINFOHEADER info;
	RGBQUAD color[256];
	int i, j, k, max;
	long w, h;

	//1.get the input file information
	if ((fp1 = fopen("img.bmp", "rb")) == NULL) {
		cout << "Fail to open the input file!" << endl;
		return 0;
	}
	fseek(fp1, 0L, SEEK_SET);
	fread(&head, sizeof(BMPFILEHEADER), 1, fp1);
	fread(&info, sizeof(BMPINFOHEADER), 1, fp1);
	h = info.biHeight;
	w = info.biWidth;
	LineByte = (w*info.biBitCount / 8 + 3) / 4 * 4;
	buf1 = new BYTE[h*LineByte];
	fseek(fp1, head.bfOffset, SEEK_SET);
	fread(buf1, LineByte*h, 1, fp1);
	fclose(fp1);
	PrintBMP(&head, &info);
	for (i = 0; i < 256; i++) {
		color[i].rgbBlue = i;
		color[i].rgbGreen = i;
		color[i].rgbRed = i;
		color[i].rgbReserved = 0;
	}

	//2.
	fp2 = fopen("img2.bmp", "wb");
	buf2 = new BYTE[h*LineByte];
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			buf2[i*LineByte + j] = 255;
		}
	}
	    
	for (i = 3; i < h - 3; i++) {
		for (j = 3; j < w - 3; j++) {
			int pixel = conv(buf1, i, j);
			if (pixel > 255) {
				pixel = 255;
			}
			else if (pixel < 0) {
				pixel = 0;
			}
			buf2[i*LineByte + j] = (BYTE)pixel;
			//cout << pixel << endl;
		}
	}

	fwrite(&head, 14, 1, fp2);
	fwrite(&info, 40, 1, fp2);
	fwrite(color, sizeof(RGBQUAD), 256, fp2);
	fwrite(buf2, LineByte*h, 1, fp2);
	fclose(fp2);

	return 0;
}

void PrintBMP(BMPFILEHEADER *fileheader, BMPINFOHEADER *infoheader)
{
	printf("位图文件头主要是对位图文件的一些描述:BMPFileHeader\n\n");
	printf("BMP 文件大小 = %d 字节\n", fileheader->bfSize);
	printf("保留值1 = %d \n", fileheader->bfReserved1);
	printf("保留值2 = %d \n", fileheader->bfReserved2);
	printf("文件头的最后到图像数据位开始的偏移量 = %d 字节\n", fileheader->bfOffset);
	printf("\n\n位图信息头主要是对位图图像方面信息的描述:BMPInfo\n\n");
	printf("信息头的大小 = %d 字节\n", infoheader->biSize);
	printf("位图的高度 = %d \n", infoheader->biHeight);
	printf("位图的宽度 = %d \n", infoheader->biWidth);
	printf("图像的位面数(位面数是调色板的数量,默认为1个调色板) = %d \n", infoheader->biPlanes);
	printf("每个像素的位数 = %d 位\n", infoheader->biBitCount);
	printf("压缩类型 = %d \n", infoheader->biCompression);
	printf("图像的大小 = %d 字节\n", infoheader->biSizeImage);
	printf("水平分辨率 = %d \n", infoheader->biXPelsPerMeter);
	printf("垂直分辨率 = %d \n", infoheader->biYPelsPerMeter);
	printf("使用的色彩数 = %d \n", infoheader->biClrUsed);
	printf("重要的色彩数 = %d \n", infoheader->biClrImportant);
}

int conv(BYTE* buf, int i, int j)
{
	int m, n;
	double weight = 0.0, weight_s, weight_r;
	double pixel = 0.0;
	for (m = 0; m < 7; m++)
	{
		for (n = 0; n < 7; n++)
		{
			weight_s = Guassian_s(m - 3, n - 3);
			weight_r = Guassian_r(i, j, i - 3 + m, j - 3 + n, buf);
			weight += weight_r * weight_s;

			pixel += buf[(i - 3 + m) * LineByte + j - 3 + n] * weight_r * weight_s;	
		}
	}
	double result = pixel / weight;
	if (result > 255) {
		return 255;
	}
	else if (result < 0) {
		return 0;
	}
	else {
		return (int)result;
	}
}

/*空间相似性高斯函数*/
double Guassian_s(int a,int b)
{
	double sigmod = 2000;
	return exp(-(pow(a, 2) + pow(b, 2)) / (2 * sigmod));
}

/*内容相似性高斯函数*/
double Guassian_r(int i, int j, int k, int l, BYTE* buf)
{
	double sigmod = 1000;
	return exp(-pow(buf[i*LineByte + j] - buf[k*LineByte + l], 2) / (2 * sigmod));
}