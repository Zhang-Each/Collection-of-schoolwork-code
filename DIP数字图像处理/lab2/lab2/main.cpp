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


void PrintBMP(BMPFILEHEADER *, BMPINFOHEADER *);
int getThreshold(BYTE* data, int h, int w, int linebyte);
int deilation(int i, int j, int linebyte, int threhold, BYTE* data);
int erosion(int i, int j, int linebyte, int threhold, BYTE* data);
int main()
{
	//1 input file and 5 output files
	FILE *fp1, *fp2, *fp3, *fp4, *fp5, *fp6;
	BYTE *buf1, *buf2, *buf3, *buf4, *buf5, *buf6;
	BMPFILEHEADER head;
	BMPINFOHEADER info;
	RGBQUAD color[256];
	int i, j, LineByte, threshold = 0;
	long w, h;//height and width


	//read the input file
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

	//get the binary image
	if ((fp2 = fopen("img2.bmp", "wb")) == NULL) {
		cout << "Fail to open the img2!" << endl;
		return 0;
	}
	fwrite(&head, 14, 1, fp2);
	fwrite(&info, 40, 1, fp2);
	fwrite(color, sizeof(RGBQUAD), 256, fp2);
	threshold = getThreshold(buf1, h, w, LineByte);

	buf2 = new BYTE[LineByte*h];
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			if (buf1[i*LineByte + j] < threshold)
				buf2[i*LineByte + j] = 0;
			else
				buf2[i*LineByte + j] = 255;
		}
	}
	fwrite(buf2, LineByte*h, 1, fp2);
	fclose(fp2);

	//binary image deilation
	fp3 = fopen("img3.bmp", "wb");
	buf3 = new BYTE[LineByte*h];
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			if (buf3[LineByte*i + j] < threshold)
				buf3[LineByte*i + j] = 0;
			else
				buf3[LineByte*i + j] = 255;
		}
	}

	for (i = 1; i < h - 1; i++) {
		for (j = 1; j < w - 1; j++) {
			if (deilation(i, j, LineByte, threshold, buf1) == 1) {
				buf3[i*LineByte + j] = 0;
			}
		}
	}
	fwrite(&head, 14, 1, fp3);
	fwrite(&info, 40, 1, fp3);
	fwrite(color, sizeof(RGBQUAD), 256, fp3);
	fwrite(buf3, LineByte*h,1, fp3);
	fclose(fp3);

	//binary image erosion
	fp4 = fopen("img4.bmp", "wb");
	buf4 = new BYTE[LineByte*h];
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			buf4[i*LineByte + j] = 255;
		}
	}

	for (i = 1; i < h - 1; i++) {
		for (j = 1; j < w - 1; j++) {
			if (erosion(i, j, LineByte, threshold, buf1) == 1) {
				buf4[i*LineByte + j] = 0;
			}
		}
	}

	fwrite(&head, 14, 1, fp4);
	fwrite(&info, 40, 1, fp4);
	fwrite(color, sizeof(RGBQUAD), 256, fp4);
	fwrite(buf4, LineByte*h, 1, fp4);
	fclose(fp4);

	//binary image closing
	fp5 = fopen("img5.bmp", "wb");
	buf5 = new BYTE[LineByte*h];
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			buf5[i*LineByte + j] = 255;
		}
	}

	for (i = 1; i < h - 1; i++) {
		for (j = 1; j < w - 1; j++) {
			if (erosion(i, j, LineByte, threshold, buf3) == 1) {
				buf5[LineByte*i + j] = 0;
			}
		}
	}
	fwrite(&head, 14, 1, fp5);
	fwrite(&info, 40, 1, fp5);
	fwrite(color, sizeof(RGBQUAD), 256, fp5);
	fwrite(buf5, LineByte*h, 1, fp5);
	fclose(fp5);

	//binary image opening
	fp6 = fopen("img6.bmp", "wb");
	buf6 = new BYTE[LineByte*h];
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			buf6[i*LineByte + j] = buf4[i*LineByte + j];
		}
	}

	for (i = 1; i < h - 1; i++) {
		for (j = 1; j < w - 1; j++) {
			if (deilation(i, j, LineByte, threshold, buf4) == 1) {
				buf6[i*LineByte + j] = 0;
			}
		}
	}
	fwrite(&head, 14, 1, fp6);
	fwrite(&info, 40, 1, fp6);
	fwrite(color, sizeof(RGBQUAD), 256, fp6);
	fwrite(buf6, LineByte*h, 1, fp6);
	fclose(fp6);

	return 0;
	

}

int getThreshold(BYTE* data, int h, int w, int linebyte)
{
	int result = 0, i, j, pix;
	int count[256];
	double pixelpro[256];
	double wback, wbacktmp, wbsum, wfor, wfortmp, wfsum, ave, var, varmax = 0;
	pix = h * w;
	for (i = 0; i < 256; i++) {
		count[i] = 0;
		pixelpro[i] = 0;
	}
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			count[data[i*linebyte + j]]++;
		}
	}

	for (i = 0; i < 256; i++) {
		pixelpro[i] = count[i] / (double)pix;
	}

	for (i = 0; i < 256; i++) {
		wback = 0;
		wbacktmp = 0;
		wfor = 0;
		wfortmp = 0;
		for (j = 0; j < 256; j++) {
			if (j <= i) {
				wback += pixelpro[j];
				wbacktmp += j * pixelpro[j];
			}
			else {
				wfor += pixelpro[j];
				wfortmp += j * pixelpro[j];
			}
		}

		wbsum = wbacktmp / wback;
		wfsum = wfortmp / wfor;
		ave = wbacktmp + wfortmp;
		var = wback * (wbsum - ave)*(wbsum - ave) + wfor * (wfsum - ave)*(wfsum - ave);
		if (var >= varmax) {
			varmax = var;
			result = i;
		}
	}

	return result;
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

int deilation(int i, int j, int linebyte, int threhold, BYTE* data)
{
	if (data[i*linebyte + j] < threhold || data[(i + 1)*linebyte + j] < threhold 
		|| data[(i - 1)*linebyte + j] < threhold || data[i*linebyte + j - 1] < threhold || data[i*linebyte + j + 1] < threhold) {
		return 1;
	}
	return 0;
}

int erosion(int i, int j, int linebyte, int threhold, BYTE* data)
{
	if (data[i*linebyte + j] < threhold && data[(i + 1)*linebyte + j] < threhold
		&& data[(i - 1)*linebyte + j] < threhold && data[i*linebyte + j - 1] < threhold && data[i*linebyte + j + 1] < threhold) {
		return 1;
	}
	return 0;
}