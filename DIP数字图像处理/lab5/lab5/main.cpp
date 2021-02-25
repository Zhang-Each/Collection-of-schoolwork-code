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
int kernel_f[3][3] = { {1,1,1},{1,1,1},{1,1,1} };
int kernel_l[3][3] = { {1,1,1},{1,-8,1},{1,1,1} };
void PrintBMP(BMPFILEHEADER *, BMPINFOHEADER *);
int conv(BYTE* data, int kind, int i, int j);
int main()
{
	FILE *fp1, *fp2, *fp3;
	BYTE *buf1, *buf2, *buf3, *buf4;
	BMPFILEHEADER head;
	BMPINFOHEADER info;
	RGBQUAD color[256];
	int i, j, k, max;
	long w, h;

	//operation 0.get the input file information
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

	//part2
	fp2 = fopen("img2.bmp", "wb");
	buf2 = new BYTE[h*LineByte];

	for (i = 0; i < h; i++) {
		for (j = 0; j < h; j++) {
			buf2[i*LineByte + j] = 255;
		}
	}

	for (i = 1; i < h - 1; i++) {
		for (j = 1; j < w - 1; j++) {
			buf2[i*LineByte + j] = conv(buf1, 1, i, j) / 9.0;
		}
	}

	fwrite(&head, 14, 1, fp2);
	fwrite(&info, 40, 1, fp2);
	fwrite(color, sizeof(RGBQUAD), 256, fp2);
	fwrite(buf2, LineByte*h, 1, fp2);
	fclose(fp2);

	//part3
	fp3 = fopen("img3.bmp", "wb");
	buf3 = new BYTE[h*LineByte];
	buf4 = new BYTE[h*LineByte];

	for (i = 1; i < h - 1; i++) {
		for (j = 1; j < w - 1; j++) {
			int pixel = conv(buf1, 2, i, j);
			if (pixel <= 0) {
				buf3[i*LineByte + j] = 0;
			}
			else if (pixel >= 255) {
				buf3[i*LineByte + j] = 255;
			}
			else {
				buf3[i*LineByte + j] = pixel;
			}
		}
	}

	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			int pixel = buf1[i*LineByte + j] - buf3[i*LineByte + j];
			if (pixel <= 0) {
				buf4[i*LineByte + j] = 0;
			}
			else if (pixel >= 255) {
				buf4[i*LineByte + j] = 255;
			}
			else {
				buf4[i*LineByte + j] = pixel;
			}
		}
	}

	fwrite(&head, 14, 1, fp3);
	fwrite(&info, 40, 1, fp3);
	fwrite(color, sizeof(RGBQUAD), 256, fp3);
	fwrite(buf4, LineByte*h, 1, fp3);
	fclose(fp3);

	return 0;
}

int conv(BYTE* data, int kind, int i, int j)
{
	if (kind == 1) {
		return data[i*LineByte + j] + data[i*LineByte + j - 1] + data[i*LineByte + j + 1] +
			data[(i - 1)*LineByte + j] + data[(i - 1)*LineByte + j - 1] + data[(i - 1)*LineByte + j + 1]
			+ data[(i + 1)*LineByte + j] + data[(i + 1)*LineByte + j - 1] + data[(i + 1)*LineByte + j + 1];
		
	}
	else if (kind == 2) {
		return -8*data[i*LineByte + j] + data[i*LineByte + j - 1] + data[i*LineByte + j + 1] +
			data[(i - 1)*LineByte + j] + data[(i - 1)*LineByte + j - 1] + data[(i - 1)*LineByte + j + 1]
			+ data[(i + 1)*LineByte + j] + data[(i + 1)*LineByte + j - 1] + data[(i + 1)*LineByte + j + 1];

	}
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