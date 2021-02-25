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

void PrintBMP(BMPFILEHEADER *, BMPINFOHEADER *);
int main()
{
	FILE *fp1, *fp2, *fp3, *fp4, *fp5, *fp6;
	BYTE *buf1, *buf2, *buf3, *buf4, *buf5, *buf6;
	BMPFILEHEADER head, head2, head3, head4, head5, head6;
	BMPINFOHEADER info, info2, info3, info4, info5, info6;
	RGBQUAD color[256];
	int i, j, k, max;
	long w, h;

	//operation0.get the input file information
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

	//operation1. translation
	fp2 = fopen("img2.bmp", "wb");
	int LineByte1;
	long h1, w1;
	h1 = h + 300;
	w1 = w + 500;
	LineByte1 = (w1 * 8 / 8 + 3) / 4 * 4;
	head2.bfType = 0x4D42;
	head2.bfSize = 14 + 40 + 256 * sizeof(RGBQUAD) + h1 * w1;
	head2.bfReserved1 = 0;
	head2.bfReserved2 = 0;
	head2.bfOffset = 14 + 40 + 256 * sizeof(RGBQUAD);
	fwrite(&head2, 14, 1, fp2);
	info2 = info;
	info2.biHeight = h1;
	info2.biWidth = w1;
	info2.biSizeImage = w1 * h1;
	PrintBMP(&head2, &info2);
	fwrite(&info2, 40, 1, fp2);
	fwrite(color, sizeof(RGBQUAD), 256, fp2);

	buf2 = new BYTE[LineByte1*h1];
	for (i = 0; i < h1; i++) {
		for (j = 0; j < w1; j++) {
			if (i >= 300 && j >= 500) {
				buf2[i*LineByte1 + j] = buf1[(i - 300)*LineByte + j - 500];
			}
			else {
				buf2[i*LineByte1 + j] = 255;
			}
		}
	}
	fwrite(buf2, h1*LineByte1, 1, fp2);
	fclose(fp2);


	//operation2. rotation
	fp3 = fopen("img3.bmp", "wb");
	long h2, w2;
	int x1, y1, x2, y2, LineByte2;
	h2 = 2000;
	w2 = 5000;
	//x1 and y1:originnal h and w
	x1 = w / 2;
	y1 = h / 2;
	x2 = w2 / 2;
	y2 = h2 / 2;
	LineByte2 = (w2 * 8 / 8 + 3) / 4 * 4;

	head3.bfType = 0x4D42;
	head3.bfSize = 14 + 40 + 256 * sizeof(RGBQUAD) + h2 * w2;
	head3.bfReserved1 = 0;
	head3.bfReserved2 = 0;
	head3.bfOffset = 14 + 40 + 256 * sizeof(RGBQUAD);
	fwrite(&head3, 14, 1, fp3);

	info3 = info;
	info3.biHeight = h2;
	info3.biWidth = w2;
	info3.biSizeImage = h2 * w2;
	fwrite(&info3, 40, 1, fp3);
	fwrite(color, sizeof(RGBQUAD), 256, fp3);

	buf3 = new BYTE[h2*LineByte2];
	//set the map all white
	for (i = 0; i < h2; i++) {
		for (j = 0; j < w2; j++) {
			buf3[i*LineByte2 + j] = 255;
		}
	}
	
	for ( i = 0; i < h; i++) {  
		for ( j = 0; j < w; j++)  {  
			buf3[(int)ceil(0.707 * (i + j - x1 - y1) + y2) * LineByte2 + (int)ceil(0.707 * (i - j + y1 - x1) + x2)] = buf1[i * LineByte + j];
			buf3[(int)floor(0.707 * (i + j - x1 - y1) + y2) * LineByte2 + (int)ceil(0.707 * (i - j + y1 - x1) + x2)] = buf1[i * LineByte + j];
			buf3[(int)floor(0.707 * (i + j - x1 - y1) + y2) * LineByte2 + (int)floor(0.707 * (i - j + y1 - x1) + x2)] = buf1[i * LineByte + j];
			buf3[(int)ceil(0.707 * (i + j - x1 - y1) + y2) * LineByte2 + (int)floor(0.707 * (i - j + y1 - x1) + x2)] = buf1[i * LineByte + j];
		}  
	} 
	
	fwrite(buf3, LineByte2*h2, 1, fp3);
	fclose(fp3);

	//operation3.scale
	fp4 = fopen("img4.bmp", "wb");
	long h3, w3;
	int LineByte3;
	h3 = h;
	w3 = w / 2;
	LineByte3 = (w3 * 8 / 8 + 3) / 4 * 4;

	head4.bfType = 0x4D42;
	head4.bfSize = 14 + 40 + 256 * sizeof(RGBQUAD) + h3 * w3;
	head4.bfReserved1 = 0;
	head4.bfReserved2 = 0;
	head4.bfOffset = 14 + 40 + 256 * sizeof(RGBQUAD);
	fwrite(&head4, 14, 1, fp4);

	info4 = info;
	info4.biWidth = w3;
	info4.biHeight = h3;
	info4.biSizeImage = LineByte3 * h3;
	fwrite(&info4, 40, 1, fp4);
	fwrite(color, sizeof(RGBQUAD), 256, fp4);

	buf4 = new BYTE[LineByte3*h3];
	for (i = 0; i < h3; i++) {
		for (j = 0; j < w3; j++) {
			buf4[i*LineByte3 + j] = (int)round((buf1[i*LineByte + j * 2] + buf1[i*LineByte + j * 2 + 1]) / 2.0);
		}
	}
	fwrite(buf4, LineByte3*h3, 1, fp4);
	fclose(fp4);

	//operation4.shear
	fp5 = fopen("img5.bmp", "wb");
	long h4, w4;
	int LineByte4;
	h4 = h;
	w4 = w + h;
	LineByte4 = (w4 * 8 / 8 + 3) / 4 * 4;

	head5.bfReserved1 = 0;
	head5.bfReserved2 = 0;
	head5.bfType = 0x4D42;
	head5.bfSize = 14 + 40 + 256 * sizeof(RGBQUAD) + h4 * w4;
	head5.bfOffset = 14 + 40 + 256 * sizeof(RGBQUAD);
	fwrite(&head5, 14, 1, fp5);

	info5 = info;
	info5.biWidth = w4;
	info5.biHeight = h4;
	info5.biSizeImage = LineByte4 * h4;
	fwrite(&info5, 40, 1, fp5);
	fwrite(color, sizeof(RGBQUAD), 256, fp5);

	buf5 = new BYTE[h4*LineByte4];
	for (i = 0; i < h4; i++) {
		for (j = 0; j < w4; j++) {
			buf5[i*LineByte4 + j] = 255;
		}
	}

	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			buf5[i*LineByte4 + j + i] = buf1[i*LineByte + j];
		}
	}
	fwrite(buf5, LineByte4*h4, 1, fp5);
	fclose(fp5);

	//operation5.mirror
	fp6 = fopen("img6.bmp", "wb");
	long h5, w5;
	h5 = h;
	w5 = w;

	head6.bfReserved1 = 0;
	head6.bfReserved2 = 0;
	head6.bfType = 0x4D42;
	head6.bfSize = 14 + 40 + 256 * sizeof(RGBQUAD) + h5 * w5;
	head6.bfOffset = 14 + 40 + 256 * sizeof(RGBQUAD);
	fwrite(&head6, 14, 1, fp6);

	info6 = info;
	info6.biWidth = w5;
	info6.biHeight = h5;
	info6.biSizeImage = LineByte * h5;
	fwrite(&info6, 40, 1, fp6);
	fwrite(color, sizeof(RGBQUAD), 256, fp6);

	buf6 = new BYTE[h5*LineByte];
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			buf6[i*LineByte + w - j] = buf1[i*LineByte + j];
		}
	}
	fwrite(buf6, h5*LineByte, 1, fp6);
	fclose(fp6);


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