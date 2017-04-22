#include<opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

void negativo(char* entrada, char* saida);
void limiarizacao(char* entrada, char* saida, int limiar);

int main(int argc, char** argv) {

	if (argc < 3) {
		cout << "A entrada precisar ter o segunte formato: ./processador <metodo> imagem_entrada imagem_saida\n";
		return -1;
	}
	string metodo = argv[1];

	if (metodo == "negativo") {
		negativo(argv[2], argv[3]);
	} else if (metodo == "limiarizacao") {
		int limiar = stoi(argv[4]);
		limiarizacao(argv[2], argv[3], limiar);
	}
	return 1;
}

void negativo(char* entrada, char* saida) {

	IplImage* img = cvLoadImage(entrada);

	cout << "Executando o negativo ... \n";
	if (!img) {
		cout << "Imagem de entrada não localizada\n";
		return;
	}

	//Imagem pra guardar o resultado da operação
	IplImage* out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);


	/* NEGATIVO */
	for (int y = 0; y < img->height; y++) {
		uchar* ptr_img = (uchar*)(img->imageData + y * img->widthStep);
		uchar* ptr_out = (uchar*)(out->imageData + y * out->widthStep);

		for (int x = 0; x < img->width; x++) {
			uchar r = ptr_img[3 * x + 2];
			uchar g = ptr_img[3 * x + 1];
			uchar b = ptr_img[3 * x];
			ptr_out[3 * x] = 255 - 1 - b;
			ptr_out[3 * x + 1] = 255 - 1 - g;
			ptr_out[3 * x + 2] = 255 - 1 - r;
		}
	}
	
	cvSaveImage(saida, out);
}

void limiarizacao(char* entrada, char* saida, int limiar) {
	IplImage* img = cvLoadImage(entrada);

	cout << "Executando o limiar ... \n";
	if (!img) {
		cout << "Imagem de entrada não localizada\n";
		return;
	}

	if (limiar > 255 || limiar < 0) {
		cout << "Seu limiar esta fora da faixa 0 <= limiar <+ 255 \n";
		return;
	}

	//Imagem pra guardar o resultado da operação
	IplImage* out = cvCreateImage(
		cvGetSize(img), IPL_DEPTH_8U, 3);
	
	for (int y = 0; y<img->height; y++) {
		uchar* ptr_img = (uchar*)(
			img->imageData + y * img->widthStep);
		uchar* ptr_out = (uchar*)(
			out->imageData + y * out->widthStep);

		for (int x = 0; x<img->width; x++) {
			uchar cor = (ptr_img[3 * x] + ptr_img[3 * x + 1] + ptr_img[3 * x + 2]) / 3;
			if (cor > limiar)
			{

				ptr_out[3 * x] = 255;
				ptr_out[3 * x + 1] = 255;
				ptr_out[3 * x + 2] = 255;
			}
			else {
				ptr_out[3 * x] = 0;
				ptr_out[3 * x + 1] = 0;
				ptr_out[3 * x + 2] = 0;
			}
		}
	}
	cvSaveImage(saida, out);
}
