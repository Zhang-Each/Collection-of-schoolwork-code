#include<iostream>
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


void PrinfBMP(BMPFILEHEADER *,BMPINFOHEADER *);

int main()
{
	int i, j, y, u, v;
	int LineByte1, LineByte2;
	BYTE *pbmpbuf1, *pbmpbuf2;
	FILE *fp1, *fp2, *fp3;
	//head1 and info1 is input
	//head2 and info2 is output
	BMPFILEHEADER head1, head2;
	BMPINFOHEADER info1, info2;
	RGBQUAD colortable[256];
	WORD fileType;
	long h, w;//the height and width of the bmp

	if ((fp1 = fopen("img.bmp", "rb")) == NULL) {
		cout << "Fail to read the input map!" << endl;
		return 0;
	}

	fseek(fp1, 0L, SEEK_SET);
	fread(&head1, sizeof(BMPFILEHEADER), 1, fp1);
	fread(&info1, sizeof(BMPINFOHEADER), 1, fp1);

	PrinfBMP(&head1, &info1);

	h = info1.biHeight;
	w = info1.biWidth;
	LineByte1 = (w*info1.biBitCount / 8 + 3) / 4 * 4;
	pbmpbuf1 = new BYTE[LineByte1*h];
	fseek(fp1, head1.bfOffset, SEEK_SET);
	fread(pbmpbuf1, LineByte1*h, 1, fp1);
	fclose(fp1);

	if ((fp2 = fopen("img2.bmp", "wb")) == NULL) {
		cout << "Fail to read the input map!" << endl;
		return 0;
	}

	LineByte2 = (w * 8 / 8 + 3) / 4 * 4;
	head2.bfType = 0X4D42;
	head2.bfSize = 14 + 40 + 256 * sizeof(RGBQUAD) + LineByte2 * h;
	head2.bfReserved1 = 0;
	head2.bfReserved2 = 0;
	head2.bfOffset = 14 + 40 + 256 * sizeof(RGBQUAD);
	//write in fileheader
	fwrite(&head2, 14, 1, fp2);

	info2 = info1;
	info2.biBitCount = 8;
	info2.biSizeImage = LineByte2 * h;
	//write in infoheader
	fwrite(&info2, 40, 1, fp2);

	for (i = 0; i < 256; i++) {
		colortable[i].rgbBlue = i;
		colortable[i].rgbRed = i;
		colortable[i].rgbGreen = i;
		colortable[i].rgbReserved = 0;
	}
	//write in RGBtable
	fwrite(colortable, sizeof(RGBQUAD), 256, fp2);
	pbmpbuf2 = new BYTE[LineByte2*h];
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			y = pbmpbuf1[i*LineByte1 + j * 3] * 0.299 + pbmpbuf1[i*LineByte1 + j * 3 + 1] * 0.587 + pbmpbuf1[i*LineByte1 + j * 3 + 2] *0.114;
			if (y < 0) {
				y = 0;
			}
			else if (y > 255) {
				y = 255;
			}
			pbmpbuf2[i*LineByte2 + j] = y;

		}
	}
	fwrite(pbmpbuf2, LineByte2*h, 1, fp2);
	fclose(fp2);
	if ((fp3 = fopen("img3.bmp", "wb")) == NULL) {
		cout << "Fail to read the input map!" << endl;
		return 0;
	}
	fwrite(&head1, 14, 1, fp3);
	fwrite(&info1, 40, 1, fp3);
	fwrite(pbmpbuf1, LineByte1*h, 1, fp3);
	fclose(fp3);

	return 0;
}

void PrinfBMP(BMPFILEHEADER *fileheader, BMPINFOHEADER *infoheader)
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