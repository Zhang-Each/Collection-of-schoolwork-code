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
int MAX(BYTE *data, int h, int w);
int main()
{
	FILE *fp1, *fp2, *fp3;
	BYTE *buf1, *buf2, *buf3;
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


	//2. visibility enhancement
	max = MAX(buf1, h, w);
	buf2 = new BYTE[h*LineByte];
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			buf2[i*LineByte + j] = (BYTE)(log(buf1[i*LineByte + j] + 1)) / log(max + 1) * 255;
		}
	}

	fp2 = fopen("img2.bmp", "wb");
	fwrite(&head, 14, 1, fp2);
	fwrite(&info, 40, 1, fp2);
	fwrite(color, sizeof(RGBQUAD), 256, fp2);
	fwrite(buf2, LineByte*h, 1, fp2);
	fclose(fp2);


	//3. Histogram Equlization
	int pixesum, count[256], pixemap[256];
	double pix1[256], pix2[256];

	fp3 = fopen("img3.bmp", "wb");
	pixesum = h * w;
	buf3 = new BYTE[h*LineByte];

	for (i = 0; i < 256; i++) {
		count[i] = 0;
		pix1[i] = 0;
	}

	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			count[buf1[i*LineByte + j]]++;
		}
	}

	for (i = 0; i < 256; i++) {
		pix1[i] = count[i] / (double)pixesum; //must be double here!!!!
	}

	for (i = 0; i < 256; i++) {
		if (i == 0) {
			pix2[i] = pix1[i];
		}
		else if (i >= 1 && i <= 255) {
			pix2[i] = pix2[i - 1] + pix1[i];
		}
	}

	for (i = 0; i < 256; i++) {
		double delta;
		delta = pix2[i] * 255 - (int)pix2[i] * 255;
		if (delta > 0.5) {
			pixemap[i] = int( pix2[i] * 255) + 1;
		}
		else pixemap[i] = int(pix2[i] * 255);
	}

	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			buf3[i*LineByte + j] = pixemap[buf1[i*LineByte + j]];
		}
	}

	fwrite(&head, 14, 1, fp3);
	fwrite(&info, 40, 1, fp3);
	fwrite(color, sizeof(RGBQUAD), 256, fp3);
	fwrite(buf3, LineByte*h, 1, fp3);

	return 0;
}

void PrintBMP(BMPFILEHEADER *fileheader, BMPINFOHEADER *infoheader)
{

	printf("λͼ�ļ�ͷ��Ҫ�Ƕ�λͼ�ļ���һЩ����:BMPFileHeader\n\n");
	printf("BMP �ļ���С = %d �ֽ�\n", fileheader->bfSize);
	printf("����ֵ1 = %d \n", fileheader->bfReserved1);
	printf("����ֵ2 = %d \n", fileheader->bfReserved2);
	printf("�ļ�ͷ�����ͼ������λ��ʼ��ƫ���� = %d �ֽ�\n", fileheader->bfOffset);
	printf("\n\nλͼ��Ϣͷ��Ҫ�Ƕ�λͼͼ������Ϣ������:BMPInfo\n\n");
	printf("��Ϣͷ�Ĵ�С = %d �ֽ�\n", infoheader->biSize);
	printf("λͼ�ĸ߶� = %d \n", infoheader->biHeight);
	printf("λͼ�Ŀ�� = %d \n", infoheader->biWidth);
	printf("ͼ���λ����(λ�����ǵ�ɫ�������,Ĭ��Ϊ1����ɫ��) = %d \n", infoheader->biPlanes);
	printf("ÿ�����ص�λ�� = %d λ\n", infoheader->biBitCount);
	printf("ѹ������ = %d \n", infoheader->biCompression);
	printf("ͼ��Ĵ�С = %d �ֽ�\n", infoheader->biSizeImage);
	printf("ˮƽ�ֱ��� = %d \n", infoheader->biXPelsPerMeter);
	printf("��ֱ�ֱ��� = %d \n", infoheader->biYPelsPerMeter);
	printf("ʹ�õ�ɫ���� = %d \n", infoheader->biClrUsed);
	printf("��Ҫ��ɫ���� = %d \n", infoheader->biClrImportant);

}

int MAX(BYTE *data, int h, int w)
{
	int i, j, result = 0;
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			if (data[i*LineByte + j] > result)
				result = data[i*LineByte + j];
		}
	}
	return result;
}